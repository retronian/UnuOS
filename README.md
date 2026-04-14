# OneOS

OneOS is a retro game launcher and libretro frontend for the Miyoo Mini Plus. It is a fork of [MinUI](https://github.com/shauninman/MinUI) that adds first-class CJK (Japanese, Chinese, Korean) support.

It is the core OS of the [Retronian](https://retronian.com) project — *"One OS, All Handhelds"*.

日本語版: [README.ja.md](README.ja.md)

## Features

- Simple launcher, simple SD card layout
- No setup, no configuration
- No box art, no themes, no distractions
- **CJK ROM names render correctly** in Japanese, Simplified/Traditional Chinese, and Korean (Noto Sans CJK)
- Hidden files, file extensions, and region/version tags are automatically stripped from display names
- Unified menu for save states, disc swap, and emulator options
- Auto sleep after 30 seconds, hold POWER to sleep / wake
- Auto power-off after 2 minutes of sleep, hold POWER for 1 second to power off
- Resumes from the last running state on power on
- Press X in the launcher to resume from the most recent save state
- Lean emulator frontend (minarch + libretro cores)

## Supported consoles

Base:

- Nintendo Entertainment System (NES / Famicom)
- Super Nintendo Entertainment System (SNES / Super Famicom)
- Game Boy
- Game Boy Color
- Game Boy Advance
- Sega Genesis / Mega Drive
- Sony PlayStation

Extras:

- Neo Geo Pocket (and Color)
- Sega Game Gear
- Sega Master System / Mark III
- Super Game Boy
- PC Engine / TurboGrafx-16 / CD
- Virtual Boy

## Supported devices

OneOS keeps the MinUI per-platform source for every device MinUI shipped with. Status:

### Tested by maintainer

| Device | platform | Status |
| -- | -- | -- |
| Miyoo Mini Plus | `miyoomini` | Active (primary development target) |

### In codebase, untested by maintainer (expected to work)

These platforms inherit working code from MinUI and should still build, but the maintainer has not personally verified them on hardware. Reports welcome.

| Device | platform |
| -- | -- |
| Miyoo Mini / Miyoo Mini Flip | `miyoomini` (single build, model detected at runtime) |
| Miyoo Flip | `my355` |
| Miyoo A30 | `my282` |
| Anbernic RG35XX Plus / H / 2024 / SP, RG34XX, RG CubeXX | `rg35xxplus` (single build, model detected at runtime) |
| Anbernic RG35XX (older model) | `rg35xx` |
| Anbernic M17 | `m17` |
| Trimui Smart | `trimuismart` |
| Trimui Smart Pro / Brick | `tg5040` |
| Powkiddy RGB30 | `rgb30` |
| MagicX XU Mini M | `magicmini` |
| MagicX Mini Zero 28 | `zero28` |
| GKD Pixel | `gkdpixel` |

### Planned (not yet supported)

| Device | Notes |
| -- | -- |
| Anbernic RG 28XX | Not in the MinUI base. Port from NextUI or similar fork is being considered. |

## Upstream

OneOS is a fork of [MinUI](https://github.com/shauninman/MinUI). All credit for the original work goes to the upstream maintainers.

## License

OneOS inherits MinUI's license. The bundled fonts in the `NotoSansCJK*` family are distributed under the SIL Open Font License (OFL) 1.1.
