# QMK keyboard configuration

This repository contains QMK keymaps and firmware build targets, using
[external userspace](https://docs.qmk.fm/newbs_external_userspace).
GitHub Actions builds the targets in [`qmk.json`](qmk.json) on pushes, pull
requests, and manual runs. Download the `Firmware` artifact from a successful
run of [Build firmware](https://github.com/Zariel/qmk-config/actions/workflows/build.yml).
Each artifact includes a `firmware-source.tar.gz` containing the corresponding
QMK tree, submodules, keymap, board support, font sources, licenses, and build
instructions.

## Keyboards

| Keyboard | Controller | QMK target | Keymap |
| --- | --- | --- | --- |
| Mechboards Corne Pro R2G, 42 keys | RP2040 | `mechboards/crkbd/r2g/6col` | [`chris`](keyboards/mechboards/crkbd/r2g/6col/keymaps/chris/) |

The connected keyboard identifies as USB `7171:0013`, and the Vial UID in
[`backups/corne.vil`](backups/corne.vil) matches Mechboards' R2G definition.
This board has its own matrix wiring, split transport, displays, and encoder
support. The upstream `crkbd/r2g` and `mechboards/crkbd/pro` targets describe
different hardware.

Builds use upstream QMK **0.34.7**, pinned to an exact commit in
[`qmk.mk`](qmk.mk). The board support is [vendored locally](vendor/mechboards/README.md)
because upstream QMK does not include this R2G revision. The display uses
[Pixelify Sans](vendor/pixelify-sans/README.md), an OFL-licensed pixel font.
The keymap builds without VIA or Vial: edit the source and rebuild to change
the layout.

QMK publishes version tags and merges breaking changes from `develop` into
`master` on a roughly three-month cadence. Its default setup follows `master`;
this repository pins a tagged version and commit for repeatable builds. See
[QMK's release process](https://docs.qmk.fm/breaking_changes).

## Build locally

Enter the development shell from this repository:

```sh
nix develop
```

The locked flake provides QMK, its ARM and AVR compiler toolchains, Make,
flashing tools, Git, Python, and `lsusb` on Linux.

Set up the upstream firmware dependency once, using the same revision as CI:

```sh
make setup
```

This clones upstream QMK, checks out the pinned revision, and initializes its
submodules. If you have a Mechboards checkout at `qmk_firmware`, move it aside
before setup. Git commands run inside the separate firmware dependency; use
`jj` for this configuration repository. The checkout and build outputs are
ignored by version control.

Build all configured targets from this repository:

```sh
make build
```

The build checks the QMK revision and copies the vendored board support and
generated fonts into the firmware tree before compiling. The output is
`mechboards_crkbd_r2g_6col_chris.uf2` in this repository's root. Set `JOBS` to
control compiler parallelism, for example `make build JOBS=8`.

To create firmware and corresponding source downloads, as CI does:

```sh
make package
```

The files are written to `dist/`. To rebuild a downloaded source archive,
extract it, enter its root, run `nix develop path:.`, and run `make build`. The
archive already contains the complete QMK source and submodules, so skip
`make setup`.
Git metadata and build outputs are omitted from source archives; builds from
these archives use QMK's `SKIP_GIT` option.

For individual QMK commands after preparation:

```sh
export QMK_HOME="$PWD/qmk_firmware"
make prepare
qmk userspace-list
qmk compile -kb mechboards/crkbd/r2g/6col -km chris -j 4
```

QMK detects this userspace from `qmk.json` when you run commands here.

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

After `make prepare`, you can also set `QMK_HOME` as above, run
`qmk flash -kb mechboards/crkbd/r2g/6col -km chris`, and put the connected half
into bootloader mode when prompted.

## Layout

[`keymap.c`](keyboards/mechboards/crkbd/r2g/6col/keymaps/chris/keymap.c) is the
editable layout, arranged in physical order: three rows across both halves,
six thumbs, then the two encoder presses.

The base layer keeps the dedicated Tab, one-shot Control, Pipe, Quote, and
Escape bindings from [`backups/corne.vil`](backups/corne.vil). NAV remains a
hold-only thumb key. The archive is an unmodified copy of `../corne.vil` and
still needs to be checked against the live keyboard in Vial.

The other layers incorporate the improvements from the TOTEM keymap in
`../zmk-config`. The Corne retains all 42 keys and its RGB controls.

| Layer | Access | Contents |
| --- | --- | --- |
| BASE | Default | QWERTY, one-shot Ctrl/Shift/GUI, six thumb keys |
| NAV | Hold the left middle thumb | Numbers, one-shot modifiers, arrows, navigation, Caps Word, Alt shortcuts |
| SYM | Hold the right middle thumb | Numbers, symbols, Shift/equals mod-tap |
| FN | Hold NAV and SYM together, in either order | F1–F12, RGB, media, brightness, screenshots, bootloader, reset |

NAV's left home row provides one-shot Control, Alt, GUI, and Shift on A, S, D,
and F, followed by Caps Word on G. Arrows follow H/J/K/L ordering. The right
outer thumb falls through to dedicated Backspace.

On SYM, Grave is on G and Quote is on the Semicolon position. The left outer
thumb falls through to one-shot GUI, keeping Command/Super shortcuts available.
One-shot Shift remains on the outer-left bottom key, and Equal still acts as
Shift while held.

FN is active only while both NAV and SYM are held. Releasing either thumb
returns to the remaining layer; releasing both returns to BASE. Its bindings
are arranged in physical order below. `▽` is transparent, and `—` is disabled.

```text
RGB toggle   F1       F2       F3       F4       F5          F6       F7       F8       F9       F10       —
RGB next    F11      F12      Hue+     Sat+     Val+        Prev     Vol-     Play     Vol+      Next      —
Boot        Hue-     Sat-     Val-      —        —          Mute   Bright-  Bright+   Print    Mac Shot   Reset
                              GUI      ▽      Space       Enter     ▽     Backspace
```

`Mac Shot` sends Command+Shift+4; `Print` sends Print Screen. The media and
brightness bindings use standard HID consumer controls. Bootloader and reset
occupy the guarded bottom outer positions. RGB controls use positions available
on this wired board in place of TOTEM's Bluetooth profile and output controls.

The encoder map preserves left volume and right previous/next track, with
transparent bindings on the other layers. Encoder presses preserve `A` and `B`
on every layer, as recorded in the export.

Tap-hold timing remains 200 ms; one-shot modifiers expire after 5 seconds and
lock after five taps. These values come from the Vial settings. The export's
175 ms value is its disabled Auto Shift timeout, not the tap-hold term.

The host's keyboard layout determines the characters produced by symbol
keycodes.

## Add a keyboard or update dependencies

Add a keymap under `keyboards/<target>/keymaps/<name>/`, then register it with:

```sh
export QMK_HOME="$PWD/qmk_firmware"
qmk userspace-add -kb <target> -km <name>
```

CI and `qmk userspace-compile` both read the resulting `qmk.json` target list.

To update the development tools, run `nix flake update nixpkgs`. To update QMK,
change the version and commit in `qmk.mk`, then run `make setup` and
`make package`. Local and CI builds share this pin and build procedure. Check
the QMK changelog and verify the resulting firmware on the keyboard before
accepting an update.

## Licensing

Original configuration, build scripts, and documentation in this repository
are covered by the [MIT license](LICENSE). The Mechboards board support and
local adaptations under `vendor/mechboards/` are covered by
[GPLv2](LICENSES/GPL-2.0.txt), with the option of later versions where their
SPDX headers specify `GPL-2.0-or-later`. Their original notices are retained.
Pixelify Sans font data is covered by its
[SIL Open Font License 1.1](vendor/pixelify-sans/OFL.txt). QMK's generator
licenses the generated C wrappers under GPL-2.0-or-later while the font data
retains its original license.

The combined QMK firmware is distributed under GPLv2, with the applicable
third-party notices and corresponding source included in the `Firmware`
artifact. The MIT license does not replace the licenses of vendored code,
fonts, or QMK's dependencies.
