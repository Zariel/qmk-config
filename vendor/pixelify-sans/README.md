# Pixelify Sans display font

Copyright 2021 The Pixelify Sans Project Authors
(<https://github.com/eifetx/Pixelify-Sans>).

The font is distributed under the [SIL Open Font License 1.1](OFL.txt).
`PixelifySans.ttf` is the unmodified variable font from
[Google Fonts](https://github.com/google/fonts/tree/8b0a1d0f5983c89bc2b93f1b5fb55f9e252744b5/ofl/pixelifysans),
revision `8b0a1d0f5983c89bc2b93f1b5fb55f9e252744b5`. Its upstream filename
is `PixelifySans[wght].ttf`.

`generated/` contains the ASCII glyph images and QMK Quantum Painter C/header
assets at 18 and 24 pixels. The generated C wrappers retain QMK's
GPL-2.0-or-later notice; the font data retains its OFL license. `make prepare`
copies the C/header assets into the R2G board's `qp_font/` directory.

To regenerate the assets from this repository's root, enter `nix develop`,
set `QMK_HOME` to the prepared QMK checkout, and run:

```sh
for size in 18 24; do
    qmk painter-make-font-image \
        -f vendor/pixelify-sans/PixelifySans.ttf -s "$size" --no-aa \
        -o "vendor/pixelify-sans/generated/pixelify$size.png"
    qmk painter-convert-font-image \
        -i "vendor/pixelify-sans/generated/pixelify$size.png" \
        -f mono2 -o vendor/pixelify-sans/generated
done
```
