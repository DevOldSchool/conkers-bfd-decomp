"""Fresh, EOF-bounded DEFLATE with the reviewed native 16K token buffer."""
from __future__ import annotations

import hashlib
import json
import os
from pathlib import Path
import platform
import shutil
import struct
import subprocess
import tempfile
import zlib

ROOT = Path(__file__).resolve().parent.parent
SOURCE = Path('scripts/vendor/bounded_deflate')
FILES = ('main.c', 'deflate.c', 'trees.c', 'bits.c', 'gzip.h', 'tailor.h', 'lzw.h', 'crypt.h')
FLAGS = ('-O2', '-std=gnu89', '-DSTDC_HEADERS=1', '-DHAVE_UNISTD_H=1',
         '-DLIT_BUFSIZE=16384', '-DDIST_BUFSIZE=16384')
ENCODER = {'format': 'rzip-bounded-deflate-v1', 'level': 6,
           'window_bits': -15, 'hash_bits': 15, 'token_buffer': 16384}


def source_hashes(root=ROOT):
    return {name: hashlib.sha256((root / SOURCE / name).read_bytes()).hexdigest() for name in FILES}


def executable(root=ROOT):
    """Cache a standalone executable by source, flags and host architecture."""
    before = source_hashes(root)
    identity = {'sources': before, 'flags': FLAGS, 'system': platform.system(), 'machine': platform.machine()}
    key = hashlib.sha256(json.dumps(identity, sort_keys=True).encode()).hexdigest()
    directory = root / 'build/tools/bounded-deflate' / key
    binary, receipt = directory / 'encoder', directory / 'encoder.json'
    if binary.is_file() and receipt.is_file():
        try:
            proof = json.loads(receipt.read_text())
            if (proof['identity'] == json.loads(json.dumps(identity))
                    and proof['sha256'] == hashlib.sha256(binary.read_bytes()).hexdigest()
                    and os.access(binary, os.X_OK)):
                return binary
        except (OSError, ValueError, KeyError, TypeError):
            pass
    compiler = shutil.which('cc')
    if compiler is None:
        raise ValueError('bounded DEFLATE requires a C compiler; run the build through ./conker')
    directory.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix='compile-', dir=directory) as temporary:
        output = Path(temporary) / 'encoder'
        command = [compiler, *FLAGS, '-o', str(output),
                   *(str(root / SOURCE / name) for name in FILES if name.endswith('.c'))]
        result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        if result.returncode:
            raise ValueError('bounded DEFLATE compiler failed: ' + result.stderr[-3000:])
        if source_hashes(root) != before:
            raise ValueError('bounded DEFLATE sources changed during compilation')
        digest = hashlib.sha256(output.read_bytes()).hexdigest()
        record = Path(temporary) / 'encoder.json'
        record.write_text(json.dumps({'identity': identity, 'sha256': digest}, indent=2) + '\n')
        os.replace(output, binary)
        os.replace(record, receipt)
    return binary


def encode_payload(payload, level=6):
    if type(level) is not int or level != 6:
        raise ValueError('unsupported reviewed bounded DEFLATE level')
    if not isinstance(payload, bytes) or len(payload) > 0xffffffff:
        raise ValueError('bounded DEFLATE requires a native-sized byte payload')
    result = subprocess.run([str(executable()), str(level)], input=payload,
                            stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if result.returncode or result.stderr:
        raise ValueError('bounded DEFLATE encoder failed: ' + result.stderr.decode(errors='replace')[-1000:])
    try:
        decoder = zlib.decompressobj(-15)
        decoded = decoder.decompress(result.stdout) + decoder.flush()
    except zlib.error as error:
        raise ValueError('bounded DEFLATE failed independent decoding') from error
    if decoded != payload or not decoder.eof or decoder.unused_data or decoder.unconsumed_tail:
        raise ValueError('bounded DEFLATE did not exactly round-trip')
    return struct.pack('>I', len(payload)) + result.stdout
