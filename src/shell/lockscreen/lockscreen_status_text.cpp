#include "shell/lockscreen/lockscreen_status_text.h"

#include "dbus/network/network_types.h"

#include <format>

namespace lockscreen_status_text {

  std::string batteryTimeLabel(std::int64_t seconds, bool charging) {
    if (seconds <= 0) {
      return {};
    }
    const std::int64_t totalMinutes = seconds / 60;
    const std::int64_t hours = totalMinutes / 60;
    const std::int64_t minutes = totalMinutes % 60;
    const char* suffix = charging ? "to full" : "left";
    if (hours == 0) {
      return std::format("{}m {}", minutes, suffix);
    }
    return std::format("{}h {:02}m {}", hours, minutes, suffix);
  }

  std::string notificationCountLabel(std::size_t unread, bool doNotDisturb) {
    if (doNotDisturb) {
      return "Do not disturb";
    }
    if (unread == 0) {
      return "All caught up";
    }
    if (unread > 99) {
      return "99+ new";
    }
    return std::format("{} new", unread);
  }

  std::string networkValueLabel(const NetworkState& state) {
    if (state.connected && state.kind == NetworkConnectivity::Wireless) {
      return state.ssid.empty() ? "Wi-Fi" : state.ssid;
    }
    if (state.connected && state.kind == NetworkConnectivity::Wired) {
      return "Wired";
    }
    if (!state.wirelessEnabled) {
      return "Wi-Fi off";
    }
    return "Offline";
  }

  std::string networkCaptionLabel(const NetworkState& state) {
    std::string caption;
    if (state.connected && state.kind == NetworkConnectivity::Wireless) {
      caption = std::format("Signal {}%", state.signalStrength);
    } else if (state.connected && state.kind == NetworkConnectivity::Wired) {
      caption = state.interfaceName;
    } else {
      return "No connection";
    }
    if (state.vpnConnected) {
      caption += " · VPN";
    }
    return caption;
  }

} // namespace lockscreen_status_text
