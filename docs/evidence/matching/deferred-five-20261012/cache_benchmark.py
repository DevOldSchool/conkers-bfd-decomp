import argparse,os,time,json,subprocess,statistics
from pathlib import Path
parser=argparse.ArgumentParser(description='Compare scorer caching after running benchmark.py in the same checkout and toolchain.')
parser.add_argument('--root',type=Path,default=Path(__file__).resolve().parents[4],help='Repository root; defaults to the checkout containing this script.')
parser.add_argument('--output',type=Path,help='Directory containing benchmark.py results; relative paths are resolved under the repository root.')
args=parser.parse_args()
root=args.output or Path('build/us/manual-attempts/deferred-five-timings/benchmark')
if not root.is_absolute():root=args.root.resolve()/root
if not (root/'results.json').is_file():parser.error('Run benchmark.py first with the same --root and --output options to create results.json.')
data=json.loads((root/'results.json').read_text());results=[]
for row in data['records']:
 identifier=row['identifier'];env=dict(os.environ,PYTHONPYCACHEPREFIX=str(root/'pycache'));samples=[]
 for i in range(6):
  t=time.perf_counter();r=subprocess.run(row['score_command'],cwd=root/identifier,env=env,capture_output=True,text=True,check=True);elapsed=time.perf_counter()-t
  samples.append({'seconds':elapsed,'score':json.loads(r.stdout).get('current_score')})
 results.append({'identifier':identifier,'cache_fill_s':samples[0]['seconds'],'warm_samples':samples[1:]});print(identifier, 'cached scoring median',statistics.median(x['seconds'] for x in samples[1:]),flush=True)
(root/'cached-results.json').write_text(json.dumps(results,indent=2))
