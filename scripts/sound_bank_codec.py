"""Typed B1 control and loader-referenced external sound-bank records."""
from __future__ import annotations
import struct

try:
    from scripts import audio_assets, audio_consumers
except ModuleNotFoundError:
    import audio_assets
    import audio_consumers

SCHEMAS = {
    'bank': ('>HBBII', ('instrument_count','flags','reserved_zero','sample_rate','percussion_offset')),
    'instrument': ('>12Bhh', ('volume','pan','priority','flags','tremolo_type','tremolo_rate','tremolo_depth','tremolo_delay','vibrato_type','vibrato_rate','vibrato_depth','vibrato_delay','bend_range','sound_count')),
    'sound': ('>IIIBBBB', ('envelope_pointer','key_map_pointer','wavetable_pointer','pan','volume','flags','reserved_zero')),
    'envelope': ('>iiiBBH', ('attack_time_us','decay_time_us','release_time_us','attack_volume','decay_volume','reserved_zero')),
    'key_map': ('>BBBBBb', ('velocity_min','velocity_max','key_min','key_max','key_base','detune')),
    'adpcm_wave': ('>IiBBHIII', ('sample_offset','stored_length','wave_type','flags','reserved_zero','loop_pointer','book_pointer','conker_field_0x14')),
    'book': ('>ii', ('order','predictor_count')),
    'adpcm_loop': ('>III', ('start_sample','end_sample','count')),
}
ARRAYS = {'bank': ('instrument_addresses','I','instrument_count'),
          'instrument': ('sound_addresses','I','sound_count'),
          'book': ('coefficients','h',None), 'adpcm_loop': ('state','h',None)}


def encode_record(record):
    if not isinstance(record,dict) or 'kind' not in record or 'offset' not in record:
        raise ValueError('invalid sound-bank record schema')
    if type(record['offset']) is not int or record['offset'] < 0:
        raise ValueError('invalid sound-bank record offset')
    kind=record['kind']
    if not isinstance(kind,str):raise ValueError('invalid sound-bank record kind')
    if kind=='zero_gap':
        if set(record)!={'kind','offset','size'} or type(record['size']) is not int or record['size'] not in (2,4,8):
            raise ValueError('unsupported sound-bank zero gap')
        return bytes(record['size'])
    if kind=='bank_file':
        if set(record)!={'kind','offset','revision','bank_offsets'} or record['revision']!=0x4231:
            raise ValueError('invalid bank-file schema')
        values=record['bank_offsets']
        if not isinstance(values,list) or not values or any(type(v) is not int for v in values):
            raise ValueError('invalid bank pointers')
        try:return struct.pack('>HH',record['revision'],len(values))+struct.pack(f'>{len(values)}I',*values)
        except struct.error as error:raise ValueError('invalid bank-file value') from error
    if kind not in SCHEMAS:
        raise ValueError('unsupported sound-bank record kind')
    fmt,fields=SCHEMAS[kind]
    required={'kind','offset',*fields}
    if kind in ARRAYS:required.add(ARRAYS[kind][0])
    if set(record)!=required or any(type(record[k]) is not int for k in fields):
        raise ValueError('invalid sound-bank native fields')
    if record.get('reserved_zero',0)!=0 or record.get('flags',0)!=0:
        raise ValueError('sound-bank reserved bytes or unpatched flags changed')
    if kind=='adpcm_wave' and (record['wave_type']!=0 or record['stored_length']<=0 or not record['book_pointer']):
        raise ValueError('unsupported ADPCM wave')
    if kind=='bank' and (record['sample_rate']<=0 or record['percussion_offset']):
        raise ValueError('unsupported bank header')
    if kind=='book' and (record['order']<=0 or record['predictor_count']<=0):
        raise ValueError('invalid predictor book dimensions')
    if kind=='adpcm_loop' and record['start_sample']>record['end_sample']:
        raise ValueError('invalid ADPCM loop bounds')
    try:
        result=struct.pack(fmt,*(record[k] for k in fields))
        if kind in ARRAYS:
            name,code,count_field=ARRAYS[kind];values=record[name]
            count=record[count_field] if count_field else 16 if kind=='adpcm_loop' else 8*record['order']*record['predictor_count']
            if not isinstance(values,list) or len(values)!=count or any(type(v) is not int for v in values):
                raise ValueError('sound-bank array count or values changed')
            result+=struct.pack(f'>{len(values)}{code}',*values)
    except struct.error as error:raise ValueError('invalid native sound-bank value') from error
    return result


def encode_region(region):
    if (not isinstance(region,dict) or set(region)!={'format','start','end','records'}
            or region['format']!='conker-b1-region' or type(region['start']) is not int
            or type(region['end']) is not int or not 0<=region['start']<region['end']
            or not isinstance(region['records'],list) or not region['records']):
        raise ValueError('invalid sound-bank region schema')
    cursor=region['start'];chunks=[]
    for record in region['records']:
        raw=encode_record(record)
        if record['offset']!=cursor:
            raise ValueError('sound-bank records overlap or leave an uncovered gap')
        chunks.append(raw);cursor+=len(raw)
    if cursor!=region['end']:raise ValueError('sound-bank records disagree with region extent')
    return b''.join(chunks)


