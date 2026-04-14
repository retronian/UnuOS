# OneOS

OneOSはMiyoo Mini Plus向けのレトロゲームランチャー兼libretroフロントエンドです。[MinUI](https://github.com/shauninman/MinUI)をベースに、日本語をはじめとするCJK（中国語・韓国語含む）対応を加えたフォークです。

「One OS, All Handhelds」をコンセプトにした[Retronian](https://retronian.com)プロジェクトの中核OSです。

## 特徴

- シンプルなランチャー、シンプルなSDカード構成
- 設定や構成不要
- ボックスアート・テーマ・気を散らす要素なし
- **日本語・中国語・韓国語のROM名表示に対応**（Noto Sans CJK JP使用）
- 隠しファイル・拡張子・地域/バージョン情報を表示名から自動的に除去
- セーブステート・ディスク交換・エミュレータオプションへの統一されたメニュー
- 30秒で自動スリープ、POWER長押しでスリープ・復帰
- スリープ中2分で自動電源オフ、POWER長押し1秒で電源オフ
- 電源オフ時の状態から自動復帰
- ランチャーで X キーを押すと最後のセーブステートから再開
- 効率化されたエミュレータフロントエンド (minarch + libretroコア)

## 対応コンソール

ベース:

- ファミコン (NES)
- スーパーファミコン (SNES)
- ゲームボーイ
- ゲームボーイカラー
- ゲームボーイアドバンス
- メガドライブ (Genesis)
- プレイステーション

エクストラ:

- ネオジオポケット (カラー含む)
- セガゲームギア
- セガマークIII (Master System)
- スーパーゲームボーイ
- PCエンジン (TurboGrafx-16/CD)
- バーチャルボーイ

## 対応デバイス

OneOS は MinUI 由来の各プラットフォーム向けソースを保持しています。状態は以下の通り:

### 開発者が実機検証済み

| デバイス | platform | 状態 |
| -- | -- | -- |
| Miyoo Mini Plus | `miyoomini` | Active（主開発ターゲット） |

### コードベースに含まれるが未検証（動作する見込み）

これらは MinUI から継承したコードがあり、ビルド可能ですが maintainer による実機動作確認は未実施です。報告歓迎。

| デバイス | platform |
| -- | -- |
| Miyoo Mini / Miyoo Mini Flip | `miyoomini`（同一ビルドが内部でモデル判別） |
| Miyoo Flip | `my355` |
| Miyoo A30 | `my282` |
| Anbernic RG35XX Plus / H / 2024 / SP, RG34XX, RG CubeXX | `rg35xxplus`（同一ビルドが内部でモデル判別） |
| Anbernic RG35XX (旧モデル) | `rg35xx` |
| Anbernic M17 | `m17` |
| Trimui Smart | `trimuismart` |
| Trimui Smart Pro / Brick | `tg5040` |
| Powkiddy RGB30 | `rgb30` |
| MagicX XU Mini M | `magicmini` |
| MagicX Mini Zero 28 | `zero28` |
| GKD Pixel | `gkdpixel` |

### 対応予定（未着手）

| デバイス | 備考 |
| -- | -- |
| Anbernic RG 28XX | MinUI base に未収録。NextUI 等のフォークから移植検討中 |

## ベースプロジェクト

OneOSは[MinUI](https://github.com/shauninman/MinUI)のフォークです。upstreamの素晴らしい仕事に感謝します。

## ライセンス

MinUIのライセンスを継承します。フォント `NotoSansCJKjp-Bold.otf` はSIL Open Font License (OFL) 1.1に基づき配布されています。
