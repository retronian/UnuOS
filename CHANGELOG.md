# Changelog

UnuOSのバージョン履歴。フォーク元のMinUIは `minui-fork-point` タグ（commit `dbf8943`）。

## Unreleased

### Added
- 日本語/CJKフォント対応（Noto Sans CJK JP Bold）
- Favorites: `Y` でゲームのお気に入り登録/解除、`SELECT+Y` でお気に入りゲームだけを表示するGame Focus Mode
- Game Focus Mode の英語・日本語・簡体字中国語スクリーンショットを Wiki 用に追加
- Miyoo Flip (`my355`) 対応
- Miyoo Mini Flip (`miyoomini`, `MY285`) 対応
- `CLAUDE.md`: プロジェクトドキュメント
- `CHANGELOG.md`: 本ファイル
- `minui-fork-point` タグ: upstream MinUIからのフォーク基点

### Changed
- `RELEASE_BASE`: `MinUI-` → `UnuOS-`
- minarchのFrontendメニュー表示: "MinUI" → "UnuOS"
- `README.md`: UnuOS用に書き換え
- `FONT_PATH`: `BPreplayBold-unhinted.otf` → `NotoSansCJKjp-Bold.otf`

### Fixed
- `GFX_truncateText()`: マルチバイトUTF-8文字の途中で切断する問題を修正。CJK文字を含むROM名で無限ループ・クラッシュが発生していた
- Linux dev simulator: video initialization and root-path cue lookup fixes for screenshot capture
- `makefile`: Linux環境向け互換性修正（`tty -s`、`find -E`）
- `makefile.toolchain`: 非対話環境でのDocker実行に対応（`-it` → `-i`）

### Excluded
- `fake-08` コア: upstreamビルド破損（`Vm::UpdateAndDraw` 削除）
- `pokemini` コア: upstreamパッチが現行ソースに適用できず
