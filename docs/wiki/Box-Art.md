# Box Art

UnuOS can show a PNG image for a ROM, folder, or collection when that item is selected in the launcher.

This is an undocumented MinUI feature that UnuOS keeps available.

## File Location

Put images in a `.res` folder next to the file or folder they belong to. The image filename is the target name with `.png` appended.

Example:

```text
/Roms/GBA/Metroid Fusion.gba
/Roms/GBA/.res/Metroid Fusion.gba.png
```

Folders can have images too. To show an image in the main system list, put it in `.res` directly under `Roms`.

Example:

```text
/Roms/GBA
/Roms/.res/GBA.png
```

Collections can also have images.

```text
/Collections/Metroid series.txt
/Collections/.res/Metroid series.txt.png
```

## Image Format

- Use PNG files.
- Transparent PNGs are supported.
- Images are drawn at their original size on the right side of the screen.
- Recommended maximum size is 240x240. Avoid images larger than the device screen.

## Notes

- The image name must match the ROM name, including the extension.
- Case, spaces, and punctuation must match the target filename.
- For `.zip`, `.chd`, and other formats, append `.png` to the full target filename.
