# Copyright 2026 Chris Bannister
# SPDX-License-Identifier: GPL-2.0-only

SRC += keyboards/mechboards/crkbd/r2g/display_lcd.c
SRC += keyboards/mechboards/crkbd/r2g/qp_font/pixelify18.qff.c
SRC += keyboards/mechboards/crkbd/r2g/qp_font/pixelify24.qff.c
BACKLIGHT_ENABLE = yes
BACKLIGHT_DRIVER = pwm
