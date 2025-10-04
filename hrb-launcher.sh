# Copyright (c) 2025 HRB Studios
# HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
# Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT

cat > /mnt/d/HRBJackpotCoin/hrb-launcher.sh <<'EOF'
#!/usr/bin/env bash
set -Eeuo pipefail

APP_ID=hrbjackpotcoin

# --- Where to find the binaries (Qt/daemon/cli) ---
# We try PATH first, then common build locations. You can hard-set HRB_ROOT if you want.
HRB_ROOT="${HRB_ROOT:-}"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
try_bins() {
  local n="$1"
  shift
  for p in "$@"; do
    [[ -x "$p" ]] && { echo "$p"; return 0; }
  done
  return 1
}
find_bin() {
  local name="$1"
  local p
  # from PATH
  p="$(command -v "$name" 2>/dev/null || true)"; [[ -n "$p" ]] && { echo "$p"; return; }
  # hints
  local hints=()
  [[ -n "$HRB_ROOT" ]] && hints+=("$HRB_ROOT")
  hints+=("$SCRIPT_DIR" "/mnt/d/HRBJackpotCoin" "$HOME/HRBJackpotCoin" "/usr/local" "/usr")
  for h in "${hints[@]}"; do
    case "$name" in
      hrbjackpotcoin-qt) p="$(try_bins "$name" "$h/src/qt/$name" "$h/bin/$name")" || true ;;
      *)                  p="$(try_bins "$name" "$h/src/$name"    "$h/bin/$name")" || true ;;
    esac
    [[ -n "${p:-}" ]] && { echo "$p"; return; }
  done
  echo "Error: cannot find $name (set HRB_ROOT=/path/to/HRBJackpotCoin)" >&2
  exit 1
}

HRB_QT="$(find_bin hrbjackpotcoin-qt)"
HRBD="$(find_bin hrbjackpotcoind)"
HRBCLI="$(find_bin hrbjackpotcoin-cli)"

# --- Data & Desktop paths ---
DATA_DIR="${XDG_DATA_HOME:-$HOME/.${APP_ID}}"
DESKTOP_DIR="${XDG_DESKTOP_DIR:-$HOME/Desktop}"
mkdir -p "$DESKTOP_DIR" "$DATA_DIR"

# --- First-run detection (no Spend/Mining wallet directories yet) ---
FIRST_RUN=true
[[ -e "$DATA_DIR/wallets/Spend" || -e "$DATA_DIR/wallets/Mining" ]] && FIRST_RUN=false

if $FIRST_RUN; then
  echo "[HRB] First run: creating wallets + backups…"
  # Start daemon to use RPC
  "$HRBD" -datadir="$DATA_DIR" -daemon=1 -server=1 -listen=0 -dnsseed=0 >/dev/null 2>&1
  "$HRBCLI" -datadir="$DATA_DIR" -rpcwait getblockchaininfo >/dev/null

  # Create descriptor wallets and load at startup
  "$HRBCLI" -datadir="$DATA_DIR" -named createwallet wallet_name=Spend  descriptors=true load_on_startup=true >/dev/null
  "$HRBCLI" -datadir="$DATA_DIR" -named createwallet wallet_name=Mining descriptors=true load_on_startup=true >/dev/null

  # One address each (handy for the user)
  SPEND_ADDR="$("$HRBCLI"  -datadir="$DATA_DIR" -rpcwallet=Spend  getnewaddress "Spend"  bech32)"
  MINING_ADDR="$("$HRBCLI" -datadir="$DATA_DIR" -rpcwallet=Mining getnewaddress "Mining" bech32)"

  # Backups on Desktop
  TS="$(date +%Y%m%d-%H%M%S)"
  BDIR="${DESKTOP_DIR}/HRB-Wallet-Backup-${TS}"
  mkdir -p "$BDIR"

  "$HRBCLI" -datadir="$DATA_DIR" -rpcwallet=Spend  dumpwallet "${BDIR}/spend.dump"
  "$HRBCLI" -datadir="$DATA_DIR" -rpcwallet=Mining dumpwallet "${BDIR}/mining.dump"
  "$HRBCLI" -datadir="$DATA_DIR" -rpcwallet=Spend  listdescriptors true > "${BDIR}/spend.descriptors.json"
  "$HRBCLI" -datadir="$DATA_DIR" -rpcwallet=Mining listdescriptors true > "${BDIR}/mining.descriptors.json"

  cat > "${BDIR}/README.txt" <<TXT
HRB Jackpot Coin – First-Run Backup (${TS})

Spend address:  ${SPEND_ADDR}
Mining address: ${MINING_ADDR}

Files in this folder:
- spend.dump / mining.dump           (full WIF key dump)
- *.descriptors.json                 (descriptor export with private keys)
Keep this folder OFFLINE & SAFE. Anyone with these can spend your coins.
TXT

  # Stop daemon before launching Qt (Qt runs its own node)
  "$HRBCLI" -datadir="$DATA_DIR" stop >/dev/null || true
  # Small wait for .lock release
  for i in {1..50}; do [[ -e "$DATA_DIR/.lock" ]] && sleep 0.1 || break; done
fi

# Launch Qt with both wallets
exec "$HRB_QT" -datadir="$DATA_DIR" -wallet=Spend -wallet=Mining "$@"
EOF
chmod +x /mnt/d/HRBJackpotCoin/hrb-launcher.sh
