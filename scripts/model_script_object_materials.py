"""One authenticated bank06 script consumer of ordinary bank09 model213.

Stored command reachability inside the dispatcher is proven. Gameplay script
activation, later callbacks, visibility, opacity and raster parity are not.
"""
from __future__ import annotations
import hashlib
import struct
try:
    from scripts.rzip_archive import AssetBank,parse_asset_banks,parse_asset_entries,decode_rzip_chunk
    from scripts import model_bank09_materials as ordinary
except ModuleNotFoundError:
    from rzip_archive import AssetBank,parse_asset_banks,parse_asset_entries,decode_rzip_chunk
    import model_bank09_materials as ordinary

CODE_SPANS=(
 (0x1501D1D4,132,'a956c60b89ac78dc93a1b0879259c2749cf59fec'),
 (0x1501D348,1892,'438ba4bb6e8349c0e0e649dadfad11df5e4c9d25'),
 (0x1502460C,8128,'363af55b580310f7cfa3dee99c50a0065274dffd'),
 (0x150265CC,13804,'32032af0b879068fc27718c536bcea6e5617b9a0'),
 (0x1502A8A0,592,'99742f426a0b5da3f225112ae76d1b83b0ee4c8b'),
 (0x1519EA78,276,'3b865718d1bfb76c6eca4af8366723c49b75b28c'),
)
SCRIPT_SHA256='964e3c6a56a067b613bc2ad7eff537c64ce0e1d938659079ea5bec773f939baf'
COMMAND=bytes.fromhex('050C005F0E0D0006')


def checked_script(data):
    if len(data)!=1600 or hashlib.sha256(data).hexdigest()!=SCRIPT_SHA256:
        raise ValueError('script object command source changed')
    if (data[:8]!=struct.pack('>II',0x128,8) or struct.unpack_from('>4H',data,0x128)!=(9,9,9,0)
            or data[36*8:37*8]!=struct.pack('>II',0x5D8,0x80000068)
            or data[0x1C0:0x1C8]!=bytes(8) or data[0x5F8:0x600]!=COMMAND):
        raise ValueError('script object stream/descriptor/command changed')
    if struct.unpack('b',data[0x5FD:0x5FE])[0]!=13:
        raise ValueError('script object selector changed')
    return {'asset_path':[6,1,8],'rom_span':['0x11867B8','0x1186A48'],
        'decoded_bytes':1600,'sha256':SCRIPT_SHA256,'header_counts':[9,9,9,0],
        'command_child':36,'stream_index':8,'stream_span':[0x5D8,0x640],
        'actor_descriptor_offset':0x1C0,'actor_descriptor_type':0,
        'command_offset':0x5F8,'command_hex':COMMAND.hex(),
        'selector':13,'selector_byte_offset':5,'selector_signed':True,
        'scope':'Authenticated stored command consumer; gameplay activation unobserved'}


def source_script(rom,layout):
    bank=next((b for b in parse_asset_banks(rom,layout['asset_table']) if b.index==6),None)
    if bank is None or bank.flags:raise ValueError('script object bank06 changed')
    scene=next((e for e in parse_asset_entries(rom,bank) if e.index==1),None)
    if scene is None or scene.type_flags:raise ValueError('script object scene directory changed')
    child=next((e for e in parse_asset_entries(rom,AssetBank(1,scene.start,scene.end,0)) if e.index==8),None)
    if child is None or (child.start,child.end,child.type_flags,child.compressed)!=(0x11867B8,0x1186A48,0x10,True):
        raise ValueError('script object indexed ROM path changed')
    decoded=decode_rzip_chunk(rom[child.start:child.end])
    if decoded.consumed!=child.end-child.start:raise ValueError('script object compressed boundary changed')
    return checked_script(decoded.data)


def material_context(rom,layout,game):
    if hashlib.sha1(rom).hexdigest()!='4cbadd3c4e0729dec46af64ad018050eada4f47a':
        raise ValueError('script object requires guarded US ROM')
    source=source_script(rom,layout);consumers=[]
    # Include the actual array helper, constructor and renderer, not just the
    # upstream command/wrapper. This helper can be audited independently.
    downstream={0x15152190,0x15132A4C,0x1513264C,0x15132B80}
    for address,size,sha1 in CODE_SPANS+tuple(r for r in ordinary.CONSUMERS if r[0] in downstream):
        raw=ordinary._slice(game.code,layout['game_vram'],address,size)
        if hashlib.sha1(raw).hexdigest()!=sha1:raise ValueError(f'script object consumer changed: {address:08X}')
        consumers.append({'function':f'func_{address:08X}','size':size,'sha1':sha1})
    switch=ordinary._slice(game.data,layout['game_data_vram'],0x80096C90,92)
    if hashlib.sha1(switch).hexdigest()!='415863408fe7f0180b4b95e777ed191e586377de' or struct.unpack_from('>I',switch,14*4)[0]!=0x15028D94:
        raise ValueError('script object operation95 switch changed')
    table=ordinary._slice(game.data,layout['game_data_vram'],ordinary.MODEL_TABLE,ordinary.MODEL_COUNT*4)
    if hashlib.sha1(table).hexdigest()!=ordinary.MODEL_TABLE_SHA1 or struct.unpack_from('>I',table,13*4)[0]!=213:
        raise ValueError('script object selector/model lookup changed')
    for kind in (25,72):
        if ordinary._slice(game.data,layout['game_data_vram'],0x8008B4A8+kind*52+8,16)!=struct.pack('>4I',0x15132B80,0x15132A88,0,0):
            raise ValueError('script object draw dispatch changed')
    proof={'source_script':source,'dispatcher':'func_1502A8A0','earlier_dispatcher':'func_1502460C',
        'earlier_result':'Returns zero for this command under both global-gate arms; no calls',
        'handler':'func_150265CC','operation':95,'subhandler':'0x15028D94',
        'wrapper':'func_1519EA78','wrapper_call_pc':'0x15028E0C','array_helper':'func_15152190',
        'array_helper_call_pc':'0x1519EB74','selector_array_count':1,'selector_array_stack_offset':0x30,
        'wrapper_flags_argument':0,'initial_flags':{'value':0x29E8},
        'model_selector':{'value':13,'store_pc':'0x15152488'},'model_table_address':'0x800A38B4',
        'call_pc':'0x151524D0','texture_callback':'disabled by initial flags bit16'}
    return {'consumers':consumers,'models':[{'bank':9,'entry':213,'segment':0,'constructors':[proof],
        'renderer':'func_15132B80','segment_8_bases':['0x80083740','0x800838C0'],
        'scope':'Stored bank06 command consumer, initial callback-disabled ordinary object draw only. Gameplay activation, later flag changes, visibility, opacity, colours and raster parity unproven.'}]}
