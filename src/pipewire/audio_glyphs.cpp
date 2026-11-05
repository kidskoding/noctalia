#include "pipewire/audio_glyphs.h"

#include <algorithm>
#include <cmath>

namespace {

  [[nodiscard]] int displayedVolumePercent(float volume) {
    return static_cast<int>(std::round(std::max(0.0F, volume) * 100.0F));
  }

} // namespace

const char* audioVolumeGlyph(float volume, bool muted, bool isInput, bool headphones) {
  if (isInput) {
    return (muted || displayedVolumePercent(volume) == 0) ? "microphone-mute" : "microphone";
  }
  if (muted || displayedVolumePercent(volume) == 0) {
    return headphones ? "headphones-off" : "volume-mute";
  }
  if (headphones) {
    return "headphones";
  }
  if (volume < 0.4F) {
    return "volume-low";
  }
  return "volume-high";
}
