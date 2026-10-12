"""Full native US consumer spans shared by the audio reconstruction codecs."""
import hashlib

AUDIO_LOADER = (0x8180, 856, '48d344a7a4e395907f0693a79c226514804a82e5')
SOUND_BANK = (AUDIO_LOADER,
              (0x128D0, 1200, '4aa9fcb168fff33dbb3fb5e0e2ac8fa0363d4c41'),
              (0x214F0, 2896, '4d737ccdfc2ab189bcb5306fb866b9091b446f80'))
SEQUENCE = (AUDIO_LOADER,
            (0x8CE8, 504, '21d68d0373511ef4017672422691890bf2badc9d'),
            (0x17F80, 3296, 'ad6237d34f7707388f7f55169c625d8d7b72ef79'))


def verify_spans(rom, spans, label):
    for start, size, digest in spans:
        if hashlib.sha1(rom[start:start + size]).hexdigest() != digest:
            raise ValueError(f'ROM {label} consumer changed at 0x{start:X}')
