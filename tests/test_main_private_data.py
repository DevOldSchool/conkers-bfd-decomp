from pathlib import Path
import contextlib
import hashlib
import io
import json
import shutil
import struct
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "scripts"))
import main_private_data as private
from types import SimpleNamespace
ai = SimpleNamespace(SYMBOL="func_80002DB0", TEXT_VRAM=0x80002DB0, TEXT_ROM=0x2DB0,
                     TEXT_SIZE=160, DATA_VRAM=0x8002AB40, DATA_ROM=0x2AB40,
                     SECTION=".main_private_ai_data", FLAG_RELOCATIONS={12:5,16:6,56:5,64:6,68:5,72:6},
                     CALLS={76:"func_80023390",100:"func_800233C0"})
import linked_aliases
from candidate_tables import Object32


def elf(entries, *, kind=2):
    names = b"\0.shstrtab\0" + b"".join(e[0].encode() + b"\0" for e in entries)
    entries = [(".shstrtab", 3, 0, 0, names, 1, 0, 0, 0)] + entries
    body = bytearray(52)
    headers = [(0,) * 10]
    for name, type_, flags, address, payload, alignment, link, info, width in entries:
        body.extend(bytes(-len(body) % max(alignment, 1)))
        headers.append((names.index(name.encode() + b"\0"), type_, flags, address,
                        len(body), len(payload), link, info, alignment, width))
        body.extend(payload)
    body.extend(bytes(-len(body) % 4))
    offset = len(body)
    body.extend(b"".join(struct.pack(">10I", *h) for h in headers))
    body[:52] = struct.pack(">16sHHIIIIIHHHHHH", b"\x7fELF\x01\x02\x01" + bytes(9),
                            kind, 8, 1, 0, 0, offset, 0, 52, 0, 0, 40, len(headers), 1)
    return bytes(body)


def object_image(*, data=bytes(16), alignment=16, flags=3, addend=0, extra=False):
    strings = b"\0.data\0" + ai.SYMBOL.encode() + b"\0func_80023390\0func_800233C0\0"
    def symbol(name, value, size, info, section):
        return struct.pack(">IIIBBH", strings.index(name.encode() + b"\0"), value, size, info, 0, section)
    symbols = bytes(16) + symbol(".data", 0, len(data), 3, 3) + symbol(ai.SYMBOL, 0, 148, 0x12, 2)
    symbols += symbol("func_80023390", 0, 0, 0x12, 0) + symbol("func_800233C0", 0, 0, 0x12, 0)
    words = [0] * 40
    relocations = []
    for offset, kind in ai.FLAG_RELOCATIONS.items():
        relocations.append(struct.pack(">II", offset, 256 + kind))
    words[4] = addend
    for index, offset in enumerate(ai.CALLS):
        words[offset // 4] = 0x0C000000
        relocations.append(struct.pack(">II", offset, ((3 + index) << 8) | 4))
    if extra:
        relocations.append(struct.pack(">II", 0x14, 261))
    return elf([(".text", 1, 6, 0, struct.pack(">40I", *words), 16, 0, 0, 0),
                (".data", 1, flags, 0, data, alignment, 0, 0, 0),
                (".strtab", 3, 0, 0, strings, 1, 0, 0, 0),
                (".symtab", 2, 0, 0, symbols, 4, 4, 2, 16),
                (".rel.text", 9, 0, 0, b"".join(relocations), 4, 5, 2, 8)], kind=1)


def executable(*, flags=1, address=ai.DATA_VRAM, data=bytes(16), alignment=16,
               main_flags=7, main_address=ai.TEXT_VRAM, omit=False, extra=False):
    backing = bytes(ai.DATA_VRAM + 16 - ai.TEXT_VRAM)
    entries = [(".main", 1, main_flags, main_address, backing, 16, 0, 0, 0)]
    if not omit:
        entries.append((ai.SECTION, 1, flags, address, data, alignment, 0, 0, 0))
    if extra:
        entries.append((".main_private_unreviewed", 1, 1, address, bytes(16), 16, 0, 0, 0))
    return elf(entries)


SOURCE = "src/main/another_unit.c"


def manifest(root, data=bytes(16)):
    evidence = root / "docs/evidence/private.md"
    evidence.parent.mkdir(parents=True, exist_ok=True); evidence.write_text("Reviewed ownership fixture")
    unit = {"sources": [SOURCE, "src/done/main/another_unit.c"],
            "evidence_reference": "docs/evidence/private.md",
            "sections": [{"input": ".data", "output": ai.SECTION, "vram": hex(ai.DATA_VRAM),
                          "rom_offset": hex(ai.DATA_ROM), "size": 16, "alignment": 16, "flags": 3,
                          "sha256": hashlib.sha256(data).hexdigest()}]}
    path = root / private.MANIFEST; path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps({"schema_version": 1, "units": [unit]}))
    return unit


