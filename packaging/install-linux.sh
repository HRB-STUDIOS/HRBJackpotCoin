#!/usr/bin/env bash
set -euo pipefail

APP_ID="hrbjackpotcoin"
INSTALL_DIR="/opt/${APP_ID}"
ICON_NAME="${APP_ID}"
DESKTOP_ID="${APP_ID}.desktop"

# Where the script is run from (your repo root or wherever this installer lives)
SRC_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")"/.. && pwd)"

require_root() {
  if [[ $EUID -ne 0 ]]; then
    echo "Please run as root: sudo $0"
    exit 1
  fi
}

install_files() {
  echo "[1/5] Installing launcher to ${INSTALL_DIR}"
  mkdir -p "$INSTALL_DIR"
  install -m 0755 "$SRC_DIR/hrb-launcher.sh" "$INSTALL_DIR/"

  echo "[2/5] Installing icons"
  mkdir -p /usr/share/icons/hicolor/256x256/apps
  mkdir -p /usr/share/icons/hicolor/128x128/apps
  # Use what you have; missing sizes are fine.
  if [[ -f "$SRC_DIR/assets/hrbjackpotcoin.png" ]]; then
    install -m 0644 "$SRC_DIR/assets/hrbjackpotcoin.png" /usr/share/icons/hicolor/256x256/apps/${ICON_NAME}.png
  fi
  if [[ -f "$SRC_DIR/assets/hrbjackpotcoin-128.png" ]]; then
    install -m 0644 "$SRC_DIR/assets/hrbjackpotcoin-128.png" /usr/share/icons/hicolor/128x128/apps/${ICON_NAME}.png
  fi
  gtk-update-icon-cache -q /usr/share/icons/hicolor 2>/dev/null || true

  echo "[3/5] Installing desktop entry"
  cat >/usr/share/applications/${DESKTOP_ID} <<DESK
[Desktop Entry]
Type=Application
Name=HRB Jackpot Coin
Comment=Create Spend & Mining wallets, back them up, and launch HRB
Exec=${INSTALL_DIR}/hrb-launcher.sh
TryExec=${INSTALL_DIR}/hrb-launcher.sh
Terminal=false
Icon=${ICON_NAME}
Categories=Finance;Network;
StartupNotify=true
DESK
  update-desktop-database /usr/share/applications 2>/dev/null || true

  echo "[4/5] Seed Desktop shortcut for NEW users"
  mkdir -p /etc/skel/Desktop
  cp -f /usr/share/applications/${DESKTOP_ID} "/etc/skel/Desktop/HRB Jackpot Coin.desktop"
  chmod +x "/etc/skel/Desktop/HRB Jackpot Coin.desktop"

  echo "[5/5] Place Desktop shortcut for EXISTING users"
  place_shortcut() {
    local user="$1" home="$2"
    local desktop="${home}/Desktop"
    mkdir -p "$desktop"
    cp -f /usr/share/applications/${DESKTOP_ID} "${desktop}/HRB Jackpot Coin.desktop"
    chmod +x "${desktop}/HRB Jackpot Coin.desktop"
    chown -R "${user}:${user}" "${desktop}/HRB Jackpot Coin.desktop" 2>/dev/null || true
    # Mark as trusted (GNOME’s “Allow Launching”)
    sudo -u "${user}" gio set "${desktop}/HRB Jackpot Coin.desktop" metadata::trusted true 2>/dev/null || true
  }

  # root
  place_shortcut root /root 2>/dev/null || true

  # normal users under /home
  for home in /home/*; do
    [[ -d "$home" ]] || continue
    user="$(basename "$home")"
    place_shortcut "$user" "$home"
  done

  echo "Done. Look for 'HRB Jackpot Coin' in the Applications menu and on each Desktop."
}

require_root
install_files
