import os,time,json,subprocess,statistics
from pathlib import Path
root=Path('/workspace/build/us/manual-attempts/deferred-five-timings/benchmark');data=json.loads((root/'results.json').read_text());results=[]
for row in data['records']:
 identifier=row['identifier'];env=dict(os.environ,PYTHONPYCACHEPREFIX=str(root/'pycache'));samples=[]
 for i in range(6):
  t=time.perf_counter();r=subprocess.run(row['score_command'],cwd=root/identifier,env=env,capture_output=True,text=True,check=True);elapsed=time.perf_counter()-t
  samples.append({'seconds':elapsed,'score':json.loads(r.stdout).get('current_score')})
 results.append({'identifier':identifier,'cache_fill_s':samples[0]['seconds'],'warm_samples':samples[1:]});print(identifier, 'cached scoring median',statistics.median(x['seconds'] for x in samples[1:]),flush=True)
(root/'cached-results.json').write_text(json.dumps(results,indent=2))
