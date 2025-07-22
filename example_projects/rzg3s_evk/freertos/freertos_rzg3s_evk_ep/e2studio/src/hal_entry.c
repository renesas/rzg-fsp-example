/***********************************************************************************************************************
 * File Name    : hal_entry.c
 * Description  : Contains data structures and functions used in hal_entry.c.
 **********************************************************************************************************************/
/*
 * Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hal_data.h"
#include "xspi_init.h"
#include "ca55_start.h"
#include "cm33_fpu_start.h"
#include "FreeRTOS.h"
#include "semphr.h"

FSP_CPP_HEADER
void R_BSP_WarmStart(bsp_warm_start_event_t event);

FSP_CPP_FOOTER


/*******************************************************************************************************************//**
 * This function is called at various points during the startup process.  This implementation uses the event that is
 * called right before main() to set up the pins.
 *
 * @param[in]  event    Where at in the start up process the code is currently at
 **********************************************************************************************************************/
void R_BSP_WarmStart (bsp_warm_start_event_t event)
{
    if (BSP_WARM_START_RESET == event)
    {
    }

    if (BSP_WARM_START_POST_C == event)
    {
        /* C runtime environment and system clocks are setup. */

        /* Configure pins. */
        R_IOPORT_Open(&IOPORT_CFG_CTRL, &IOPORT_CFG_NAME);

        if (0 == (R_SYSC_SYS_LSI_MODE_STAT_BOOTCPUSEL_Msk & R_SYSC->SYS_LSI_MODE))
        {
            xspi_open();

#if BSP_CFG_MCU_LAUNCH_CM33_FPU

            /* Load Cortex-M33_FPU program to SRAM(MCPU) */
            load_cm33fpu_prog();

            /* Release reset of Cortex-M33_FPU */
            release_reset_cm33_fpu();
#endif

#if BSP_CFG_MCU_LAUNCH_CA55

            /* Load Cortex-A55 program to SRAM(ACPU) */
            load_ca55_prog();

            xspi_close();

            /* Release reset of Cortex-A55(Core0) */
            release_reset_ca55();
#endif
        }
    }
}
