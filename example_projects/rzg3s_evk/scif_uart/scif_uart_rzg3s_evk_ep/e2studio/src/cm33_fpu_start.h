/*
 * Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef CM33_FPU_START_H_
#define CM33_FPU_START_H_

#define CM33_FPU_RESET_VECTOR_ADDRESS    (0x00060000) /* Please specify the address in MCPU SRAM. */

#define RZG3S_XSPI_BASE_ADDR             (0x80000000)
#define RZG3S_SPIROM_CM33FPU_BASE        (RZG3S_XSPI_BASE_ADDR + 0x00240000)
#define RZG3S_SPIROM_CM33FPU_LIMIT       (RZG3S_XSPI_BASE_ADDR + 0x00280000)
#define CM33FPU_FW_BASE                  (RZG3S_SPIROM_CM33FPU_BASE)
#define CM33FPU_FW_LIMIT                 (RZG3S_SPIROM_CM33FPU_LIMIT)
#define RZG3S_CM33FPU_FW_SIZE_MAX        (CM33FPU_FW_LIMIT - CM33FPU_FW_BASE)

void load_cm33fpu_prog(void);
void release_reset_cm33_fpu(void);

#endif
