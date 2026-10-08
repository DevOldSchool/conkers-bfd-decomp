#!/usr/bin/env python3
"""Fetch and verify the reviewed public OCI image, without persistent credentials."""
import argparse, concurrent.futures, hashlib, json, os, pathlib, shutil, stat, tarfile, urllib.request
REPO='devoldschool/conkers-bfd-decomp-toolchain'
DIGEST='sha256:8da82ea0fc3ea2ca84987f521040732a7bc8b0e9595469a5363b90d3f306ae11'
BASE='https://ghcr.io/v2/'+REPO
HOME=pathlib.Path(__file__).resolve().parent
CACHE=HOME/'oci'; ROOT=HOME/'rootfs'

def digest(path):
 h=hashlib.sha256()
 with open(path,'rb') as f:
  for chunk in iter(lambda:f.read(1024*1024),b''): h.update(chunk)
 return 'sha256:'+h.hexdigest()

def fetch(url, token=None):
 headers={'Accept':'application/vnd.oci.image.index.v1+json, application/vnd.oci.image.manifest.v1+json, application/vnd.docker.distribution.manifest.list.v2+json, application/vnd.docker.distribution.manifest.v2+json'}
 if token: headers['Authorization']='Bearer '+token
 return urllib.request.urlopen(urllib.request.Request(url,headers=headers),timeout=180)

def get_blob(ref, kind, token):
 p=CACHE/ref.replace(':','_')
 if p.exists() and digest(p)==ref: return p
 print('Fetching',kind,ref,flush=True)
 with fetch(BASE+'/'+kind+'/'+ref,token) as r,open(str(p)+'.part','wb') as f: shutil.copyfileobj(r,f,1024*1024)
 if digest(str(p)+'.part')!=ref: raise RuntimeError('OCI digest mismatch: '+ref)
 os.replace(str(p)+'.part',p)
 return p

def path_inside(name):
 # Resolve symlinks with container-root semantics, never with host-root semantics.
 parts=list(pathlib.PurePosixPath(name).parts); out=[]; hops=0
 while parts:
  part=parts.pop(0)
  if part in ('/','.',''): continue
  if part=='..':
   if not out: raise ValueError('Archive path escapes root: '+name)
   out.pop(); continue
  p=ROOT.joinpath(*out,part)
  if p.is_symlink():
   hops+=1
   if hops>40: raise ValueError('Symlink loop: '+name)
   target=os.readlink(p)
   if target.startswith('/'): out=[]
   parts=list(pathlib.PurePosixPath(target).parts)+parts
  else: out.append(part)
 return ROOT.joinpath(*out)

def remove(p):
 if p.is_dir() and not p.is_symlink(): shutil.rmtree(p)
 elif p.exists() or p.is_symlink(): p.unlink()

def extract(layer):
 with tarfile.open(layer,'r:*') as tf:
  for m in tf:
   name=m.name.lstrip('./') if m.name.startswith('./') else m.name
   rel=pathlib.PurePosixPath(name)
   if rel.is_absolute() or '..' in rel.parts: raise ValueError('Invalid archive name '+name)
   parent=path_inside(str(rel.parent)); parent.mkdir(parents=True,exist_ok=True)
   p=parent/rel.name
   if rel.name=='.wh..wh..opq':
    for child in parent.iterdir(): remove(child)
    continue
   if rel.name.startswith('.wh.'):
    remove(parent/rel.name[4:]); continue
   if m.isdir():
    if p.is_symlink() or (p.exists() and not p.is_dir()): remove(p)
    p.mkdir(exist_ok=True); p.chmod(m.mode&0o1777|0o700)
   elif m.issym():
    remove(p); p.symlink_to(m.linkname)
   elif m.islnk():
    remove(p); os.link(path_inside(m.linkname),p)
   elif m.isfile():
    remove(p)
    with tf.extractfile(m) as src,open(p,'wb') as dest: shutil.copyfileobj(src,dest)
    p.chmod(m.mode&0o1777)
    os.utime(p,(m.mtime,m.mtime))
   elif m.ischr() or m.isblk() or m.isfifo():
    # A fresh minimal /dev is provided by bubblewrap, never host device nodes.
    continue
   else: raise ValueError('Unsupported OCI tar member '+m.name)

def main():
 CACHE.mkdir(exist_ok=True); ROOT.mkdir(exist_ok=True)
 # Public anonymous registry bearer token is kept in memory only.
 with fetch('https://ghcr.io/token?service=ghcr.io&scope=repository:'+REPO+':pull') as r: token=json.load(r)['token']
 index=get_blob(DIGEST,'manifests',token); manifest=json.loads(index.read_bytes()); platform_digest=DIGEST
 if 'manifests' in manifest:
  matches=[x for x in manifest['manifests'] if x.get('platform',{}).get('os')=='linux' and x.get('platform',{}).get('architecture')=='amd64']
  if len(matches)!=1: raise RuntimeError('Expected one linux/amd64 image')
  platform_digest=matches[0]['digest']; manifest=json.loads(get_blob(platform_digest,'manifests',token).read_bytes())
 config_path=get_blob(manifest['config']['digest'],'blobs',token)
 with concurrent.futures.ThreadPoolExecutor(max_workers=4) as pool:
  layers=list(pool.map(lambda x:get_blob(x['digest'],'blobs',token),manifest['layers']))
 receipt=HOME/'state'/'base-image.json'
 if not receipt.exists() or not any(ROOT.iterdir()):
  if any(ROOT.iterdir()): raise RuntimeError('Incomplete rootfs: inspect before removing and rerunning')
  for i,layer in enumerate(layers):
   print('Extracting layer',i+1,'of',len(layers),flush=True); extract(layer)
  record={'image':'ghcr.io/'+REPO+'@'+DIGEST,'platform_manifest':platform_digest,'config_digest':manifest['config']['digest'],'layers':[x['digest'] for x in manifest['layers']],'config':json.loads(config_path.read_bytes())}
  receipt.write_text(json.dumps(record,indent=2)+'\n')
 print('Verified base image ready:',ROOT,flush=True)
if __name__=='__main__': main()
