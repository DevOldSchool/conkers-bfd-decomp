"""Keep ordinary overlay function declarations in their canonical headers.

This is an ownership convention check, not a C/ABI validator. It recognizes
literal identifiers, ordinary file-scope prototypes and direct includes;
macro-generated names/includes and conditional compilation need compiler review.
"""
from __future__ import annotations

from pathlib import Path
import re
import sys
import tempfile
import unittest


ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "scripts"))
import call_signatures
import candidate_syntax
import declaration_facts


def active_source(source: str) -> str:
    # Remove comments before interpreting #if 0, without altering literals.
    source = "".join(
        re.sub(r"[^\n]", " ", token.group())
        if token.group().startswith(("/*", "//")) else token.group()
        for token in candidate_syntax.TOKEN.finditer(source)
    )
    return declaration_facts.active_text(source)


def file_prototypes(source: str) -> set[str]:
    """Reuse the signature reader on top-level declarations, excluding bodies."""
    names: set[str] = set()
    start = depth = 0
    for token in candidate_syntax.tokens(source):
        if depth == 0 and token.text == ";":
            names.update(call_signatures.source_signatures(source[start:token.end]))
            start = token.end
        if token.text == "{":
            depth += 1
        elif token.text == "}":
            depth -= 1
            if depth == 0:
                start = token.end
    return names


def ownership_errors(root: Path) -> list[str]:
    errors: list[str] = []
    owners: dict[str, str] = {}
    headers = sorted((root / "include").glob("*_functions.h"))
    if not headers:
        errors.append("include/: no canonical *_functions.h headers found")
    for header in headers:
        names = file_prototypes(active_source(header.read_text()))
        if not names:
            errors.append(f"{header.name}: no ordinary function prototypes found")
        for name in sorted(names):
            if name in owners:
                errors.append(f"{name}: owned by both {owners[name]} and {header.name}")
            owners[name] = header.name
    for header in sorted((root / "include").rglob("*.h")):
        if header in headers:
            continue
        prototypes = file_prototypes(active_source(header.read_text()))
        for name in sorted(prototypes & owners.keys()):
            errors.append(
                f"{header.relative_to(root)}: remove local prototype for {name}; "
                f"owned by {owners[name]}"
            )
    for path in sorted((root / "src").rglob("*")):
        if path.suffix not in {".c", ".h"} or not path.is_file():
            continue
        source = active_source(path.read_text())
        references = {token.text for token in candidate_syntax.tokens(source)} & owners.keys()
        if not references:
            continue
        # Read directive tokens, so a string containing #include cannot count.
        includes = {
            match[1]
            for token in candidate_syntax.TOKEN.finditer(source)
            if (match := re.match(r'#\s*include\s*[<"]([^>"\n]+)[>"]', token.group()))
        }
        local_prototypes = file_prototypes(source)
        for name in sorted(references):
            location = path.relative_to(root)
            if owners[name] not in includes:
                errors.append(f"{location}: {name} requires direct #include \"{owners[name]}\"")
            if name in local_prototypes:
                errors.append(f"{location}: remove local prototype for {name}; owned by {owners[name]}")
    return errors


class OverlayHeaderOwnershipTests(unittest.TestCase):
    def test_repository_uses_canonical_overlay_headers(self) -> None:
        self.assertEqual([], ownership_errors(ROOT))


class OwnershipCheckerTests(unittest.TestCase):
    def check(self, source: str, *, second_header: str | None = None,
              legacy_header: str | None = None) -> list[str]:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / "include").mkdir()
            (root / "src").mkdir()
            (root / "include/example_functions.h").write_text(
                '#ifndef EXAMPLE_FUNCTIONS_H\n#define EXAMPLE_FUNCTIONS_H\n'
                'Thing *owned(Thing *, int);\n#endif\n'
            )
            if second_header is not None:
                (root / "include/other_functions.h").write_text(second_header)
            if legacy_header is not None:
                (root / "include/nested").mkdir()
                (root / "include/nested/legacy.h").write_text(legacy_header)
            (root / "src/example.c").write_text(source)
            return ownership_errors(root)

    def test_definitions_calls_and_addresses_use_the_header(self) -> None:
        for source in (
            "Thing *owned(Thing *p, int n) { return p; }",
            "void caller(void) { owned(0, 1); }",
            "void caller(void) { callback = &owned; }",
        ):
            with self.subTest(source=source):
                self.assertEqual(1, len(self.check(source)))
                self.assertEqual([], self.check('#include "example_functions.h"\n' + source))

    def test_local_prototype_is_rejected_even_beside_its_definition(self) -> None:
        errors = self.check(
            '#include "example_functions.h"\n'
            'Thing *owned(Thing *, int);\n'
            'Thing *owned(Thing *p, int n) { return p; }\n'
        )
        self.assertEqual(1, len(errors))
        self.assertIn("remove local prototype for owned", errors[0])

    def test_disabled_candidates_comments_and_strings_are_ignored(self) -> None:
        self.assertEqual([], self.check(
            '#if 0\nThing *owned(Thing *, int);\nvoid old(void) { owned(0, 1); }\n#endif\n'
            '/* owned(0, 1);\n#if 0\n*/\n// owned\n'
            'const char *text = "owned /* not a comment */";\n'
        ))

    def test_commented_or_disabled_include_does_not_satisfy_ownership(self) -> None:
        for prefix in (
            '/* #include "example_functions.h" */\n',
            '#if 0\n#include "example_functions.h"\n#endif\n',
            'const char *fake = "#include \\\"example_functions.h\\\"";\n',
        ):
            with self.subTest(prefix=prefix):
                self.assertEqual(1, len(self.check(prefix + 'void caller(void) { owned(0, 1); }')))

    def test_duplicate_header_ownership_is_rejected(self) -> None:
        errors = self.check("", second_header="Thing *owned(Thing *, int);\n")
        self.assertEqual(1, len(errors))
        self.assertIn("owned by both", errors[0])

    def test_noncanonical_header_cannot_duplicate_an_owned_prototype(self) -> None:
        errors = self.check("", legacy_header="Thing *owned(Thing *, int);\n")
        self.assertEqual(1, len(errors))
        self.assertIn("include/nested/legacy.h: remove local prototype for owned", errors[0])
        self.assertEqual([], self.check("", legacy_header=(
            '#if 0\nThing *owned(Thing *, int);\n#endif\n'
            'typedef struct Thing { int value; } Thing;\n'
        )))

    def test_empty_canonical_header_does_not_pass_silently(self) -> None:
        errors = self.check("", second_header="/* no declarations */\n")
        self.assertEqual(1, len(errors))
        self.assertIn("no ordinary function prototypes", errors[0])


if __name__ == "__main__":
    unittest.main()
