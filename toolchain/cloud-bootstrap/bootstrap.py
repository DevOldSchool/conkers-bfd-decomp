#!/usr/bin/env python3
"""Restore the Conker toolchain adapter outside the checkout. Never handles ROMs."""
import argparse, hashlib, json, os, pathlib, platform, shutil, subprocess, sys
HOME=pathlib.Path(__file__).resolve().parent
IMAGE='ghcr.io/devoldschool/conkers-bfd-decomp-toolchain@sha256:b3e29a92f2c26f11a58fbafde2d5d3b1184416e21b635e07b2a6303591ed5c8b'
REV='156f78f6bccfc07498578ac491ce7fe2a1e807a6'
CMAKE_HASH='2f766bb46367e5e0559fa33184653754bce044583a06014dcaebf8e6dff8a1f1'
DOCKERFILE_HASH='b161bd2fdb84561aa0480fe553e1806420ba7f3caf648dffa0331b42b426713c'

def run(args,**kwargs): subprocess.run([str(x) for x in args],check=True,**kwargs)
def sha(p): return hashlib.sha256(pathlib.Path(p).read_bytes()).hexdigest()
def validate_runtime_location(roots):
 for repo in roots:
  if HOME == repo or repo in HOME.parents or HOME in repo.parents:
   raise RuntimeError('Copy bootstrap to a runtime directory outside all checkout roots')

def main():
 p=argparse.ArgumentParser(description=__doc__)
 p.add_argument('checkouts',nargs='+',type=pathlib.Path,help='Explicit allowed Conker checkout roots; first is used for doctor')
 p.add_argument('--rebuild-armips',action='store_true',help='Build the pinned assembler rather than reuse the supplied verified binary')
 a=p.parse_args()
 if platform.system()!='Linux' or platform.machine() not in ('x86_64','amd64'): raise RuntimeError('Requires a Linux x86-64 executor')
 for binary in ('bwrap','unshare'):
  if not shutil.which(binary): raise RuntimeError('Missing required host tool: '+binary)
 roots=[x.resolve(strict=True) for x in a.checkouts]
 validate_runtime_location(roots)
 for repo in roots:
  lock=json.loads((repo/'toolchain/tools.lock.json').read_text())
  if lock['container_image']['repository']+'@'+lock['container_image']['digest']!=IMAGE: raise RuntimeError('Checkout CPU image pin differs; review adapter before proceeding')
  if lock['tools']['armips']['revision']!=REV: raise RuntimeError('Checkout armips pin differs')
  if sha(repo/'toolchain/rsp.Dockerfile')!=DOCKERFILE_HASH: raise RuntimeError('Checkout RSP recipe differs')
 for d in ('state','oci','rootfs','armips/install'): (HOME/d).mkdir(parents=True,exist_ok=True)
 (HOME/'state/allowed-workspaces.json').write_text(json.dumps([str(x) for x in roots],indent=2)+'\n')
 run([sys.executable,HOME/'pull_oci.py'])
 receipt=json.loads((HOME/'provenance/armips.json').read_text()) if (HOME/'provenance/armips.json').exists() else json.loads((HOME/'state/armips.json').read_text())
 binary=HOME/'armips/install/armips'
 if not a.rebuild_armips and binary.exists():
  if sha(binary)!=receipt['sha256']: raise RuntimeError('Supplied armips binary hash differs from receipt')
 else:
  source=HOME/'armips/source'; build=HOME/'armips/build'; cmake=HOME/'cmake-package'
  if not source.exists(): run(['git','clone','--filter=blob:none','--no-checkout','https://github.com/Kingcom/armips.git',source])
  run(['git','-C',source,'checkout','--detach',REV]); run(['git','-C',source,'submodule','update','--init','--recursive'])
  actual=subprocess.check_output(['git','-C',str(source),'rev-parse','HEAD'],text=True).strip()
  if actual!=REV: raise RuntimeError('armips revision mismatch')
  requirement=HOME/'cmake-requirements.txt'
  requirement.write_text('cmake==3.31.10 --hash=sha256:'+CMAKE_HASH+'\n')
  if not (cmake/'cmake/data/bin/cmake').exists():
   run([sys.executable,'-m','pip','install','--target',cmake,'--no-deps','--only-binary=:all:','--require-hashes','-r',requirement])
  build.mkdir(exist_ok=True)
  args=['unshare','--user','--map-current-user','--net','bwrap','--unshare-user','--unshare-pid','--unshare-ipc','--unshare-uts','--unshare-cgroup','--die-with-parent','--new-session','--cap-drop','ALL','--disable-userns','--ro-bind',HOME/'rootfs','/','--proc','/proc','--dev','/dev','--size','1073741824','--tmpfs','/tmp','--ro-bind',source,'/tmp/armips-src','--bind',build,'/tmp/armips-build','--bind',HOME/'armips/install','/tmp/armips-install','--ro-bind',cmake/'cmake/data','/tmp/cmake','--clearenv','--setenv','HOME','/tmp','--setenv','PATH','/tmp/cmake/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin','--chdir','/tmp/armips-src','/bin/sh','-c','cmake -S /tmp/armips-src -B /tmp/armips-build -DCMAKE_BUILD_TYPE=Release "-DCMAKE_CXX_FLAGS=-include limits" && cmake --build /tmp/armips-build --parallel 4 && cp /tmp/armips-build/armips /tmp/armips-install/armips && cp /tmp/armips-src/LICENSE.txt /tmp/armips-install/LICENSE.txt']
  import resource
  def limit():
   hard=resource.getrlimit(resource.RLIMIT_NPROC)[1]
   value=512 if hard==resource.RLIM_INFINITY else min(hard,512)
   resource.setrlimit(resource.RLIMIT_NPROC,(value,value))
  run(args,preexec_fn=limit)
  receipt['sha256']=sha(binary)
  (HOME/'armips/install/revision').write_text(REV+'\n')
 if (HOME/'armips/install/revision').read_text().strip()!=REV: raise RuntimeError('armips revision marker differs')
 (HOME/'state/armips.json').write_text(json.dumps(receipt,indent=2)+'\n')
 # An empty mountpoint is the only addition to the extracted CPU rootfs;
 # the independently built RSP extension is bound read-only at execution.
 (HOME/'rootfs/opt/armips').mkdir(exist_ok=True)
 env=dict(os.environ,PATH=str(HOME/'bin')+os.pathsep+os.environ['PATH'])
 run([roots[0]/'conker','doctor'],cwd=roots[0],env=env)
 print('\nReady. For this shell use:\nexport PATH='+str(HOME/'bin')+':"$PATH"')
 print('No ROM input was read or copied. Restore the owned ROM separately via ./conker setup.')
if __name__=='__main__':
 try: main()
 except (RuntimeError,subprocess.CalledProcessError) as e: sys.exit(str(e))
