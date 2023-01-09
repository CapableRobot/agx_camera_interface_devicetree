/*
 * Copyright (c) 2020-2021, NVIDIA CORPORATION.  All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <nvgpu/gk20a.h>

#include "perf_ga100.h"

#include <nvgpu/hw/ga100/hw_perf_ga100.h>

static const u32 hwpm_sys_perfmon_regs[] =
{
	/* This list is autogenerated. Do not edit. */
	0x00260000,
	0x00260004,
	0x00260008,
	0x0026000c,
	0x00260010,
	0x00260014,
	0x00260020,
	0x00260024,
	0x00260028,
	0x0026002c,
	0x00260030,
	0x00260034,
	0x00260040,
	0x00260044,
	0x00260048,
	0x0026004c,
	0x00260050,
	0x00260054,
	0x00260058,
	0x0026005c,
	0x00260060,
	0x00260064,
	0x00260068,
	0x0026006c,
	0x00260070,
	0x00260074,
	0x00260078,
	0x0026007c,
	0x00260080,
	0x00260084,
	0x00260088,
	0x0026008c,
	0x00260090,
	0x00260094,
	0x00260098,
	0x0026009c,
	0x002600a0,
	0x002600a4,
	0x002600a8,
	0x002600ac,
	0x002600b0,
	0x002600b4,
	0x002600b8,
	0x002600bc,
	0x002600c0,
	0x002600c4,
	0x002600c8,
	0x002600cc,
	0x002600d0,
	0x002600d4,
	0x002600d8,
	0x002600dc,
	0x002600e0,
	0x002600e4,
	0x002600e8,
	0x002600ec,
	0x002600f8,
	0x002600fc,
	0x00260104,
	0x00260108,
	0x0026010c,
	0x00260110,
	0x00260128,
	0x00260114,
	0x00260118,
	0x0026011c,
	0x00260124,
	0x00260130,
	0x00260100,
};

static const u32 hwpm_gpc_perfmon_regs[] =
{
	/* This list is autogenerated. Do not edit. */
	0x00278000,
	0x00278004,
	0x00278008,
	0x0027800c,
	0x00278010,
	0x00278014,
	0x00278020,
	0x00278024,
	0x00278028,
	0x0027802c,
	0x00278030,
	0x00278034,
	0x00278040,
	0x00278044,
	0x00278048,
	0x0027804c,
	0x00278050,
	0x00278054,
	0x00278058,
	0x0027805c,
	0x00278060,
	0x00278064,
	0x00278068,
	0x0027806c,
	0x00278070,
	0x00278074,
	0x00278078,
	0x0027807c,
	0x00278080,
	0x00278084,
	0x00278088,
	0x0027808c,
	0x00278090,
	0x00278094,
	0x00278098,
	0x0027809c,
	0x002780a0,
	0x002780a4,
	0x002780a8,
	0x002780ac,
	0x002780b0,
	0x002780b4,
	0x002780b8,
	0x002780bc,
	0x002780c0,
	0x002780c4,
	0x002780c8,
	0x002780cc,
	0x002780d0,
	0x002780d4,
	0x002780d8,
	0x002780dc,
	0x002780e0,
	0x002780e4,
	0x002780e8,
	0x002780ec,
	0x002780f8,
	0x002780fc,
	0x00278104,
	0x00278108,
	0x0027810c,
	0x00278110,
	0x00278128,
	0x00278114,
	0x00278118,
	0x0027811c,
	0x00278124,
	0x00278130,
	0x00278100,
};

static const u32 hwpm_fbp_perfmon_regs[] =
{
	/* This list is autogenerated. Do not edit. */
	0x0027c000,
	0x0027c004,
	0x0027c008,
	0x0027c00c,
	0x0027c010,
	0x0027c014,
	0x0027c020,
	0x0027c024,
	0x0027c028,
	0x0027c02c,
	0x0027c030,
	0x0027c034,
	0x0027c040,
	0x0027c044,
	0x0027c048,
	0x0027c04c,
	0x0027c050,
	0x0027c054,
	0x0027c058,
	0x0027c05c,
	0x0027c060,
	0x0027c064,
	0x0027c068,
	0x0027c06c,
	0x0027c070,
	0x0027c074,
	0x0027c078,
	0x0027c07c,
	0x0027c080,
	0x0027c084,
	0x0027c088,
	0x0027c08c,
	0x0027c090,
	0x0027c094,
	0x0027c098,
	0x0027c09c,
	0x0027c0a0,
	0x0027c0a4,
	0x0027c0a8,
	0x0027c0ac,
	0x0027c0b0,
	0x0027c0b4,
	0x0027c0b8,
	0x0027c0bc,
	0x0027c0c0,
	0x0027c0c4,
	0x0027c0c8,
	0x0027c0cc,
	0x0027c0d0,
	0x0027c0d4,
	0x0027c0d8,
	0x0027c0dc,
	0x0027c0e0,
	0x0027c0e4,
	0x0027c0e8,
	0x0027c0ec,
	0x0027c0f8,
	0x0027c0fc,
	0x0027c104,
	0x0027c108,
	0x0027c10c,
	0x0027c110,
	0x0027c128,
	0x0027c114,
	0x0027c118,
	0x0027c11c,
	0x0027c124,
	0x0027c130,
	0x0027c100,
};

