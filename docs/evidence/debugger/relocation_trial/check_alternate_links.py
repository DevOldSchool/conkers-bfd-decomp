from pathlib import Path
import json,subprocess,sys
sys.path.insert(0,'scripts')
from elf_sections import sections
r=Path('build/us/manual-attempts/debugger-completion/relocation')
rawscript=(r/'link-proof/raw.ld').read_text();canscript=(r/'link-proof/canonical.ld').read_text()
actual={'.text':0x16001AD0,'.rodata':0x16004800,'.data':0x16003C70}
placements=[{'.text':0x10000000,'.rodata':0x10010000,'.data':0x10008000},
            {'.text':0x18004000,'.rodata':0x40001000,'.data':0x30002000}]
proofs=[]
for number,bases in enumerate(placements):
    linked=[]
    for label,script,obj in [('raw',rawscript,'build/us/objdiff-report/debugger/1A0558/base.o'),('canonical',canscript,str(r/'canonical.o'))]:
        for name,value in bases.items():script=script.replace(f'{name} 0x{actual[name]:X}',f'{name} 0x{value:X}')
        ld=r/f'alternate-{number}-{label}.ld';ld.write_text(script);out=ld.with_suffix('.elf')
        subprocess.run(['mips-linux-gnu-ld','-m','elf32btsmip','-T',str(ld),'-o',str(out),obj],check=True)
        linked.append(sections(out.read_bytes(),2))
    for name in bases:assert linked[0][name][1]==linked[1][name][1],(number,name)
    proofs.append({'placements':bases,'all_code_and_data_identical':True})
(r/'alternate-link-proof.json').write_text(json.dumps(proofs,indent=2)+'\n');print(json.dumps(proofs,indent=2))
