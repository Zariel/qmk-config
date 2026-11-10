# QMK keyboard configuration

This repository contains QMK keymaps and firmware build targets, using
[external userspace](https://docs.qmk.fm/newbs_external_userspace).
GitHub Actions builds the targets in [`qmk.json`](qmk.json) on pushes, pull
requests, and manual runs. Download the `Firmware` artifact from a successful
run of [Build firmware](https://github.com/Zariel/qmk-config/actions/workflows/build.yml).

## Keyboards

| Keyboard | Controller | QMK target | Keymap |
| --- | --- | --- | --- |
| Mechboards Corne Pro R2G, 42 keys | RP2040 | `mechboards/crkbd/r2g/6col` | [`chris`](keyboards/mechboards/crkbd/r2g/6col/keymaps/chris/) |

The connected keyboard identifies as USB `7171:0013`, and the Vial UID in
[`backups/corne.vil`](backups/corne.vil) matches Mechboards' R2G definition.
This board has its own matrix wiring, split transport, displays, and encoder
support. The upstream `crkbd/r2g` and `mechboards/crkbd/pro` targets describe
different hardware.

Builds use [Mechboards' firmware fork](https://github.com/MechboardsLTD/vial-qmk/tree/1bf4f3183a8d05ef2ff1010a61740071bfa69139/keyboards/mechboards/crkbd/r2g),
pinned in [the workflow](.github/workflows/build.yml). Although the source fork
supports Vial, this keymap builds without VIA or Vial: edit the source and
rebuild to change the layout.

## Build locally

Enter the development shell from this repository:

```sh
nix develop
```

The locked flake provides QMK, its ARM and AVR compiler toolchains, Make,
flashing tools, Git, Python, and `lsusb` on Linux.

Set up the firmware dependency once, using the same revision as CI:

```sh
qmk setup MechboardsLTD/vial-qmk -b r2g -H "$PWD/qmk_firmware"
git -C qmk_firmware checkout --detach 1bf4f3183a8d05ef2ff1010a61740071bfa69139
git -C qmk_firmware submodule update --init --recursive
```

These Git commands operate on the separate firmware dependency. Use `jj` for
this configuration repository. The firmware checkout and build outputs are
ignored by version control.

Build all configured targets from this repository:

```sh
export QMK_HOME="$PWD/qmk_firmware"
qmk userspace-list
qmk userspace-compile -j 4
```

The output is `mechboards_crkbd_r2g_6col_chris.uf2` in this repository's root.
To build only the Corne:

```sh
qmk compile -kb mechboards/crkbd/r2g/6col -km chris -j 4
```

QMK detects this userspace from `qmk.json` when you run commands here. To use it
from other directories, set `qmk config user.overlay_dir="$PWD"` from this
repository.

## Flash the Corne

Flash both halves with the same UF2 when installing this firmware. Handedness
is detected by the board's hardware pin.

1. Unplug USB before disconnecting the cable between the halves.
2. Connect one half to USB while holding its silver boot button underneath the
   PCB. It appears as an `RPI-RP2` drive.
3. Copy `mechboards_crkbd_r2g_6col_chris.uf2` onto that drive. The half reboots.
4. Repeat for the other half, then unplug USB, reconnect the halves, and plug
   USB back in.
5. Check keys on both halves, the NAV/SYM/FN layers, one-shot modifiers, RGB,
   displays, and any fitted encoders.

You can also run `qmk flash -kb mechboards/crkbd/r2g/6col -km chris` and put
the connected half into bootloader mode when prompted.

## Layout

[`keymap.c`](keyboards/mechboards/crkbd/r2g/6col/keymaps/chris/keymap.c) is the
editable layout, arranged in physical order: three rows across both halves,
six thumbs, then the two encoder presses.

The initial layout is transcribed from [`backups/corne.vil`](backups/corne.vil),
copied from `../corne.vil`. **The export still needs to be checked against the
live keyboard in Vial.** The TOTEM keymap in `../zmk-config` is a related layout
with later changes; this import preserves the Corne export instead.

| Layer | Access | Contents |
| --- | --- | --- |
| BASE | Default | QWERTY, one-shot Ctrl/Shift/GUI, six thumb keys |
| NAV | Hold the left middle thumb | Numbers, one-shot modifiers, arrows, navigation, Caps Word, Alt shortcuts |
| SYM | Hold the right middle thumb | Numbers, symbols, Shift/equals mod-tap |
| FN | Hold NAV then the right middle thumb, or SYM then the left middle thumb | F1–F12, RGB controls, Print Screen, Ctrl+Shift+GUI |

The encoder map preserves left volume and right previous/next track, with
transparent bindings on the other layers. Encoder presses preserve `A` and `B`
on every layer, as recorded in the export.

Tap-hold timing is 200 ms; one-shot modifiers expire after 5 seconds and lock
after five taps. These values come from the Vial settings. The export's 175 ms
value is its disabled Auto Shift timeout, not the tap-hold term.

Symbol keycodes preserve the export's HID usages and modifiers. The host's
keyboard layout determines the characters they produce.

## Add a keyboard or update dependencies

Add a keymap under `keyboards/<target>/keymaps/<name>/`, then register it with:

```sh
qmk userspace-add -kb <target> -km <name>
```

CI and `qmk userspace-compile` both read the resulting `qmk.json` target list.

To update the development tools, run `nix flake update nixpkgs`. To update the
firmware source, change `qmk_ref` in the workflow, check out that same revision
in the local firmware dependency, and update its submodules. Build all targets
before accepting either update.
