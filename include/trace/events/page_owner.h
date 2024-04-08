/* SPDX-License-Identifier: GPL-2.0 */
#undef TRACE_SYSTEM
#define TRACE_SYSTEM page_owner

#if !defined(_TRACE_PAGE_OWNER_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_PAGE_OWNER_H

#include <linux/tracepoint.h>

TRACE_EVENT(stack_record_list_alloc,

        TP_PROTO(struct stack *list, struct stack *p, struct stack_record *r),

        TP_ARGS(list, p, r),

        TP_STRUCT__entry(
                __field(struct stack *, list)
                __field(struct stack *, p)
                __field(struct stack_record *, r)
        ),

        TP_fast_assign(
                __entry->list = list;
                __entry->p = p;
                __entry->r    = r;
        ),

        TP_printk("list=%px p=%px r=%px",
		  __entry->list,
                  __entry->p,
                  __entry->r)
);

TRACE_EVENT(stack_record_list_add,

        TP_PROTO(struct stack *list, struct stack *p, struct stack *n, struct stack_record *r),

        TP_ARGS(list, p, n, r),

        TP_STRUCT__entry(
                __field(struct stack *, list)
                __field(struct stack *, p)
                __field(struct stack *, n)
                __field(struct stack_record *, r)
        ),

        TP_fast_assign(
                __entry->list = list;
                __entry->p = p;
                __entry->n = n;
                __entry->r    = r;
        ),

        TP_printk("list=%px p=%px n=%px r=%px",
		  __entry->list,
                  __entry->p,
                  __entry->n,
                  __entry->r)
);


#endif /* _TRACE_PAGE_OWNER_H */

/* This part must be outside protection */
#include <trace/define_trace.h>
