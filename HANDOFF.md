# OneOS Project Handoff

このドキュメントは OneOS プロジェクトの現状を別の AI エージェントに引き継ぐためのものです。

## プロジェクトの目的

**OneOS** は Miyoo Mini Plus 用のカスタムファームウェア。[MinUI](https://github.com/shauninman/MinUI) のフォークに以下を追加:

1. **日本語/CJK 対応**（フォント + UTF-8 テキスト処理）
2. **UI 多言語化**（7言語: en / ja / zh_cn / zh_tw / ko / es / fr）
3. **libretro コアオプションの多言語化**（コア側の翻訳テーブルを活用）
4. **OneOS ブランディング**（Retronian ブランドの一部）
5. **Extras 概念の撤去**（1 zip で完結）

オーナー: **komagata** (retronian 名義)。日本語で会話すること。

## アーキテクチャ

OneOS = MinUI fork。RetroArch は使わず、独自の軽量 libretro frontend `minarch` を使う。

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

workspace/linux/         # ★OneOS 独自: Linux 開発シミュレータ
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
make PLATFORMS=miyoomini        # フルパッケージ (releases/OneOS-YYYYMMDD-N-base.zip 生成)
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
   - 対策: `workspace/miyoomini/cores/makefile` に `picodrive_FLAGS = GIT_REVISION=-oneos` を追加（実装済み）。

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
  - **NextUI 等他のフォークでは未修正**、OneOS 独自の差別化ポイント
- 実機で日本語 ROM 名表示を確認済み

### ✅ Phase 2: OneOS ブランディング
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
- **Settings UI**: ランチャーのルートに仮想エントリ `SETTINGS_PATH` (`SDCARD/.oneos-settings`) を追加 →
  `Entry_open` で intercept → `openSettings()` が言語リスト表示 → 選択時に `lang.txt` を更新 + カレントディレクトリ再構築で即時反映
- 翻訳は UI 面積制約に合わせて短縮（例: `ja エミュレータ` / `fr Sauv. état`）
- minarch の **Options > Frontend > Language** からも切替可能
- 実機で日本語 UI を確認済み

### ✅ Phase 4b (libretro): コアオプション多言語化
- minarch に `RETRO_ENVIRONMENT_GET_LANGUAGE` ハンドラを追加（`lang.retro_lang` を返す）
- `SET_CORE_OPTIONS_INTL` (v1) で `options->local` を優先使用するよう修正
- **コア側翻訳パッチ** (`workspace/all/cores/patches/<core>/`):
  - ✅ **snes9x2005_plus**: 4言語 (ja/zh_cn/zh_tw/ko) フル翻訳
  - ✅ **gpsp**: 4言語 (ja/zh_cn/zh_tw/ko) フル翻訳
  - ✅ **picodrive**: ja のみ
  - ⏳ **pcsx_rearmed**: **未着手** (73オプションで大規模、Pass 2 へ)
- 既訳コア（未修正で利用中）:
  - fceumm / gambatte / mgba / mednafen_pce_fast は upstream で ja/zh/ko を持つ

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
- 結果: **OneOS パッケージは `releases/OneOS-YYYYMMDD-N-base.zip` 1 個のみ** (extras.zip は生成されない)

## 同梱 core の最終ラインナップ

| Core | エミュ対象 | 翻訳（コアオプション） |
|---|---|---|
| fceumm | NES | ja/zh/ko (upstream) |
| gambatte | GB / GBC | ja/zh/ko (upstream) |
| gpsp | GBA | **ja/zh_cn/zh_tw/ko (OneOS patch)** |
| picodrive | Mega Drive / Genesis / 32X / Mega CD / SMS / Game Gear | **ja (OneOS patch)** |
| snes9x2005_plus | SNES / Super Famicom | **ja/zh_cn/zh_tw/ko (OneOS patch)** |
| pcsx_rearmed | PlayStation | **未翻訳** (Pass 2) |
| mednafen_pce_fast | PC Engine / TurboGrafx-16 | ja/zh/ko (upstream) |

EXTRAS にあった mgba / race / mednafen_vb / mednafen_supafaust / pokemini / fake-08 は **廃止**。Miyoo Mini Flip も現状対象外。

## シミュレータ

**Docker を使わない開発を可能にするための OneOS 独自の仕組み**:

- `workspace/linux/` ディレクトリが macOS platform をベースにした Linux ポート
- 実機転送なしに数秒で minui の挙動を確認可能
- **ただし**: SDL2 ウィンドウが必要で、Claude Code の background から走らせるとウィンドウが出ず入力待ちでハングする（dummy driver 使うと別の問題）
- 検証方法: バイナリに翻訳文字列が埋め込まれているか `grep -ac "本体リージョン" path/to/core.so` で確認が確実

## コミット履歴（重要なもの）

```
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
1. **pcsx_rearmed 翻訳**（Pass 2）
   - 73 オプション、値配列が巨大（gun adjust は -40〜+40 の 81 値等）
   - 推奨アプローチ: `workspace/all/cores/patches/pcsx_rearmed/` にパッチとして追加
   - マクロで値配列を共有すると line 数を減らせる
   - 日本語のみで OK
2. **pcsx_rearmed を除く 3 コアの追加言語** (zh_cn / zh_tw / ko)
   - picodrive は ja のみ。他も同じ方針で後から追加

### 優先度中
3. **minarch の SET_CORE_OPTIONS_V2_INTL 対応**
   - 現在は v1 の `SET_CORE_OPTIONS_INTL` のみ。v2 (categories 付き) のハンドラも追加すると、v2 core の翻訳が自動で効く
   - fceumm や mednafen_pce_fast は v2 で提供しているので、v2 ハンドラがあれば翻訳が確実に使われる（現状は v1 fallback で動いている可能性）
4. **`workspace/miyoomini/cores/makefile` の setup 順序**
   - `setup` で `rm -rf ./build` だけでなく core の src/ 配下の stale `.o` が残る場合がある
   - 翻訳パッチを入れ替えたときは、対応 core の `.patched-all` を削除して `libretro.o` も削除する必要がある

### 優先度低
5. **Cloud sync (Phase 3)** — Miyoo Mini Plus は WiFi なしなので romu (Go 製 ROM manager) 経由で PC → SD カード → device の同期方式を想定
6. **game DB 連携** — retrogame-db / gamelist-ja との連携
7. **box art 表示** — オプション機能として

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
