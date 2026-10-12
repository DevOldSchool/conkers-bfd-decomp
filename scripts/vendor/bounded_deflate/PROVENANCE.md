# Bounded raw-DEFLATE encoder

The compression core (deflate.c, trees.c, bits.c and their headers) is
derived from GNU gzip 1.2.4 (18 August 1993), by Jean-loup Gailly and
contributors. Its GNU GPL version 2 or later license is retained in COPYING
and the original source notices. The standalone driver is part of this
GPL-covered utility. The utility runs as a separate process.

Original archive:
https://ftp.gnu.org/gnu/gzip/gzip-1.2.4.tar.gz

Archive SHA-256:
1ca41818a23c9c59ef1d5e1d00c0d5eaa2285d931c0fb059637d7c0cc02ad967

Changes:
- A standalone stdin/stdout driver emits raw DEFLATE without a gzip wrapper.
- longest_match bounds comparisons by the remaining valid input when it
  falls below MAX_MATCH. This removes lookahead into bytes beyond EOF.
- Compilation uses 16,384-token literal/distance buffers while retaining
  the default 15-bit hash table.
- Existing source copyright notices remain intact; trailing whitespace is normalized.

These settings come from independent ROM token diagnostics: excluded sprite
entries diverged only at their last match; larger models used a 16,383-token
full-block threshold and subsequent 4,096-token heuristic boundaries.
No original compressed bytes, token sequences, Huffman tables, or patch
masks are encoder inputs. Fresh typed assets are its sole input.

Read-only diagnostic format reference:
https://www.rfc-editor.org/rfc/rfc1951
