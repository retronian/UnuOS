# Localization

UnuOS supports localized text for the launcher, Settings, Tools labels, and libretro core options.

## Supported Languages

- English
- Japanese
- Simplified Chinese
- Traditional Chinese
- Korean
- Spanish
- French

## Changing Language

Choose the language from Settings in the launcher. The selected language is applied immediately.

The setting is saved in shared user data on the SD card.

```text
/.userdata/shared/lang.txt
```

The file contains one language code.

```text
en
ja
zh_cn
zh_tw
ko
es
fr
```

If `lang.txt` does not exist, or if it contains an unsupported value, UnuOS uses English.

## Localized Areas

Localization covers:

- Main launcher UI
- Settings language selection
- Built-in Tools menu labels
- minarch menu items
- libretro core options

## CJK Text

UnuOS bundles Noto Sans CJK fonts so Japanese, Chinese, and Korean ROM names and UI strings render correctly. ROM name truncation is also UTF-8 safe and avoids cutting multi-byte characters in the middle.

## Notes

- User-created ROM names and collection names should be saved as UTF-8.
- Core option translations depend on each libretro core's translation tables and UnuOS integration.
- External Tools packages are shown as-is unless UnuOS has a built-in localized label for that tool.
