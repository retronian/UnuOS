# Localization

UnuOSは、ランチャー、Settings、Tools表示名、libretroコアオプションの多言語表示に対応しています。

## 対応言語

- English
- 日本語
- 简体中文
- 繁體中文
- 한국어
- Español
- Français

## 言語の変更

ランチャーのSettingsから言語を選択します。選択するとすぐに表示へ反映されます。

設定値はSDカード上の共有ユーザーデータに保存されます。

```text
/.userdata/shared/lang.txt
```

ファイルには言語コードが1行で保存されます。

```text
en
ja
zh_cn
zh_tw
ko
es
fr
```

`lang.txt` が存在しない場合や未対応の値の場合、英語表示になります。

## 表示対象

多言語化の対象は主に次の項目です。

- ランチャーの基本UI
- Settingsの言語選択
- Toolsメニュー内の標準ツール名
- minarchのメニュー項目
- libretroコアオプション

## CJK表示

UnuOSはNoto Sans CJKフォントを同梱しており、日本語、中国語、韓国語のROM名やUI文字列を表示できます。ROM名の省略処理もUTF-8の文字境界に合わせて行います。

## 注意点

- ユーザーが追加したROM名やコレクション名はUTF-8で保存してください。
- コアオプションの翻訳は、各libretroコアが持つ翻訳テーブルとUnuOS側の対応状況に依存します。
- Toolsの外部パッケージ名は、UnuOS側に翻訳がある標準ツールのみローカライズされます。
