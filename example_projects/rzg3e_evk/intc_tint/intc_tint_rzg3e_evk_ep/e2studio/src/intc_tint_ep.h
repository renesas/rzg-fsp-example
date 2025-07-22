/***********************************************************************************************************************
 * File Name    : intc_tint_ep.h
 * Description  : Contains Macros and function declarations.
 **********************************************************************************************************************/
/*
 * Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef INTC_TINT_EP_H_
#define INTC_TINT_EP_H_

/* External IRQ channel*/
#define USER_SW_IRQ_NUMBER        (0x0E)        /* Channel 14 */

#define EP_INFO    "\r\nThis Example Project demonstrates the functionality of INTC_TINT driver.\r\n" \
    "On pressing the user push button, an external IRQ is triggered, which toggles user LED.\r\n"


/* Function declaration */
fsp_err_t intc_tint_init(void);
fsp_err_t intc_tint_enable(void);
void intc_tint_deinit(void);

#endif /* INTC_TINT_EP_H_ */
