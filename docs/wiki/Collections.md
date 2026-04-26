# Collections

Collections let you group ROMs from multiple systems into one launcher list. They are useful for series order, genre lists, favorites, or any other custom grouping.

This is an undocumented MinUI feature that UnuOS keeps available.

## Creating A Collection

Create a `Collections` folder at the root of the SD card, then place `.txt` files inside it. The text filename becomes the collection name shown in the launcher.

Example:

```text
/Collections/Metroid series.txt
```

Each `.txt` file contains one full path per line. Paths should point to ROMs, `.cue` files, or `.m3u` files, and should start from the SD card root.

```text
/Roms/GBA/Metroid Zero Mission.gba
/Roms/GB/Metroid II.gb
/Roms/SNES (SFC)/Super Metroid.sfc
/Roms/GBA/Metroid Fusion.gba
```

In this example, `Metroid series` appears in the launcher and lists the games in the same order as the text file.

## Box Art

Collections can have their own box art.

```text
/Collections/Metroid series.txt
/Collections/.res/Metroid series.txt.png
```

Images for individual ROMs inside a collection use the normal box art location.

```text
/Roms/GBA/Metroid Fusion.gba
/Roms/GBA/.res/Metroid Fusion.gba.png
```

## Notes

- Use absolute paths from the SD card root.
- Missing or incorrect paths will not launch correctly.
- The order in the `.txt` file is the display order.
- To hide a collection, prefix the collection filename with `.`.
