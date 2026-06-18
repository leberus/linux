// SPDX-License-Identifier: GPL-2.0-only
/*
 * ARC700 mmap
 *
 * (started from arm version - for VIPT alias handling)
 *
 * Copyright (C) 2013 Synopsys, Inc. (www.synopsys.com)
 */

#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/mman.h>
#include <linux/sched/mm.h>

#include <asm/cacheflush.h>

/*
 * Ensure that shared mappings are correctly aligned to
 * avoid aliasing issues with VIPT caches.
 * We need to ensure that
 * a specific page of an object is always mapped at a multiple of
 * SHMLBA bytes.
 */
bool arch_shared_mmap_aligned(unsigned long addr, unsigned long pgoff)
{
	return !((addr - (pgoff << PAGE_SHIFT)) & (SHMLBA - 1));
}

bool arch_shared_mmap_aliasing(void)
{
	return true;
}

static const pgprot_t protection_map[16] = {
	[VM_NONE]					= PAGE_U_NONE,
	[VM_READ]					= PAGE_U_R,
	[VM_WRITE]					= PAGE_U_R,
	[VM_WRITE | VM_READ]				= PAGE_U_R,
	[VM_EXEC]					= PAGE_U_X_R,
	[VM_EXEC | VM_READ]				= PAGE_U_X_R,
	[VM_EXEC | VM_WRITE]				= PAGE_U_X_R,
	[VM_EXEC | VM_WRITE | VM_READ]			= PAGE_U_X_R,
	[VM_SHARED]					= PAGE_U_NONE,
	[VM_SHARED | VM_READ]				= PAGE_U_R,
	[VM_SHARED | VM_WRITE]				= PAGE_U_W_R,
	[VM_SHARED | VM_WRITE | VM_READ]		= PAGE_U_W_R,
	[VM_SHARED | VM_EXEC]				= PAGE_U_X_R,
	[VM_SHARED | VM_EXEC | VM_READ]			= PAGE_U_X_R,
	[VM_SHARED | VM_EXEC | VM_WRITE]		= PAGE_U_X_W_R,
	[VM_SHARED | VM_EXEC | VM_WRITE | VM_READ]	= PAGE_U_X_W_R
};
DECLARE_VM_GET_PAGE_PROT
