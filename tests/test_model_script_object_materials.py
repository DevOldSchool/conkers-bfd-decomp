import hashlib
import struct
import unittest
from unittest.mock import patch
from scripts import model_script_object_materials as s


def fixture():
    raw=bytearray(1600);struct.pack_into('>II',raw,0,0x128,8);struct.pack_into('>4H',raw,0x128,9,9,9,0)
    struct.pack_into('>II',raw,36*8,0x5D8,0x80000068);raw[0x5F8:0x600]=s.COMMAND
    return bytes(raw)


class ScriptObjectMaterialTests(unittest.TestCase):
    def test_exact_structural_consumer(self):
        raw=fixture()
        with patch.object(s,'SCRIPT_SHA256',hashlib.sha256(raw).hexdigest()):
            proof=s.checked_script(raw)
        self.assertEqual([6,1,8],proof['asset_path']);self.assertEqual(13,proof['selector'])
        self.assertEqual([0x5D8,0x640],proof['stream_span'])
        self.assertIn('activation unobserved',proof['scope'])

    def test_authentication_covers_entire_script(self):
        raw=fixture()
        with patch.object(s,'SCRIPT_SHA256',hashlib.sha256(raw).hexdigest()):
            for offset in (0,100,0x128,0x1C0,36*8,0x5D8,0x5FD,1599):
                changed=bytearray(raw);changed[offset]^=1
                with self.assertRaisesRegex(ValueError,'source changed'):s.checked_script(bytes(changed))
            with self.assertRaises(ValueError):s.checked_script(raw[:-1])

    def test_structure_guard_independent_of_source_hash(self):
        raw=fixture()
        for offset in (0,0x128,36*8,0x1C0,0x5FC,0x5FD,0x5FE):
            changed=bytearray(raw);changed[offset]^=1;changed=bytes(changed)
            with patch.object(s,'SCRIPT_SHA256',hashlib.sha256(changed).hexdigest()),self.assertRaises(ValueError):s.checked_script(changed)

    def test_unverified_rom_not_admitted(self):
        with self.assertRaisesRegex(ValueError,'guarded US ROM'):s.material_context(bytes(128),{},None)

    def test_no_general_selector_or_activation_admission(self):
        self.assertEqual('050c005f0e0d0006',s.COMMAND.hex())
        for selector in (0,12,14,162,233,255):
            raw=bytearray(fixture());raw[0x5FD]=selector;raw=bytes(raw)
            with patch.object(s,'SCRIPT_SHA256',hashlib.sha256(raw).hexdigest()),self.assertRaises(ValueError):s.checked_script(raw)
