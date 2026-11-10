// Local adaptation by Chris Bannister, 2026-11-10.
// Copyright 2026 Mechboards
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "qp.h"
#include "painter/generic/qp_surface.h"

extern painter_device_t      lcd;
extern painter_device_t      surface;
extern painter_font_handle_t pixelify_14;
extern painter_font_handle_t pixelify_18;
extern painter_font_handle_t pixelify_24;

void display_init_kb(void);
bool display_init_user(void);
void display_task_kb(void);
bool display_task_user(void);
