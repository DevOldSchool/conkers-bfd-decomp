"""Bounded initial-ROM MIPS argument analysis for discovery, not admission.

Join disagreement becomes unknown. Calls kill caller-saved registers and stack
memory; unsupported instructions stop that analysis instead of guessing writes.
Candidate prologues are search boundaries only. ROM data may be mutated at run
time, so even a constant table result still requires consumer review.
"""
from collections import deque
import struct


def const(value):
    return ('constant', value & 0xFFFFFFFF)


def signed(value, bits=32):
    return (value & ((1 << (bits - 1)) - 1)) - (value & (1 << (bits - 1)))


def add(value, amount):
    if value is None:
        return None
    return ('stack', value[1] + amount) if value[0] == 'stack' else const(value[1] + amount)


def merge(left, right):
    return ([a if a == b else None for a, b in zip(left[0], right[0])],
            {k: v for k, v in left[1].items() if right[1].get(k) == v})


def analyze(code, base, data, data_base, *, max_steps=20000):
    words = struct.unpack(f'>{len(code) // 4}I', code[:len(code) // 4 * 4])
    registers = [None] * 32
    registers[0], registers[29] = const(0), ('stack', 0)
    states = {0: (registers, {})}
    pending = deque([0])
    calls, loads, barriers = {}, {}, set()
    steps = 0

    def load(state, address, width, sign=False):
        if address is None:
            return None
        kind, offset = address
        if offset % width:
            return None
        if kind == 'stack':
            cells = [state[1].get(offset + i) for i in range(width)]
            if any(c is None for c in cells):
                return None
            value = int.from_bytes(bytes(cells), 'big')
        elif data_base <= offset and offset + width <= data_base + len(data):
            value = int.from_bytes(data[offset - data_base:offset - data_base + width], 'big')
        else:
            return None
        return const(signed(value, width * 8) if sign else value)

    def step(index, incoming):
        regs, stack = list(incoming[0]), dict(incoming[1])
        word = words[index]
        op, rs, rt, rd, shift, fn = word >> 26, word >> 21 & 31, word >> 16 & 31, word >> 11 & 31, word >> 6 & 31, word & 63
        imm = signed(word & 0xFFFF, 16)
        a, b = regs[rs], regs[rt]
        av = a[1] if a and a[0] == 'constant' else None
        bv = b[1] if b and b[0] == 'constant' else None
        if op == 0 and fn in (0, 2, 3):
            regs[rd] = const(bv << shift if fn == 0 else (bv if fn == 2 else signed(bv)) >> shift) if bv is not None else None
        elif op == 0 and fn in (0x21, 0x23, 0x24, 0x25, 0x26, 0x27, 0x2A, 0x2B):
            result = None
            if fn == 0x21:
                result = add(a, bv) if bv is not None else add(b, av) if av is not None else None
            elif fn == 0x23 and bv is not None:
                result = add(a, -bv)
            elif fn == 0x25 and (av == 0 or bv == 0):
                result = b if av == 0 else a
            elif av is not None and bv is not None:
                result = const({0x24: lambda: av & bv, 0x25: lambda: av | bv,
                    0x26: lambda: av ^ bv, 0x27: lambda: ~(av | bv),
                    0x2A: lambda: int(signed(av) < signed(bv)), 0x2B: lambda: int(av < bv)}[fn]())
            regs[rd] = result
        elif op == 9:
            regs[rt] = add(a, imm)
        elif op == 15:
            regs[rt] = const((word & 0xFFFF) << 16)
        elif op in (10, 11, 12, 13, 14):
            regs[rt] = const({10: lambda: int(signed(av) < imm), 11: lambda: int(av < (imm & 0xFFFFFFFF)),
                12: lambda: av & (word & 0xFFFF), 13: lambda: av | (word & 0xFFFF),
                14: lambda: av ^ (word & 0xFFFF)}[op]()) if av is not None else None
        elif op in (32, 33, 35, 36, 37):
            width = {32: 1, 33: 2, 35: 4, 36: 1, 37: 2}[op]
            address = add(a, imm)
            regs[rt] = load((regs, stack), address, width, op in (32, 33))
            if regs[rt] and address and address[0] == 'constant':
                loads[(index, address[1], width)] = {'pc': f'0x{base + index * 4:08X}',
                    'address': f'0x{address[1]:08X}', 'width': width, 'value': regs[rt][1]}
        elif op in (40, 41, 43, 49, 53, 57, 61):
            # FP loads do not write integer state. FP stores invalidate bytes.
            if op not in (49, 53):
                width = {40: 1, 41: 2, 43: 4, 57: 4, 61: 8}[op]
                address = add(a, imm)
                if address and address[0] == 'stack':
                    for i in range(width):
                        at = address[1] + i
                        stack.pop(at, None)
                        if bv is not None and op in (40, 41, 43):
                            stack[at] = (bv >> ((width - 1 - i) * 8)) & 255
                elif address is None:
                    stack.clear()  # An unknown pointer may alias the template.
                elif address[0] == 'constant' and data_base <= address[1] < data_base + len(data):
                    raise ValueError('ROM data write needs mutation analysis')
        elif op == 17 and rs in (0, 2):
            regs[rt] = None  # mfc1/cfc1
        elif op == 17 and (rs in (4, 6) or rs >= 16):
            pass  # FPU transfer/arithmetic, no integer destination
        elif op == 0 and fn in (0x10, 0x12):
            regs[rd] = None  # HI/LO are deliberately not propagated.
        elif op == 0 and fn in (0x11, 0x13, 0x18, 0x19, 0x1A, 0x1B):
            pass
        else:
            raise ValueError(f'unsupported instruction at 0x{base + index * 4:08X}: {word:08X}')
        regs[0] = const(0)
        return regs, stack

    def enqueue(index, state):
        if not 0 <= index < len(words):
            return
        joined = merge(states[index], state) if index in states else state
        if index not in states or joined != states[index]:
            states[index] = joined
            pending.append(index)

    while pending and steps < max_steps:
        index = pending.popleft()
        incoming = states[index]
        word = words[index]
        op, rs, rt, fn = word >> 26, word >> 21 & 31, word >> 16 & 31, word & 63
        steps += 1
        try:
            is_call = op == 3 or (op == 0 and fn == 9)
            is_jump = op == 2 or (op == 0 and fn == 8)
            branch = op in (1, 4, 5, 6, 7, 20, 21, 22, 23) or (op == 17 and rs == 8)
            if not (is_call or is_jump or branch):
                enqueue(index + 1, step(index, incoming))
                continue
            if index + 1 >= len(words):
                raise ValueError('missing delay slot')
            slot_input = incoming
            if is_call:
                if op == 0 and word >> 11 & 31 != 31:
                    raise ValueError('nonstandard link register')
                linked = list(incoming[0])
                linked[31] = const(base + index * 4 + 8)
                slot_input = linked, incoming[1]
            delayed = step(index + 1, slot_input)
            if is_call:
                # Apply the delay slot before observing argument/template values.
                calls[index] = merge(calls[index], delayed) if index in calls else delayed
                regs = list(delayed[0])
                for register in (*range(1, 16), 24, 25, 26, 27, 31):
                    regs[register] = None
                enqueue(index + 2, (regs, {}))
            elif is_jump:
                if op == 2:
                    target = ((base + index * 4 + 4) & 0xF0000000) | ((word & 0x3FFFFFF) << 2)
                    enqueue((target - base) // 4, delayed)
                elif rs != 31:
                    raise ValueError('indirect jump needs consumer review')
            else:
                if op == 1 and rt not in (0, 1, 2, 3):
                    raise ValueError('link or unsupported regimm branch')
                target = index + 1 + signed(word & 0xFFFF, 16)
                a, b = incoming[0][rs], incoming[0][rt]
                condition = None
                if op in (4, 5, 20, 21) and a is not None and b is not None:
                    condition = (a == b) if op in (4, 20) else (a != b)
                likely = op in (20, 21, 22, 23) or op == 1 and rt in (2, 3) or op == 17 and bool(rt & 2)
                if condition is not False:
                    enqueue(target, delayed)
                if condition is not True:
                    enqueue(index + 2, incoming if likely else delayed)
        except ValueError as error:
            barriers.add(str(error))
    if pending:
        barriers.add('instruction budget exhausted')
    # Incomplete control flow can bypass a join. Discard its argument claims.
    if barriers:
        calls = {}
    results = {}
    for index, (regs, stack) in calls.items():
        row = {'arguments': {f'a{i}': {'kind': regs[4+i][0], 'value': regs[4+i][1]}
                            for i in range(4) if regs[4+i] is not None}}
        if regs[4] and regs[4][0] == 'stack':
            fields = {}
            for name, offset, width in (('flags', 0x50, 4), ('selector', 0x56, 2)):
                value = load((regs, stack), add(regs[4], offset), width)
                if value is not None:
                    fields[name] = value[1]
            row['template_fields'] = fields
        count = regs[7]
        if regs[5] and count and count[0] == 'constant' and 0 < count[1] <= 64:
            values = [load((regs, stack), add(regs[5], i * 4), 4) for i in range(count[1])]
            if all(value is not None for value in values):
                row['initial_array_words'] = [v[1] for v in values]
        results[f'0x{base + index * 4:08X}'] = row
    return {'status': 'incomplete' if barriers else 'analyzed', 'steps': steps,
            'barriers': sorted(barriers), 'calls': results, 'initial_rom_loads': list(loads.values())}
