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

| デバイス | 状態 |
| -- | -- |
| Miyoo Mini Plus | Active |

その他のデバイス対応は今後追加予定です。

## ベースプロジェクト

OneOSは[MinUI](https://github.com/shauninman/MinUI)のフォークです。upstreamの素晴らしい仕事に感謝します。

## ライセンス

MinUIのライセンスを継承します。フォント `NotoSansCJKjp-Bold.otf` はSIL Open Font License (OFL) 1.1に基づき配布されています。
