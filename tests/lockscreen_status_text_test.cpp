#include "dbus/network/network_types.h"
#include "shell/lockscreen/lockscreen_status_text.h"

#include <cstdio>
#include <print>
#include <string>

namespace {

  bool expectText(const std::string& actual, const std::string& expected, const char* message) {
    if (actual != expected) {
      std::println(stderr, "lockscreen_status_text_test: {}: expected '{}', got '{}'", message, expected, actual);
      return false;
    }
    return true;
  }

} // namespace

int main() {
  using namespace lockscreen_status_text;
  bool ok = true;

  ok = expectText(batteryTimeLabel(12000, false), "3h 20m left", "hours and minutes left") && ok;
  ok = expectText(batteryTimeLabel(3900, true), "1h 05m to full", "charging pads minutes") && ok;
  ok = expectText(batteryTimeLabel(2700, false), "45m left", "minutes only") && ok;
  ok = expectText(batteryTimeLabel(0, false), "", "unknown estimate") && ok;
  ok = expectText(batteryTimeLabel(-5, true), "", "negative estimate") && ok;

  ok = expectText(notificationCountLabel(0, false), "All caught up", "no unread") && ok;
  ok = expectText(notificationCountLabel(3, false), "3 new", "some unread") && ok;
  ok = expectText(notificationCountLabel(150, false), "99+ new", "many unread") && ok;
  ok = expectText(notificationCountLabel(3, true), "Do not disturb", "dnd wins") && ok;

  NetworkState wifi;
  wifi.kind = NetworkConnectivity::Wireless;
  wifi.connected = true;
  wifi.wirelessEnabled = true;
  wifi.ssid = "eduroam";
  wifi.signalStrength = 82;
  ok = expectText(networkValueLabel(wifi), "eduroam", "wifi ssid") && ok;
  ok = expectText(networkCaptionLabel(wifi), "Signal 82%", "wifi signal") && ok;
  wifi.vpnConnected = true;
  ok = expectText(networkCaptionLabel(wifi), "Signal 82% · VPN", "wifi with vpn") && ok;
  wifi.ssid.clear();
  ok = expectText(networkValueLabel(wifi), "Wi-Fi", "hidden ssid") && ok;

  NetworkState wired;
  wired.kind = NetworkConnectivity::Wired;
  wired.connected = true;
  wired.interfaceName = "enp5s0";
  ok = expectText(networkValueLabel(wired), "Wired", "wired value") && ok;
  ok = expectText(networkCaptionLabel(wired), "enp5s0", "wired caption") && ok;

  NetworkState off;
  off.kind = NetworkConnectivity::None;
  off.wirelessEnabled = false;
  ok = expectText(networkValueLabel(off), "Wi-Fi off", "radio off") && ok;
  ok = expectText(networkCaptionLabel(off), "No connection", "radio off caption") && ok;
  off.wirelessEnabled = true;
  ok = expectText(networkValueLabel(off), "Offline", "offline value") && ok;

  return ok ? 0 : 1;
}
