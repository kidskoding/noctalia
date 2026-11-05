#pragma once

// Canonical bar/OSD glyph for a sink (isInput == false) or source (isInput == true) given its
// volume and effective mute. Single source of the speaker mute->slashed-icon rule and the
// volume-level thresholds so the bar widget and the OSD can never map the same state to different
// icons.
// An output on headphones shows the headphones glyph instead of the speaker level, and
// headphones-off instead of volume-mute when muted or at 0%.
[[nodiscard]] const char* audioVolumeGlyph(float volume, bool muted, bool isInput, bool headphones = false);
