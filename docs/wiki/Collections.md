# Collections

Collectionsは、複数の機種にまたがるROMを1つの一覧にまとめる機能です。シリーズ順、ジャンル別、お気に入りなど、SDカード上のテキストファイルだけで任意のコレクションを作れます。

この機能はMinUI由来の未文書化機能をUnuOSでも利用できるようにしているものです。

## 作成方法

SDカード直下に `Collections` フォルダを作り、その中に `.txt` ファイルを置きます。ファイル名がランチャー上のコレクション名になります。

例:

```text
/Collections/Metroid series.txt
```

`.txt` ファイルには、ROM、`.cue`、`.m3u` へのフルパスを1行ずつ書きます。パスはSDカード直下から始まる形式です。

```text
/Roms/GBA/Metroid Zero Mission.gba
/Roms/GB/Metroid II.gb
/Roms/SNES (SFC)/Super Metroid.sfc
/Roms/GBA/Metroid Fusion.gba
```

この例では、`Metroid series` がルートのランチャー一覧に表示され、ファイル内の順番でROMが並びます。

## Box Art

コレクション自体にも画像を付けられます。

```text
/Collections/Metroid series.txt
/Collections/.res/Metroid series.txt.png
```

コレクション内の各ROMの画像は、通常のBox Artと同じ場所に置きます。

```text
/Roms/GBA/Metroid Fusion.gba
/Roms/GBA/.res/Metroid Fusion.gba.png
```

## 注意点

- パスはSDカード上の絶対パスで書きます。
- 存在しないパスは正しく起動できません。
- `.txt` ファイル内の順番が表示順になります。
- コレクション名を隠したい場合は、通常の隠し項目と同じくファイル名の先頭に `.` を付けます。
