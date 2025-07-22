/*
 * Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "i2c_pmic.h"

/*******************************************************************************************************************//**
 * @addtogroup pd_all_on
 * @{
 **********************************************************************************************************************/

#if defined(BSP_FEATURE_BSP_HAS_CM33BOOT_SUPPORT) && (BSP_FEATURE_BSP_HAS_CM33BOOT_SUPPORT == 1)

/*******************************************************************************************************************//**
 *  @brief
 *  @param[IN]   None
 *  @retval      FSP_SUCCESS
 *  @retval      Any Other Error code apart from FSP_SUCCESS is  Unsuccessful open or start
 **********************************************************************************************************************/
fsp_err_t pd_all_on_postproc (void)
{
    fsp_err_t         err = FSP_SUCCESS;
    volatile uint32_t read_rstmon_reg;

    /* Allow access to RCPU-Bus(Initialize TZC400-RCPU) */
    R_TZC_AXI_RCPU->GATE_KEEPER        = 0x00000000; /* Close filter before initialization */
    R_TZC_AXI_RCPU->REGION_ID_ACCESS_0 = 0x000F000F; /* Permit Secure/Nonsecure access */
    R_TZC_AXI_RCPU->GATE_KEEPER        = 0x00000001; /* Open filter #0 */

    /* Release Reset of GIC */
    R_CPG->CPG_RST_3 = 0x4B004B00;

    do
    {
        read_rstmon_reg = R_CPG->CPG_RSTMON_1;
    } while ((read_rstmon_reg & 0x00009600) != 0x00000000);

    /* Allow access to xSPI(Initialize TZC400_XSPI) */
    R_TZC_XSPI->GATE_KEEPER         = 0x00000000; /* Close filter before initialization */
    R_TZC_XSPI->REGION_ID_ACCESS_0  = 0x000F000F; /* Permit Secure/Nonsecure access */
    R_TZC_XSPI->REGION_ATTRIBUTES_0 = 0x0000000F; /* Disable secure read/write access */
    R_TZC_XSPI->SPECULATION_CTRL    = 0x00000003; /* Disable read/write speculation */
    R_TZC_XSPI->GATE_KEEPER         = 0x0000000F; /* Open filter #0-#3 */

    return err;
}

#endif                                 /*defined(BSP_FEATURE_BSP_HAS_CM33BOOT_SUPPORT) && (BSP_FEATURE_BSP_HAS_CM33BOOT_SUPPORT == 1)*/

/*******************************************************************************************************************//**
 *  @brief
 *  @param[IN]   None
 *  @retval      FSP_SUCCESS
 *  @retval      Any Other Error code apart from FSP_SUCCESS is  Unsuccessful open or start
 **********************************************************************************************************************/
fsp_err_t pd_all_on_postproc_axi (void)
{
    fsp_err_t         err = FSP_SUCCESS;
    volatile uint32_t read_rstmon_reg;

    /* Allow access "from MCPU-Bus to ACPU-Bus" and "from ACPU-Bus to MCPU-Bus" */
    R_CPG->CPG_BUS_12_MSTOP = 0x06000000;

    /* Release reset of AXIs */
    R_CPG->CPG_RST_15 = 0x40004000;    /* Release reset of RCPU_AXI_RESETN and MCPU_AXI_RESETN */
    R_CPG->CPG_RST_16 = 0xFFFFFFFF;    /* Release reset of ACPU_AXI* and VIDEO_AXI* and DRP_AXI* and COM_AXI* and TZC_AXI* */
    R_CPG->CPG_RST_17 = 0x00070007;    /* Release reset of TZC_AXI* */

    do
    {
        read_rstmon_reg = R_CPG->CPG_RSTMON_7;
    } while ((read_rstmon_reg & 0xFFFF8000) != 0x00000000);

    do
    {
        read_rstmon_reg = R_CPG->CPG_RSTMON_8;
    } while ((read_rstmon_reg & 0x0000000F) != 0x00000000);

    return err;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup pd_all_on)
 **********************************************************************************************************************/
