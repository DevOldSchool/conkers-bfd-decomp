// Batch adapter for the pinned Khronos validator. No network resource loading.
const fs = require('node:fs');
const path = require('node:path');
const crypto = require('node:crypto');
const validator = require(path.resolve(process.argv[2]));
const requests = JSON.parse(fs.readFileSync(process.argv[3], 'utf8'));
(async () => {
  for (const request of requests) {
    let result;
    try {
      const allowed = new Set(Object.keys(request.fingerprint.dependencies_sha256));
      const hash = data => crypto.createHash('sha256').update(data).digest('hex');
      const checkInputs = () => {
        if (hash(fs.readFileSync(request.path)) !== request.fingerprint.gltf_sha256)
          throw new Error('glTF changed during validation');
        for (const uri of allowed) {
          const resource = path.resolve(path.dirname(request.path), decodeURIComponent(uri));
          if (hash(fs.readFileSync(resource)) !== request.fingerprint.dependencies_sha256[uri])
            throw new Error(`Resource changed during validation: ${uri}`);
        }
      };
      checkInputs();
      const report = await validator.validateString(fs.readFileSync(request.path, 'utf8'), {
        uri: path.basename(request.path), maxIssues: 1000,
        externalResourceFunction: async uri => {
          if (!allowed.has(uri)) throw new Error(`Unlisted resource: ${uri}`);
          return new Uint8Array(fs.readFileSync(path.resolve(path.dirname(request.path), decodeURIComponent(uri))));
        }
      });
      checkInputs();
      result = {status: report.issues.numErrors ? 'failed' : 'passed',
        validator_version: validator.version(), issues: report.issues};
    } catch (error) {
      result = {status: 'failed', error: String(error)};
    }
    fs.writeFileSync(request.output + '.tmp', JSON.stringify({key: request.key, result}));
    fs.renameSync(request.output + '.tmp', request.output);
  }
})().catch(error => { console.error(error); process.exitCode = 1; });
