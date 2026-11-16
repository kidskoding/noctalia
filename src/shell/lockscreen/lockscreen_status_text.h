#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

struct NetworkState;

namespace lockscreen_status_text {

  // Empty when UPower has no estimate yet (seconds <= 0).
  [[nodiscard]] std::string batteryTimeLabel(std::int64_t seconds, bool charging);
  [[nodiscard]] std::string notificationCountLabel(std::size_t unread, bool doNotDisturb);
  [[nodiscard]] std::string networkValueLabel(const NetworkState& state);
  [[nodiscard]] std::string networkCaptionLabel(const NetworkState& state);

} // namespace lockscreen_status_text
