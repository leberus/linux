// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microsystems co.,ltd.

#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/mman.h>
#include <linux/shm.h>
#include <linux/sched.h>
#include <linux/random.h>
#include <linux/io.h>

#define COLOUR_ALIGN(addr,pgoff)		\
	((((addr)+SHMLBA-1)&~(SHMLBA-1)) +	\
	 (((pgoff)<<PAGE_SHIFT) & (SHMLBA-1)))

/*
 * We need to ensure that shared mappings are correctly aligned to
 * avoid aliasing issues with VIPT caches.  We need to ensure that
 * a specific page of an object is always mapped at a multiple of
 * SHMLBA bytes.
 *
 * We unconditionally provide this function for all cases.
 */
bool arch_mappings_need_coloring(struct file *filp, unsigned long flags)
{
	return filp || (flags & MAP_SHARED)
}

bool arch_shared_mmap_aliasing(void)
{
	return true;
}

bool arch_shared_mmap_aligned(unsigned long addr, unsigned long pgoff)
{
	return !((addr - (pgoff << PAGE_SHIFT)) & (SHMLBA - 1));
}

unsigned long arch_mmap_addr_color_align(unsigned long addr, unsigned long pgoff)
{
	return COLOUR_ALIGN(addr, pgoff);
}

unsigned long arch_mmap_align_mask(bool do_color_align)
{
	if (do_color_align)
		return (PAGE_MASK & (SHMLBA - 1));
	return 0;
}
