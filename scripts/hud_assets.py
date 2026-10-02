#!/usr/bin/env python3
"""Extract code-backed US HUD/menu glyph and sprite metadata."""

from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import html
import json
import struct
from dataclasses import dataclass
from pathlib import Path
from typing import Any

try:
    from scripts import hud_additional_artwork
    from scripts import texture_assets as texture_base
    from scripts import texture_native
    from scripts.rzip_archive import (
        iter_indexed_flat_rzip_entries,
        normalize_rom,
        parse_game_archive,
    )
    from scripts.rzip_extract import (
        ROOT,
        display_path,
        load_layout,
        manifest_source,
        prepare_output,
    )
except ModuleNotFoundError:
    import hud_additional_artwork  # type: ignore[no-redef]
    import texture_assets as texture_base  # type: ignore[no-redef]
    import texture_native  # type: ignore[no-redef]
    from rzip_archive import (  # type: ignore[no-redef]
        iter_indexed_flat_rzip_entries,
        normalize_rom,
        parse_game_archive,
    )
    from rzip_extract import (  # type: ignore[no-redef]
        ROOT,
        display_path,
        load_layout,
        manifest_source,
        prepare_output,
    )


GLYPH_MAP_VRAM = 0x80085930
GLYPH_MAP_SIZE = 95
SPACE_GLYPH_INDEX = 0x60
SPRITE_TABLE_VRAM = 0x800859E0
SPRITE_TABLE_END_VRAM = 0x80085CC0
SPRITE_RECORD_SIZE = 8
SPRITE_RECORD_COUNT = (SPRITE_TABLE_END_VRAM - SPRITE_TABLE_VRAM) // SPRITE_RECORD_SIZE
ANIMATED_SELECTOR = 26
ANIMATED_FRAME_COUNT = 6
FORMAT_SCRATCH_SIGNATURE = b"%s%s        \0"
SPRITE_DESCRIPTOR_VRAM = 0x80090060
SPRITE_DESCRIPTOR_TAIL = bytes.fromhex("010000200020000301080f15")
SPRITE_TILE_WIDTH = 32
SPRITE_TILE_HEIGHT = 32
SPRITE_TILE_SIZE = SPRITE_TILE_WIDTH * SPRITE_TILE_HEIGHT * 4
SMALL_SPRITE_TILE_WIDTH = 16
SMALL_SPRITE_TILE_HEIGHT = 16
HUD_SOURCE_ORIGIN = "top-left"
HUD_PREVIEW_ORIGIN = "top-left"
# All selector sources use the renderer's RGBA32 dimensions and TMEM layout.
# Runtime IDs retain the empty slots in D_80091D20; stream ordinals do not.
RUNTIME_FLAT_ASSET_COUNT = 0x1E52
RUNTIME_FLAT_SIZE_TABLE = 0x80091D20
RUNTIME_FLAT_IDENTITY = {
    "index_space": "runtime-compressed-size-table",
    "size_table_vram": "0x80091D20",
    "runtime_slot_count": RUNTIME_FLAT_ASSET_COUNT,
    "empty_runtime_slots": [1767, 1768],
    "physical_stream_count": RUNTIME_FLAT_ASSET_COUNT - 2,
}
# Previous overrides described different physical payloads. The complete
# replacement catalog below was reviewed after resolving runtime IDs.
# Prior source and outputs are preserved in build/hud-reference-review/.
REVIEWED_RGBA16_FLAT_INDICES = frozenset()
REVIEWED_LINEAR_RGBA32_FLAT_INDICES = frozenset()
REVIEWED_NATIVE_PREVIEW_CONTRACTS = {}
REVIEWED_RESOURCE_DIMENSIONS = {}
REVIEWED_RAW_ONLY_FLAT_INDICES = {}
SELECTOR_PREVIEW_NOTES = {}
SELECTOR_REVIEWED_VARIANTS = {}
SELECTOR_REVIEWED_COMPOSITIONS = {}
SELECTOR_REVIEWED_IDENTITIES = {1: {'name': 'red-p1-badge',
     'display_name': 'Red P1 badge',
     'elements': ['P1'],
     'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                 'identification, runtime use unproven',
     'category': 'word-art',
     'flat_indices': [2196],
     'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
     'reference_title': 'Main Menu Text & Icons reference sheet',
     'reference_status': 'matched'},
 2: {'name': 'blue-p2-badge',
     'display_name': 'Blue P2 badge',
     'elements': ['P2'],
     'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                 'identification, runtime use unproven',
     'category': 'word-art',
     'flat_indices': [2197],
     'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
     'reference_title': 'Main Menu Text & Icons reference sheet',
     'reference_status': 'matched'},
 3: {'name': 'green-p3-badge',
     'display_name': 'Green P3 badge',
     'elements': ['P3'],
     'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                 'identification, runtime use unproven',
     'category': 'word-art',
     'flat_indices': [2198],
     'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
     'reference_title': 'Main Menu Text & Icons reference sheet',
     'reference_status': 'matched'},
 4: {'name': 'yellow-p4-badge',
     'display_name': 'Yellow P4 badge',
     'elements': ['P4'],
     'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                 'identification, runtime use unproven',
     'category': 'word-art',
     'flat_indices': [2199],
     'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
     'reference_title': 'Main Menu Text & Icons reference sheet',
     'reference_status': 'matched'},
 5: {'name': 'purple-figure-icon',
     'display_name': 'Purple figure icon',
     'elements': ['purple figure'],
     'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                 'identification, runtime use unproven',
     'category': 'icon',
     'flat_indices': [2171],
     'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
     'reference_title': 'Main Menu Text & Icons reference sheet',
     'reference_status': 'matched'},
 6: {'name': 'ai-label',
     'display_name': 'Ai label',
     'elements': ['Ai'],
     'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                 'identification, runtime use unproven',
     'category': 'word-art',
     'flat_indices': [2166],
     'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
     'reference_title': 'Main Menu Text & Icons reference sheet',
     'reference_status': 'matched'},
 7: {'name': 'four-direction-arrows',
     'display_name': 'Four directional arrows',
     'elements': ['up', 'down', 'left', 'right'],
     'evidence': 'decoded retail US resource pixels visually match ECTS demo reference artwork; '
                 'beta reference only, retail runtime use unproven',
     'category': 'icon',
     'flat_indices': [2167],
     'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62893/',
     'reference_title': 'ECTS Demo reference sheet (visual comparison only)',
     'reference_status': 'matched'},
 8: {'name': 'tediz-head-icon',
      'display_name': 'Tediz head icon',
      'elements': ['Tediz'],
      'evidence': 'user-supplied character identification; decoded pixels match the reference-sheet '
                  'artwork; runtime use unproven',
      'category': 'character',
      'flat_indices': [2215],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet',
      'reference_status': 'matched'},
 9: {'name': 'shc-soldier-head-icon',
      'display_name': 'SHC Soldier head icon',
      'elements': ['SHC Soldier'],
      'evidence': 'user-supplied character identification; decoded pixels match the reference-sheet '
                  'artwork; runtime use unproven',
      'category': 'character',
      'flat_indices': [2211],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet',
      'reference_status': 'matched'},
 10: {'name': 'uga-buga-head-icon',
      'display_name': 'Uga Buga head icon',
      'elements': ['Uga Buga'],
      'evidence': 'user-supplied character identification; decoded pixels match the reference-sheet '
                  'artwork; runtime use unproven',
      'category': 'character',
      'flat_indices': [2220],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet',
      'reference_status': 'matched'},
 11: {'name': 'raptor-head-icon',
      'display_name': 'Raptor head icon',
      'elements': ['Raptor'],
      'evidence': 'user-supplied character identification; decoded pixels match the reference-sheet '
                  'artwork; runtime use unproven',
      'category': 'character',
      'flat_indices': [2203],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet',
      'reference_status': 'matched'},
 12: {'name': 'cont-label-dark',
      'display_name': 'CONT... label (dark)',
      'elements': ['CONT...'],
      'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                  'identification, runtime use unproven',
      'category': 'word-art',
      'flat_indices': [2003, 2004],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62744/',
      'reference_title': 'Pause Menu & Multi Results reference sheet',
      'reference_status': 'matched'},
 13: {'name': 'cont-label-bright',
      'display_name': 'CONT... label (bright)',
      'elements': ['CONT...'],
      'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                  'identification, runtime use unproven',
      'category': 'word-art',
      'flat_indices': [2005, 2006],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62744/',
      'reference_title': 'Pause Menu & Multi Results reference sheet',
      'reference_status': 'matched'},
 14: {'name': 'quit-label-dark',
      'display_name': 'QUIT label (dark)',
      'elements': ['QUIT'],
      'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                  'identification, runtime use unproven',
      'category': 'word-art',
      'flat_indices': [2044, 2045],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62744/',
      'reference_title': 'Pause Menu & Multi Results reference sheet',
      'reference_status': 'matched'},
 15: {'name': 'quit-label-bright',
      'display_name': 'QUIT label (bright)',
      'elements': ['QUIT'],
      'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                  'identification, runtime use unproven',
      'category': 'word-art',
      'flat_indices': [2046, 2047],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62744/',
      'reference_title': 'Pause Menu & Multi Results reference sheet',
      'reference_status': 'matched'},
 16: {'name': 'cheats-label',
      'display_name': 'CHEATS label',
      'elements': ['CHEATS'],
      'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                  'identification, runtime use unproven',
      'category': 'word-art',
      'flat_indices': [1997, 1998],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet',
      'reference_status': 'matched'},
 17: {'name': 'off-speech-bubble',
      'display_name': 'OFF speech bubble',
      'elements': ['OFF'],
      'evidence': 'decoded retail US resource pixels visually match ECTS demo reference artwork; '
                  'beta reference only, retail runtime use unproven',
      'category': 'word-art',
      'flat_indices': [1988],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62893/',
      'reference_title': 'ECTS Demo reference sheet (visual comparison only)',
      'reference_status': 'matched'},
 18: {'name': 'on-speech-bubble',
      'display_name': 'ON speech bubble',
      'elements': ['ON'],
      'evidence': 'decoded retail US resource pixels visually match ECTS demo reference artwork; '
                  'beta reference only, retail runtime use unproven',
      'category': 'word-art',
      'flat_indices': [1989],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62893/',
      'reference_title': 'ECTS Demo reference sheet (visual comparison only)',
      'reference_status': 'matched'},
 19: {'name': 'speaker-pair',
      'display_name': 'Speaker pair',
      'elements': ['speakers'],
      'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                  'identification, runtime use unproven',
      'category': 'icon',
      'flat_indices': [2072, 2073],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet',
      'reference_status': 'matched'},
 20: {'name': 'five-speaker-arrangement',
      'display_name': 'Five-speaker arrangement',
      'elements': ['speakers'],
      'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                  'identification, runtime use unproven',
      'category': 'icon',
      'flat_indices': [2074, 2075],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet',
      'reference_status': 'matched'},
 21: {'name': 'single-speaker',
      'display_name': 'Single speaker',
      'elements': ['speaker'],
      'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                  'identification, runtime use unproven',
      'category': 'icon',
      'flat_indices': [2029],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet',
      'reference_status': 'matched'},
 22: {'name': 'play-label-dark',
      'display_name': 'PLAY label (dark)',
      'elements': ['PLAY'],
      'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                  'identification, runtime use unproven',
      'category': 'word-art',
      'flat_indices': [2039, 2040],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet',
      'reference_status': 'matched'},
 23: {'name': 'play-label-bright',
      'display_name': 'PLAY label (bright)',
      'elements': ['PLAY'],
      'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                  'identification, runtime use unproven',
      'category': 'word-art',
      'flat_indices': [2041, 2042],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet',
      'reference_status': 'matched'},
 24: {'name': 'erase-label-dark',
      'display_name': 'ERASE label (dark)',
      'elements': ['ERASE'],
      'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                  'identification, runtime use unproven',
      'category': 'word-art',
      'flat_indices': [2007, 2008],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet',
      'reference_status': 'matched'},
 25: {'name': 'erase-label-bright',
      'display_name': 'ERASE label (bright)',
      'elements': ['ERASE'],
      'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                  'identification, runtime use unproven',
      'category': 'word-art',
      'flat_indices': [2009, 2010],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet',
      'reference_status': 'matched'},
 26: {'name': 'analog-stick-animation',
      'display_name': 'Analog stick animation',
      'elements': ['analog stick'],
      'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                  'identification, runtime use unproven',
      'category': 'controller',
      'flat_indices': [2023, 2024, 2025, 2026, 2027, 2028],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet',
      'reference_status': 'matched'},
 27: {'name': 'set-up-label-dark',
      'display_name': 'SET-UP label (dark)',
      'elements': ['SET-UP'],
      'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                  'identification, runtime use unproven',
      'category': 'word-art',
      'flat_indices': [2066, 2067],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet',
      'reference_status': 'matched'},
 28: {'name': 'set-up-label-bright',
      'display_name': 'SET-UP label (bright)',
      'elements': ['SET-UP'],
      'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                  'identification, runtime use unproven',
      'category': 'word-art',
      'flat_indices': [2068, 2069],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet',
      'reference_status': 'matched'},
 29: {'name': 'n-button-dark',
      'display_name': 'N button (dark)',
      'elements': ['N'],
      'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                  'identification, runtime use unproven',
      'category': 'word-art',
      'flat_indices': [2033],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet',
      'reference_status': 'matched'},
 30: {'name': 'n-button-bright',
      'display_name': 'N button (bright)',
      'elements': ['N'],
      'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                  'identification, runtime use unproven',
      'category': 'word-art',
      'flat_indices': [2034],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet',
      'reference_status': 'matched'},
 31: {'name': 'y-button-dark',
      'display_name': 'Y button (dark)',
      'elements': ['Y'],
      'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                  'identification, runtime use unproven',
      'category': 'word-art',
      'flat_indices': [2095],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet',
      'reference_status': 'matched'},
 32: {'name': 'y-button-bright',
      'display_name': 'Y button (bright)',
      'elements': ['Y'],
      'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                  'identification, runtime use unproven',
      'category': 'word-art',
      'flat_indices': [2096],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet',
      'reference_status': 'matched'},
 33: {'name': 'restart-label-dark',
      'display_name': 'RESTART label (dark)',
      'elements': ['RESTART'],
      'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                  'identification, runtime use unproven',
      'category': 'word-art',
      'flat_indices': [2062, 2063],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62744/',
      'reference_title': 'Pause Menu & Multi Results reference sheet',
      'reference_status': 'matched'},
 34: {'name': 'restart-label-bright',
      'display_name': 'RESTART label (bright)',
      'elements': ['RESTART'],
      'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                  'identification, runtime use unproven',
      'category': 'word-art',
      'flat_indices': [2064, 2065],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62744/',
      'reference_title': 'Pause Menu & Multi Results reference sheet',
      'reference_status': 'matched'},
 35: {'name': 'race-a-label-dark',
      'display_name': 'RACE A label (dark)',
      'elements': ['RACE A'],
      'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                  'identification, runtime use unproven',
      'category': 'word-art',
      'flat_indices': [2048, 2049],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet',
      'reference_status': 'matched'},
 36: {'name': 'race-a-label-bright',
      'display_name': 'RACE A label (bright)',
      'elements': ['RACE A'],
      'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                  'identification, runtime use unproven',
      'category': 'word-art',
      'flat_indices': [2050, 2051],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet',
      'reference_status': 'matched'},
 37: {'name': 'race-b-label-dark',
      'display_name': 'RACE B label (dark)',
      'elements': ['RACE B'],
      'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                  'identification, runtime use unproven',
      'category': 'word-art',
      'flat_indices': [2052, 2053],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet',
      'reference_status': 'matched'},
 38: {'name': 'race-b-label-bright',
      'display_name': 'RACE B label (bright)',
      'elements': ['RACE B'],
      'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                  'identification, runtime use unproven',
      'category': 'word-art',
      'flat_indices': [2054, 2055],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet',
      'reference_status': 'matched'},
 39: {'name': 'temple-label-dark',
      'display_name': 'TEMPLE label (dark)',
      'elements': ['TEMPLE'],
      'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                  'identification, runtime use unproven',
      'category': 'word-art',
      'flat_indices': [2076, 2077],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet',
      'reference_status': 'matched'},
 40: {'name': 'temple-label-bright',
      'display_name': 'TEMPLE label (bright)',
      'elements': ['TEMPLE'],
      'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                  'identification, runtime use unproven',
      'category': 'word-art',
      'flat_indices': [2078, 2079],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet',
      'reference_status': 'matched'},
 41: {'name': 'the-vault-label-dark',
      'display_name': 'THE VAULT label (dark)',
      'elements': ['THE VAULT'],
      'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                  'identification, runtime use unproven',
      'category': 'word-art',
      'flat_indices': [2085, 2086],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet',
      'reference_status': 'matched'},
 42: {'name': 'the-vault-label-bright',
      'display_name': 'THE VAULT label (bright)',
      'elements': ['THE VAULT'],
      'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                  'identification, runtime use unproven',
      'category': 'word-art',
      'flat_indices': [2087, 2088],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet',
      'reference_status': 'matched'},
 43: {'name': 'total-war-label-dark',
      'display_name': 'TOTAL WAR label (dark)',
      'elements': ['TOTAL WAR'],
      'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                  'identification, runtime use unproven',
      'category': 'word-art',
      'flat_indices': [1984, 1985],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet',
      'reference_status': 'matched'},
 44: {'name': 'total-war-label-bright',
      'display_name': 'TOTAL WAR label (bright)',
      'elements': ['TOTAL WAR'],
      'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                  'identification, runtime use unproven',
      'category': 'word-art',
      'flat_indices': [1986, 1987],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet',
      'reference_status': 'matched'},
 45: {'name': 'colors-label-dark',
      'display_name': 'COLORS label (dark)',
      'elements': ['COLORS'],
      'evidence': 'decoded selector pixels corroborated by the reference sheet; visual '
                  'identification, runtime use unproven',
      'category': 'word-art',
      'flat_indices': [1999, 2000],
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet',
      'reference_status': 'matched'},
 46: {'name': 'colors-label-bright',
      'display_name': 'COLORS label (bright)',
      'elements': ['COLORS label (bright)'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2001, 2002],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet'},
 47: {'name': 'bunker-label-dark',
      'display_name': 'BUNKER label (dark)',
      'elements': ['BUNKER label (dark)'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [1990, 1991],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet'},
 48: {'name': 'bunker-label-bright',
      'display_name': 'BUNKER label (bright)',
      'elements': ['BUNKER label (bright)'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [1992, 1993],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet'},
 49: {'name': 'new-game-label-bright',
      'display_name': 'NEW GAME label (bright)',
      'elements': ['NEW GAME label (bright)'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2030, 2031, 2032],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet'},
 50: {'name': 'restart-label-bright',
      'display_name': 'RESTART label (bright)',
      'elements': ['RESTART label (bright)'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2064, 2065],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62744/',
      'reference_title': 'Pause Menu & Multi Results reference sheet'},
 51: {'name': 'quit-label-bright',
      'display_name': 'QUIT label (bright)',
      'elements': ['QUIT label (bright)'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2046, 2047],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62744/',
      'reference_title': 'Pause Menu & Multi Results reference sheet'},
 52: {'name': 'gray-character-brown-hat',
      'display_name': 'Gray character with brown hat',
      'elements': ['Gray character with brown hat'],
      'evidence': 'Matches reference character icon visually; exact character/species name '
                  'deliberately not inferred.',
      'flat_indices': [2172],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet'},
 53: {'name': 'blue-player-group',
      'display_name': 'Blue group of player pieces',
      'elements': ['Blue group of player pieces'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2187],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet'},
 54: {'name': 'lap-checkered-flag',
      'display_name': 'LAP checkered flag',
      'elements': ['LAP checkered flag'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2186],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet'},
 55: {'name': 'red-running-figures',
      'display_name': 'Red running figures',
      'elements': ['Red running figures'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2185],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet'},
 56: {'name': 'green-tank',
      'display_name': 'Tank turret icon',
      'elements': ['Tank turret', 'Green tank'],
      'evidence': 'Source pixels agree with the reference artwork and the green turret in the '
                  'user-supplied Tank setup screenshot; visual screen association.',
      'flat_indices': [2218],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet'},
 57: {'name': 'green-radar',
      'display_name': 'Green radar',
      'elements': ['Green radar'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2202],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet'},
 58: {'name': 'gold-balance-scales',
      'display_name': 'Gold balance scales',
      'elements': ['Gold balance scales'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2208],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet'},
 59: {'name': 'c-left-button',
      'display_name': 'N64 C-left button',
      'elements': ['N64 C-left button'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2224],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet'},
 60: {'name': 'c-right-button',
      'display_name': 'N64 C-right button',
      'elements': ['N64 C-right button'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2225],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet'},
 61: {'name': 'stopwatch',
      'display_name': 'Stopwatch',
      'elements': ['Stopwatch'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2222],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet'},
 62: {'name': 'opposed-red-arrows',
      'display_name': 'Two opposed red arrows',
      'elements': ['Two opposed red arrows'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2205],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet'},
 63: {'name': 'snowy-mountains-clouds',
      'display_name': 'Snowy mountains and clouds',
      'elements': ['Snowy mountains and clouds'],
      'evidence': 'No matching icon found in supplied reference sheets.',
      'flat_indices': [2116],
      'reference_status': 'not-in-supplied-sheets'},
 64: {'name': 'money-bag',
      'display_name': 'Money bag',
      'elements': ['Money bag'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2114],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet'},
 65: {'name': 'score-circle',
      'display_name': 'SCORE circular icon',
      'elements': ['SCORE circular icon'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2149],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet'},
 66: {'name': 'hungover-label',
      'display_name': 'HUNGOVER label',
      'elements': ['HUNGOVER label'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2108, 2109, 2110],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet'},
 67: {'name': 'windy-label',
      'display_name': 'WINDY label',
      'elements': ['WINDY label'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2126, 2127, 2128],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet'},
 68: {'name': 'batstower-label',
      'display_name': 'BATSTOWER label',
      'elements': ['BATSTOWER label'],
      'evidence': 'Readable text; no matching word art found in supplied reference sheets.',
      'flat_indices': [2102, 2103, 2104],
      'reference_status': 'not-in-supplied-sheets'},
 69: {'name': 'barn-boys-label',
      'display_name': 'BARN BOYS label',
      'elements': ['BARN BOYS label'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2099, 2100, 2101],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet'},
 70: {'name': 'sloprano-label',
      'display_name': 'SLOPRANO label',
      'elements': ['SLOPRANO label'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2117, 2118, 2119],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet'},
 71: {'name': 'uga-buga-label',
      'display_name': 'UGA BUGA label',
      'elements': ['UGA BUGA label'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2123, 2124, 2125],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet'},
 72: {'name': 'spooky-label',
      'display_name': 'SPOOKY label',
      'elements': ['SPOOKY label'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2120, 2121, 2122],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet'},
 73: {'name': 'its-war-label',
      'display_name': "IT'S WAR label",
      'elements': ["IT'S WAR label"],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2111, 2112, 2113],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet'},
 74: {'name': 'heist-label',
      'display_name': 'HEIST label',
      'elements': ['HEIST label'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2105, 2106, 2107],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet'},
 75: {'name': 'stats-label',
      'display_name': 'STATS label',
      'elements': ['STATS label'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2070, 2071],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62744/',
      'reference_title': 'Pause Menu & Multi Results reference sheet'},
 76: {'name': 'reds-label',
      'display_name': 'REDS label',
      'elements': ['REDS label'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2147, 2148],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet'},
 77: {'name': 'blues-label',
      'display_name': 'BLUES label',
      'elements': ['BLUES label'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2129, 2130],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet'},
 78: {'name': 'greens-label',
      'display_name': 'GREENS label',
      'elements': ['GREENS label'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2136, 2137, 2138],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet'},
 79: {'name': 'yellows-label',
      'display_name': 'YELLOWS label',
      'elements': ['YELLOWS label'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2159, 2160, 2161],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet'},
 80: {'name': 'squirrels-label',
      'display_name': 'SQUIRRELS label',
      'elements': ['SQUIRRELS label'],
      'evidence': 'Readable text; no matching word art found in supplied reference sheets.',
      'flat_indices': [2150, 2151, 2152],
      'reference_status': 'not-in-supplied-sheets'},
 81: {'name': 'tediz-label',
      'display_name': 'TEDIZ label',
      'elements': ['TEDIZ label'],
      'evidence': 'Readable text; no matching word art found in supplied reference sheets.',
      'flat_indices': [2153, 2154],
      'reference_status': 'not-in-supplied-sheets'},
 82: {'name': 'you-label',
      'display_name': 'YOU label',
      'elements': ['YOU label'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2162, 2163],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62744/',
      'reference_title': 'Pause Menu & Multi Results reference sheet'},
 83: {'name': 'ugas-label',
      'display_name': 'UGAS label',
      'elements': ['UGAS label'],
      'evidence': 'Readable text; no matching word art found in supplied reference sheets.',
      'flat_indices': [2155, 2156],
      'reference_status': 'not-in-supplied-sheets'},
 84: {'name': 'raptors-label',
      'display_name': 'RAPTORS label',
      'elements': ['RAPTORS label'],
      'evidence': 'Readable text; no matching word art found in supplied reference sheets.',
      'flat_indices': [2144, 2145, 2146],
      'reference_status': 'not-in-supplied-sheets'},
 85: {'name': 'frenchys-label',
      'display_name': 'FRENCHYS label',
      'elements': ['FRENCHYS label'],
      'evidence': 'Readable text; no matching word art found in supplied reference sheets.',
      'flat_indices': [2133, 2134, 2135],
      'reference_status': 'not-in-supplied-sheets'},
 86: {'name': 'win-label',
      'display_name': 'WIN label',
      'elements': ['WIN label'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2157, 2158],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62744/',
      'reference_title': 'Pause Menu & Multi Results reference sheet'},
 87: {'name': 'lose-label',
      'display_name': 'LOSE label',
      'elements': ['LOSE label'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2139, 2140],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62744/',
      'reference_title': 'Pause Menu & Multi Results reference sheet'},
 88: {'name': 'draw-label',
      'display_name': 'DRAW label',
      'elements': ['DRAW label'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2131, 2132],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62744/',
      'reference_title': 'Pause Menu & Multi Results reference sheet'},
 89: {'name': 'reds-label-small',
      'display_name': 'REDS label (smaller display scale)',
      'elements': ['REDS label (smaller display scale)'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2147, 2148],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet'},
 90: {'name': 'blues-label-small',
      'display_name': 'BLUES label (smaller display scale)',
      'elements': ['BLUES label (smaller display scale)'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2129, 2130],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet'},
 91: {'name': 'greens-label-small',
      'display_name': 'GREENS label (smaller display scale)',
      'elements': ['GREENS label (smaller display scale)'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2136, 2137, 2138],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet'},
 92: {'name': 'yellows-label-small',
      'display_name': 'YELLOWS label (smaller display scale)',
      'elements': ['YELLOWS label (smaller display scale)'],
      'evidence': 'Source pixels agree with the reference artwork; this does not establish a '
                  'runtime screen association.',
      'flat_indices': [2159, 2160, 2161],
      'reference_status': 'matched',
      'reference_url': 'https://www.spriters-resource.com/nintendo_64/conkersbadfurday/asset/62742/',
      'reference_title': 'Main Menu Text & Icons reference sheet'}}
LAYOUT_CALL_WORDS = {
    "positioned_template_calls": (0x0D410B65, 87, "func_15042D94"),
    "current_position_template_calls": (0x0D410B8F, 35, "func_15042E3C"),
    "position_state_updates": (0x0D410CBF, 18, "func_150432FC"),
}

# These instructions prove the two data consumers before any bytes are labelled.
# func_15042C40 folds ASCII lowercase, special-cases space, and scans 95 bytes at
# D_80085930. func_15043384 selects (kind - 1) * 8 at D_800859E0 and passes
# fields 0/1/4 to func_151ED430. That renderer then sends the word at +0 of its
# temporary descriptor to the flat-asset loader func_1510D0EC.
GAME_CODE_SIGNATURES = {
    0x15042C4C: 0x28810061,  # slti at, a0, 0x61
    0x15042C58: 0x2881007B,  # slti at, a0, 0x7b
    0x15042C60: 0x2482FFE0,  # addiu v0, a0, -0x20
    0x15042C74: 0x24010020,  # addiu at, zero, 0x20
    0x15042C84: 0x24020060,  # addiu v0, zero, 0x60
    0x15042C88: 0x93185930,  # lbu t8, 0x5930(t8)
    0x15042CD8: 0x2406005F,  # addiu a2, zero, 0x5f
    0x15042F30: 0x2404005C,  # allocate 0x5c-byte layout record
    0x15042F74: 0xA040000D,  # initial kind selector = text
    0x15043108: 0xA1CD000D,  # inline control argument -> kind selector
    0x15043428: 0x24170010,  # small selector dimension = 16
    0x15043434: 0x9204000D,  # renderer reads kind selector
    0x1504343C: 0x273959E0,  # sprite metadata table base
    0x15043444: 0x2483FFFF,  # selector -> zero-based index
    0x150436CC: 0x0003C0C0,  # eight-byte record stride
    0x150436D4: 0x92280002,  # scale byte
    0x15043720: 0x92250003,  # raw flag byte
    0x15043734: 0xA6770006,  # flag bit 1 sets descriptor width to 16
    0x15043738: 0xA6770008,  # flag bit 1 sets descriptor height to 16
    0x15043788: 0x8E2FFFFC,  # flat asset index at record +4
    0x1504378C: 0x9228FFF8,  # tile columns at record +0
    0x15043790: 0x922AFFF9,  # tile rows at record +1
    0x15043858: 0x8E240004,  # ordinary flat asset index
    0x15043860: 0x258C5AA8,  # animated selector's record address
    0x150438A8: 0x922F0000,  # tile columns at record +0
    0x150438AC: 0x922A0001,  # tile rows at record +1
    0x151ED4B8: 0x8E4E0000,  # descriptor's flat asset index
    0x151ED4B0: 0x964F0006,  # descriptor width
    0x151ED4EC: 0x96590008,  # descriptor height
    0x151ED614: 0x9258000B,  # descriptor image size
    0x151ED628: 0x9258000A,  # descriptor image format
    0x151ED5E0: 0x0D44343B,  # jal func_1510D0EC
    0x151ED89C: 0x26940001,  # advance to the next flat entry
    # Loader ID bounds, empty-slot handling and cumulative u16 ROM offsets.
    0x1510D140: 0x2A011E52,
    0x1510D150: 0x0010C040,
    0x1510D15C: 0x3C038009,
    0x1510D164: 0x94631D20,
    0x1510D170: 0x14600007,
    0x1510D180: 0x3C0B8000,
    0x1510D1CC: 0x02002025,
    0x1510D1D8: 0x0D4434DD,
    0x1510D374: 0x3C03001A,
    0x1510D378: 0x246337E0,
    0x1510D390: 0x3C0F8009,
    0x1510D394: 0x25EF1D20,
    0x1510D3A0: 0x94B80000,
    0x1510D3A8: 0x24A50002,
    0x1510D3B0: 0x00781821,
    0x1510D3C4: 0x00044840,
    0x1510D3D0: 0x94AA0000,
    0x1510D3D4: 0x94AB0002,
    0x1510D3D8: 0x94AC0004,
    0x1510D3E0: 0x94AD0006,
    0x1510D3F4: 0x006D1821,

}

LAYOUT_RECORD_SCHEMA = (
    {"offset": 0x00, "size": 4, "type": "pointer", "name": "attached_object"},
    {"offset": 0x04, "size": 4, "type": "f32", "name": "scale"},
    {"offset": 0x08, "size": 2, "type": "s16", "name": "x"},
    {"offset": 0x0A, "size": 2, "type": "s16", "name": "y"},
    {"offset": 0x0C, "size": 1, "type": "u8", "name": "flags_raw"},
    {
        "offset": 0x0D,
        "size": 1,
        "type": "u8",
        "name": "kind_selector",
        "meaning": "0=text; 1..92 select sprite metadata",
    },
    {"offset": 0x0E, "size": 4, "type": "rgba8", "name": "primary_rgba"},
    {"offset": 0x12, "size": 4, "type": "bytes", "name": "secondary_rgba_unresolved"},
    {"offset": 0x18, "size": 4, "type": "pointer", "name": "next"},
    {"offset": 0x1C, "size": 0x40, "type": "char[64]", "name": "inline_text"},
)


@dataclass(frozen=True)
class SpriteMetadata:
    selector: int
    tile_columns: int
    tile_rows: int
    scale_byte: int
    flags_raw: int
    flat_asset_index: int

    @property
    def scale(self) -> float:
        return self.scale_byte / 128.0


@dataclass(frozen=True)
class HudAssetFamily:
    glyph_map: bytes
    sprite_table: bytes
    sprites: tuple[SpriteMetadata, ...]
    layout_call_sites: dict[str, tuple[int, ...]] | None = None


@dataclass(frozen=True)
class FlatHudAsset:
    flat_index: int
    rom_start: int
    rom_end: int
    data: bytes


@dataclass(frozen=True)
class HudPreviewImage:
    width: int
    height: int
    pixels: bytes
    bytes_used: int
    texture_format: str
    row_layout: str
    status: str


def parse_glyph_map(data: bytes) -> tuple[int, ...]:
    if len(data) != GLYPH_MAP_SIZE:
        raise ValueError(
            f"HUD glyph map is {len(data)} bytes; expected {GLYPH_MAP_SIZE}"
        )
    if data[:36] != b"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ":
        raise ValueError("HUD glyph map does not begin with the code-proven ASCII order")
    if 0 in data:
        raise ValueError("HUD glyph map contains an unexpected terminator")
    return tuple(data)


def glyph_index_for_byte(value: int, glyph_map: bytes) -> int | None:
    """Mirror func_15042C40 for the table-backed and space cases."""

    value &= 0xFF
    folded = value - 0x20 if 0x61 <= value < 0x7B else value
    if value == 0x20:
        return SPACE_GLYPH_INDEX
    try:
        return glyph_map.index(folded)
    except ValueError:
        return None


def parse_sprite_table(data: bytes) -> tuple[SpriteMetadata, ...]:
    if len(data) != SPRITE_RECORD_COUNT * SPRITE_RECORD_SIZE:
        raise ValueError(
            f"HUD sprite table is {len(data)} bytes; expected "
            f"{SPRITE_RECORD_COUNT * SPRITE_RECORD_SIZE}"
        )
    records = []
    for offset in range(0, len(data), SPRITE_RECORD_SIZE):
        columns, rows, scale_byte, flags_raw, flat_asset_index = struct.unpack_from(
            ">BBBBI", data, offset
        )
        selector = offset // SPRITE_RECORD_SIZE + 1
        if columns not in (1, 2, 3) or rows != 1:
            raise ValueError(f"HUD sprite selector {selector} has invalid tile dimensions")
        if scale_byte == 0:
            raise ValueError(f"HUD sprite selector {selector} has a zero scale byte")
        if flags_raw & ~0x03:
            raise ValueError(f"HUD sprite selector {selector} has unknown flag bits")
        records.append(
            SpriteMetadata(
                selector=selector,
                tile_columns=columns,
                tile_rows=rows,
                scale_byte=scale_byte,
                flags_raw=flags_raw,
                flat_asset_index=flat_asset_index,
            )
        )
    return tuple(records)


def validate_code(code: bytes, game_vram: int) -> None:
    for address, expected in GAME_CODE_SIGNATURES.items():
        offset = address - game_vram
        if offset < 0 or offset + 4 > len(code):
            raise ValueError(f"HUD code signature address 0x{address:X} is outside game code")
        actual = struct.unpack_from(">I", code, offset)[0]
        if actual != expected:
            raise ValueError(
                f"HUD code signature mismatch at 0x{address:X}: "
                f"got 0x{actual:08X}, expected 0x{expected:08X}"
            )


def layout_call_sites(code: bytes, game_vram: int) -> dict[str, tuple[int, ...]]:
    words = struct.iter_unpack(">I", code[: len(code) - len(code) % 4])
    addresses_by_word: dict[int, list[int]] = {}
    for index, (word,) in enumerate(words):
        addresses_by_word.setdefault(word, []).append(game_vram + index * 4)
    result = {}
    for name, (word, expected_count, _) in LAYOUT_CALL_WORDS.items():
        addresses = tuple(addresses_by_word.get(word, ()))
        if len(addresses) != expected_count:
            raise ValueError(
                f"HUD {name} count is {len(addresses)}; expected {expected_count}"
            )
        result[name] = addresses
    return result


def data_slice(data: bytes, data_vram: int, start: int, end: int) -> bytes:
    relative_start = start - data_vram
    relative_end = end - data_vram
    if relative_start < 0 or relative_end > len(data) or relative_start > relative_end:
        raise ValueError(f"HUD data range 0x{start:X}:0x{end:X} is outside game data")
    return data[relative_start:relative_end]


def parse_hud_assets(code: bytes, data: bytes, game_vram: int, data_vram: int) -> HudAssetFamily:
    validate_code(code, game_vram)
    glyph_map = data_slice(
        data, data_vram, GLYPH_MAP_VRAM, GLYPH_MAP_VRAM + GLYPH_MAP_SIZE
    )
    sprite_table = data_slice(
        data, data_vram, SPRITE_TABLE_VRAM, SPRITE_TABLE_END_VRAM
    )
    scratch = data_slice(
        data,
        data_vram,
        SPRITE_TABLE_END_VRAM,
        SPRITE_TABLE_END_VRAM + len(FORMAT_SCRATCH_SIGNATURE),
    )
    if scratch != FORMAT_SCRATCH_SIGNATURE:
        raise ValueError("HUD sprite table end is not followed by the parser scratch format")
    descriptor_tail = data_slice(
        data,
        data_vram,
        SPRITE_DESCRIPTOR_VRAM + 4,
        SPRITE_DESCRIPTOR_VRAM + 4 + len(SPRITE_DESCRIPTOR_TAIL),
    )
    if descriptor_tail != SPRITE_DESCRIPTOR_TAIL:
        raise ValueError("HUD sprite renderer descriptor is not 32x32 RGBA32")
    parse_glyph_map(glyph_map)
    sprites = parse_sprite_table(sprite_table)
    return HudAssetFamily(
        glyph_map,
        sprite_table,
        sprites,
        layout_call_sites=layout_call_sites(code, game_vram),
    )


def resolve_rom(profile: str, rom_argument: Path | None) -> tuple[Path, dict[str, Any]]:
    if profile != "us":
        raise ValueError("HUD/menu metadata is currently proven only for US")
    layout = load_layout(profile)
    default_rom = layout.get("default_rom")
    rom_path = rom_argument or (ROOT / default_rom if default_rom else None)
    if rom_path is None:
        raise ValueError("--rom is required for the US profile")
    if not rom_path.is_absolute():
        rom_path = ROOT / rom_path
    if not rom_path.is_file():
        raise ValueError(f"ROM does not exist: {display_path(rom_path)}")
    return rom_path, layout


def load_profile_hud_assets(
    profile: str, rom_argument: Path | None
) -> tuple[Path, str, str, HudAssetFamily]:
    rom_path, layout = resolve_rom(profile, rom_argument)
    normalized, source_order = normalize_rom(rom_path.read_bytes())
    digest = hashlib.sha1(normalized).hexdigest()
    if digest not in layout["normalized_sha1"]:
        raise ValueError(f"US normalized ROM SHA-1 mismatch: got {digest}")
    archive = parse_game_archive(normalized[layout["game_start"] : layout["game_end"]])
    family = parse_hud_assets(
        archive.code, archive.data, layout["game_vram"], layout["game_data_vram"]
    )
    return rom_path, source_order, digest, family


def reachable_flat_indices(sprites: tuple[SpriteMetadata, ...]) -> tuple[int, ...]:
    indices: set[int] = set()
    for sprite in sprites:
        frame_offsets = range(ANIMATED_FRAME_COUNT) if sprite.selector == ANIMATED_SELECTOR else range(1)
        for frame_offset in frame_offsets:
            first = sprite.flat_asset_index + frame_offset
            indices.update(range(first, first + sprite.tile_columns * sprite.tile_rows))
        indices.update(
            variant["flat_index"]
            for variant in SELECTOR_REVIEWED_VARIANTS.get(sprite.selector, ())
        )
        composition = SELECTOR_REVIEWED_COMPOSITIONS.get(sprite.selector)
        if composition:
            indices.update(composition["flat_indices"])
    return tuple(sorted(indices))


def load_reachable_flat_assets(
    profile: str,
    rom_argument: Path | None,
    sprites: tuple[SpriteMetadata, ...],
    extra_resource_ids: tuple[int, ...] = (),
) -> dict[int, FlatHudAsset]:
    rom_path, layout = resolve_rom(profile, rom_argument)
    normalized, _ = normalize_rom(rom_path.read_bytes())
    digest = hashlib.sha1(normalized).hexdigest()
    if digest not in layout["normalized_sha1"]:
        raise ValueError(f"US normalized ROM SHA-1 mismatch: got {digest}")
    wanted = set(reachable_flat_indices(sprites)) | set(extra_resource_ids)
    flat_start = layout["flat_assets_start"]
    flat_end = layout["flat_assets_end"]
    game = parse_game_archive(normalized[layout["game_start"] : layout["game_end"]])
    validate_code(game.code, layout["game_vram"])
    size_bytes = data_slice(game.data, layout["game_data_vram"],
        RUNTIME_FLAT_SIZE_TABLE, RUNTIME_FLAT_SIZE_TABLE + RUNTIME_FLAT_ASSET_COUNT * 2)
    compressed_sizes = struct.unpack(f">{RUNTIME_FLAT_ASSET_COUNT}H", size_bytes)
    if [index for index, size in enumerate(compressed_sizes) if not size] != RUNTIME_FLAT_IDENTITY["empty_runtime_slots"]:
        raise ValueError("US runtime flat asset empty slots changed")
    assets = {
        entry.index: FlatHudAsset(
            flat_index=entry.index,
            rom_start=flat_start + entry.start,
            rom_end=flat_start + entry.end,
            data=entry.data,
        )
        for entry in iter_indexed_flat_rzip_entries(
            normalized[flat_start:flat_end], compressed_sizes)
        if entry.index in wanted
    }
    missing = sorted(wanted - assets.keys())
    if missing:
        raise ValueError(f"HUD sprite resources are missing flat indices: {missing}")
    return assets


def glyph_records(glyph_map: bytes) -> list[dict[str, Any]]:
    records = []
    for index, value in enumerate(glyph_map):
        printable = bytes((value,)).decode("latin-1")
        records.append(
            {
                "glyph_index": index,
                "input_byte": value,
                "input_hex": f"0x{value:02X}",
                "display_latin1": printable,
            }
        )
    records.append(
        {
            "glyph_index": SPACE_GLYPH_INDEX,
            "input_byte": 0x20,
            "input_hex": "0x20",
            "display_latin1": " ",
            "special_case": "func_15042C40 returns index 0x60 without reading the table",
        }
    )
    return records


def sprite_records(sprites: tuple[SpriteMetadata, ...]) -> list[dict[str, Any]]:
    records = []
    for sprite in sprites:
        record: dict[str, Any] = {
            "selector": sprite.selector,
            "table_offset": (sprite.selector - 1) * SPRITE_RECORD_SIZE,
            "tile_columns": sprite.tile_columns,
            "tile_rows": sprite.tile_rows,
            "scale_byte": sprite.scale_byte,
            "scale": sprite.scale,
            "flags_raw": sprite.flags_raw,
            "flag_bit_0": bool(sprite.flags_raw & 1),
            "flag_bit_1": bool(sprite.flags_raw & 2),
            "renderer_tile_width": (
                SMALL_SPRITE_TILE_WIDTH
                if sprite.flags_raw & 2
                else SPRITE_TILE_WIDTH
            ),
            "renderer_tile_height": (
                SMALL_SPRITE_TILE_HEIGHT
                if sprite.flags_raw & 2
                else SPRITE_TILE_HEIGHT
            ),
            "flat_asset_index": sprite.flat_asset_index,
        }
        if sprite.selector == ANIMATED_SELECTOR:
            record["runtime_animation"] = {
                "kind": "triangular-index-offset",
                "frame_count": ANIMATED_FRAME_COUNT,
                "flat_asset_indices": list(
                    range(
                        sprite.flat_asset_index,
                        sprite.flat_asset_index + ANIMATED_FRAME_COUNT,
                    )
                ),
                "evidence": "func_15043384 special-cases D_80085AA8",
            }
        records.append(record)
    return records


def build_manifest(
    profile: str,
    rom_path: Path,
    source_order: str,
    digest: str,
    family: HudAssetFamily,
) -> dict[str, Any]:
    flags = Counter(sprite.flags_raw for sprite in family.sprites)
    scales = Counter(sprite.scale_byte for sprite in family.sprites)
    call_sites = family.layout_call_sites or {}
    return {
        "schema_version": 1,
        "family": "hud-menu-layout-and-sprite-metadata",
        "profile": profile,
        "source_rom": manifest_source(rom_path),
        "source_byte_order": source_order,
        "normalized_sha1": digest,
        "glyph_map": {
            "vram": f"0x{GLYPH_MAP_VRAM:X}",
            "size": len(family.glyph_map),
            "sha1": hashlib.sha1(family.glyph_map).hexdigest(),
            "file": "glyph-map.bin",
            "lowercase_rule": "ASCII a-z folds to A-Z",
            "space_glyph_index": SPACE_GLYPH_INDEX,
            "records": glyph_records(family.glyph_map),
        },
        "sprite_metadata": {
            "vram_start": f"0x{SPRITE_TABLE_VRAM:X}",
            "vram_end": f"0x{SPRITE_TABLE_END_VRAM:X}",
            "record_size": SPRITE_RECORD_SIZE,
            "record_count": len(family.sprites),
            "sha1": hashlib.sha1(family.sprite_table).hexdigest(),
            "file": "sprite-metadata.bin",
            "unique_flat_asset_count": len(
                {sprite.flat_asset_index for sprite in family.sprites}
            ),
            "reachable_flat_asset_count": len(reachable_flat_indices(family.sprites)),
            "flag_counts": {str(key): value for key, value in sorted(flags.items())},
            "scale_byte_counts": {
                str(key): value for key, value in sorted(scales.items())
            },
            "records": sprite_records(family.sprites),
        },
        "runtime_layout_record": {
            "size": 0x5C,
            "allocation_function": "func_15042ECC",
            "render_function": "func_15043384",
            "fields": list(LAYOUT_RECORD_SCHEMA),
            "note": (
                "These linked records are assembled dynamically from text/control "
                "templates; this extraction preserves the code-proven schema but does "
                "not invent static screen names or placements."
            ),
        },
        "runtime_layout_call_sites": {
            name: {
                "callee": LAYOUT_CALL_WORDS[name][2],
                "count": len(addresses),
                "addresses": [f"0x{address:X}" for address in addresses],
            }
            for name, addresses in call_sites.items()
        },
        "evidence": {
            "glyph_lookup": "func_15042C40",
            "layout_parser": "func_15042ECC",
            "layout_renderer": "func_15043384",
            "sprite_renderer": "func_151ED430",
            "flat_asset_loader": "func_1510D0EC",
            "verified_instruction_count": len(GAME_CODE_SIGNATURES),
            "resource_identity": RUNTIME_FLAT_IDENTITY,
            "sprite_descriptor": {
                "vram": f"0x{SPRITE_DESCRIPTOR_VRAM:X}",
                "default_width": SPRITE_TILE_WIDTH,
                "default_height": SPRITE_TILE_HEIGHT,
                "flag_bit_1_width": SMALL_SPRITE_TILE_WIDTH,
                "flag_bit_1_height": SMALL_SPRITE_TILE_HEIGHT,
                "format": "rgba32",
            },
        },
    }


def selector_tile_dimensions(sprite: SpriteMetadata) -> tuple[int, int]:
    """Return the dimensions selected by func_15043384 for this record."""

    if sprite.flags_raw & 2:
        return SMALL_SPRITE_TILE_WIDTH, SMALL_SPRITE_TILE_HEIGHT
    return SPRITE_TILE_WIDTH, SPRITE_TILE_HEIGHT


def resource_render_dimensions(
    sprites: tuple[SpriteMetadata, ...],
) -> dict[int, tuple[int, int]]:
    """Map reachable resources to their code-selected render dimensions."""

    dimensions: dict[int, tuple[int, int]] = {}
    for sprite in sprites:
        selected = selector_tile_dimensions(sprite)
        for frame in selector_frame_indices(sprite):
            for flat_index in frame:
                previous = dimensions.setdefault(flat_index, selected)
                if previous != selected:
                    raise ValueError(
                        f"HUD resource {flat_index} has conflicting render dimensions"
                    )
    return dimensions


def resource_preview_dimensions(
    sprites: tuple[SpriteMetadata, ...],
) -> dict[int, tuple[int, int]]:
    """Map preview resources to their reviewed source-pixel dimensions."""

    dimensions = resource_render_dimensions(sprites)
    for flat_index in tuple(dimensions):
        dimensions[flat_index] = REVIEWED_RESOURCE_DIMENSIONS.get(
            flat_index, dimensions[flat_index]
        )
    for sprite in sprites:
        for variant in SELECTOR_REVIEWED_VARIANTS.get(sprite.selector, ()):
            flat_index = variant["flat_index"]
            reviewed = REVIEWED_RESOURCE_DIMENSIONS[flat_index]
            previous = dimensions.setdefault(flat_index, reviewed)
            if previous != reviewed:
                raise ValueError(
                    f"HUD resource {flat_index} has conflicting render dimensions"
                )
        composition = SELECTOR_REVIEWED_COMPOSITIONS.get(sprite.selector)
        if composition:
            for flat_index in composition["flat_indices"]:
                reviewed = REVIEWED_RESOURCE_DIMENSIONS[flat_index]
                previous = dimensions.setdefault(flat_index, reviewed)
                if previous != reviewed:
                    raise ValueError(
                        f"HUD resource {flat_index} has conflicting preview dimensions"
                    )
    return dimensions


def rgba32_preview_pixels(
    data: bytes,
    width: int = SPRITE_TILE_WIDTH,
    height: int = SPRITE_TILE_HEIGHT,
    row_layout: str = texture_base.ROW_LAYOUT_TMEM,
) -> tuple[int, bytes, int]:
    """Decode the row-complete RGBA32 window consumed by the sprite renderer.

    The renderer's source coordinates are already top-left oriented.  The only
    storage conversion required for a conventional PNG is undoing the odd-row
    TMEM word permutation.  Short resources contain a whole number of source
    rows; retain that encoded height instead of fabricating missing rows.
    """

    row_size = width * 4
    expected_size = row_size * height
    used_size = min(len(data), expected_size)
    if used_size == 0 or used_size % row_size:
        raise ValueError(
            f"HUD RGBA32 resource size {len(data)} does not contain complete "
            f"{width}-pixel rows"
        )
    decoded_height = used_size // row_size
    linear = texture_native.convert_row_layout(
        data[:used_size],
        row_layout,
        "rgba32",
        width,
        decoded_height,
    )
    return decoded_height, linear, used_size


def rgba16_preview_pixels(
    data: bytes,
    width: int = SPRITE_TILE_WIDTH,
    height: int = SPRITE_TILE_HEIGHT,
) -> tuple[int, bytes, int]:
    """Decode a reviewed RGBA5551 structural preview without claiming runtime format."""

    row_size = width * 2
    used_size = min(len(data), row_size * height)
    if used_size == 0 or used_size % row_size:
        raise ValueError(
            f"HUD RGBA16 candidate size {len(data)} does not contain complete "
            f"{width}-pixel rows"
        )
    decoded_height = used_size // row_size
    stored = data[:used_size]
    converted = bytearray(stored)
    for row_index in range(1, decoded_height, 2):
        row_start = row_index * row_size
        source = stored[row_start : row_start + row_size]
        converted[row_start : row_start + row_size] = bytes(
            source[column ^ 4] for column in range(row_size)
        )
    pixels = bytearray()
    for offset in range(0, len(converted), 2):
        value = struct.unpack_from(">H", converted, offset)[0]
        pixels.extend(
            (
                texture_base.expand_5bit((value >> 11) & 0x1F),
                texture_base.expand_5bit((value >> 6) & 0x1F),
                texture_base.expand_5bit((value >> 1) & 0x1F),
                255 if value & 1 else 0,
            )
        )
    return decoded_height, bytes(pixels), used_size


def resource_preview_image(
    flat_index: int, data: bytes, width: int, nominal_height: int
) -> HudPreviewImage | None:
    """Apply the reviewed per-resource preview contract for one HUD payload."""

    if flat_index in REVIEWED_RAW_ONLY_FLAT_INDICES:
        return None
    native_contract = REVIEWED_NATIVE_PREVIEW_CONTRACTS.get(flat_index)
    if native_contract:
        texture_format, row_layout, status = native_contract
        expected_size = texture_native.packed_row_size(texture_format, width) * nominal_height
        if len(data) < expected_size:
            raise ValueError(
                f"HUD {texture_format.upper()} resource size {len(data)} is smaller "
                f"than its reviewed {width}x{nominal_height} window"
            )
        linear = texture_native.convert_row_layout(
            data[:expected_size], row_layout, texture_format, width, nominal_height
        )
        return HudPreviewImage(
            width,
            nominal_height,
            texture_native.payload_to_rgba(linear, texture_format),
            expected_size,
            texture_format,
            row_layout,
            status,
        )
    if flat_index in REVIEWED_RGBA16_FLAT_INDICES:
        decoded_height, pixels, bytes_used = rgba16_preview_pixels(
            data, width, nominal_height
        )
        return HudPreviewImage(
            width,
            decoded_height,
            pixels,
            bytes_used,
            "rgba16-candidate",
            texture_base.ROW_LAYOUT_TMEM,
            "reviewed-rgba16-structural-preview",
        )
    row_layout = (
        texture_base.ROW_LAYOUT_LINEAR
        if flat_index in REVIEWED_LINEAR_RGBA32_FLAT_INDICES
        else texture_base.ROW_LAYOUT_TMEM
    )
    decoded_height, pixels, bytes_used = rgba32_preview_pixels(
        data, width, nominal_height, row_layout
    )
    status = (
        "reviewed-linear-rgba32-preview"
        if row_layout == texture_base.ROW_LAYOUT_LINEAR
        else "previewable-render-window"
    )
    if decoded_height < nominal_height:
        status = (
            "reviewed-linear-rgba32-short-preview"
            if row_layout == texture_base.ROW_LAYOUT_LINEAR
            else "previewable-row-complete-prefix"
        )
    elif len(data) > bytes_used:
        status = "previewable-render-window-with-trailing-bytes"
    return HudPreviewImage(
        width,
        decoded_height,
        pixels,
        bytes_used,
        "rgba32",
        row_layout,
        status,
    )


def compose_rgba_tiles(
    tiles: list[bytes], columns: int, rows: int
) -> tuple[int, int, bytes]:
    if len(tiles) != columns * rows:
        raise ValueError("HUD selector tile count does not match its grid")
    width = columns * SPRITE_TILE_WIDTH
    height = rows * SPRITE_TILE_HEIGHT
    output = bytearray(width * height * 4)
    for column in range(columns):
        for row in range(rows):
            tile = tiles[column * rows + row]
            if len(tile) != SPRITE_TILE_SIZE:
                raise ValueError("HUD selector contains an unresolved tile")
            for tile_y in range(SPRITE_TILE_HEIGHT):
                source = tile_y * SPRITE_TILE_WIDTH * 4
                target_y = row * SPRITE_TILE_HEIGHT + tile_y
                target = (target_y * width + column * SPRITE_TILE_WIDTH) * 4
                output[target : target + SPRITE_TILE_WIDTH * 4] = tile[
                    source : source + SPRITE_TILE_WIDTH * 4
                ]
    return width, height, bytes(output)


def compose_preview_tiles(
    tiles: list[tuple[int, int, bytes]], columns: int, rows: int
) -> tuple[int, int, bytes]:
    """Compose variable-height decoded source windows in selector order."""

    if len(tiles) != columns * rows:
        raise ValueError("HUD selector tile count does not match its grid")
    column_widths = [
        max(tiles[column * rows + row][0] for row in range(rows))
        for column in range(columns)
    ]
    row_heights = [
        max(tiles[column * rows + row][1] for column in range(columns))
        for row in range(rows)
    ]
    width = sum(column_widths)
    height = sum(row_heights)
    output = bytearray(width * height * 4)
    target_x = 0
    for column, column_width in enumerate(column_widths):
        target_y = 0
        for row, row_height in enumerate(row_heights):
            tile_width, tile_height, tile = tiles[column * rows + row]
            if len(tile) != tile_width * tile_height * 4:
                raise ValueError("HUD selector contains an invalid decoded tile")
            for tile_y in range(tile_height):
                source = tile_y * tile_width * 4
                target = ((target_y + tile_y) * width + target_x) * 4
                output[target : target + tile_width * 4] = tile[
                    source : source + tile_width * 4
                ]
            target_y += row_height
        target_x += column_width
    return width, height, bytes(output)


def rotate_rgba_pixels_clockwise(
    width: int, height: int, pixels: bytes, quarter_turns: int
) -> tuple[int, int, bytes]:
    """Rotate a decoded RGBA image in clockwise quarter turns."""

    turns = quarter_turns % 4
    current_width = width
    current_height = height
    current = pixels
    for _ in range(turns):
        rotated = bytearray(current_width * current_height * 4)
        next_width = current_height
        next_height = current_width
        for target_y in range(next_height):
            for target_x in range(next_width):
                source_x = target_y
                source_y = current_height - 1 - target_x
                source = (source_y * current_width + source_x) * 4
                target = (target_y * next_width + target_x) * 4
                rotated[target : target + 4] = current[source : source + 4]
        current_width = next_width
        current_height = next_height
        current = bytes(rotated)
    return current_width, current_height, current


def selector_preview_outputs(
    sprite: SpriteMetadata,
    preview_pixels: dict[int, tuple[int, int, bytes]],
) -> list[tuple[str, tuple[int, ...], int, int, bytes]]:
    """Build ordinary selector frames or reviewed presentation variants."""

    composition = SELECTOR_REVIEWED_COMPOSITIONS.get(sprite.selector)
    if composition:
        indices = composition["flat_indices"]
        if any(flat_index not in preview_pixels for flat_index in indices):
            return []
        width, height, pixels = compose_preview_tiles(
            [preview_pixels[flat_index] for flat_index in indices],
            composition["tile_columns"],
            composition["tile_rows"],
        )
        return [("", tuple(indices), width, height, pixels)]

    variants = SELECTOR_REVIEWED_VARIANTS.get(sprite.selector)
    if variants:
        outputs = []
        for variant in variants:
            flat_index = variant["flat_index"]
            if flat_index not in preview_pixels:
                continue
            width, height, pixels = preview_pixels[flat_index]
            width, height, pixels = rotate_rgba_pixels_clockwise(
                width,
                height,
                pixels,
                variant["clockwise_quarter_turns"],
            )
            outputs.append(
                (
                    f'-{variant["name"]}',
                    (flat_index,),
                    width,
                    height,
                    pixels,
                )
            )
        return outputs

    outputs = []
    frames = selector_frame_indices(sprite)
    for frame_index, indices in enumerate(frames):
        if any(index not in preview_pixels for index in indices):
            continue
        width, height, pixels = compose_preview_tiles(
            [preview_pixels[index] for index in indices],
            sprite.tile_columns,
            sprite.tile_rows,
        )
        suffix = f"-frame-{frame_index}" if len(frames) > 1 else ""
        outputs.append((suffix, tuple(indices), width, height, pixels))
    return outputs


def selector_preview_resource_groups(sprite: SpriteMetadata) -> list[list[int]]:
    composition = SELECTOR_REVIEWED_COMPOSITIONS.get(sprite.selector)
    if composition:
        return [composition["flat_indices"]]
    variants = SELECTOR_REVIEWED_VARIANTS.get(sprite.selector)
    if variants:
        return [[variant["flat_index"]] for variant in variants]
    return selector_frame_indices(sprite)


def selector_frame_indices(sprite: SpriteMetadata) -> list[list[int]]:
    frame_offsets = (
        range(ANIMATED_FRAME_COUNT)
        if sprite.selector == ANIMATED_SELECTOR
        else range(1)
    )
    tile_count = sprite.tile_columns * sprite.tile_rows
    return [
        list(
            range(
                sprite.flat_asset_index + frame_offset,
                sprite.flat_asset_index + frame_offset + tile_count,
            )
        )
        for frame_offset in frame_offsets
    ]


def named_exports(record: dict[str, Any]) -> list[dict[str, str]]:
    identity = record.get("reviewed_identity")
    if not identity:
        return []
    prefix = f"{record['selector']:04d}"
    return [
        {"source": path, "file": f"named/{prefix}-{identity['name']}{Path(path).stem[len(prefix):]}.png"}
        for path in record["preview_files"]
    ]


def preview_html(manifest: dict[str, Any], glyph_map: bytes) -> str:
    cards = []
    for record in manifest["selectors"]:
        image_class = ' class="variant"' if record.get("reviewed_variants") else ""
        normalized_height = 32 if record.get("reviewed_variants") else 64
        display_height = max(1, round(normalized_height * record["scale"]))
        images = "".join(
            f'<img{image_class} style="height:{display_height}px" '
            f'src="{html.escape(path)}" '
            f'alt="Selector {record["selector"]} preview">'
            for path in record["preview_files"]
        )
        if not images:
            unresolved = record.get("unresolved_resources", [])
            details = "<br>".join(
                f'flat {resource["flat_index"]}: '
                f'{html.escape(resource["reason"])}'
                for resource in unresolved
            )
            images = f'<div class="unresolved">raw only<br>{details}</div>'
        modes = ", ".join(record.get("preview_modes", ()))
        mode_line = f'<p class="mode">{html.escape(modes)}</p>' if modes else ""
        note = record.get("preview_note")
        note_line = f'<p class="note">{html.escape(note)}</p>' if note else ""
        identity = record.get("reviewed_identity")
        title = identity["display_name"] if identity else f'Selector {record["selector"]}'
        source_indices = sorted({index for frame in record.get("frames", [[record["flat_asset_index"]]]) for index in frame})
        source_indices = sorted(set(source_indices)
            | {item["flat_index"] for item in (record.get("reviewed_variants") or [])}
            | set((record.get("reviewed_composition") or {}).get("flat_indices", [])))
        category = "raw" if not record["preview_files"] else ("named" if identity else "numeric")
        exports = record.get("named_exports", [])
        downloads = " ".join(
            f'<a href="{html.escape(item["file"])}" download>PNG {index + 1}</a>'
            for index, item in enumerate(exports)
        ) or " ".join(
            f'<a href="{html.escape(path)}" download>PNG {index + 1}</a>'
            for index, path in enumerate(record["preview_files"])
        )
        source_downloads = " ".join(
            f'<a href="resources/{index:04d}.bin" download>flat {index}</a>'
            for index in source_indices
        )
        evidence = html.escape(identity["evidence"]) if identity else "Identity unresolved."
        reference = ""
        if identity and identity.get("reference_url"):
            reference = (
                f'<p><a href="{html.escape(identity["reference_url"], quote=True)}">'
                f'{html.escape(identity["reference_title"])}</a></p>'
            )
        search = " ".join([str(record["selector"]), f'{record["selector"]:04d}', title,
            identity["name"] if identity else "", " ".join(map(str, source_indices)),
            " ".join(record["preview_files"]), " ".join(item["file"] for item in exports)])
        cards.append(
            f'<article class="card" data-search="{html.escape(search.lower(), quote=True)}" data-kind="{category}">'
            f'<h2>{html.escape(title)}</h2>'
            f'<p class="source-id">Selector {record["selector"]}</p>'
            f'<div class="images">{images}</div>'
            f'<p>resource {record["flat_asset_index"]} · '
            f'{record["tile_columns"]}×{record["tile_rows"]} tiles · '
            f'scale {record["scale"]:g} · flags {record["flags_raw"]}</p>'
            f'{mode_line}{note_line}<p class="downloads">{downloads}</p>'
            f'<details><summary>Source and naming evidence</summary><p>{evidence}</p>{reference}<p>{source_downloads}</p></details>'
            '</article>'
        )
    glyphs = "".join(
        '<div class="glyph">'
        f'<span>{index}</span><b>&#x{value:02X};</b><code>{value:02X}</code>'
        '</div>'
        for index, value in enumerate(glyph_map)
    )
    return f"""<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>Conker US HUD/menu selector preview</title>
<style>
:root {{ color-scheme: dark; font-family: ui-monospace, SFMono-Regular, Menlo, monospace; }}
* {{ box-sizing: border-box; }}
[hidden] {{ display:none !important; }}
a {{ color:#a6dbff; }}
body {{ margin: 0; padding: 24px; background: #171a1f; color: #eef1f5; }}
h1 {{ margin: 0 0 8px; }} .summary {{ color: #aeb7c4; margin-bottom: 24px; }}
.grid {{ display: grid; grid-template-columns: repeat(auto-fill,minmax(min(100%,260px),1fr)); gap: 12px; }}
.card {{ min-width:0; overflow-wrap:anywhere; background: #232830; border: 1px solid #3b4350; border-radius: 8px; padding: 12px; }}
.card h2 {{ font-size: 14px; margin: 0 0 10px; }}
.card p {{ color: #b9c2ce; font-size: 11px; margin: 10px 0 0; }}
.card .identity {{ color: #f5df59; font-weight: 700; }}
.card .mode {{ color: #8ed7a6; }} .card .note {{ color: #f1c66d; }}
.images {{ min-height: 96px; display: flex; flex-wrap: wrap; gap: 5px; align-items: center;
  padding: 8px; background-color: #cbd0d6;
  background-image: linear-gradient(45deg,#9da4ac 25%,transparent 25%),linear-gradient(-45deg,#9da4ac 25%,transparent 25%),linear-gradient(45deg,transparent 75%,#9da4ac 75%),linear-gradient(-45deg,transparent 75%,#9da4ac 75%);
  background-size: 16px 16px; background-position: 0 0,0 8px,8px -8px,-8px 0; }}
.images img {{ max-width:100%; image-rendering: pixelated; width: auto; object-fit: contain; }}
.unresolved {{ color: #5d220d; background: #ffd6c5; padding: 15px; text-align: center; width: 100%; font-size: 11px; }}
.glyphs {{ display: grid; grid-template-columns: repeat(auto-fill,minmax(72px,1fr)); gap: 6px; margin: 12px 0 28px; }}
.glyph {{ display: grid; grid-template-columns: 1fr 1fr 1fr; align-items: center; background: #232830; padding: 7px; }}
.glyph span,.glyph code {{ color: #9fa9b7; font-size: 10px; }} .glyph b {{ font-size: 20px; text-align: center; }}
.toolbar {{ display:flex; flex-wrap:wrap; align-items:end; gap:12px; margin:24px 0 12px; }}
.toolbar label {{ display:grid; gap:6px; font-size:13px; }}
input,select {{ padding:10px; border:1px solid #647185; border-radius:5px; background:#232830; color:#fff; max-width:100%; font:inherit; }}
input {{ width:340px; }} .card details {{ margin-top:12px; font-size:11px; color:#c6d0dc; }}
.downloads {{ display:flex; gap:12px; flex-wrap:wrap; }}
.regions {{ display:grid; grid-template-columns:repeat(auto-fit,minmax(96px,1fr)); gap:10px; margin-top:10px; }}
.region {{ display:grid; gap:5px; font-size:11px; }}
.regions .images {{ min-height:64px; justify-content:center; padding:6px; }}
.regions img {{ width:48px; height:48px; }}
@media(max-width:600px) {{ body {{ padding:16px; }} h1 {{ font-size:25px; }} .toolbar label {{ width:100%; }} input,select {{ width:100%; }} }}
</style>
</head>
<body>
<h1>HUD &amp; menu artwork</h1>
<p><a href="preview-manifest.json" download>Download source manifest</a></p>
<p class="summary">{manifest['previewable_selector_count']} of {manifest['selector_count']} selectors have defensible previews. All selector images use the renderer’s RGBA32 dimensions and TMEM row layout. Runtime resource IDs preserve empty table slots.</p>
<p class="summary">{len(manifest.get("additional_artwork", []))} additional artwork groups include logos, controller buttons and labels outside the HUD selector table; {manifest.get("additional_region_count", 0)} small icons also have individual PNG downloads.</p>
<p class="summary">Names describe visible artwork. They do not assign a gameplay action or screen. Numeric IDs, raw bytes and unresolved entries are retained.</p>
<details><summary>Glyph input map (metadata, not font bitmaps)</summary><div class="glyphs">{glyphs}</div></details>
<div class="toolbar"><label>Search artwork<input id="search" type="search" placeholder="Name, selector or flat resource ID"></label>
<label>Show<select id="filter"><option value="all">All artwork</option><option value="selectors">HUD selectors</option><option value="additional">Additional artwork</option><option value="named">Named artwork</option><option value="numeric">Unidentified artwork</option><option value="raw">Raw only</option></select></label></div>
<p id="result-count" role="status"></p><p id="empty" hidden>No artwork matches your search.</p>
<main class="grid">{''.join(cards)}{hud_additional_artwork.gallery_cards(manifest.get("additional_artwork", []))}</main>
<script>
const search = document.querySelector('#search'), filter = document.querySelector('#filter');
const cards = [...document.querySelectorAll('.card')];
function update() {{
  const terms = search.value.toLowerCase().trim().split(/\\s+/).filter(Boolean);
  let count = 0;
  for (const card of cards) {{
    const show = (filter.value === 'all' || card.dataset.kind === filter.value || (filter.value === 'selectors' && card.dataset.kind !== 'additional') || (filter.value === 'named' && card.dataset.kind === 'additional')) && terms.every(term => card.dataset.search.includes(term));
    card.hidden = !show; count += Number(show);
  }}
  document.querySelector('#result-count').textContent = `${{count}} of ${{cards.length}} items`;
  document.querySelector('#empty').hidden = count !== 0;
}}
search.addEventListener('input', update); filter.addEventListener('change', update); update();
</script>
</body>
</html>
"""


def build_preview(
    family: HudAssetFamily,
    assets: dict[int, FlatHudAsset],
    output: Path,
    force: bool,
    include_additional: bool = False,
) -> dict[str, Any]:
    prepare_output(output, force)
    raw_directory = output / "resources"
    texture_directory = output / "textures"
    selector_directory = output / "selectors"
    raw_directory.mkdir()
    texture_directory.mkdir()
    selector_directory.mkdir()

    resource_records = []
    preview_pixels: dict[int, tuple[int, int, bytes]] = {}
    render_dimensions = resource_render_dimensions(family.sprites)
    preview_dimensions = resource_preview_dimensions(family.sprites)
    for flat_index in reachable_flat_indices(family.sprites):
        asset = assets[flat_index]
        raw_file = f"resources/{flat_index:04d}.bin"
        (output / raw_file).write_bytes(asset.data)
        texture_file = None
        width, nominal_height = preview_dimensions[flat_index]
        renderer_width, renderer_height = render_dimensions.get(
            flat_index, (None, None)
        )
        status = "raw-size-is-not-row-complete-rgba32"
        decoded_height = None
        bytes_used = 0
        trailing_bytes = len(asset.data)
        texture_format = None
        row_layout = None
        raw_only_reason = REVIEWED_RAW_ONLY_FLAT_INDICES.get(flat_index)
        try:
            preview = resource_preview_image(
                flat_index, asset.data, width, nominal_height
            )
        except ValueError:
            pass
        else:
            if preview is not None:
                decoded_height = preview.height
                bytes_used = preview.bytes_used
                texture_format = preview.texture_format
                row_layout = preview.row_layout
                status = preview.status
                preview_pixels[flat_index] = (
                    preview.width,
                    preview.height,
                    preview.pixels,
                )
                texture_file = (
                    f"textures/{flat_index:04d}.{preview.texture_format}.png"
                )
                (output / texture_file).write_bytes(
                    texture_base.encode_rgba_png(
                        preview.width, preview.height, preview.pixels
                    )
                )
                trailing_bytes = len(asset.data) - bytes_used
            elif raw_only_reason:
                status = "reviewed-raw-only-unresolved"
        resource_records.append(
            {
                "flat_index": flat_index,
                "rom_start": f"0x{asset.rom_start:X}",
                "rom_end": f"0x{asset.rom_end:X}",
                "decoded_size": len(asset.data),
                "sha1": hashlib.sha1(asset.data).hexdigest(),
                "raw_file": raw_file,
                "status": status,
                "preview_format": texture_format,
                "row_layout": row_layout,
                "raw_only_reason": raw_only_reason,
                "texture_file": texture_file,
                "renderer_width": renderer_width,
                "renderer_height": renderer_height,
                "preview_source_width": width,
                "preview_source_height": nominal_height,
                "preview_width": width if texture_file else None,
                "preview_height": decoded_height,
                "bytes_used_by_preview": bytes_used,
                "trailing_raw_bytes": trailing_bytes,
            }
        )

    selector_records = []
    for sprite in family.sprites:
        preview_files = []
        unresolved_sizes: set[int] = set()
        unresolved_resources = []
        preview_modes = []
        frames = selector_frame_indices(sprite)
        resource_groups = selector_preview_resource_groups(sprite)
        for indices in resource_groups:
            unresolved_sizes.update(
                len(assets[index].data)
                for index in indices
                if index not in preview_pixels
            )
            unresolved_resources.extend(
                {
                    "flat_index": index,
                    "decoded_size": len(assets[index].data),
                    "reason": REVIEWED_RAW_ONLY_FLAT_INDICES.get(
                        index, "no defensible row-complete preview contract"
                    ),
                }
                for index in indices
                if index not in preview_pixels
                and not any(
                    record["flat_index"] == index for record in unresolved_resources
                )
            )
            if any(index not in preview_pixels for index in indices):
                continue
            preview_modes.extend(
                mode
                for index in indices
                for mode in (
                    next(
                        record["status"]
                        for record in resource_records
                        if record["flat_index"] == index
                    ),
                )
                if mode not in preview_modes
            )
        for suffix, _indices, width, height, pixels in selector_preview_outputs(
            sprite, preview_pixels
        ):
            preview_file = f"selectors/{sprite.selector:04d}{suffix}.png"
            (output / preview_file).write_bytes(
                texture_base.encode_rgba_png(width, height, pixels)
            )
            preview_files.append(preview_file)
        selector_records.append(
            {
                "selector": sprite.selector,
                "flat_asset_index": sprite.flat_asset_index,
                "tile_columns": sprite.tile_columns,
                "tile_rows": sprite.tile_rows,
                "scale": sprite.scale,
                "flags_raw": sprite.flags_raw,
                "frames": frames,
                "preview_files": preview_files,
                "unresolved_sizes": sorted(unresolved_sizes),
                "unresolved_resources": unresolved_resources,
                "preview_modes": preview_modes,
                "preview_note": SELECTOR_PREVIEW_NOTES.get(sprite.selector),
                "reviewed_identity": SELECTOR_REVIEWED_IDENTITIES.get(
                    sprite.selector
                ),
                "reviewed_variants": SELECTOR_REVIEWED_VARIANTS.get(
                    sprite.selector
                ),
                "reviewed_composition": SELECTOR_REVIEWED_COMPOSITIONS.get(
                    sprite.selector
                ),
            }
        )

    (output / "named").mkdir()
    for record in selector_records:
        record["named_exports"] = named_exports(record)
        for item in record["named_exports"]:
            (output / item["file"]).write_bytes((output / item["source"]).read_bytes())
    additional_artwork = (hud_additional_artwork.write_preview(assets, output)
        if include_additional else [])
    previewable = sum(bool(record["preview_files"]) for record in selector_records)
    manifest = {
        "schema_version": 1,
        "family": "hud-menu-selector-preview",
        "additional_artwork": additional_artwork,
        "additional_artwork_count": len(additional_artwork),
        "additional_region_count": sum(len(record.get("regions", [])) for record in additional_artwork),
        "additional_png_count": len(additional_artwork) + sum(len(record.get("regions", [])) for record in additional_artwork),
        "additional_resource_count": len(hud_additional_artwork.RESOURCE_IDS) if include_additional else 0,
        "resource_identity": RUNTIME_FLAT_IDENTITY,
        "default_row_layout": texture_base.ROW_LAYOUT_TMEM,
        "source_origin": HUD_SOURCE_ORIGIN,
        "preview_origin": HUD_PREVIEW_ORIGIN,
        "default_tile_format": "rgba32",
        "default_tile_width": SPRITE_TILE_WIDTH,
        "default_tile_height": SPRITE_TILE_HEIGHT,
        "small_tile_width": SMALL_SPRITE_TILE_WIDTH,
        "small_tile_height": SMALL_SPRITE_TILE_HEIGHT,
        "resource_count": len(resource_records),
        "previewable_resource_count": len(preview_pixels),
        "raw_only_resource_count": len(resource_records) - len(preview_pixels),
        "selector_count": len(selector_records),
        "named_selector_count": sum(bool(record["reviewed_identity"]) for record in selector_records),
        "named_png_count": sum(len(record["named_exports"]) for record in selector_records),
        "previewable_selector_count": previewable,
        "raw_only_selector_count": len(selector_records) - previewable,
        "resources": resource_records,
        "selectors": selector_records,
        "limitations": [
            "Row-complete short payloads are previewed at their encoded height without padding; the raw file remains authoritative.",
            "Resource IDs follow the runtime compressed-size table, preserving empty slots; physical stream ordinals are different IDs.",
            "All current selector sources use their code-selected dimensions and RGBA32 TMEM layout without per-resource exceptions.",
            "Artwork names are visual identifications; runtime use remains unproven. Unidentified selectors retain numeric names.",
            "This preview does not claim complete named menu screens or final runtime placements.",
        ],
    }
    (output / "preview-manifest.json").write_text(
        json.dumps(manifest, indent=2) + "\n", encoding="utf-8"
    )
    (output / "index.html").write_text(
        preview_html(manifest, family.glyph_map), encoding="utf-8"
    )
    return manifest


def verify_preview(
    family: HudAssetFamily,
    assets: dict[int, FlatHudAsset],
    preview_directory: Path,
    include_additional: bool = False,
) -> tuple[int, int]:
    manifest_path = preview_directory / "preview-manifest.json"
    if not manifest_path.is_file() or not (preview_directory / "index.html").is_file():
        raise ValueError("HUD selector preview manifest or index.html is missing")
    manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
    if manifest.get("resource_identity") != RUNTIME_FLAT_IDENTITY:
        raise ValueError("HUD resource identity space is stale")
    additional_artwork = manifest.get("additional_artwork", [])
    if include_additional:
        hud_additional_artwork.verify_preview(assets, preview_directory, additional_artwork)
    elif additional_artwork:
        raise ValueError("Unexpected additional artwork in selector-only preview")
    expected_additional_count = len(hud_additional_artwork.ARTWORK) if include_additional else 0
    expected_additional_resources = len(hud_additional_artwork.RESOURCE_IDS) if include_additional else 0
    expected_regions = sum(len(regions) for regions in hud_additional_artwork.REGIONS.values()) if include_additional else 0
    if (manifest.get("additional_artwork_count") != expected_additional_count
            or manifest.get("additional_region_count") != expected_regions
            or manifest.get("additional_png_count") != expected_additional_count + expected_regions
            or manifest.get("additional_resource_count") != expected_additional_resources):
        raise ValueError("Additional artwork counts are stale")
    expected_indices = reachable_flat_indices(family.sprites)
    resources = manifest.get("resources")
    if not isinstance(resources, list) or [record.get("flat_index") for record in resources] != list(expected_indices):
        raise ValueError("HUD preview resource inventory does not match selector spans")
    preview_pixels: dict[int, tuple[int, int, bytes]] = {}
    render_dimensions = resource_render_dimensions(family.sprites)
    preview_dimensions = resource_preview_dimensions(family.sprites)
    for record in resources:
        flat_index = record["flat_index"]
        asset = assets[flat_index]
        raw_file = preview_directory / record["raw_file"]
        if raw_file.read_bytes() != asset.data:
            raise ValueError(f"HUD raw resource {flat_index} is not byte-identical")
        if (record["decoded_size"] != len(asset.data)
                or record["sha1"] != hashlib.sha1(asset.data).hexdigest()
                or record["rom_start"] != f"0x{asset.rom_start:X}"
                or record["rom_end"] != f"0x{asset.rom_end:X}"):
            raise ValueError(f"HUD resource {flat_index} provenance is stale")
        texture_file = record.get("texture_file")
        width, nominal_height = preview_dimensions[flat_index]
        renderer_width, renderer_height = render_dimensions.get(
            flat_index, (None, None)
        )
        try:
            preview = resource_preview_image(
                flat_index, asset.data, width, nominal_height
            )
        except ValueError:
            if texture_file is not None:
                raise ValueError(f"HUD resource {flat_index} has a guessed PNG")
            continue
        if preview is None:
            expected_raw_reason = REVIEWED_RAW_ONLY_FLAT_INDICES.get(flat_index)
            expected_raw = {
                "status": "reviewed-raw-only-unresolved",
                "preview_format": None,
                "row_layout": None,
                "raw_only_reason": expected_raw_reason,
                "texture_file": None,
                "preview_width": None,
                "preview_height": None,
                "bytes_used_by_preview": 0,
                "trailing_raw_bytes": len(asset.data),
            }
            if any(record.get(key) != value for key, value in expected_raw.items()):
                raise ValueError(f"HUD raw-only resource {flat_index} metadata is stale")
            continue
        if not texture_file:
            raise ValueError(f"HUD resource {flat_index} is missing its PNG preview")
        expected_geometry = {
            "renderer_width": renderer_width,
            "renderer_height": renderer_height,
            "preview_source_width": width,
            "preview_source_height": nominal_height,
            "preview_width": preview.width,
            "preview_height": preview.height,
            "bytes_used_by_preview": preview.bytes_used,
            "trailing_raw_bytes": len(asset.data) - preview.bytes_used,
            "preview_format": preview.texture_format,
            "row_layout": preview.row_layout,
            "status": preview.status,
            "raw_only_reason": None,
        }
        if any(record.get(key) != value for key, value in expected_geometry.items()):
            raise ValueError(f"HUD resource {flat_index} geometry is stale")
        decoded = texture_base.decode_rgba_png_pixels(
            (preview_directory / texture_file).read_bytes(),
            preview.width,
            preview.height,
        )
        if decoded != preview.pixels:
            raise ValueError(f"HUD resource {flat_index} PNG does not match its source")
        preview_pixels[flat_index] = (
            preview.width,
            preview.height,
            preview.pixels,
        )

    selectors = manifest.get("selectors")
    if not isinstance(selectors, list) or len(selectors) != len(family.sprites):
        raise ValueError("HUD preview selector inventory is incomplete")
    previewable = 0
    for sprite, record in zip(family.sprites, selectors, strict=True):
        frames = selector_frame_indices(sprite)
        expected_metadata = {
            "selector": sprite.selector,
            "frames": frames,
            "flat_asset_index": sprite.flat_asset_index,
            "tile_columns": sprite.tile_columns,
            "tile_rows": sprite.tile_rows,
            "scale": sprite.scale,
            "flags_raw": sprite.flags_raw,
        }
        if any(record.get(key) != value for key, value in expected_metadata.items()):
            raise ValueError(f"HUD selector {sprite.selector} preview metadata is stale")
        expected_unresolved = []
        expected_modes = []
        for indices in selector_preview_resource_groups(sprite):
            frame_is_previewable = all(index in preview_pixels for index in indices)
            for index in indices:
                if index not in preview_pixels and not any(
                    item["flat_index"] == index for item in expected_unresolved
                ):
                    expected_unresolved.append(
                        {
                            "flat_index": index,
                            "decoded_size": len(assets[index].data),
                            "reason": REVIEWED_RAW_ONLY_FLAT_INDICES.get(
                                index, "no defensible row-complete preview contract"
                            ),
                        }
                    )
                resource_status = next(
                    item["status"]
                    for item in resources
                    if item["flat_index"] == index
                )
                if frame_is_previewable and resource_status not in expected_modes:
                    expected_modes.append(resource_status)
        if record.get("unresolved_sizes") != sorted({item["decoded_size"] for item in expected_unresolved}):
            raise ValueError(f"HUD selector {sprite.selector} unresolved sizes are stale")
        if record.get("unresolved_resources") != expected_unresolved:
            raise ValueError(f"HUD selector {sprite.selector} unresolved metadata is stale")
        if record.get("preview_modes") != expected_modes:
            raise ValueError(f"HUD selector {sprite.selector} preview modes are stale")
        if record.get("preview_note") != SELECTOR_PREVIEW_NOTES.get(sprite.selector):
            raise ValueError(f"HUD selector {sprite.selector} preview note is stale")
        if record.get("reviewed_identity") != SELECTOR_REVIEWED_IDENTITIES.get(
            sprite.selector
        ):
            raise ValueError(f"HUD selector {sprite.selector} identity is stale")
        if record.get("reviewed_variants") != SELECTOR_REVIEWED_VARIANTS.get(
            sprite.selector
        ):
            raise ValueError(f"HUD selector {sprite.selector} variants are stale")
        if record.get("reviewed_composition") != SELECTOR_REVIEWED_COMPOSITIONS.get(
            sprite.selector
        ):
            raise ValueError(f"HUD selector {sprite.selector} composition is stale")
        expected_files = []
        for suffix, _indices, width, height, pixels in selector_preview_outputs(
            sprite, preview_pixels
        ):
            relative = f"selectors/{sprite.selector:04d}{suffix}.png"
            decoded = texture_base.decode_rgba_png_pixels(
                (preview_directory / relative).read_bytes(), width, height
            )
            if decoded != pixels:
                raise ValueError(f"HUD selector {sprite.selector} PNG is stale")
            expected_files.append(relative)
        if record.get("preview_files") != expected_files:
            raise ValueError(f"HUD selector {sprite.selector} preview file list is stale")
        expected_exports = named_exports(record)
        if record.get("named_exports") != expected_exports:
            raise ValueError(f"HUD selector {sprite.selector} named exports are stale")
        for item in expected_exports:
            if (preview_directory / item["file"]).read_bytes() != (preview_directory / item["source"]).read_bytes():
                raise ValueError(f"HUD selector {sprite.selector} named PNG is stale")
        previewable += bool(expected_files)
    if manifest.get("previewable_resource_count") != len(preview_pixels) or manifest.get("previewable_selector_count") != previewable:
        raise ValueError("HUD preview summary counts are stale")
    if manifest.get("named_selector_count") != sum(bool(record["reviewed_identity"]) for record in selectors) or manifest.get("named_png_count") != sum(len(named_exports(record)) for record in selectors):
        raise ValueError("HUD named export counts are stale")
    if (preview_directory / "index.html").read_text(encoding="utf-8") != preview_html(manifest, family.glyph_map):
        raise ValueError("HUD gallery HTML is stale")
    return len(preview_pixels), previewable


def extract(
    profile: str, rom_argument: Path | None, output: Path, force: bool
) -> dict[str, Any]:
    rom_path, source_order, digest, family = load_profile_hud_assets(
        profile, rom_argument
    )
    prepare_output(output, force)
    (output / "glyph-map.bin").write_bytes(family.glyph_map)
    (output / "sprite-metadata.bin").write_bytes(family.sprite_table)
    manifest = build_manifest(profile, rom_path, source_order, digest, family)
    (output / "manifest.json").write_text(
        json.dumps(manifest, indent=2, ensure_ascii=False) + "\n", encoding="utf-8"
    )
    return manifest


def verify_extraction(
    profile: str, rom_argument: Path | None, input_directory: Path
) -> tuple[int, int]:
    rom_path, source_order, digest, family = load_profile_hud_assets(
        profile, rom_argument
    )
    manifest_path = input_directory / "manifest.json"
    if not manifest_path.is_file():
        raise ValueError(f"HUD manifest does not exist: {display_path(manifest_path)}")
    manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
    expected = build_manifest(profile, rom_path, source_order, digest, family)
    if manifest != expected:
        raise ValueError("HUD manifest does not match the code-backed ROM extraction")
    if (input_directory / "glyph-map.bin").read_bytes() != family.glyph_map:
        raise ValueError("extracted HUD glyph map is not byte-identical")
    if (input_directory / "sprite-metadata.bin").read_bytes() != family.sprite_table:
        raise ValueError("extracted HUD sprite metadata is not byte-identical")
    return len(family.glyph_map), len(family.sprites)


def default_output(profile: str) -> Path:
    return ROOT / "build" / "assets" / "interface" / profile


def default_preview_output(profile: str) -> Path:
    return default_output(profile) / "preview"


def parser() -> argparse.ArgumentParser:
    result = argparse.ArgumentParser(description=__doc__)
    commands = result.add_subparsers(dest="command", required=True)
    for name in ("survey", "extract", "preview", "verify"):
        command = commands.add_parser(name)
        command.add_argument("--profile", default="us")
        command.add_argument("--rom", type=Path)
        if name in ("extract", "preview"):
            command.add_argument("--output", type=Path)
            command.add_argument("--force", action="store_true")
        elif name == "verify":
            command.add_argument("--input", type=Path)
    return result


def main() -> int:
    args = parser().parse_args()
    try:
        if args.command == "survey":
            _, _, _, family = load_profile_hud_assets(args.profile, args.rom)
            flags = Counter(sprite.flags_raw for sprite in family.sprites)
            print(
                f"{args.profile} HUD/menu metadata: {len(family.glyph_map)} table glyphs "
                f"plus space, {len(family.sprites)} sprite selectors, "
                f"{len(reachable_flat_indices(family.sprites))} reachable flat assets "
                f"from {len({sprite.flat_asset_index for sprite in family.sprites})} "
                f"base indices, flags {dict(sorted(flags.items()))}"
            )
        elif args.command == "extract":
            output = args.output or default_output(args.profile)
            manifest = extract(args.profile, args.rom, output, args.force)
            print(
                f"Extracted {manifest['glyph_map']['size']} table glyphs and "
                f"{manifest['sprite_metadata']['record_count']} sprite selectors to "
                f"{display_path(output)}"
            )
        elif args.command == "preview":
            _, _, _, family = load_profile_hud_assets(args.profile, args.rom)
            assets = load_reachable_flat_assets(args.profile, args.rom, family.sprites,
                extra_resource_ids=hud_additional_artwork.RESOURCE_IDS)
            output = args.output or default_preview_output(args.profile)
            manifest = build_preview(family, assets, output, args.force, include_additional=True)
            print(
                f"Previewed {manifest['previewable_selector_count']} of "
                f"{manifest['selector_count']} HUD/menu selectors from "
                f"{manifest['previewable_resource_count']} reviewed resource windows; "
                f"{manifest['additional_artwork_count']} additional artwork previews and "
                f"{manifest['additional_region_count']} icon crops; "
                f"{manifest['raw_only_resource_count']} resources remain raw-only in "
                f"{display_path(output)}"
            )
        else:
            input_directory = args.input or default_output(args.profile)
            glyph_count, sprite_count = verify_extraction(
                args.profile, args.rom, input_directory
            )
            preview_directory = input_directory / "preview"
            preview_summary = ""
            if preview_directory.is_dir():
                _, _, _, family = load_profile_hud_assets(args.profile, args.rom)
                assets = load_reachable_flat_assets(
                    args.profile, args.rom, family.sprites,
                    extra_resource_ids=hud_additional_artwork.RESOURCE_IDS
                )
                resource_count, selector_count = verify_preview(
                    family, assets, preview_directory, include_additional=True
                )
                preview_summary = (
                    f"; {resource_count} PNG resources and {selector_count} "
                    f"selector previews and {len(hud_additional_artwork.ARTWORK)} additional groups "
                    f"with {sum(len(regions) for regions in hud_additional_artwork.REGIONS.values())} icon crops verified"
                )
            print(
                f"Verified {args.profile} HUD/menu metadata: {glyph_count} table glyphs, "
                f"{sprite_count} sprite selectors, byte-identical{preview_summary}"
            )
    except (OSError, ValueError, json.JSONDecodeError) as error:
        raise SystemExit(f"error: {error}") from error
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
