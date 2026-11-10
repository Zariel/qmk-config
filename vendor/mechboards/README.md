# Mechboards Corne Pro R2G support

This directory contains the board support needed to build the 42-key RP2040
Corne Pro R2G against upstream QMK. `make prepare` copies only the
`mechboards/crkbd/r2g` subtree into QMK; it does not replace upstream's shared
Mechboards files or firmware core.

## Origin and license

- Repository: <https://github.com/MechboardsLTD/vial-qmk>
- Revision: `1bf4f3183a8d05ef2ff1010a61740071bfa69139` (`r2g` branch)
- Board source: `keyboards/mechboards/crkbd/r2g/`
- Shared source: `keyboards/mechboards/common/`
- License: [GPLv2](../../LICENSES/GPL-2.0.txt), with the option of later
  versions where a file's SPDX header specifies `GPL-2.0-or-later`.

The original copyright and SPDX notices are retained. Files without their own
headers are covered by the upstream repository's GPLv2 license; they are not
covered by this repository's MIT license.

Only the 6-column board definition is included. The upstream default/Vial
keymaps, 5-column variant, OLED code, and Pixellari font assets are omitted.
The editable keymap remains outside the vendored tree in `keyboards/`.

## Local modifications

Adapted by Chris Bannister on 2026-11-10:

- Moved `display_lcd.c`, `display_lcd.h`, `rgb_effects.h`, and
  `split_matrix_add_enc.c` from the shared directory into the R2G directory.
- Updated includes in `config.h` and `r2g.c`, and source paths in `rules.mk`
  and `post_rules.mk`, to keep this port local to its board.
- Removed `rgb_matrix_get_mode_name()` from `display_lcd.c`. Upstream QMK
  provides this function when `RGB_MATRIX_MODE_NAME_ENABLE` is enabled.
- Replaced the Pixellari font references in `display_lcd.c` and
  `display_lcd.h` with Pixelify Sans. Font sources and notices live in
  [`../pixelify-sans/`](../pixelify-sans/).

The electrical matrix, encoder switch scanning, split transport, pin mapping,
handedness, RGB layout, and display wiring are retained from Mechboards.
Updating QMK does not update this vendored port automatically. Check changes
against the recorded source and review compatibility when updating either.
