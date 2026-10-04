'use strict';

const $ = (id) => document.getElementById(id);
const pad = (id) => String(id).padStart(4, '0');
const duration = (seconds) => { const rounded = Math.round(seconds); return `${Math.floor(rounded / 60)}:${String(rounded % 60).padStart(2, '0')}`; };
let manifest, selected, sampleManifest;
let drafts = {};
let storageKey;

function message(text) { $('status').textContent = text; }
function safeLink(url, title) {
  const link = document.createElement('a');
  const parsed = new URL(url, location.href);
  const localFile = location.protocol === 'file:' && parsed.protocol === 'file:';
  if (!localFile && !['http:', 'https:'].includes(parsed.protocol)) throw new Error('Unsupported link');
  link.href = parsed.href;
  link.textContent = title;
  link.target = '_blank';
  link.rel = 'noopener noreferrer';
  return link;
}
function confidenceLabel(value) {
  return {identified: 'Identified by contributor', tentative: 'Tentative', unidentified: 'Unidentified'}[value] || 'Unspecified';
}
function trackName(track) { return track.album_title || track.name || 'Unknown sequence'; }
function renderTracks() {
  const search = $('search').value.toLowerCase();
  const records = manifest.sequences.filter((track) =>
    (!$('confidence').value || track.confidence === $('confidence').value) &&
    (!$('category').value || (track.category || 'Unassigned') === $('category').value) &&
    [pad(track.index), track.name, track.album_title, track.album_variant, ...(track.aliases || []), ...(track.album_matches || []).map((item) => item.title), track.note, track.category, drafts[track.index]?.name].join(' ').toLowerCase().includes(search));
  $('tracks').replaceChildren();
  $('count').textContent = `${records.length} / ${manifest.sequences.length}`;
  for (const track of records) {
    const button = document.createElement('button');
    button.type = 'button';
    button.className = 'track';
    button.setAttribute('aria-pressed', String(selected?.index === track.index));
    const title = document.createElement('span');
    title.className = 'track-title';
    const id = document.createElement('span');
    id.className = 'track-id';
    id.textContent = pad(track.index);
    title.append(id, drafts[track.index]?.name || trackName(track));
    const meta = document.createElement('span');
    meta.className = 'track-meta';
    meta.textContent = `${track.album_title ? `${track.album_variant} · Album match: ${track.album_match_confidence} · ` : ''}${confidenceLabel(track.confidence)} · ${track.category || 'Unassigned'} · ${duration(track.duration_seconds)}${!track.audible ? ' · Silent' : ''}${drafts[track.index] ? ' · Draft saved' : ''}`;
    button.append(title, meta);
    button.addEventListener('click', () => selectTrack(track));
    $('tracks').append(button);
  }
  if (!records.length) $('tracks').textContent = 'No sequences match these filters.';
}
function selectTrack(track) {
  selected = track;
  $('player').pause();
  $('sample-player').pause();
  $('player').src = track.file;
  $('identity').textContent = `SEQUENCE ${pad(track.index)} / BANK 0x17 · ENTRY 3`;
  $('title').textContent = drafts[track.index]?.name || trackName(track);
  $('album-name').textContent = track.album_title ? `${track.album_variant} · Album match: ${track.album_match_confidence}. Contributor alias: ${track.name || 'Unidentified'}. ${track.album_match_note}` : '';
  $('details').textContent = `${confidenceLabel(track.confidence)} · ${track.category || 'Unassigned'} · ${duration(track.duration_seconds)} · ${track.mapped_notes}/${track.note_count} notes mapped · ${track.loop_markers} sequence loop markers · ${track.loop_jumps || 0} bounded loop jumps`;
  $('note').textContent = track.note || 'No contributor listening note.';
  $('downloads').replaceChildren();
  for (const [title, url] of [['WAV', track.file], ['MIDI', track.midi_file || `midi/${pad(track.index)}.mid`], ['CSeq source', track.source_file || `sequences/${pad(track.index)}.cseq`]]) {
    const link = safeLink(url, title);
    link.download = '';
    $('downloads').append(link, '  ');
  }
  $('evidence').replaceChildren();
  const caution = document.createElement('p');
  caution.textContent = 'Contributor’s automated recording correlations; not independently confirmed by ear.';
  $('evidence').append(caution);
  for (const ref of track.heard_at || []) {
    const p = document.createElement('p');
    p.append(safeLink(ref.url, `${ref.reference} at ${duration(ref.start_seconds)} (render offset ${duration(ref.sequence_offset_seconds)})`));
    $('evidence').append(p);
  }
  $('comparisons').replaceChildren();
  const comparisons = [...manifest.album_reference.comparisons, ...(manifest.album_reference.additional_comparisons || [])].filter((item) => item.sequence_ids.includes(track.index));
  for (const comparison of comparisons) {
    const p = document.createElement('p');
    p.textContent = `${comparison.status}: ${comparison.title}. ${comparison.basis}`;
    if (comparison.reference_url) p.append(' ', safeLink(comparison.reference_url, 'Album reference'));
    $('comparisons').append(p);
  }
  if (!comparisons.length) $('comparisons').textContent = 'No album correspondence established for this ID. Use the reference albums below to compare.';
  const draft = drafts[track.index];
  $('draft-name').value = draft ? draft.name : trackName(track);
  $('draft-confidence').value = draft ? draft.confidence : 'tentative';
  $('draft-note').value = draft ? draft.note : '';
  for (const id of ['play', 'save', 'clear', 'draft-name', 'draft-confidence', 'draft-note']) $(id).disabled = false;
  message(track.audible ? 'Ready. Playback uses the extracted game samples.' : 'This single-pass render is silent; source and MIDI remain available.');
  renderTracks();
}
function persistDrafts() {
  try { localStorage.setItem(storageKey, JSON.stringify(drafts)); return true; }
  catch { $('storage-notice').textContent = 'Browser storage is unavailable. Drafts exist only in this open page; prepare and copy JSON before leaving.'; message('Browser storage is unavailable. Prepare and copy drafts before leaving.'); return false; }
}
$('draft').addEventListener('submit', (event) => {
  event.preventDefault();
  if (!selected) return;
  drafts[selected.index] = {index: selected.index, source_sha1: selected.source_sha1, name: $('draft-name').value.trim(), confidence: $('draft-confidence').value, note: $('draft-note').value.trim()};
  if (persistDrafts()) message(`Draft saved for ${pad(selected.index)}. Export to keep a reviewable copy.`);
  renderTracks();
});
$('clear').addEventListener('click', () => {
  if (!selected) return;
  delete drafts[selected.index];
  const stored = persistDrafts();
  selectTrack(selected);
  message(stored ? 'Draft removed; contributor label restored.' : 'Browser storage is unavailable. Export remaining drafts before leaving.');
});
$('export').addEventListener('click', () => {
  const data = {schema_version: 1, family: 'conker-soundtrack-naming-drafts', profile: 'us', normalized_rom_sha1: manifest.normalized_rom_sha1, notice: 'User listening drafts, not verified source names or album matches.', sequences: Object.values(drafts).sort((a, b) => a.index - b.index)};
  const json = JSON.stringify(data, null, 2) + '\n';
  $('export-json').value = json;
  $('export-preview').hidden = false;
  $('export-preview').open = true;
  message(`Prepared ${data.sequences.length} naming draft(s). Copy the JSON or choose Download prepared JSON.`);
});
$('download-export').addEventListener('click', () => {
  const json = $('export-json').value;
  if (!json) return;
  const url = URL.createObjectURL(new Blob([json], {type: 'application/json'}));
  const link = document.createElement('a');
  link.href = url; link.download = 'soundtrack-naming-drafts.json'; link.click();
  setTimeout(() => URL.revokeObjectURL(url), 1000);
  message('Download requested. The prepared JSON remains available to copy.');
});
$('play').addEventListener('click', async () => {
  try { await $('player').play(); message(`Playing sequence ${pad(selected.index)}.`); }
  catch { message('Audio playback failed. Reload or open the WAV link.'); }
});
$('player').addEventListener('error', () => message('Audio failed to load. Keep the preview folder together and check that the WAV file exists.'));
$('sample-play').addEventListener('click', async () => {
  try {
    const index = Number($('sample-id').value);
    const sample = sampleManifest.samples.find((item) => item.index === index);
    if (!Number.isInteger(index) || !sample) throw new Error('Choose a valid sample ID.');
    $('player').pause();
    $('sample-player').src = `${sampleManifest.base_path || "samples/"}${sample.file}`;
    $('sample-details').textContent = `Sample ${pad(index)} · ${sample.duration_seconds.toFixed(3)} seconds · ${sample.sample_rate} Hz mono · ${sample.loop ? 'Loop metadata retained; WAV plays once' : 'No sample loop'}`;
  } catch (error) { message(error.message); }
});
for (const id of ['search', 'confidence', 'category']) $(id).addEventListener('input', () => { if (manifest) renderTracks(); });
async function initialize() {
  const embedded = JSON.parse($('preview-data').textContent);
  manifest = embedded.manifest;
  sampleManifest = embedded.samples;
  storageKey = `conker-soundtrack-drafts-v1-${manifest.normalized_rom_sha1}`;
  try {
    const saved = JSON.parse(localStorage.getItem(storageKey) || '{}');
    for (const track of manifest.sequences) {
      const draft = saved[track.index];
      if (draft && draft.index === track.index && draft.source_sha1 === track.source_sha1 && typeof draft.name === 'string' && typeof draft.note === 'string' && ['identified', 'tentative', 'unidentified'].includes(draft.confidence)) drafts[track.index] = draft;
    }
  } catch { $('storage-notice').textContent = 'Browser storage is unavailable. Drafts exist only in this open page; prepare and copy JSON before leaving.'; }
  if (location.protocol === 'file:') $('storage-notice').textContent += ' Direct-file storage varies by browser and file location; keep an exported copy before moving the folder.';
  const c = manifest.coverage;
  $('coverage').textContent = `${c.sequences} extracted sequences · ${c.audible} audible renders · ${c.samples.toLocaleString()} separate samples · ${c.confidence.identified} contributor identifications / ${c.confidence.tentative} tentative / ${c.confidence.unidentified} unknown`;
  $('notice').textContent = manifest.label_notice;
  for (const text of manifest.limitations) { const li = document.createElement('li'); li.textContent = text; $('limitations').append(li); }
  for (const category of [...new Set(manifest.sequences.map((t) => t.category || 'Unassigned'))].sort()) {
    const option = document.createElement('option'); option.textContent = category; $('category').append(option);
  }
  $('reference-notice').textContent = manifest.album_reference.notice;
  $('albums').className = 'album-grid';
  const streamPlayers = new Map();
  for (const album of [...manifest.album_reference.albums, ...(manifest.album_reference.additional_albums || [])]) {
    const section = document.createElement('section'); const title = document.createElement('h3'); title.append(safeLink(album.url, `${album.title} · ${album.tracks.length} tracks`)); section.append(title);
    if (album.coverage) {
      const coverage = document.createElement('p');
      coverage.className = 'muted';
      coverage.textContent = `${album.coverage.matched} verified matches · ${album.coverage.tentative} tentative · ${album.coverage.unresolved} unresolved`;
      section.append(coverage);
    }
    const list = document.createElement('ol');
    for (const track of album.tracks) {
      const li = document.createElement('li');
      const detail = document.createElement('details');
      const heading = document.createElement('summary');
      heading.textContent = `${track.title} · ${duration(track.duration_seconds)} · ${track.review?.status || 'Unreviewed'}`;
      detail.append(heading);
      if (track.review) {
        const note = document.createElement('p'); note.className = 'muted'; note.textContent = track.review.reason;
        detail.append(note, safeLink(track.review.reference_url, 'Reference recording'));
        const buttons = document.createElement('div'); buttons.className = 'candidate-buttons';
        for (const match of track.review.matches) {
          const button = document.createElement('button'); button.type = 'button';
          button.textContent = `${match.kind === 'sequence' ? 'Sequence' : 'MP3'} ${pad(match.index)}`;
          button.title = `${match.role} · ${match.confidence}`;
          button.addEventListener('click', () => {
            if (match.kind === 'sequence') {
              $('search').value = ''; $('confidence').value = ''; $('category').value = '';
              selectTrack(manifest.sequences.find((item) => item.index === match.index));
              $('listening').scrollIntoView({block: 'start'}); $('play').focus();
            } else {
              const player = streamPlayers.get(match.index);
              if (!player) return;
              player.closest('details').open = true;
              player.scrollIntoView({block: 'center'}); player.focus();
            }
          });
          buttons.append(button);
        }
        detail.append(buttons);
        if (!track.review.matches.length) {
          const unresolved = document.createElement('p');
          unresolved.textContent = 'No accepted candidate. Similarity leads are retained in the comparison metadata.';
          detail.append(unresolved);
        }
      }
      li.append(detail); list.append(li);
    }
    section.append(list); $('albums').append(section);
  }
  $('sample-id').max = c.samples - 1;
  for (const stream of manifest.music_streams || []) {
    const section = document.createElement('section');
    const title = document.createElement('h3'); title.textContent = `MP3 ${pad(stream.index)} · ${stream.name}`;
    const note = document.createElement('p'); note.textContent = `${stream.variant || 'Music candidate'} · Album match: ${stream.confidence}. ${stream.status}. ${stream.basis}`;
    const audio = document.createElement('audio'); audio.id = `stream-${pad(stream.index)}`; audio.setAttribute('aria-label', `MP3 ${pad(stream.index)} ${stream.name}`); audio.tabIndex = 0; streamPlayers.set(stream.index, audio); audio.controls = true; audio.preload = 'none'; audio.src = stream.file;
    audio.addEventListener('play', () => { $('player').pause(); $('sample-player').pause(); for (const other of $('music-streams').querySelectorAll('audio')) if (other !== audio) other.pause(); });
    $('player').addEventListener('play', () => audio.pause());
    $('sample-player').addEventListener('play', () => audio.pause());
    section.append(title, note, audio, safeLink(stream.reference_url, 'Album reference'));
    $('music-streams').append(section);
  }
  if (!(manifest.music_streams || []).length) $('music-streams').textContent = 'No MP3 candidates included. Build with --mp3-input to include nominated streams from the same ROM.';
  for (const experiment of manifest.experiments || []) {
    const section = document.createElement('section');
    const title = document.createElement('h3'); title.textContent = `Sequence ${pad(experiment.sequence_index)} · ${experiment.title}`;
    const note = document.createElement('p'); note.textContent = experiment.note;
    const audio = document.createElement('audio'); audio.controls = true; audio.preload = 'none'; audio.src = experiment.file;
    audio.setAttribute('aria-label', `Sequence ${pad(experiment.sequence_index)} ${experiment.title}`);
    audio.addEventListener('play', () => { for (const other of document.querySelectorAll('audio')) if (other !== audio) other.pause(); });
    for (const other of document.querySelectorAll('audio')) other.addEventListener('play', () => audio.pause());
    section.append(title, note, audio); $('experiments').append(section);
  }
  for (const capture of manifest.native_captures || []) {
    const section = document.createElement('section');
    const title = document.createElement('h3'); title.textContent = capture.title;
    const note = document.createElement('p'); note.textContent = capture.note;
    const audio = document.createElement('audio'); audio.controls = true; audio.preload = 'none'; audio.src = capture.file;
    audio.setAttribute('aria-label', capture.title);
    audio.addEventListener('play', () => { for (const other of document.querySelectorAll('audio')) if (other !== audio) other.pause(); });
    for (const other of document.querySelectorAll('audio')) other.addEventListener('play', () => audio.pause());
    section.append(title, note, audio); $('native-captures').append(section);
  }
  for (const song of manifest.reconstructions || []) {
    const instrumental = manifest.sequences.find((track) => track.index === song.sequence_index);
    if (!instrumental) throw new Error('Reconstruction instrumental is missing.');
    const section = document.createElement('section');
    const title = document.createElement('h3'); title.textContent = song.title;
    const note = document.createElement('p'); note.textContent = song.note; note.className = 'muted';
    const pair = document.createElement('div'); pair.className = 'reconstruction-pair';
    for (const [label, file, seconds] of [
      [`${song.title} · full reconstruction`, song.file, song.duration_seconds],
      [instrumental.album_title || 'Instrumental', instrumental.file, instrumental.duration_seconds]
    ]) {
      const card = document.createElement('section');
      const heading = document.createElement('h4'); heading.textContent = `${label} · ${duration(seconds)}`;
      const audio = document.createElement('audio'); audio.controls = true; audio.preload = 'metadata'; audio.src = file;
      audio.setAttribute('aria-label', label);
      audio.addEventListener('play', () => { for (const other of document.querySelectorAll('audio')) if (other !== audio) other.pause(); });
      for (const other of document.querySelectorAll('audio')) other.addEventListener('play', () => audio.pause());
      const button = document.createElement('button'); button.type = 'button'; button.textContent = `Play ${label}`;
      button.addEventListener('click', async () => {
        try { await audio.play(); message(`Playing ${label}.`); }
        catch (error) { message(`Playback failed: ${error.message}`); }
      });
      const link = safeLink(file, 'Open WAV');
      card.append(heading, audio, button, document.createTextNode(' '), link); pair.append(card);
    }
    section.append(title, pair, note); $('reconstructions').append(section);
  }
  const hasFullSongs = (manifest.reconstructions || []).length > 0;
  $('full-songs').hidden = !hasFullSongs;
  $('full-navigation').hidden = !hasFullSongs;
  $('native-notice').textContent = manifest.native_review_notice || '';
  $('native-section').hidden = !(manifest.native_captures || []).length;
  $('experiment-section').hidden = !(manifest.experiments || []).length;
  renderTracks();
  const requested = Number(new URLSearchParams(location.search).get('sequence') || 1);
  selectTrack(manifest.sequences.find((t) => t.index === requested) || manifest.sequences[0]);
}
initialize().catch((error) => { $('coverage').textContent = 'Preview could not load.'; message(error.message); });
