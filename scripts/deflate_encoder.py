"""Deterministic raw DEFLATE for the reviewed Conker asset compression profile.

Independently authored from RFC 1951 and compression diagnostics. Only decoded
input is accepted: no reference streams, token recipes, or patches are used.
"""
from bisect import bisect_right

# RFC 1951 section 3.2.5: code ranges, not an implementation-specific table.
LENGTH_BASE = (3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31,
               35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258)
LENGTH_EXTRA = (0,) * 8 + tuple(n for n in range(1, 6) for _ in range(4)) + (0,)
DISTANCE_BASE = (1, 2, 3, 4) + tuple((1 << n) + 1 + j * (1 << (n - 1))
                                    for n in range(2, 15) for j in range(2))
DISTANCE_EXTRA = (0,) * 4 + tuple(n for n in range(1, 14) for _ in range(2))
CODE_ORDER = (16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15)


class Bits:
    def __init__(self):
        self.output = bytearray()
        self.pending = self.width = 0

    def put(self, value, width):
        self.pending |= value << self.width
        self.width += width
        while self.width >= 8:
            self.output.append(self.pending & 255)
            self.pending >>= 8
            self.width -= 8

    def align(self):
        if self.width:
            self.put(0, 8 - self.width)


def codes(lengths):
    counts = [lengths.count(n) for n in range(16)]
    counts[0] = 0
    next_code, value = [0] * 16, 0
    for width in range(1, 16):
        value = (value + counts[width - 1]) << 1
        next_code[width] = value
    result = []
    for width in lengths:
        value = next_code[width] if width else 0
        next_code[width] += bool(width)
        reversed_bits = 0
        for _ in range(width):
            reversed_bits = (reversed_bits << 1) | (value & 1)
            value >>= 1
        result.append((reversed_bits, width))
    return result


