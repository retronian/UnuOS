# UnuUI: only the 7 supported cores (no Extras concept)
CORES = fceumm gambatte gpsp pcsx_rearmed picodrive snes9x2005_plus mednafen_pce_fast

###############################

# optional core vars
# *_REPO=
# *_HASH=
# *_CORE=
# *_FLAGS=
# *_MAKEFILE=
# *_BUILD_PATH=

mednafen_pce_fast_REPO = https://github.com/libretro/beetle-pce-fast-libretro

fceumm_REPO = https://github.com/libretro/libretro-fceumm

gambatte_REPO = https://github.com/libretro/gambatte-libretro

pcsx_rearmed_MAKEFILE = Makefile.libretro

picodrive_REPO = https://github.com/irixxxx/picodrive
picodrive_MAKEFILE = Makefile.libretro
# avoid picodrive's "|| echo ???" shell-glob fallback that expands to "cpu jni"
# when git rev-parse fails (docker safe.directory issue on host-mounted source)
picodrive_FLAGS = GIT_REVISION=-unuui

snes9x2005_plus_REPO = https://github.com/libretro/snes9x2005
snes9x2005_plus_FLAGS = USE_BLARGG_APU=1

###############################

include ../../all/cores/makefile