/*
 * Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef CA55_START_H_
#define CA55_START_H_

#define CA55_RESET_VECTOR_ADDRESS    (0x000A3000) /* Please specify the address in ACPU SRAM. */

#define RZG3S_XSPI_BASE_ADDRESS      (0x80000000)
#define RZG3S_SPIROM_BL2_BASE        (RZG3S_XSPI_BASE_ADDRESS + 0x00200000)
#define RZG3S_SPIROM_BL2_LIMIT       (RZG3S_XSPI_BASE_ADDRESS + 0x00240000)
#define BL2_BASE                     (RZG3S_SPIROM_BL2_BASE)
#define BL2_LIMIT                    (RZG3S_SPIROM_BL2_LIMIT)
#define RZG3S_BL2_SIZE_MAX           (BL2_LIMIT - BL2_BASE) /* This value is not checked/enforced anywhwere */

void release_reset_ca55(void);
void load_ca55_prog(void);

#endif
