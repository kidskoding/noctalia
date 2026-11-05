#include "pipewire/audio_glyphs.h"

#include <cstdio>
#include <cstring>
#include <print>

namespace {

  bool expectGlyph(const char* actual, const char* expected, const char* message) {
    if (std::strcmp(actual, expected) != 0) {
      std::println(stderr, "audio_glyphs_test: {}: expected '{}', got '{}'", message, expected, actual);
      return false;
    }
    return true;
  }

} // namespace

int main() {
  bool ok = true;

  ok = expectGlyph(audioVolumeGlyph(0.0F, false, false), "volume-mute", "zero speaker volume") && ok;
  ok = expectGlyph(audioVolumeGlyph(0.004F, false, false), "volume-mute", "speaker volume displayed as 0%") && ok;
  ok = expectGlyph(audioVolumeGlyph(0.006F, false, false), "volume-low", "speaker volume displayed above 0%") && ok;
  ok = expectGlyph(audioVolumeGlyph(0.39F, false, false), "volume-low", "low speaker volume") && ok;
  ok = expectGlyph(audioVolumeGlyph(0.4F, false, false), "volume-high", "high speaker volume threshold") && ok;
  ok = expectGlyph(audioVolumeGlyph(0.8F, true, false), "volume-mute", "muted speaker") && ok;
  ok = expectGlyph(audioVolumeGlyph(0.0F, false, true), "microphone-mute", "zero microphone volume") && ok;
  ok = expectGlyph(audioVolumeGlyph(0.8F, true, true), "microphone-mute", "muted microphone") && ok;
  ok = expectGlyph(audioVolumeGlyph(0.8F, false, false, true), "headphones", "headphones output") && ok;
  ok = expectGlyph(audioVolumeGlyph(0.8F, true, false, true), "headphones-off", "muted headphones") && ok;
  ok = expectGlyph(audioVolumeGlyph(0.0F, false, false, true), "headphones-off", "zero headphones volume") && ok;
  ok = expectGlyph(audioVolumeGlyph(0.0F, true, true, true), "microphone-mute", "muted mic ignores headphones") && ok;

  return ok ? 0 : 1;
}
