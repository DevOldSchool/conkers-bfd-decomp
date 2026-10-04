#!/usr/bin/env python3
"""Compare local recordings with aligned spectral windows, never infer identity.

Requires optional numpy, scipy and soundfile. Scores are not probabilities;
independent windows can select different offsets. Inspect the reported offsets
and durations before treating a result as evidence of a coherent arrangement.
"""
from __future__ import annotations

import argparse
import hashlib
import json
from math import gcd
from pathlib import Path

import numpy as np
import soundfile as sf
from scipy.fft import irfft, next_fast_len, rfft
from scipy.signal import resample_poly, stft

HOP = 2048 / 11025


def features(path: Path) -> np.ndarray:
    pcm, rate = sf.read(path, dtype="float32", always_2d=True)
    pcm = pcm.mean(axis=1)
    divisor = gcd(rate, 11025)
    pcm = resample_poly(pcm, 11025 // divisor, rate // divisor)
    if len(pcm) < 2048:
        return np.zeros((61, 0), dtype=np.float32)
    frequencies, _, spectrum = stft(pcm, 11025, nperseg=2048, noverlap=1024, boundary=None)
    power = np.abs(spectrum) ** 2
    bands = []
    for note in range(36, 97):
        low = 440 * 2 ** ((note - 69 - 0.5) / 12)
        high = 440 * 2 ** ((note - 69 + 0.5) / 12)
        indices = np.where((frequencies >= low) & (frequencies < high))[0]
        bands.append(np.log1p(power[indices].sum(axis=0) * 10000))
    result = np.asarray(bands, dtype=np.float32)
    result -= result.mean(axis=0)
    result /= np.maximum(np.linalg.norm(result, axis=0), 1e-9)
    return result[:, :result.shape[1] // 2 * 2].reshape(61, -1, 2).mean(axis=2)


def compare(source: np.ndarray, reference: np.ndarray, seconds: float = 8) -> list[dict]:
    source, reference = np.asarray(source, dtype=np.float64), np.asarray(reference, dtype=np.float64)
    if not 1 <= seconds <= 30 or source.ndim != 2 or reference.ndim != 2 or source.shape[0] != reference.shape[0]:
        raise ValueError("matching fingerprint bands and a 1..30 second window are required")
    if not np.all(np.isfinite(source)) or not np.all(np.isfinite(reference)):
        raise ValueError("fingerprints must be finite")
    length = min(round(seconds / HOP), source.shape[1], reference.shape[1])
    if length < 4:
        return []
    size = next_fast_len(reference.shape[1] + length - 1)
    transform = rfft(reference, size, axis=1)
    padded = np.pad(reference, ((0, 0), (1, 0)))
    sums, squares = np.cumsum(padded, axis=1), np.cumsum(padded * padded, axis=1)
    variance = ((squares[:, length:] - squares[:, :-length]) -
                (sums[:, length:] - sums[:, :-length]) ** 2 / length).sum(axis=0)
    denominator = np.sqrt(np.maximum(variance, 1e-9))
    # Retain the original comparison sampling rule, including its terminal window.
    offsets = list(range(0, max(1, source.shape[1] - length + 1), max(1, length // 2)))
    offsets.append(source.shape[1] - length)
    windows = []
    for offset in offsets:
        chunk = source[:, offset:offset + length]
        chunk = chunk - chunk.mean(axis=1, keepdims=True)
        norm = np.linalg.norm(chunk)
        if norm < 1e-8:
            continue
        dot = irfft((transform * rfft(chunk[:, ::-1], size, axis=1)).sum(axis=0), size)[length - 1:reference.shape[1]]
        scores = dot / (norm * denominator)
        match = int(np.argmax(scores))
        windows.append({"score": round(float(np.clip(scores[match], -1, 1)), 6),
                        "source_seconds": round(offset * HOP, 4),
                        "reference_seconds": round(match * HOP, 4),
                        "seconds": round(length * HOP, 4)})
    return sorted(windows, key=lambda window: window["score"], reverse=True)


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", type=Path, required=True)
    parser.add_argument("--reference", type=Path, required=True)
    parser.add_argument("--seconds", type=float, default=8)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    if not 1 <= args.seconds <= 30:
        parser.error("window duration must be from 1 through 30 seconds")
    if args.output.exists():
        parser.error("output already exists; preserve earlier comparisons")
    windows = compare(features(args.source), features(args.reference), args.seconds)
    report = {"method": "61 semitone-band centred spectral fingerprints, 11025 Hz, hop 2048 samples",
              "notice": "Exploratory similarity, not calibrated identity confidence or an ear review; offsets may differ by window.",
              "source_sha1": hashlib.sha1(args.source.read_bytes()).hexdigest(),
              "reference_sha1": hashlib.sha1(args.reference.read_bytes()).hexdigest(),
              "window_seconds": args.seconds, "windows": windows,
              "median_best_window_score": float(np.median([w["score"] for w in windows])) if windows else None}
    args.output.parent.mkdir(parents=True, exist_ok=True)
    with args.output.open("x") as output:
        json.dump(report, output, indent=2)
        output.write("\n")
    print(json.dumps({"windows": len(windows), "best": windows[0] if windows else None,
                      "median_best_window_score": report["median_best_window_score"]}))


if __name__ == "__main__":
    main()
