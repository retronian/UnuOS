# Game Focus Mode

Game Focus Mode shows only the games listed in a dedicated collection.

This is useful when you want the launcher to show a small, intentional set of games instead of the full SD card library.

## Enabling Game Focus Mode

Create this file on the SD card:

```text
/Collections/Only.txt
```

When `Only.txt` exists, UnuOS enters Game Focus Mode automatically.

The file uses the same format as a normal collection: one absolute SD card path per line.

```text
/Roms/GBA/Metroid Zero Mission.gba
/Roms/SNES (SFC)/Super Metroid.sfc
/Roms/GBA/Metroid Fusion.gba
```

## What Changes

While `Only.txt` exists, the launcher root shows only the valid games listed in that file.

The following entries are hidden:

- Recently Played
- Collections
- Tools
- Settings
- System folders

## Disabling Game Focus Mode

Delete or rename `Only.txt`.

Example:

```text
/Collections/.Only.txt
```

After `Only.txt` no longer exists, UnuOS returns to the normal launcher root.

## Notes

- Empty lines are ignored.
- Missing or incorrect paths are skipped.
- If `Only.txt` exists but contains no valid games, the launcher root is empty.
- Game order follows the order in `Only.txt`.
