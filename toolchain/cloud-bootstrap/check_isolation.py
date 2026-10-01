#!/usr/bin/env python3
"""Run inside a Conker adapter namespace; fail closed on isolation regressions."""
import errno, json, os, pathlib, resource, socket
status=dict(line.split(':',1) for line in pathlib.Path('/proc/self/status').read_text().splitlines() if ':' in line)
for key in ('CapInh','CapPrm','CapEff','CapBnd','CapAmb'):
 assert int(status[key].strip(),16)==0,(key,status[key])
assert status['NoNewPrivs'].strip()=='1'
assert os.getuid()!=0
assert resource.getrlimit(resource.RLIMIT_NPROC)==(512,512)
for path in ('/etc/os-release','/workspace/Makefile'):
 try: fd=os.open(path,os.O_WRONLY)
 except OSError as e: assert e.errno in (errno.EROFS,errno.EACCES),e
 else:
  os.close(fd); raise AssertionError('unexpected write permission: '+path)
p=pathlib.Path('/tmp/adapter-isolation-smoke'); p.write_text('temporary write permitted'); p.unlink()
interfaces=[line.split(':',1)[0].strip() for line in pathlib.Path('/proc/net/dev').read_text().splitlines()[2:]]
assert set(interfaces)<={'lo'},interfaces
try:
 with socket.socket() as s:
  s.settimeout(1); s.connect(('198.51.100.1',443))
except OSError as e: network_error=str(e)
else: raise AssertionError('unexpected external network connectivity')
mounts=[line for line in pathlib.Path('/proc/mounts').read_text().splitlines() if line.split()[1] in ('/','/tmp','/workspace','/workspace/Makefile')]
for line in mounts:
 fields=line.split(); options=fields[3].split(',')
 if fields[1] in ('/','/workspace/Makefile'): assert 'ro' in options,line
 if fields[1] in ('/tmp','/workspace'): assert 'nosuid' in options and 'nodev' in options,line
print(json.dumps({'result':'PASS','uid':os.getuid(),'gid':os.getgid(),'network_namespace':os.readlink('/proc/self/ns/net'),'interfaces':interfaces,'network_attempt':network_error,'capabilities':'all zero','NoNewPrivs':1,'RLIMIT_NPROC':[512,512],'mount_flags':{line.split()[1]:[x for x in line.split()[3].split(',') if x in ('ro','rw','nosuid','nodev') or x.startswith(('size=','uid=','gid='))] for line in mounts}},indent=2))
