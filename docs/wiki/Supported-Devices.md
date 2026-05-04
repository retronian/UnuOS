# Supported Devices

UnuOS builds and packages all supported platform targets in one release. Some device families share a single platform build and detect the exact model at runtime.

| Device | Platform |
| --- | --- |
| Miyoo Mini / Miyoo Mini Plus | `miyoomini` |
| Miyoo A30 | `my282` |
| Miyoo Flip | `my355` |
| Miyoo Mini Flip | `miyoomini` |
| Anbernic RG35XX Plus / H / 2024 / SP, RG28XX, RG40XX H, RG34XX, RG CubeXX | `rg35xxplus` |
| Anbernic RG35XX (original) | `rg35xx` |
| Anbernic M17 | `m17` |
| Trimui Smart | `trimuismart` |
| Trimui Smart Pro / Trimui Brick | `tg5040` |
| Powkiddy RGB30 | `rgb30` |
| MagicX XU Mini M | `magicmini` |
| MagicX Mini Zero 28 | `zero28` |
| GKD Pixel | `gkdpixel` |

## Release Targets

The release build covers these targets:

```text
miyoomini my282 rg35xxplus rg35xx m17 trimuismart tg5040 rgb30 magicmini zero28 gkdpixel my355
```
