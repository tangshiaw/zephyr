/*
 * Copyright (c) 2013-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Exception/interrupt context helpers for Cortex-M CPUs
 *
 * Exception/interrupt context helpers.
 */

#ifndef _ARM_CORTEXM_ISR__H_
#define _ARM_CORTEXM_ISR__H_

#include <arch/cpu.h>
#include <asm_inline.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _ASMLANGUAGE

/* nothing */

#else

/**
 *
 * @brief Find out if running in an ISR context
	 *
 * The current executing vector is found in the IPSR register. We consider the
 * IRQs (exception 16 and up), and the SVC, PendSV, and SYSTICK exceptions,
 * to be interrupts. Taking a fault within an exception is also considered in
 * interrupt context.
 *
 * @return 1 if in ISR, 0 if not.
 */
static ALWAYS_INLINE int _IsInIsr(void)
{
	uint32_t vector = _IpsrGet();

	/*
	 * IRQs + PendSV (14) + SVC (11) + SYSTICK (15) are interrupts.
	 * Vectors 12 and 13 are reserved, we'll never be in there
	 * On ARMv6-M there is no nested execution bit, so we check exception 3,
	 * hard fault, to a detect a nested exception.
	 */
#if defined(CONFIG_ARMV6_M)
	return (vector > 10) || (vector == 3);
#elif defined(CONFIG_ARMV7_M)
	return (vector > 10) || (vector && _ScbIsNestedExc());
#else
#error Unknown ARM architecture
#endif /* CONFIG_ARMV6_M */
}

/**
 * @brief Setup system exceptions
 *
 * Set exception priorities to conform with the BASEPRI locking mechanism.
 * Set PendSV priority to lowest possible.
 *
 * Enable fault exceptions.
 *
 * @return N/A
 */
static ALWAYS_INLINE void _ExcSetup(void)
{
	_ScbExcPrioSet(_EXC_PENDSV, _EXC_PRIO(0xff));

#ifdef CONFIG_CPU_CORTEX_M_HAS_BASEPRI
	_ScbExcPrioSet(_EXC_SVC, _EXC_PRIO(_EXC_SVC_PRIO));
#endif

#ifdef CONFIG_CPU_CORTEX_M_HAS_PROGRAMMABLE_FAULT_PRIOS
	_ScbExcPrioSet(_EXC_MPU_FAULT, _EXC_PRIO(_EXC_FAULT_PRIO));
	_ScbExcPrioSet(_EXC_BUS_FAULT, _EXC_PRIO(_EXC_FAULT_PRIO));
	_ScbExcPrioSet(_EXC_USAGE_FAULT, _EXC_PRIO(_EXC_FAULT_PRIO));

	_ScbUsageFaultEnable();
	_ScbBusFaultEnable();
	_ScbMemFaultEnable();
#endif
}

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif


#endif /* _ARM_CORTEXM_ISR__H_ */