def typed_regions(control,external,wavetable):
    graph=audio_assets.parse_sound_bank_graph(control,external,wavetable).manifest
    summary=audio_assets.parse_sound_bank_control(control)
    bank=summary.bank_offsets[0]
    control_records=[{'kind':'bank_file','offset':0,'revision':summary.revision,'bank_offsets':list(summary.bank_offsets)}]
    fields=struct.unpack_from(SCHEMAS['bank'][0],control,bank)
    control_records.append(dict(kind='bank',offset=bank,**dict(zip(SCHEMAS['bank'][1],fields)),instrument_addresses=list(struct.unpack_from(f'>{summary.instrument_count}I',control,bank+12))))
    external_records=[]
    for row in graph['instruments']:
        values={k:row[k] for k in ('volume','pan','priority','flags','bend_range','sound_count')}
        for name in ('tremolo','vibrato'):
            values.update({name+'_'+k:row[name][k] for k in ('type','rate','depth','delay')})
        values['sound_addresses']=[int(graph['sounds'][i]['pointer_value'],16) for i in row['sound_indices']]
        target=control_records if row['storage']=='control' else external_records
        target.append(dict(kind='instrument',offset=int(row['offset'],16),**values))
    for family,kind in [('sounds','sound'),('envelopes','envelope'),('key_maps','key_map'),('wavetables','adpcm_wave'),('adpcm_books','book'),('loops','adpcm_loop')]:
        for row in graph[family]:
            if family in ('wavetables','loops') and row['kind']!='adpcm':raise ValueError('only reviewed ADPCM records are supported')
            values={}
            for field in SCHEMAS[kind][1]:
                source={'reserved_zero':'padding','sample_offset':'base'}.get(field,field)
                value=0 if field=='wave_type' else row[source]
                values[field]=int(value,16) if isinstance(value,str) else value
            if kind in ARRAYS:
                name=ARRAYS[kind][0];values[name]=list(row[name])
            external_records.append(dict(kind=kind,offset=int(row['offset'],16),**values))

    def regions(records,raw,allow_unknown):
        parts=[];unknown=[];current=[];cursor=0;start=0
        for record in sorted(records,key=lambda r:r['offset']):
            offset=record['offset']
            if offset<cursor:raise ValueError('native sound-bank records overlap')
            if offset>cursor:
                gap=raw[cursor:offset]
                if len(gap) in (2,4,8) and not any(gap):
                    current.append({'kind':'zero_gap','offset':cursor,'size':len(gap)})
                elif allow_unknown:
                    if current:parts.append({'format':'conker-b1-region','start':start,'end':cursor,'records':current})
                    unknown.append((cursor,offset));current=[];start=offset
                else:raise ValueError('unexplained sound-bank control gap')
            encoded=encode_record(record)
            if encoded!=raw[offset:offset+len(encoded)]:raise ValueError('native record bytes disagree with independent source')
            current.append(record);cursor=offset+len(encoded)
        if cursor<len(raw):
            gap=raw[cursor:]
            if len(gap) in (2,4,8) and not any(gap):
                current.append({'kind':'zero_gap','offset':cursor,'size':len(gap)});cursor=len(raw)
            elif allow_unknown:unknown.append((cursor,len(raw)))
            else:raise ValueError('unexplained sound-bank suffix')
        if current:parts.append({'format':'conker-b1-region','start':start,'end':cursor,'records':current})
        for part in parts:
            if encode_region(part)!=raw[part['start']:part['end']]:raise ValueError('sound-bank region reconstruction differs')
        return parts,unknown
    control_parts,control_unknown=regions(control_records,control,False)
    external_parts,unknown=regions(external_records,external,True)
    return {'control':control_parts,'external':external_parts,'external_unknown_ranges':unknown}


def verify_consumers(rom):
    audio_consumers.verify_spans(rom, audio_consumers.SOUND_BANK, 'sound-bank')


def external_partition(asset, regions):
    rows = [(asset.rom_start + row['start'], asset.rom_start + row['end'],
             f"audio/bank17/sound-bank/regions/{row['start']:08X}") for row in regions['external']]
    rows.extend((asset.rom_start + start, asset.rom_start + end,
                 f'audio/bank17/sound-bank/unreconstructed/{start:08X}')
                for start, end in regions['external_unknown_ranges'])
    cursor = asset.rom_start
    for start, end, _ in sorted(rows):
        if start != cursor or not start < end <= asset.rom_end:
            raise ValueError('sound-bank partition overlaps or leaves unexplained storage')
        cursor = end
    if cursor != asset.rom_end:
        raise ValueError('sound-bank partition does not reach its original end')
    return sorted(rows)
