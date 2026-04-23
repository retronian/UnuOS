#!/bin/bash
# Build UnuUI for Linux dev simulator
set -e

cd "$(dirname "$0")"
ROOT="$(cd ../.. && pwd)"

mkdir -p ../all/unuui/build/linux

BUILD_DATE=$(date +%Y%m%d)
BUILD_HASH=$(cd "$ROOT" && git rev-parse --short HEAD 2>/dev/null || echo dev)

gcc \
    ../all/unuui/unuui.c \
    ../all/common/api.c \
    ../all/common/scaler.c \
    ../all/common/utils.c \
    ../all/common/lang.c \
    ./platform/platform.c \
    -o ../all/unuui/build/linux/unuui \
    -I. \
    -I./platform \
    -I../all/common \
    $(pkg-config --cflags sdl2 SDL2_image SDL2_ttf) \
    $(pkg-config --libs sdl2 SDL2_image SDL2_ttf) \
    -lm -lpthread -ldl \
    -DPLATFORM=\"linux\" \
    -DUSE_SDL2 \
    -DBUILD_DATE=\"$BUILD_DATE\" \
    -DBUILD_HASH=\"$BUILD_HASH\" \
    -O0 -g \
    -std=gnu99 \
    -Wno-unused-result \
    -Wno-format-truncation

echo ""
echo "Built: ../all/unuui/build/linux/unuui"
echo "Run with: ./run-unuui.sh"
