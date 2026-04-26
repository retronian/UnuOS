# Box Art

UnuOSは、ROMやフォルダに対応するPNG画像をSDカード上に置くと、ランチャーで項目を選択したときに右側へ表示します。

この機能はMinUI由来の未文書化機能をUnuOSでも利用できるようにしているものです。

## 配置場所

画像は対象ファイルまたは対象フォルダと同じ階層にある `.res` フォルダへ置きます。ファイル名は対象の名前に `.png` を付けたものです。

例:

```text
/Roms/GBA/Metroid Fusion.gba
/Roms/GBA/.res/Metroid Fusion.gba.png
```

フォルダにも画像を付けられます。メインの機種一覧で表示したい場合は、`Roms` フォルダ直下の `.res` に置きます。

例:

```text
/Roms/GBA
/Roms/.res/GBA.png
```

Collectionsにも画像を付けられます。

```text
/Collections/Metroid series.txt
/Collections/.res/Metroid series.txt.png
```

## 画像形式

- PNG形式を使用します。
- 透過PNGを使用できます。
- 画面右側へ等倍で表示されます。
- 推奨サイズは最大240x240です。端末の画面サイズより大きい画像は避けてください。

## 注意点

- ROM名と画像名は拡張子を含めて一致させます。
- 大文字小文字や空白もファイル名として一致している必要があります。
- `.zip` や `.chd` などでも、対象ファイル名にそのまま `.png` を付けます。
