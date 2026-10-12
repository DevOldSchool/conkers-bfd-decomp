"""Complete isolated canonicalization trial; never edits production artifacts."""
import builtins
import hashlib
import json
from pathlib import Path
import struct
import subprocess
import sys
from unittest.mock import patch
import objdiff_candidate as c

root=Path('build/us/manual-attempts/debugger-completion/relocation')
old=Path('build/us/manual-attempts/debugger-completion/annotation')
binary=Path('build/host-tools/objdiff-v3.8.1/objdiff-cli-macos-arm64')
rawpath=Path('build/us/objdiff-report/debugger/1A0558/base.o')
target=Path('build/us/objdiff-report/owned/debugger/1A0558/target.o')
runtimepath=Path('build/us/original-assets/conker.us.elf')
protected=[rawpath,target,runtimepath,Path('build/us/src/done/debugger/debugger_1AD0.o'),
           Path('build/us/objdiff-report/report.json'),Path('build/us/objdiff-report/validation.json'),binary]
hashes={str(p):hashlib.sha256(p.read_bytes()).hexdigest() for p in protected}
assert hashes[str(binary)]=='98f8275c27900c4fe2248fce3af37617658be49648fa7dbb5b376371f046dfdb'
raw=rawpath.read_bytes();bases=c.linked_section_bases(raw,runtimepath.read_bytes())
with patch.object(builtins,'open',side_effect=AssertionError('file access')), \
     patch.object(Path,'read_bytes',side_effect=AssertionError('file access')), \
     patch.object(subprocess,'run',side_effect=AssertionError('subprocess access')):
    canonical,proof=c.canonicalize(raw,bases)
    assert c.canonicalize(canonical,bases)[0]==canonical
(root/'canonical.o').write_bytes(canonical)


def native(label,data,reference=target):
    obj=root/(label+'.o');obj.write_bytes(data);out=root/(label+'-diff.json')
    subprocess.run([str(binary),'diff','-1',str(reference),'-2',str(obj),'-o',str(out)],check=True)
    doc=json.loads(out.read_text());sections={s['name']:s for s in doc['left']['sections']}
    return {'text':sections['.text'].get('match_percent'),
            'rodata':sections['.rodata'].get('match_percent'),
            'rodata_bytes':int(sections['.rodata']['size']),
            'relocations_matched':sum('kind' not in x for x in sections['.rodata'].get('reloc_diff',[]))}

results={'baseline':native('raw-control',raw),'canonical':native('canonical',canonical)}
assert results['canonical']=={'text':100.0,'rodata':100.0,'rodata_bytes':352,'relocations_matched':52}
for name in ('double','reorder','case_count','alignment'):
    mutant=(old/(name+'-unannotated.o')).read_bytes()
    converted,record=c.canonicalize(mutant,bases)
    assert c.canonicalize(converted,bases)[0]==converted
    c.verify_canonicalization(mutant,converted,bases)
    untouched=native(name+'-raw',mutant)
    result=native(name,converted)
    assert result['text']==untouched['text'],name
    assert result['rodata']<100 and result['rodata_bytes']==352,name
    results[name]=result
# The non-relocated constant must stay exposed after the new relocation step.
for side in ('a','b'):
    candidate=(old.parent/('anonymous-literal-'+side+'.o')).read_bytes()
    converted,record=c.canonicalize(candidate,{'.rodata':0x1000})
    (root/('literal-'+side+'.o')).write_bytes(converted)
results['literal']=native('literal-different',(root/'literal-b.o').read_bytes(),root/'literal-a.o')
assert results['literal']['rodata']<100 and results['literal']['text']==100
# Named/zero-addend input is already canonical; no extra pass can change its score.
assert native('idempotent',c.canonicalize(canonical,bases)[0])==results['canonical']
obj=c.Elf(canonical);ro=obj.names.index('.rodata');text=obj.names.index('.text');rel=obj.names.index('.rel.rodata')
negative={}
for name,offset,value in (
    ('code',obj.headers[text][4],obj.word(text,0)^1),
    ('literal',obj.headers[ro][4]+336,obj.word(ro,336)^1),
    ('table_addend',obj.headers[ro][4]+124,4),
    ('relocation_type',obj.headers[rel][4]+4,struct.unpack_from('>I',canonical,obj.headers[rel][4]+4)[0]^1),
    ('relocation_destination',obj.headers[rel][4]+4,struct.unpack_from('>I',canonical,obj.headers[rel][4]+12)[0]),
    ('section_size',obj.header[6]+40*ro+20,obj.headers[ro][5]-4)):
    modified=bytearray(canonical);struct.pack_into('>I',modified,offset,value)
    try:c.verify_canonicalization(raw,bytes(modified),bases)
    except c.AnnotationError as e:negative[name]=str(e)
    else:raise AssertionError('verifier accepted '+name)
# Invalid source inputs must fail rather than being repaired by canonicalization.
original=c.Elf(raw)
for name,offset,value in (
    ('wrong_bound',original.headers[text][4]+0x778,0x2de10033),
    ('interior_table',original.headers[text][4]+0x78c,0x8c2f0080),
    ('out_of_range',original.headers[ro][4]+124,0xfffffffc)):
    modified=bytearray(raw);struct.pack_into('>I',modified,offset,value)
    try:c.canonicalize(bytes(modified),bases)
    except c.AnnotationError as e:negative[name]=str(e)
    else:raise AssertionError('accepted '+name)
# No anonymous rodata references: exact no-op, not a generic relocation rewriter.
no_refs=bytearray(raw);reltext=original.names.index('.rel.text');h=original.headers[reltext]
entries=[raw[at:at+8] for at in range(h[4],h[4]+h[5],8)
         if original.symbols[struct.unpack_from('>I',raw,at+4)[0]>>8][0]!='.rodata']
no_refs[h[4]:h[4]+len(entries)*8]=b''.join(entries)
struct.pack_into('>I',no_refs,original.header[6]+40*reltext+20,len(entries)*8)
assert c.canonicalize(bytes(no_refs),bases)[0]==bytes(no_refs)
assert {str(p):hashlib.sha256(p.read_bytes()).hexdigest() for p in protected}==hashes
results.update(proof=proof,negative_tests=negative,independence=True,idempotence=True,no_op=True,
               protected_file_hashes=hashes)
(root/'results.json').write_text(json.dumps(results,indent=2)+'\n')
print(json.dumps({k:v for k,v in results.items() if k not in ('proof','protected_file_hashes')},indent=2))
