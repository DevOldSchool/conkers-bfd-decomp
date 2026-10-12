import sys,time,json,subprocess,statistics,platform
from pathlib import Path
root=Path('/workspace');sys.path.insert(0,str(root/'scripts'))
import permute,diff,compile_c
out=root/'build/us/manual-attempts/deferred-five-timings/benchmark';out.mkdir(exist_ok=True)
records=[]
for identifier in ['func_151D3354','func_15002754','func_1514401C']:
 entry,symbol=permute.work_item(identifier,'us');source,content=permute.active_candidate_content(entry,identifier)
 start,end=permute.candidate_function_span(content,identifier,symbol)
 t=time.perf_counter();variants=permute.source_variants(content[start:end],32);generation=time.perf_counter()-t
 asm=diff.ensure_reference_function('us',symbol,game_reference=True)
 reference=diff.reference_object('us',symbol,game_reference=True,assembly=asm)
 size=diff.expected_function_size('us',symbol);directory=out/identifier;directory.mkdir(exist_ok=True)
 diff.write_settings('us',source,directory=directory)
 candidate=directory/'candidate.c';obj=directory/'candidate.o';candidate.write_text(diff.GLOBAL_ASM_LINE.sub('',content))
 compile_cmd=compile_c.compile_command('us',candidate,obj);score_cmd=diff.asm_diff_command(obj,reference,symbol,size,require_match=True)
 samples=[]
 for i in range(5):
  t=time.perf_counter();subprocess.run(compile_cmd,cwd=root,check=True,stdout=subprocess.DEVNULL,stderr=subprocess.DEVNULL);compile_s=time.perf_counter()-t
  t=time.perf_counter();r=subprocess.run(score_cmd,cwd=directory,check=True,capture_output=True,text=True);score_s=time.perf_counter()-t
  samples.append(dict(compile_s=compile_s,score_s=score_s,score=diff.current_difference_count(r.stdout)))
 profile_cmd=[score_cmd[0],'-m','cProfile','-o',str(directory/'asm-diff.prof'),*score_cmd[1:]]
 subprocess.run(profile_cmd,cwd=directory,check=True,stdout=subprocess.DEVNULL)
 records.append(dict(identifier=identifier,size_bytes=size,generated=len(variants),generation_s=generation,samples=samples,compile_command=compile_cmd,score_command=score_cmd))
 print(identifier, 'compile median',statistics.median(x['compile_s'] for x in samples),'score median',statistics.median(x['score_s'] for x in samples),flush=True)
(out/'results.json').write_text(json.dumps(dict(python=sys.version,platform=platform.platform(),records=records),indent=2))