class PrivateDataTests(unittest.TestCase):
    def test_candidate_contract_uses_actual_section_and_nonzero_rom_bytes(self):
        data = bytes(range(16)); rom = bytes(ai.DATA_ROM) + data
        with tempfile.TemporaryDirectory() as temporary:
            unit = manifest(Path(temporary), data)
            obj = Object32(object_image(data=data))
            indices = private.candidate_sections(obj, unit, rom)
            self.assertEqual(indices, frozenset({3}))
            self.assertIsNone(linked_aliases.definitions(obj))
            self.assertEqual(linked_aliases.definitions(obj, private_sections=indices),
                             {"func_80023390": 0x80023390, "func_800233C0": 0x800233C0})
            for kwargs in [{"data": bytes(15)}, {"data": bytes(32)}, {"data": bytes(16)},
                           {"alignment": 8}, {"flags": 1}]:
                with self.subTest(kwargs=kwargs):
                    self.assertIsNone(private.candidate_sections(Object32(object_image(**kwargs)), unit, rom))
            with self.assertRaisesRegex(ValueError, "digest"):
                private.expected_data(unit["sections"][0], rom[:-1])

    def test_unmapped_allocated_storage_and_pointer_initializers_rejected(self):
        with tempfile.TemporaryDirectory() as temporary:
            unit = manifest(Path(temporary)); blob = object_image(); rom = bytes(ai.DATA_ROM + 16)
            headers = struct.unpack_from(">16sHHIIIIIHHHHHH", blob)
            # Make the string table allocated data: extra emitted storage must not be discarded.
            changed = bytearray(blob); struct.pack_into(">II", changed, headers[6] + 4*40 + 4, 1, 2)
            self.assertIsNone(private.candidate_sections(Object32(changed), unit, rom))
            # Relocations originating in initialized storage are unsupported.
            changed = bytearray(blob); struct.pack_into(">I", changed, headers[6] + 6*40 + 28, 3)
            self.assertIsNone(private.candidate_sections(Object32(changed), unit, rom))

    def test_manifest_fails_closed_on_unreviewed_ambiguous_or_invalid_mapping(self):
        mutations = [lambda u: u.update(evidence_reference="docs/evidence/missing.md"),
                     lambda u: u.update(sources=["../other.c"]),
                     lambda u: u["sources"].append(SOURCE),
                     lambda u: u["sections"][0].update(output=".main"),
                     lambda u: u["sections"][0].update(flags=True),
                     lambda u: u["sections"][0].update(vram="0x8002AB41"),
                     lambda u: u["sections"].append(dict(u["sections"][0]))]
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            for mutate in mutations:
                unit = manifest(root); mutate(unit)
                (root / private.MANIFEST).write_text(json.dumps({"schema_version":1,"units":[unit]}))
                with self.subTest(mutate=mutate), self.assertRaises(ValueError): private.mappings(root)
            manifest(root)
            self.assertIsNone(private.mapping(root, "src/main/unreviewed.c"))
            with self.assertRaisesRegex(ValueError, "both"):
                private.active_units(root, [SOURCE, "src/done/main/another_unit.c"])

    def test_linker_selects_exact_active_object_and_does_not_rewrite_unchanged_file(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary); manifest(root); output = root / "generated.ld"
            private.linker(root, output, [SOURCE]); stamp = output.stat().st_mtime_ns
            self.assertIn("build/us/src/main/another_unit.o(.data)", output.read_text())
            self.assertIn('(INFO)', output.read_text())
            private.linker(root, output, [SOURCE]); self.assertEqual(stamp, output.stat().st_mtime_ns)
            private.linker(root, output, []); self.assertNotIn(ai.SECTION, output.read_text())

    def verify(self, blob, *, rom=None, reviewed=True):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary); manifest(root)
            (root / "progress").mkdir()
            (root / "progress/source_units.json").write_text(json.dumps({"source_units":[{
                "source":SOURCE,"functions":[ai.SYMBOL],"boundary_evidence":{"us":{"reviewed":reviewed}},
                "regions":{"us":{"start":hex(ai.TEXT_ROM),"end":hex(ai.TEXT_ROM+160)}}}]}))
            (root / "progress/functions.json").write_text(json.dumps({"functions":[{
                "symbol":ai.SYMBOL,"overlay":"main","regions":{"us":{"vram":hex(ai.TEXT_VRAM)}}}]}))
            output = root / "linked.elf"; output.write_bytes(blob)
            with patch.object(private, "validated_rom", return_value=bytes(ai.DATA_ROM+16) if rom is None else rom), contextlib.redirect_stdout(io.StringIO()):
                private.verify(root, output, [SOURCE])

    def test_integration_checks_info_contract_ownership_entire_text_and_backing(self):
        self.verify(executable())
        for kwargs in [{"flags":3}, {"address":ai.DATA_VRAM+16}, {"data":b"\1"+bytes(15)},
                       {"data":bytes(32)}, {"alignment":8}, {"main_flags":1}, {"omit":True}, {"extra":True}]:
            with self.subTest(kwargs=kwargs), self.assertRaises(ValueError): self.verify(executable(**kwargs))
        with self.assertRaisesRegex(ValueError, "owner"): self.verify(executable(), reviewed=False)
        for offset in [ai.TEXT_ROM, ai.TEXT_ROM+159, ai.DATA_ROM, ai.DATA_ROM+15]:
            rom=bytearray(ai.DATA_ROM+16); rom[offset]=1
            with self.subTest(offset=offset), self.assertRaises(ValueError): self.verify(executable(),rom=bytes(rom))

    def test_malformed_elf_and_duplicate_section_rejected(self):
        valid = executable()
        for length in [0, 51, 52, len(valid)-1]:
            with self.subTest(length=length), self.assertRaises(ValueError): private.sections(valid[:length],2)
        h=struct.unpack_from(">16sHHIIIIIHHHHHH",valid); blob=bytearray(valid)
        blob[h[6]+3*40:h[6]+4*40]=blob[h[6]+2*40:h[6]+3*40]
        with self.assertRaisesRegex(ValueError,"duplicate"): private.sections(bytes(blob),2)

    def test_rom_checksum_and_size_required(self):
        with tempfile.TemporaryDirectory() as temporary:
            root=Path(temporary); (root/"config").mkdir(); (root/"roms").mkdir()
            (root/"roms/baserom.us.z64").write_bytes(b"wrong")
            for sha,size in [("0"*40,5),(hashlib.sha1(b"wrong").hexdigest(),6)]:
                (root/"config/roms.json").write_text(json.dumps({"profiles":{"us":{"sha1":sha,"size_bytes":size}}}))
                with patch.object(private.rzip_archive,"normalize_rom",return_value=(b"wrong",None)), self.assertRaisesRegex(ValueError,"checksum-validated"):
                    private.validated_rom(root)


