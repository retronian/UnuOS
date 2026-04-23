# UnuUI (MinUI Fork)

Miyoo Mini Plus向けレトロゲームランチャー。MinUIフォークにCJK日本語対応を追加する。

## ビルド

```bash
# miyoomini のみビルド（Docker必須）
make build PLATFORM=miyoomini

# 全プラットフォーム + パッケージング
make PLATFORMS=miyoomini
```

初回はtoolchainリポジトリのclone + Dockerイメージ構築が走る。
ビルド成果物は `workspace/` 内の各 `build/$(PLATFORM)/` に出力される。

### ビルドフロー

1. `makefile` (ホスト) → `makefile.toolchain` でDocker起動
2. Docker内で `workspace/makefile` が実行される
3. `workspace/makefile` が共通コード(`all/`)とプラットフォーム固有コード(`miyoomini/`)をビルド

## アーキテクチャ

### コア構成

| コンポーネント | パス | 役割 |
|---|---|---|
| minui | `workspace/all/minui/minui.c` | ランチャーUI（ROM一覧・コレクション・最近のプレイ） |
| minarch | `workspace/all/minarch/minarch.c` | エミュレータフロントエンド（libretro） |
| common/api | `workspace/all/common/api.c` | グラフィックス・フォント・サウンドAPI |
| common/defines | `workspace/all/common/defines.h` | パス定数・色・フォントサイズ・マクロ |
| common/utils | `workspace/all/common/utils.c` | ファイル・文字列ユーティリティ |
| platform | `workspace/miyoomini/platform/platform.h` | ハードウェア抽象化（ボタン・解像度・パス） |
| keymon | `workspace/miyoomini/keymon/` | キー入力モニター |
| libmsettings | `workspace/miyoomini/libmsettings/` | 設定管理ライブラリ |

### フォントシステム

- フォントファイル: `skeleton/SYSTEM/res/BPreplayBold-unhinted.otf`
- パス定数: `defines.h:17` の `FONT_PATH`
- 読み込み: `api.c:154-158` で4サイズ (LARGE=16, MEDIUM=14, SMALL=12, TINY=10)
- スケール: `FIXED_SCALE=2` (miyoomini) → 実際は 32/28/24/20px
- 描画: `TTF_RenderUTF8_Blended()` — UTF-8対応済み

### テキスト切り詰め

- `api.c:228-241` の `GFX_truncateText()` — **バイト単位で切り詰めるためCJK文字で壊れる（要修正）**
- `api.c:243-300` の `GFX_wrapText()` — スペースで折り返し（日本語はスペースなしで折り返されない）

### Miyoo Mini Plus固有

- 解像度: 640x480 (標準) / 752x560 (560pモデル)
- SDカード: `/mnt/SDCARD`
- セーブデータ: `.userdata/miyoomini/`
- WiFi: なし

## 主要パス (SDカード上)

- `Roms/` — ROMフォルダ
- `.system/` — システムバイナリ・コア・リソース
- `.system/res/` — フォント・アセット
- `.userdata/` — セーブデータ・設定
- `Collections/` — コレクション定義
- `Recently Played/` — 最近プレイしたゲーム

## コーディング規約

- C言語 (C99)
- タブインデント
- 変数名・関数名: snake_case (ローカル) / PascalCase (モジュール名_関数名, 例: `GFX_truncateText`)
- プラットフォーム抽象化: `PLAT_*` プレフィックス
