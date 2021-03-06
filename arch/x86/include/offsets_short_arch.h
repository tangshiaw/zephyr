/*
 * Copyright (c) 2016 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _offsets_short_arch__h_
#define _offsets_short_arch__h_

#include <offsets.h>

/* kernel */

#define _kernel_offset_to_isf \
	(___kernel_t_arch_OFFSET + ___kernel_arch_t_isf_OFFSET)

/* end - kernel */

/* threads */

#define _thread_offset_to_excNestCount \
	(___thread_t_arch_OFFSET + ___thread_arch_t_excNestCount_OFFSET)

#define _thread_offset_to_esp \
	(___thread_t_callee_saved_OFFSET + ___callee_saved_t_esp_OFFSET)

#define _thread_offset_to_coopFloatReg \
	(___thread_t_arch_OFFSET + ___thread_arch_t_coopFloatReg_OFFSET)

#define _thread_offset_to_preempFloatReg \
	(___thread_t_arch_OFFSET + ___thread_arch_t_preempFloatReg_OFFSET)

/* end - threads */

#endif /* _offsets_short_arch__h_ */