const u32 *ga100_perf_get_hwpm_sys_perfmon_regs(u32 *count)
{
	*count = sizeof(hwpm_sys_perfmon_regs) / sizeof(hwpm_sys_perfmon_regs[0]);
	return hwpm_sys_perfmon_regs;
}

const u32 *ga100_perf_get_hwpm_gpc_perfmon_regs(u32 *count)
{
	*count = sizeof(hwpm_gpc_perfmon_regs) / sizeof(hwpm_gpc_perfmon_regs[0]);
	return hwpm_gpc_perfmon_regs;
}

const u32 *ga100_perf_get_hwpm_fbp_perfmon_regs(u32 *count)
{
	*count = sizeof(hwpm_fbp_perfmon_regs) / sizeof(hwpm_fbp_perfmon_regs[0]);
	return hwpm_fbp_perfmon_regs;
}

u32 ga100_perf_get_pmmsys_per_chiplet_offset(void)
{
	/*
	 * No register to find the offset of pmmsys register.
	 * Difference of pmmsys register address ranges plus 1 will provide
	 * the offset
	 */
	u32 reg_offset = 1U;

	return (perf_pmmsys_extent_v() - perf_pmmsys_base_v() + reg_offset);
}

u32 ga100_perf_get_pmmgpc_per_chiplet_offset(void)
{
	/*
	 * No register to find the offset of pmmgpc register.
	 * Difference of pmmgpc register address ranges plus 1 will provide
	 * the offset
	 */
	u32 reg_offset = 1U;

	return (perf_pmmgpc_extent_v() - perf_pmmgpc_base_v() + reg_offset);
}

u32 ga100_perf_get_pmmfbp_per_chiplet_offset(void)
{
	/*
	 * No register to find the offset of pmmfbp register.
	 * Difference of pmmfbp register address ranges plus 1 will provide
	 * the offset
	 */
	u32 reg_offset = 1U;

	return (perf_pmmfbp_extent_v() - perf_pmmfbp_base_v() + reg_offset);
}

void ga100_perf_get_num_hwpm_perfmon(struct gk20a *g, u32 *num_sys_perfmon,
				u32 *num_fbp_perfmon, u32 *num_gpc_perfmon)
{
	int err;
	u32 buf_offset_lo, buf_offset_addr, num_offsets;
	u32 perfmon_index = 0U;
	u32 max_offsets = 1U;

	for (perfmon_index = 0U; perfmon_index <
			perf_pmmsys_engine_sel__size_1_v();
			perfmon_index++) {
		err = g->ops.gr.get_pm_ctx_buffer_offsets(g,
				perf_pmmsys_engine_sel_r(perfmon_index),
				max_offsets,
				&buf_offset_lo,
				&buf_offset_addr,
				&num_offsets);
		if (err != 0U) {
			break;
		}
	}
	*num_sys_perfmon = perfmon_index;

	for (perfmon_index = 0U; perfmon_index <
			perf_pmmfbp_engine_sel__size_1_v();
			perfmon_index++) {
		err = g->ops.gr.get_pm_ctx_buffer_offsets(g,
				perf_pmmfbp_engine_sel_r(perfmon_index),
				max_offsets,
				&buf_offset_lo,
				&buf_offset_addr,
				&num_offsets);
		if (err != 0U) {
			break;
		}
	}
	*num_fbp_perfmon = perfmon_index;

	for (perfmon_index = 0U; perfmon_index <
			perf_pmmgpc_engine_sel__size_1_v();
			perfmon_index++) {
		err = g->ops.gr.get_pm_ctx_buffer_offsets(g,
				perf_pmmgpc_engine_sel_r(perfmon_index),
				max_offsets,
				&buf_offset_lo,
				&buf_offset_addr,
				&num_offsets);
		if (err != 0U) {
			break;
		}
	}
	*num_gpc_perfmon = perfmon_index;
}
