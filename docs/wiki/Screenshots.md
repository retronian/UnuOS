# Screenshots

UnuOS can save the current launcher or gameplay screen as a BMP image.

## Controls

Hold `SELECT` and press `START` to save a screenshot of the current screen.

This works from:

- The launcher
- Settings
- Gameplay
- minarch menus and save state screens

## Save Location

Screenshots are saved in the `Screenshots` folder at the root of the SD card. The folder is created automatically if it does not exist.

```text
/Screenshots/YYYY-MM-DD_HH-MM-SS.bmp
```

Example:

```text
/Screenshots/2026-04-27_02-15-30.bmp
```

## Format

- Files are saved as BMP.
- The saved image is whatever UnuOS is currently displaying.
- Filenames are based on the capture timestamp.

## Notes

- Screenshots cannot be saved if the SD card is not writable.
- Taking multiple screenshots within the same second can reuse the same filename.