def tree_lengths(frequencies, limit):
    """Build a binary Huffman tree, breaking weight ties by subtree height.

    Leaves enter the heap in symbol order. The right child wins equal heap
    comparisons; an equally ranked replacement stays at its current position.
    These deterministic ties are part of the byte-level compression profile.
    """
    weights = list(frequencies)
    count = len(weights)
    active = [i for i, weight in enumerate(weights) if weight]
    while len(active) < 2:
        symbol = (max(active, default=-1) + 1) if max(active, default=-1) < 2 else 0
        weights[symbol] = 1
        active.append(symbol)
    heights = [0] * (2 * count)
    parents = [-1] * (2 * count)
    heap = [None] + active

    def le(a, b):
        return (weights[a], heights[a]) <= (weights[b], heights[b])

    def sift(index):
        item = heap[index]
        while index * 2 < len(heap):
            child = index * 2
            if child + 1 < len(heap) and le(heap[child + 1], heap[child]):
                child += 1
            if le(item, heap[child]):
                break
            heap[index] = heap[child]
            index = child
        heap[index] = item

    for i in range(len(active) // 2, 0, -1):
        sift(i)
    removed = []
    while len(heap) > 2:
        first = heap[1]
        heap[1] = heap.pop()
        sift(1)
        second = heap[1]
        parent = len(weights)
        weights.append(weights[first] + weights[second])
        heights[parent] = max(heights[first], heights[second]) + 1
        parents[first] = parents[second] = parent
        removed.extend((first, second))
        heap[1] = parent
        sift(1)
    depths = [0] * len(weights)
    lengths = [0] * count
    histogram = [0] * (limit + 1)
    overflow = 0
    for node in reversed(removed):
        depth = depths[parents[node]] + 1
        if depth > limit:
            depth = limit
            overflow += 1
        depths[node] = depth
        if node < count:
            lengths[node] = depth
            histogram[depth] += 1
    if overflow:
        while overflow > 0:
            width = limit - 1
            while not histogram[width]:
                width -= 1
            histogram[width] -= 1
            histogram[width + 1] += 2
            histogram[limit] -= 1
            overflow -= 2
        leaves = iter(node for node in removed if node < count)
        for width in range(limit, 0, -1):
            for _ in range(histogram[width]):
                lengths[next(leaves)] = width
    return lengths


def length_runs(lengths):
    """RFC 1951 code-length run symbols, with runs restarted per alphabet."""
    result, at, previous = [], 0, -1
    while at < len(lengths):
        value = lengths[at]
        end = at + 1
        maximum = 138 if value == 0 else (6 if value == previous else 7)
        while end < len(lengths) and lengths[end] == value and end - at < maximum:
            end += 1
        run = end - at
        minimum = 3 if value == 0 or value == previous else 4
        if run < minimum:
            result.extend((value, 0, 0) for _ in range(run))
        elif value:
            if value != previous:
                result.append((value, 0, 0))
                run -= 1
            result.append((16, run - 3, 2))
        elif run <= 10:
            result.append((17, run - 3, 3))
        else:
            result.append((18, run - 11, 7))
        previous, at = value, end
    return result


def symbol(token):
    if isinstance(token, int):
        return token, 0, 0, 0, 0, 0
    length, distance = token
    lc = bisect_right(LENGTH_BASE, length) - 1
    dc = bisect_right(DISTANCE_BASE, distance) - 1
    return 257 + lc, length - LENGTH_BASE[lc], LENGTH_EXTRA[lc], dc, distance - DISTANCE_BASE[dc], DISTANCE_EXTRA[dc]


def blocks(data):
    """Lazy LZ77 parsing with a bounded 32K history and 16K token blocks."""
    heads = [-1] * 32768
    previous = [-1] * len(data)
    size = len(data)

    def insert(at):
        if at + 2 >= size:
            return -1
        key = ((data[at] << 10) ^ (data[at + 1] << 5) ^ data[at + 2]) & 32767
        candidate, heads[key] = heads[key], at
        previous[at] = candidate
        return candidate

    def match(at, candidate, best):
        found = -1
        lower = max(0, at - 32506)
        attempts = 32 if best >= 8 else 128
        maximum = min(258, size - at)
        while candidate > 0 and candidate >= lower and attempts:
            attempts -= 1
            if best < maximum and data[candidate:candidate + 2] == data[at:at + 2] and data[candidate + best] == data[at + best]:
                length = 2
                while length < maximum and data[candidate + length] == data[at + length]:
                    length += 1
                if length > best:
                    best, found = length, candidate
                    if length >= 128:
                        break
            candidate = previous[candidate]
            if candidate <= lower:
                break
        return best, found

    tokens, start, at, pending = [], 0, 0, False
    best, found = 2, -1
    distances = [0] * 30
    matches = 0
    slide = 0
    while at < size:
        if at >= slide + 65274:
            slide += 32768
        candidate = insert(at)
        last_length, last_found = best, found
        best = 2
        if candidate >= slide and candidate > 0 and at - candidate <= 32506 and last_length < 16:
            best, new_found = match(at, candidate, last_length)
            if new_found >= 0:
                found = new_found
            if best == 3 and at - found > 4096:
                best = 2
        # The heuristic measures input before consuming this token.
        # The emitted block boundary below still includes the complete match.
        estimate_at = at
        if last_length >= 3 and best <= last_length:
            distance = at - 1 - last_found
            tokens.append((last_length, distance))
            distances[bisect_right(DISTANCE_BASE, distance) - 1] += 1
            matches += 1
            for pos in range(at + 1, at + last_length - 1):
                insert(pos)
            at += last_length - 1
            best, pending = 2, False
        elif pending:
            tokens.append(data[at - 1])
            at += 1
        else:
            pending = True
            at += 1
            continue
        boundary = at - int(pending)
        flush = len(tokens) == 16383
        if len(tokens) % 4096 == 0:
            estimate = (len(tokens) * 8 + sum(n * (5 + DISTANCE_EXTRA[i]) for i, n in enumerate(distances))) >> 3
            flush |= matches < len(tokens) // 2 and estimate < (estimate_at - start) // 2
        if flush:
            yield tokens, start, boundary, start >= slide
            tokens, start, distances, matches = [], boundary, [0] * 30, 0
    if pending:
        tokens.append(data[-1])
    yield tokens, start, size, start >= slide


FIXED_LITERALS = [8] * 144 + [9] * 112 + [7] * 24 + [8] * 8
FIXED_DISTANCES = [5] * 30


def emit_block(writer, data, tokens, start, end, stored_available, final):
    symbols = [symbol(token) for token in tokens] + [(256, 0, 0, 0, 0, 0)]
    lf, df = [0] * 286, [0] * 30
    for lit, _, _, dist, _, _ in symbols:
        lf[lit] += 1
        if lit > 256:
            df[dist] += 1
    ll, dl = tree_lengths(lf, 15), tree_lengths(df, 15)
    nl = max(257, max(i for i, v in enumerate(ll) if v) + 1)
    nd = max(i for i, v in enumerate(dl) if v) + 1
    runs = length_runs(ll[:nl]) + length_runs(dl[:nd])
    cf = [0] * 19
    for sym, _, _ in runs:
        cf[sym] += 1
    cl = tree_lengths(cf, 7)
    nc = max(4, max(i for i, c in enumerate(CODE_ORDER) if cl[c]) + 1)
    extra = sum(le + de for _, _, le, _, _, de in symbols)
    fixed_bits = extra + sum(a * b for a, b in zip(lf, FIXED_LITERALS)) + sum(df) * 5
    dynamic_bits = extra + sum(a * b for a, b in zip(lf, ll)) + sum(a * b for a, b in zip(df, dl))
    dynamic_bits += 14 + 3 * nc + sum(cl[s] + n for s, _, n in runs)
    fixed_size, dynamic_size = (fixed_bits + 10) >> 3, (dynamic_bits + 10) >> 3
    if stored_available and end - start <= 65535 and end - start + 4 <= min(fixed_size, dynamic_size):
        writer.put(int(final), 3)
        writer.align()
        length = end - start
        writer.put(length, 16)
        writer.put(length ^ 65535, 16)
        writer.output.extend(data[start:end])
        return
    fixed = fixed_size <= dynamic_size
    writer.put(int(final) | (2 if fixed else 4), 3)
    if fixed:
        ll, dl = FIXED_LITERALS, FIXED_DISTANCES
    else:
        writer.put(nl - 257, 5)
        writer.put(nd - 1, 5)
        writer.put(nc - 4, 4)
        for c in CODE_ORDER[:nc]:
            writer.put(cl[c], 3)
        cc = codes(cl)
        for sym, value, width in runs:
            writer.put(*cc[sym])
            writer.put(value, width)
    lc, dc = codes(ll), codes(dl)
    for lit, value, width, dist, dvalue, dwidth in symbols:
        writer.put(*lc[lit])
        if lit > 256:
            writer.put(value, width)
            writer.put(*dc[dist])
            writer.put(dvalue, dwidth)


def encode(data):
    """Encode immutable bytes with the sole reviewed level-six profile."""
    if not isinstance(data, bytes):
        raise ValueError('DEFLATE input must be bytes')
    writer = Bits()
    iterator = iter(blocks(data))
    block = next(iterator)
    for following in iterator:
        emit_block(writer, data, *block, False)
        block = following
    emit_block(writer, data, *block, True)
    writer.align()
    return bytes(writer.output)
