/*
 * Copyright (c) 2020-2021, NVIDIA CORPORATION.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __IMX477_I2C_TABLES__
#define __IMX477_I2C_TABLES__

#include <media/camera_common.h>

#define IMX477_TABLE_WAIT_MS 0
#define IMX477_TABLE_END 1
#define IMX477_WAIT_MS 1
#define IMX477_STANDBY_REG 0x0100

#define imx477_reg struct reg_8

#include "imx477_mode_common.h"
#include "imx477_mode_3840x2160_30fps.h"
#include "imx477_mode_1920x1080_60fps.h"
#include "imx477_mode_4032x3040_30fps.h"

static const imx477_reg imx477_start[] = {
	{IMX477_STANDBY_REG, 0x1},
	{IMX477_TABLE_WAIT_MS, IMX477_WAIT_MS*3},
	{IMX477_TABLE_END, 0x00}
};

static const imx477_reg imx477_stop[] = {
	{IMX477_STANDBY_REG, 0x0},
	{IMX477_TABLE_END, 0x00}
};

enum {
	IMX477_MODE_3840x2160_30FPS,
	IMX477_MODE_1920x1080_60FPS,
	IMX477_MODE_4032x3040_30FPS,
	IMX477_MODE_COMMON,
	IMX477_START_STREAM,
	IMX477_STOP_STREAM,
};

static const imx477_reg *mode_table[] = {
	[IMX477_MODE_3840x2160_30FPS] = imx477_mode_3840x2160_30fps,
	[IMX477_MODE_1920x1080_60FPS] = imx477_mode_1920x1080_60fps,
	[IMX477_MODE_4032x3040_30FPS] = imx477_mode_4032x3040_30fps,
	[IMX477_MODE_COMMON] = imx477_mode_common,
	[IMX477_START_STREAM] = imx477_start,
	[IMX477_STOP_STREAM] = imx477_stop,
};

static const int imx477_30_fr[] = {
	30,
};

static const int imx477_60_fr[] = {
	60,
};

static const struct camera_common_frmfmt imx477_frmfmt[] = {
	{{3840, 2160}, imx477_30_fr, 1, 0, IMX477_MODE_3840x2160_30FPS},
	{{1920, 1080}, imx477_60_fr, 1, 0, IMX477_MODE_1920x1080_60FPS},
	{{4032, 3040}, imx477_30_fr, 1, 0, IMX477_MODE_4032x3040_30FPS},
};
#endif /* __IMX477_I2C_TABLES__ */