@unittest.skipUnless(shutil.which("mips-linux-gnu-as") and shutil.which("mips-linux-gnu-ld"),
                     "requires pinned MIPS binutils")
class PrivateLinkedTests(unittest.TestCase):
    def assemble(self, root, name, *, raw=False, mutation=None, flag_addend=0, data=bytes(16)):
        flag = "D_8002AB40" if raw else "private_flag"
        if flag_addend:
            flag += "+" + str(flag_addend)
        rows = ["nop"] * 40
        accesses = {3: f"lui $t6,%hi({flag})", 4: f"lbu $t6,%lo({flag})($t6)",
                    14: f"lui $at,%hi({flag})", 16: f"sb $t0,%lo({flag})($at)",
                    17: f"lui $at,%hi({flag})", 18: f"sb $zero,%lo({flag})($at)",
                    19: "jal func_80023390", 25: "jal func_800233C0",
                    27: "lui $t1,%hi(D_A4500000)" if raw else "lui $t1,0xa450",
                    28: "sw $v0,%lo(D_A4500000)($t1)" if raw else "sw $v0,0($t1)",
                    30: "lui $t3,%hi(D_A4500004)" if raw else "lui $t3,0xa450",
                    32: "sw $t2,%lo(D_A4500004)($t3)" if raw else "sw $t2,4($t3)"}
        for index, row in accesses.items(): rows[index] = row
        if mutation: rows[mutation[0]] = mutation[1]
        source = root / (name + ".s")
        source.write_text(".text\n.set noreorder\n.set noat\n.globl " + ai.SYMBOL + "\n.type " + ai.SYMBOL + ",@function\n" + ai.SYMBOL + ":\n" + "\n".join(rows) + "\n.size " + ai.SYMBOL + (",160\n" if raw else ",148\n") +
                          ("" if raw else ".data\n.p2align 4\nprivate_flag:\n.byte " + ",".join(map(str, data)) + "\n"))
        output = source.with_suffix(".o")
        subprocess.run(["mips-linux-gnu-as", "-EB", "-mabi=32", "-march=vr4300", "-o", str(output), str(source)], check=True, capture_output=True)
        return output

    def prove(self, root, candidate, reference):
        words = [0] * 40
        fixed = {3: 0x3C0E8003, 4: 0x91CEAB40, 14: 0x3C018003, 16: 0xA028AB40,
                 17: 0x3C018003, 18: 0xA020AB40, 19: 0x0C008CE4, 25: 0x0C008CF0,
                 27: 0x3C09A450, 28: 0xAD220000, 30: 0x3C0BA450, 32: 0xAD6A0004}
        for index, word in fixed.items(): words[index] = word
        payload = struct.pack(">40I", *words)
        rom = bytearray(ai.DATA_ROM + 16); rom[ai.TEXT_ROM:ai.TEXT_ROM + 160] = payload
        assembly = root / "reference-words.s"
        assembly.write_text("".join(f"/* {ai.TEXT_ROM+i*4:X} {ai.TEXT_VRAM+i*4:08X} {word:08X} */ instruction\n" for i, word in enumerate(words)))
        manifest(root)
        with patch.object(private, "validated_rom", return_value=bytes(rom)), patch.object(private.rom_span, "main_code", return_value=(payload, ai.TEXT_VRAM, "validated")):
            return private.prepare(root, SOURCE, candidate, reference, assembly, ai.SYMBOL, ai.TEXT_VRAM, 160, {})

    def test_full_linked_private_data_and_literal_mmio_proof(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            candidate = self.assemble(root, "candidate")
            reference = self.assemble(root, "reference", raw=True)
            originals = candidate.read_bytes(), reference.read_bytes()
            pair = self.prove(root, candidate, reference)
            self.assertIsNotNone(pair)
            self.assertEqual(pair[0].read_bytes(), pair[1].read_bytes())
            self.assertEqual(originals, (candidate.read_bytes(), reference.read_bytes()))

    def test_wrong_code_padding_mmio_flag_addend_and_initializer_fail(self):
        cases = [{"mutation": (27, "lui $t1,0xa451")}, {"mutation": (32, "sw $t2,8($t3)")},
                 {"mutation": (39, "addiu $v0,$zero,1")}, {"mutation": (4, "lbu $t7,%lo(private_flag)($t6)")},
                 {"flag_addend": 1}, {"data": b"\1" + bytes(15)}]
        for kwargs in cases:
            with self.subTest(kwargs=kwargs), tempfile.TemporaryDirectory() as temporary:
                root = Path(temporary)
                self.assertIsNone(self.prove(root, self.assemble(root, "candidate", **kwargs), self.assemble(root, "reference", raw=True)))

    def test_unrelated_function_nonzero_data_and_rodata_natural_relocations(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary); symbol="func_80001000"; start=0x80001000
            unit=manifest(root, bytes(range(16)))
            unit["sections"].append({"input":".rodata","output":".main_private_constants",
                "vram":"0x8002AB50","rom_offset":"0x2AB50","size":16,"alignment":16,
                "flags":2,"sha256":hashlib.sha256(bytes(range(16,32))).hexdigest()})
            unit["sections"].append({"input":".sdata","output":".main_private_small_data",
                "vram":"0x8002AB60","rom_offset":"0x2AB60","size":16,"alignment":16,
                "flags":0x10000003,"sha256":hashlib.sha256(bytes(range(32,48))).hexdigest()})
            (root/private.MANIFEST).write_text(json.dumps({"schema_version":1,"units":[unit]}))
            for name,raw in [("candidate",False),("reference",True)]:
                text=(".text\n.set noreorder\n.globl " + symbol + "\n.type " + symbol + ",@function\n" + symbol + ":\n"
                      + "lui $t0,%hi(" + ("D_8002AB40" if raw else "counter") + ")\n"
                      + "lbu $t0,%lo(" + ("D_8002AB40" if raw else "counter") + ")($t0)\n"
                      + "lui $t1,%hi(" + ("D_8002AB50" if raw else "constant") + ")\n"
                      + "lbu $t1,%lo(" + ("D_8002AB50" if raw else "constant") + ")($t1)\n"
                      + "lui $t2,%hi(" + ("D_8002AB60" if raw else "small") + ")\n"
                      + "lbu $t2,%lo(" + ("D_8002AB60" if raw else "small") + ")($t2)\n.size " + symbol + ",24\n")
                if not raw:
                    for section,label,values in [(".data","counter",range(16)),(".rodata","constant",range(16,32)),(".sdata","small",range(32,48))]:
                        text += ".section "+section+"\n.p2align 4\n"+label+":\n.byte "+",".join(map(str,values))+"\n"
                source=root/(name+".s"); source.write_text(text)
                subprocess.run(["mips-linux-gnu-as","-EB","-mabi=32","-march=vr4300","-o",str(source.with_suffix(".o")),str(source)],check=True,capture_output=True)
            payload=struct.pack(">6I",0x3C088003,0x9108AB40,0x3C098003,0x9129AB50,0x3C0A8003,0x914AAB60)
            rom=bytearray(ai.DATA_ROM+48); rom[0x1000:0x1018]=payload; rom[ai.DATA_ROM:]=bytes(range(48))
            assembly=root/"raw.s"; assembly.write_text("".join(f"/* {0x1000+i*4:X} {start+i*4:08X} {word:08X} */ instruction\n" for i,word in enumerate(struct.unpack(">6I",payload))))
            with patch.object(private,"validated_rom",return_value=bytes(rom)), patch.object(private.rom_span,"main_code",return_value=(payload,start,"validated")):
                pair=private.prepare(root,SOURCE,root/"candidate.o",root/"reference.o",assembly,symbol,start,24,{})
                self.assertIsNotNone(pair); self.assertEqual(pair[0].read_bytes(),pair[1].read_bytes())

    def test_wrong_raw_bytes_cannot_become_comparison_evidence(self):
        with tempfile.TemporaryDirectory() as temporary:
            root = Path(temporary)
            candidate = self.assemble(root, "candidate")
            reference = self.assemble(root, "reference", raw=True, mutation=(39, "addiu $v0,$zero,1"))
            with self.assertRaisesRegex(ValueError, "raw reference"):
                self.prove(root, candidate, reference)


if __name__ == "__main__":
    unittest.main()
