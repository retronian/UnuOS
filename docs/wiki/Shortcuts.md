This page is the complete shortcut reference for UnuOS. It covers the launcher, Settings, gameplay, the in-game menu, screenshots, power, volume, and brightness controls.

## Button Names

UnuOS uses these generic button names:

| Name | Meaning |
| --- | --- |
| `A` | Confirm / open |
| `B` | Back / cancel |
| `X` | Resume the selected game when a resume state exists |
| `MENU` | Open info in the launcher, open the in-game menu during gameplay |
| `START` | Start button |
| `SELECT` | Select button |
| `L1` / `R1` | Shoulder buttons |
| `L2` / `R2` | Trigger buttons, when the device has them |
| `L3` / `R3` | Stick buttons, when the device has them |
| `POWER` | Power button, when the device has one |

Some devices do not have a dedicated `MENU` button:

| Device | `MENU` substitute |
| --- | --- |
| Powkiddy RGB30 | `L3` or `R3` |
| Anbernic M17 | `+` or `-` |

## Launcher

These shortcuts apply while browsing games, folders, collections, tools, and Settings in the UnuOS launcher.

| Shortcut | Action |
| --- | --- |
| `UP` / `DOWN` | Move the selection one item |
| `LEFT` / `RIGHT` | Page up or page down |
| `L1` / `R1` | Jump to the previous or next alphabetical section |
| `A` | Open the selected item or launch the selected game |
| `B` | Go back to the previous folder |
| `X` | Resume the selected game, if a resume state is available |
| `Y` | Add or remove the selected game from Favorites |
| `SELECT` + `Y` | Toggle Game Focus Mode, showing only favorite games |
| Tap `MENU` | Show or hide the launcher info screen |
| `SELECT` + `START` | Save a screenshot |

## Settings

These shortcuts apply inside the built-in Settings screens.

| Shortcut | Action |
| --- | --- |
| `UP` / `DOWN` | Move the selection |
| `LEFT` / `RIGHT` | Change the selected option, where available |
| `A` | Confirm, open, or save the selected item |
| `B` | Back / cancel |
| `X` | Clear a button binding on input-binding screens |
| `SELECT` + `START` | Save a screenshot |

Button binding screens accept both single buttons and `MENU` + button combinations.

## Screenshots

| Shortcut | Action |
| --- | --- |
| `SELECT` + `START` | Save a BMP screenshot of the current screen |

Screenshots work from the launcher, Settings, gameplay, the in-game menu, and save state screens. Files are saved to:

```text
/Screenshots/YYYY-MM-DD_HH-MM-SS.bmp
```

## Power And Sleep

UnuOS automatically sleeps after 30 seconds without input. Manual sleep and wake shortcuts depend on the device.

| Device | Sleep | Wake |
| --- | --- | --- |
| Miyoo Mini | `POWER` | `POWER` |
| Trimui Smart / Anbernic M17 | `MENU` twice | `MENU` |
| RGB30 / Miyoo Mini Plus / RG35XX family / Trimui Smart Pro / Trimui Brick / GKD Pixel / Miyoo A30 / MagicX XU Mini M / Miyoo Flip / MagicX Mini Zero 28 | `POWER` | `POWER` |

During gameplay, powering off creates a quicksave when possible. The next boot resumes from that state automatically. On devices without a real `POWER` button, use the manual sleep shortcut before switching the device off.

## Volume And Brightness

| Device | Volume | Brightness |
| --- | --- | --- |
| Miyoo Mini | `SELECT` + `L1` / `R1` | `START` + `L1` / `R1` |
| Trimui Smart / Anbernic M17 | `SELECT` + `L1` / `R1` | `START` + `L1` / `R1` |
| RGB30 / Miyoo Mini Plus / RG35XX family / Trimui Smart Pro / Trimui Brick / GKD Pixel / Miyoo A30 / MagicX XU Mini M / Miyoo Flip / MagicX Mini Zero 28 | Hardware volume buttons | `MENU` + volume up / volume down |

Trimui Smart Pro and Trimui Brick also support the `FN` switch for mute.

## Gameplay

These controls apply while a game is running.

There are two different kinds of controls during gameplay:

- Game controls are the normal buttons sent to the emulator core.
- Gameplay shortcuts are UnuOS actions such as save state, load state, reset, quit, scaling, effects, and fast-forward.

By default, game controls are mapped, and the most common gameplay shortcuts are preassigned.

Default game control mapping:

| Emulator input | Device button |
| --- | --- |
| D-pad Up / Down / Left / Right | `UP` / `DOWN` / `LEFT` / `RIGHT` |
| A Button | `A` |
| B Button | `B` |
| X Button | `X` |
| Y Button | `Y` |
| Start | `START` |
| Select | `SELECT` |
| L1 Button | `L1` |
| R1 Button | `R1` |
| L2 Button | `L2` |
| R2 Button | `R2` |
| L3 Button | `L3` |
| R3 Button | `R3` |

Some console paks override this mapping where the original system uses different button names. For example, Mega Drive / Genesis uses `SELECT` as Mode.

| Shortcut | Action |
| --- | --- |
| Tap `MENU` | Open the in-game menu |
| `SELECT` + `START` | Save a screenshot |
| Power / sleep shortcut | Sleep or power off, creating a quicksave when possible |
| Configured shortcut | Run the action assigned in `Options` -> `Shortcuts` |

Default gameplay shortcut mapping:

| Shortcut action | Default button |
| --- | --- |
| Save State | `MENU` + `R1` |
| Load State | `MENU` + `L1` |
| Reset Game | `NONE` |
| Save & Quit | `NONE` |
| Cycle Scaling | `NONE` |
| Cycle Effect | `NONE` |
| Toggle Fast Forward | `MENU` + `X` |
| Hold Fast Forward | `NONE` |

You can configure gameplay shortcuts per console or per game from the in-game menu.

## Configurable Gameplay Shortcuts

Open the in-game menu, then go to:

```text
Options -> Shortcuts
```

Available shortcut actions:

| Action | Description |
| --- | --- |
| Save State | Save the current state |
| Load State | Load the current state |
| Reset Game | Reset the running game |
| Save & Quit | Save state, then quit to the launcher |
| Cycle Scaling | Switch to the next screen scaling mode |
| Cycle Effect | Switch to the next screen effect |
| Toggle Fast Forward | Toggle fast-forward on or off |
| Hold Fast Forward | Fast-forward while the assigned button is held |

Each action can be bound to a single button or to `MENU` + another button. `X` clears a binding while editing shortcuts.

## In-Game Menu

Tap `MENU` during gameplay to open the in-game menu.

| Shortcut | Action |
| --- | --- |
| `UP` / `DOWN` | Move between menu items |
| `A` | Confirm the selected item |
| `B` | Close the menu and continue the game |
| Tap `MENU` | Close the menu and continue the game on devices where `MENU` is not the wake button |
| `LEFT` / `RIGHT` on Save or Load | Change save state slot |
| `LEFT` / `RIGHT` on Continue for multi-disc games | Change disc |
| `SELECT` + `START` | Save a screenshot |

In simple mode, the in-game menu replaces `Options` with `Reset`.

## In-Game Options

These shortcuts apply inside in-game `Options`.

| Shortcut | Action |
| --- | --- |
| `UP` / `DOWN` | Move the selection |
| `LEFT` / `RIGHT` | Change the selected option |
| `A` | Confirm, open a submenu, or start assigning a button |
| `B` | Back / close Options |
| `X` | Clear a button binding on input-binding screens |
| `SELECT` + `START` | Save a screenshot |

Button binding screens support single buttons and `MENU` + button combinations.
