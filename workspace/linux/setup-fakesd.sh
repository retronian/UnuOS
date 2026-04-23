#!/bin/bash
# Setup a fake SD card structure for the Linux dev simulator
set -e

cd "$(dirname "$0")"
FAKESD="$(pwd)/FAKESD"

mkdir -p "$FAKESD"/.system/linux/{bin,cores,dat,lib,paks,res}
mkdir -p "$FAKESD"/.userdata/linux
mkdir -p "$FAKESD"/.userdata/shared/.unuui
mkdir -p "$FAKESD"/Roms
mkdir -p "$FAKESD"/Saves
mkdir -p "$FAKESD"/Bios

# Copy resources from skeleton (fonts, assets, etc.)
SKELETON_RES="../../skeleton/SYSTEM/res"
mkdir -p "$FAKESD"/.system/res
for font in NotoSansCJKjp-Bold.otf NotoSansCJKsc-Bold.otf NotoSansCJKtc-Bold.otf NotoSansCJKkr-Bold.otf; do
    [ -f "$SKELETON_RES/$font" ] && cp "$SKELETON_RES/$font" "$FAKESD"/.system/res/
done
cp "$SKELETON_RES"/assets@2x.png "$FAKESD"/.system/res/ 2>/dev/null || true
cp "$SKELETON_RES"/charging-640-480.png "$FAKESD"/.system/res/ 2>/dev/null || true

# Sample Japanese ROM names (touch empty files for testing display)
mkdir -p "$FAKESD/Roms/Game Boy (GB)"
touch "$FAKESD/Roms/Game Boy (GB)/Pokemon - Aka (Japan).gb"
touch "$FAKESD/Roms/Game Boy (GB)/スーパーマリオランド (Japan).gb"

mkdir -p "$FAKESD/Roms/Nintendo Entertainment System (FC)"
touch "$FAKESD/Roms/Nintendo Entertainment System (FC)/スーパーマリオブラザーズ (Japan).nes"
touch "$FAKESD/Roms/Nintendo Entertainment System (FC)/ドラゴンクエスト (Japan).nes"
touch "$FAKESD/Roms/Nintendo Entertainment System (FC)/ファイナルファンタジー (Japan).nes"

mkdir -p "$FAKESD/Roms/Super Nintendo Entertainment System (SFC)"
touch "$FAKESD/Roms/Super Nintendo Entertainment System (SFC)/ゼルダの伝説 神々のトライフォース (Japan).sfc"
touch "$FAKESD/Roms/Super Nintendo Entertainment System (SFC)/聖剣伝説2 (Japan).sfc"
touch "$FAKESD/Roms/Super Nintendo Entertainment System (SFC)/星のカービィ スーパーデラックス (Japan).sfc"
touch "$FAKESD/Roms/Super Nintendo Entertainment System (SFC)/Super Mario World (USA).sfc"

echo ""
echo "FAKESD created at: $FAKESD"
ls -la "$FAKESD"
