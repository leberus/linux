/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_HUGETLB_INLINE_H
#define _LINUX_HUGETLB_INLINE_H

#ifdef CONFIG_HUGETLB_PAGE

#include <linux/mm.h>

static inline bool is_vm_hugetlb_page(struct vm_area_struct *vma)
{
	return !!(vma->vm_flags & VM_HUGETLB);
}

static inline bool pmd_vma_hugetlb(pmd_t pmd, struct vm_area_struct *vma)
{
	return !!(pmd_leaf(pmd) && vma && is_vm_hugetlb_page(vma));
}

static inline bool pud_vma_hugetlb(pud_t pud, struct vm_area_struct *vma)
{
	return !!(pud_leaf(pud) && vma && is_vm_hugetlb_page(vma));
}

static inline bool p4d_vma_hugetlb(p4d_t pud, struct vm_area_struct *vma)
{
	return !!(p4d_leaf(p4d) && vma && is_vm_hugetlb_page(vma));
}

#else

static inline bool is_vm_hugetlb_page(struct vm_area_struct *vma)
{
	return false;
}

static inline bool pmd_vma_hugetlb(pmd_t pmd, struct vm_area_struct *vma)
{
	return false;
}

static inline bool pud_vma_hugetlb(pud_t pud, struct vm_area_struct *vma)
{
	return false;
}

static inline bool p4d_vma_hugetlb(p4d_t p4d, struct vm_area_struct *vma)
{
	return false;
}

#endif

#endif
