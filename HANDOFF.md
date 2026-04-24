# UnuUI Project Handoff

このドキュメントは UnuUI プロジェクトの現状を別の AI エージェントに引き継ぐためのものです。

## プロジェクトの目的

**UnuUI** は Miyoo Mini Plus 用のカスタムファームウェア。[MinUI](https://github.com/shauninman/MinUI) のフォークに以下を追加:

1. **日本語/CJK 対応**（フォント + UTF-8 テキスト処理）
2. **UI 多言語化**（7言語: en / ja / zh_cn / zh_tw / ko / es / fr）
3. **libretro コアオプションの多言語化**（コア側の翻訳テーブルを活用）
4. **UnuUI ブランディング**（Retronian ブランドの一部）
5. **Extras 概念の撤去**（1 zip で完結）

オーナー: **komagata** (retronian 名義)。日本語で会話すること。

## アーキテクチャ

UnuUI = MinUI fork。RetroArch は使わず、独自の軽量 libretro frontend `minarch` を使う。

```
workspace/all/           # プラットフォーム共通コード
  minui/                 # ランチャー (SDL2)
  minarch/               # libretro frontend
  common/                # api.c / defines.h / utils.c / lang.c / lang.h
  clock/                 # 時計ツール
  minput/                # 入力テスト
  syncsettings/          # 設定同期
  say/                   # 音声出力

workspace/miyoomini/     # Miyoo Mini Plus 固有
  platform/              # ハードウェア抽象化 (platform.c/h)
  cores/                 # 同梱する libretro core の定義
  install/               # 初回インストーラ
  libmsettings/          # 設定ライブラリ

workspace/linux/         # ★UnuUI 独自: Linux 開発シミュレータ
  platform/              # SDL2 ベースのダミープラットフォーム
  build-minui.sh         # ホストで minui をビルドするスクリプト
  run-minui.sh           # シミュレータ起動
  setup-fakesd.sh        # FAKESD の初期化

skeleton/                # SD カードの雛形
  BASE/                  # インストールされるファイル（Bios/Roms/Saves/Tools/miyoo/...）
    Tools/miyoomini/     # Clock.pak / Files.pak / Input.pak / IP.pak など
  BOOT/                  # ブートストラップスクリプト
  SYSTEM/                # .system 配下になる内容
    SYSTEM/res/          # フォント・アセット
    SYSTEM/miyoomini/paks/Emus/  # 同梱エミュレータ pak (FC/GB/GBA/GBC/MD/PAK/PCE/PS/SFC)

makefile                 # ホスト側のオーケストレーション
makefile.toolchain       # Docker 呼び出し
workspace/makefile       # Docker 内のビルド
workspace/all/cores/patches/<core>/*.patch  # クロスプラットフォーム core パッチ（翻訳等）
workspace/miyoomini/cores/patches/<core>.patch  # miyoomini 専用 core パッチ（ビルド設定）
```

## ビルドシステム

### 必要環境
- Docker
- Arch Linux (ホスト側。ImageMagick は含まれる)
- `sdl2 sdl2_image sdl2_ttf`（Linux シミュレータ用）

### 主要コマンド

```bash
# 初回: toolchain は自動で clone + Docker image build される
make PLATFORMS=miyoomini        # フルパッケージ (releases/UnuUI-YYYYMMDD-N-base.zip 生成)
make build PLATFORM=miyoomini   # バイナリのみビルド (Docker内)
make clean                       # build/ 削除

# Linux シミュレータ (minui のみ、Docker 不要)
cd workspace/linux
./build-minui.sh    # 数秒でビルド
./setup-fakesd.sh   # FAKESD 初期化 (日本語 ROM サンプル入り)
./run-minui.sh      # SDL2 ウィンドウ起動
```

### ビルドの落とし穴（重要！）

1. **Docker ownership**: ホストから mount されたソースは Docker 内で「dubious ownership」となり `git rev-parse` が失敗する。影響:
   - **picodrive** の `GIT_REVISION ?= -$(shell git rev-parse --short HEAD || echo ???)` で `???` が shell glob として展開され、picodrive ルートの `cpu` と `jni` ディレクトリにマッチして `-cpu jni` という壊れた値になる。
   - 対策: `workspace/miyoomini/cores/makefile` に `picodrive_FLAGS = GIT_REVISION=-unuui` を追加（実装済み）。

2. **TTY の問題**: makefile の `tty -s` と Docker の `-it` は Claude Code の非対話環境で動かない。
   - 対策: `makefile.toolchain` は `docker run -i` (not `-it`)、`makefile` の setup target は `tty -s || true` に修正済み。

3. **macOS 系コマンド**: `find -E` は GNU find では `-regextype posix-extended` を使う。`makefile:23` の `RELEASE_DOT` 計算で対応済み。

4. **Stale .o files**: core のソースを git checkout でリセットすると、stale な .o が残り arch mismatch で link に失敗する。完全クリーンするには `rm -rf workspace/miyoomini/cores/src/<core>` で再クローンさせるのが確実。

5. **cores/src は .gitignore 済み**: 直接編集はコミットに含まれない。翻訳は **必ずパッチ化** して `workspace/all/cores/patches/<core>/*.patch` に置くこと。

6. **core の翻訳パッチを当てたあと**: libretro.o が stale になっていても make が気づかない場合がある。直接 `libretro.o` を削除して再ビルドが確実。

7. **fake-08 / pokemini は build 不能**:
   - fake-08: upstream で `Vm::UpdateAndDraw` が削除され、古い libretro core.cpp がコンパイル不可
   - pokemini: upstream patch が現 source に適用できない
   - どちらも CORES リストから除外済み（**この方針は維持**）

## 現在の phase 進捗

### ✅ Phase 0: ビルド検証・CLAUDE.md 作成
- コミット: `bbded10` (および前の一連)
- Docker ビルドが通ることを確認済み
- `CLAUDE.md` に build / アーキテクチャ / フォント / 切り詰めバグをドキュメント化

### ✅ Phase 1: CJK フォント対応
- `skeleton/SYSTEM/res/NotoSansCJKjp-Bold.otf` (~17MB) を追加
- `workspace/all/common/defines.h:17` の `FONT_PATH` を更新 → のちに動的参照に変更
- **`GFX_truncateText()` の UTF-8 バグ修正** (`workspace/all/common/api.c:228`付近)
  - 元は `strcpy(&out_name[len-4], "...\0")` でマルチバイト UTF-8 を途中で切断してクラッシュ
  - 修正後は `keep_len` を コードポイント単位で後退させる方式
  - **NextUI 等他のフォークでは未修正**、UnuUI 独自の差別化ポイント
- 実機で日本語 ROM 名表示を確認済み

### ✅ Phase 2: OneOS ブランディング（後に UnuUI に改名、Phase 5 参照）
- `MinUI` → `OneOS` リネーム（makefile RELEASE_BASE / minarch Frontend label / minui ログ / README）
- `skeleton/SYSTEM/res/charging-640-480.png` を One/OS 正方形ロゴに置換（ImageMagick）
- `workspace/miyoomini/install/installing.png` / `updating.png` も OneOS 化
- tag `minui-fork-point` を dbf8943 に打った
- `CHANGELOG.md` 開始
- **注意**: 他プラットフォーム (rg35xx, trimui, etc.) のコードは残す方針。OneOS は Miyoo Mini Plus 専用だが将来のマルチプラットフォーム展開余地は保つ。
- **重要**: `RECENT_PATH` の `.minui/` と `MinUI.zip` ファイル名は互換性のため維持（既存ユーザの data を壊さない）。

### ✅ Phase 4a: UI 多言語化（7言語）
- `workspace/all/common/lang.h` / `lang.c` を新設
- 構造体 `Lang` に UI 文字列 + `font_path` + `retro_lang` フィールド
- 対応言語: **en / ja / zh_cn / zh_tw / ko / es / fr**
- CJK 4 バリアント フォントをバンドル: `NotoSansCJKjp/sc/tc/kr-Bold.otf` (各 ~17MB)
- 言語切替は `<SHARED_USERDATA>/lang.txt` に言語コードを書く
- GFX_init 先頭で `Lang_init()` を呼び、`api.c` はフォントを `lang.font_path` から読む
- **Settings UI**: ランチャーのルートに仮想エントリ `SETTINGS_PATH` (`SDCARD/.unuui-settings`) を追加 →
  `Entry_open` で intercept → `openSettings()` が言語リスト表示 → 選択時に `lang.txt` を更新 + カレントディレクトリ再構築で即時反映
- 翻訳は UI 面積制約に合わせて短縮（例: `ja エミュレータ` / `fr Sauv. état`）
- minarch の **Options > Frontend > Language** からも切替可能
- 実機で日本語 UI を確認済み

### ✅ Phase 4b (libretro): コアオプション多言語化
- minarch に `RETRO_ENVIRONMENT_GET_LANGUAGE` ハンドラを追加（`lang.retro_lang` を返す）
- `SET_CORE_OPTIONS_INTL` (v1) で merge-aware 実装：`options->local` の欠けたキーは `us` にフォールバック
- **minarch v2 対応** (コミット `0c0e2d2`):
  - `GET_CORE_OPTIONS_VERSION` は 2 を返す
  - `SET_CORE_OPTIONS_V2` / `SET_CORE_OPTIONS_V2_INTL` ハンドラ
  - `OptionList_initV2Full()` / `OptionList_initV2FromIntl()` は v1 と同じ merge セマンティクス
- **カテゴリ表示対応** (コミット `d418561` + `5194739`):
  - Option 構造体に `category_key` / `category_name` を追加
  - `OptionEmulator_openMenu` で `category_key` を qsort で安定ソート
  - 各カテゴリ グループの先頭オプションに `[カテゴリ名] オプション名` とプレフィックス表示
  - カテゴリ名は local_cats からの翻訳を優先、未翻訳は us_cats にフォールバック
- **コア側翻訳パッチ** (`workspace/all/cores/patches/<core>/`):
  - ✅ **snes9x2005_plus**: 4言語 (ja/zh_cn/zh_tw/ko) フル翻訳 (7 オプション)
  - ✅ **gpsp**: 4言語 (ja/zh_cn/zh_tw/ko) フル翻訳 (13 オプション)
  - ✅ **picodrive**: 4言語 (ja/zh_cn/zh_tw/ko) フル翻訳 (21 オプション)
  - ✅ **pcsx_rearmed**: 4言語 (ja/zh_cn/zh_tw/ko) 全 73 オプション完全翻訳
- 既訳コア（未修正で利用中）:
  - fceumm / gambatte / mednafen_pce_fast は upstream で ja/zh_cn/zh_tw/ko を持つ

### ✅ Extras 概念の撤去 + PCE 昇格
- `skeleton/EXTRAS/` を完全削除
- `skeleton/EXTRAS/Tools/` → `skeleton/BASE/Tools/` に移動
- `skeleton/EXTRAS/Emus/miyoomini/PCE.pak` → `skeleton/SYSTEM/miyoomini/paks/Emus/PCE.pak`
- `workspace/miyoomini/cores/makefile` の CORES を 7 つに削減:
  ```
  CORES = fceumm gambatte gpsp pcsx_rearmed picodrive snes9x2005_plus mednafen_pce_fast
  ```
- `makefile` の `cores:` / `package:` / `system:` ターゲットから EXTRAS 関連を削除
- `workspace/miyoomini/platform/makefile.copy` を `build/BASE/Tools/` に更新
- 結果: **UnuUI パッケージは `releases/UnuUI-YYYYMMDD-N-base.zip` 1 個のみ** (extras.zip は生成されない)

### ✅ Phase 5 (2026-04-23): OneOS → UnuUI 改名
- プロジェクト名を **OneOS** から **UnuUI** に変更（エスペラント語「一」= Unu + MinUI 系譜の UI サフィックス）
- 動機: OneOS は同名プロジェクト多数（DependableSystemsLab/OneOS 等）、ブランド弱く検索で埋もれる。多言語中立・シンプル・ミニマルの方針で UnuUI を選定
- 変更: `workspace/all/oneos/` → `workspace/all/unuui/`、`OneOS.pak` → `UnuUI.pak` (8 プラットフォーム)、`RELEASE_BASE=OneOS-` → `UnuUI-`、スクリプト・ドキュメント一式
- 後方互換: 旧 `<SHARED_USERDATA>/.oneos/` は起動時 `.unuui/` に自動 rename（`workspace/all/unuui/unuui.c:main()` 内）
- **重要**: `RECENT_PATH` の `.minui/` と `MinUI.zip` ファイル名はそのまま（既存ユーザの data を壊さない方針は継続）

## 同梱 core の最終ラインナップ

| Core | エミュ対象 | 翻訳（コアオプション） |
|---|---|---|
| fceumm | NES | ja/zh_cn/zh_tw/ko (upstream) |
| gambatte | GB / GBC | ja/zh_cn/zh_tw/ko (upstream) |
| gpsp | GBA | **ja/zh_cn/zh_tw/ko (UnuUI patch) — 13 options** |
| picodrive | Mega Drive / Genesis / 32X / Mega CD / SMS / Game Gear | **ja/zh_cn/zh_tw/ko (UnuUI patch) — 21 options** |
| snes9x2005_plus | SNES / Super Famicom | **ja/zh_cn/zh_tw/ko (UnuUI patch) — 7 options** |
| pcsx_rearmed | PlayStation | **ja/zh_cn/zh_tw/ko (UnuUI patch) — 全 73 options** |
| mednafen_pce_fast | PC Engine / TurboGrafx-16 | ja/zh_cn/zh_tw/ko (upstream) |

**全 BASE 7 コアが ja/zh_cn/zh_tw/ko 4 言語すべてでカテゴリも含め翻訳完了**。minarch 側の merge-aware fallback により、local struct が us より少ない場合でも欠けたキーは英語で表示される。

EXTRAS にあった mgba / race / mednafen_vb / mednafen_supafaust / pokemini / fake-08 は **廃止**。Miyoo Mini Flip も現状対象外。

## シミュレータ

**Docker を使わない開発を可能にするための UnuUI 独自の仕組み**:

- `workspace/linux/` ディレクトリが macOS platform をベースにした Linux ポート
- 実機転送なしに数秒で minui の挙動を確認可能
- **ただし**: SDL2 ウィンドウが必要で、Claude Code の background から走らせるとウィンドウが出ず入力待ちでハングする（dummy driver 使うと別の問題）
- 検証方法: バイナリに翻訳文字列が埋め込まれているか `grep -ac "本体リージョン" path/to/core.so` で確認が確実

## コミット履歴（重要なもの）

```
5194739 minarch: v2 category name prefix display
d418561 minarch: group core options by v2 category_key
fccc3d9 cores: complete pcsx_rearmed zh_cn/zh_tw/ko (all 73 options)
e022223 cores: extend pcsx_rearmed translation with zh_cn/zh_tw/ko
09e5281 cores: extend picodrive translation with zh_cn/zh_tw/ko
6d81432 cores: complete pcsx_rearmed ja translation (all 73 options)
0c0e2d2 minarch: support libretro core options v2 interface
3fae297 cores: add pcsx_rearmed partial ja translation
840b270 minarch: merge-aware SET_CORE_OPTIONS_INTL fallback
6f987f3 docs: add HANDOFF.md for AI session handoff
d92f478 cores: add picodrive ja translation + fix GIT_REVISION glob
bbded10 cores: add snes9x2005_plus and gpsp translation patches
991d400 phase 4b: additional localization + Settings UI + libretro i18n + restructure
7b5b5da phase 4a: UI localization (7 languages)
26d6da5 phase 2: rebrand to OneOS + linux dev simulator
94fecb6 miyoomini: added Japanese/CJK font support
minui-fork-point (tag) → dbf8943 (upstream MinUI の最終状態)
```

## 現在の TODO / 保留中

### 優先度高
1. **実機総合テスト**
   - 7 コアすべてで Options > Emulator メニューが日本語（zh/ko も確認可）で表示されることを確認
   - 特に **カテゴリプレフィックス表示** (`[システム] リージョン` 等) が正しく動作するかチェック
   - 現状 binary level では全 core の翻訳キーワードを grep で確認済み

### 優先度中
2. **カテゴリ表示のさらなる改善**
   - 現状: カテゴリ先頭オプションに `[カテゴリ名]` プレフィックスを付けるのみ
   - 改善案: 非選択 "ヘッダー行" としてカテゴリ名を表示、またはサブメニュー化
   - サブメニュー化する場合は `Menu_options` の挙動拡張が必要
3. **`workspace/miyoomini/cores/makefile` の setup 順序**
   - `setup` で `rm -rf ./build` だけでなく core の src/ 配下の stale `.o` が残る場合がある
   - 翻訳パッチを入れ替えたときは、対応 core の `.patched-all` を削除して `libretro.o` も削除する必要がある

### 優先度低
4. **Cloud sync (Phase 3)** — Miyoo Mini Plus は WiFi なしなので romu (Go 製 ROM manager) 経由で PC → SD カード → device の同期方式を想定
5. **game DB 連携** — retrogame-db / gamelist-ja との連携
6. **box art 表示** — オプション機能として
7. **upstream PR** — UnuUI コア翻訳パッチ (snes9x2005_plus / gpsp / picodrive / pcsx_rearmed の ja/zh/ko) は upstream にも貢献価値あり。各 core リポジトリに PR 提出を検討

## 注意事項 / 文化的ガイドライン

- **会話は日本語**（`~/.claude/CLAUDE.md` のユーザ全体ルール）
- **komagata は Ruby/Rails 出身で C/組込みは学習中** — C コードの説明は Ruby のイディオムとの対応を添えると親切
- **プランモードデフォルト** — 非自明な変更はプランから始める
- **実機テストは最小限** — 実機転送は手間なので、できるだけシミュレータや `grep -ac` などで検証
- **作業途中でコミット** — 実機確認前でも、動作確認がバイナリレベルで取れているならコミットして良い
- **パク (pak)** は MinUI で「インストール可能なツール/エミュレータ」を指す概念。Tools/Clock.pak のような構造

## 参考リンク

- Upstream MinUI: https://github.com/shauninman/MinUI
- NextUI (別の MinUI fork、font 切替のみ): https://github.com/LoveRetro/NextUI
- libretro core options 仕様: https://github.com/libretro/libretro-common/blob/master/include/libretro_core_options.h
- retronian organization: https://github.com/retronian

## 引き継ぎ時のチェックリスト

- [ ] `git log --oneline | head -10` で最新コミットを確認
- [ ] `releases/` の最新 zip を実機で動作確認（optional）
- [ ] このドキュメントに書いた **ビルドの落とし穴** を一通り把握
- [ ] pcsx_rearmed 翻訳に着手するなら、まず既存 core パッチ（gpsp/snes9x2005_plus）のパターンを読む
- [ ] Linux シミュレータで minui を触ってみる（`workspace/linux/run-minui.sh`）

## 質問があれば

このファイルは時間の経過とともに古くなります。疑問があれば:
1. `git log` でコミットメッセージから意図を読む
2. `CLAUDE.md` でプロジェクト基本方針を確認
3. komagata さんに直接聞く（最終判断）
