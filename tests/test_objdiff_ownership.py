from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch
sys.path.insert(0, str(Path(__file__).resolve().parent.parent/'scripts'))
import objdiff_ownership as ownership


class OwnershipTests(unittest.TestCase):
    def test_owned_data_joins_source_and_prevents_premature_completion(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root/'src').mkdir()
            (root/'src/test.c').touch()
            code = {'kind':'source','source':'src/test.c','key':'code','report_code_bytes':16,
                    'complete':True,'base_path':'actual.o','target_path':'code.o'}
            data = {'kind':'external_payload','owner':{'sources':['src/test.c']},'key':'data',
                    'report_code_bytes':0,'report_data_bytes':8,'target_path':'data.o'}
            cfg = [{'name':'test.c','base_path':'actual.o','target_path':'code.o',
                    'metadata':{'complete':True,'progress_categories':['main','project']}},
                   {'name':'main/data/address','target_path':'data.o',
                    'metadata':{'complete':False,'progress_categories':['main','data']}}]
            with patch.object(ownership,'combine_targets',return_value={'target_path':'owned.o','target_sha256':'hash'}):
                units, configs=ownership.group_units([code,data],cfg,root,root,verify=False)
            self.assertEqual(len(units),1)
            self.assertEqual(configs[0]['name'],'test.c')
            self.assertEqual(units[0]['report_code_bytes'],16)
            self.assertEqual(units[0]['report_data_bytes'],8)
            self.assertEqual(configs[0]['base_path'],'actual.o')
            self.assertFalse(configs[0]['metadata']['complete'])
            self.assertEqual(units[0]['data_ranges'],[data])

    def test_unowned_ranges_never_merge_or_gain_source_credit(self):
        parts=[{'kind':'unassigned','key':str(i),'report_code_bytes':0,'report_data_bytes':8} for i in range(2)]
        cfg=[{'name':str(i),'metadata':{'complete':False}} for i in range(2)]
        units, configs=ownership.group_units(parts,cfg,Path('/unused'),Path('/unused'),verify=False)
        self.assertEqual(len(units),2)
        self.assertTrue(all(not c['metadata']['complete'] for c in configs))

    def test_shared_sdk_storage_groups_only_with_its_backing_overlay(self):
        owner={'archive':'libultra','member':'controller.o'}
        main={'kind':'sdk_placement','overlay':'main','owner':owner}
        game={'kind':'sdk','overlay':'game',**owner}
        self.assertNotEqual(ownership.owner_key(main,Path('/unused')),ownership.owner_key(game,Path('/unused')))


class ReferenceCombinationTests(unittest.TestCase):
    @unittest.skipUnless(__import__('shutil').which('mips-linux-gnu-as'), 'requires pinned MIPS binutils')
    def test_combination_preserves_unaligned_payload_and_relocation(self):
        import subprocess
        from elf_sections import sections
        from candidate_tables import Object32
        with tempfile.TemporaryDirectory() as tmp:
            root=Path(tmp)
            for name,text in [('code','.text\n.globl function\n.type function,@function\nfunction:\nnop\n.size function,.-function\n'),
                              ('data','.section .rodata,"a"\n.align 0\n.globl table\ntable:\n.word function\n.byte 1,2,3\n')]:
                (root/f'{name}.s').write_text(text)
                subprocess.run(['mips-linux-gnu-as','-EB','-march=vr4300','-mabi=32','-no-pad-sections',
                                '-o',str(root/f'{name}.o'),str(root/f'{name}.s')],check=True)
            result=ownership.combine_targets([{'target_path':'code.o'},{'target_path':'data.o'}],root,root/'joined.o')
            parsed=sections((root/result['target_path']).read_bytes(),1)
            self.assertEqual(parsed['.text'][0][5],4)
            self.assertEqual(parsed['.rodata'][0][5],7)
            self.assertEqual(len(Object32((root/'joined.o').read_bytes()).relocations),1)
