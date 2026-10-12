from pathlib import Path
import json,sys
sys.path.insert(0,'scripts')
import objdiff_candidate as c
from link_copies import verify_linked_copies
r=Path('build/us/manual-attempts/debugger-completion/relocation')
raw=Path('build/us/objdiff-report/debugger/1A0558/base.o')
runtime=Path('build/us/original-assets/conker.us.elf').read_bytes()
bases=c.linked_section_bases(raw.read_bytes(),runtime)
proof=verify_linked_copies(raw,r/'canonical.o',runtime,bases,r/'link-proof')
(r/'link-proof.json').write_text(json.dumps(proof,indent=2)+'\n');print(json.dumps(proof,indent=2))
