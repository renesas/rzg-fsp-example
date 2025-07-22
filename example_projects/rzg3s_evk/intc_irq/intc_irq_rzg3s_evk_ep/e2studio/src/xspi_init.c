/*
 * Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "xspi_init.h"
#include "ca55_start.h"

#define TZC_GATE_KEEP_OPEN_ALLFLT          (0x0000000Ful) /* Open all filter unit */
#define TZC_SPECUL_DIS_PREFETCH            (0x00000003ul) /* Disable pre-fetch */
#define TZC_RGN_ATTR_EN_ALLFLT             (0x0000000Ful) /* Enable all filter unit */
#define TZC_RGN_ID_ACC_EN_RDWR_NSAID0_1    (0x000F000Ful) /* Enable NSAIDW<x>: 0, 1, NSAIDR<x>: 0, 1   */

#define G3S_SYSC_IPCONT_SEL_SPI            (0x00000000)
#define G3S_SYSC_MAP_XSPI_CS0_START        (0x20000000)
#define G3S_SYSC_MAP_XSPI_CS0_END          (0x27FFFFFF)
#define G3S_SYSC_MAP_XSPI_CS1_START        (0x28000000)
#define G3S_SYSC_MAP_XSPI_CS1_END          (0x2fFFFFFF)
#define G3S_CPG_SPI_SSEL_WE                (0x00010000)
#define G3S_CPG_SPI_SSEL_400M              (0x00000000)
#define G3S_CPG_SPI_DDIV_WE                (0x00010000)
#define G3S_CPG_SPI_DDIV_4                 (0x00000002)
#define G3S_GPIO_XSPI_POC_18               (0x00000001)
#define G3S_GPIO_SPI_OCTA_SORST_N_1        (0x00000001)
#define G3S_GPIO_IOLH_04_L_18              (0x02020202)
#define G3S_GPIO_IOLH_04_H_18              (0x00000202)
#define G3S_GPIO_IOLH_05_L_18              (0x02020202)
#define G3S_GPIO_IOLH_05_H_18              (0x02020202)

static uint32_t CPG_SPI_SSEL_val = 0;
static uint32_t CPG_SPI_DDIV_val = 0;

/*******************************************************************************************************************//**
 * @brief  Open r_xspi_qspi driver
 *
 **********************************************************************************************************************/
void xspi_open (void)
{
    uint32_t reg = 0;

    /*** Initialize TZC-400 for xSPI ***/
    R_TZC_XSPI->REGION_ATTRIBUTES_0 = TZC_RGN_ATTR_EN_ALLFLT;
    R_TZC_XSPI->REGION_ID_ACCESS_0  = TZC_RGN_ID_ACC_EN_RDWR_NSAID0_1;
    R_TZC_XSPI->GATE_KEEPER         = TZC_GATE_KEEP_OPEN_ALLFLT;
    R_TZC_XSPI->SPECULATION_CTRL    = TZC_SPECUL_DIS_PREFETCH;

    /* Backup register original value */
    CPG_SPI_SSEL_val = R_CPG->CPG_SPI_SSEL;
    CPG_SPI_DDIV_val = R_CPG->CPG_SPI_DDIV;

    /* Set xSPI clock */
    /* Select 400MHz */
    reg                 = 0;
    reg                |= G3S_CPG_SPI_SSEL_WE;   // write enable
    reg                |= G3S_CPG_SPI_SSEL_400M; // SELSPI_SET[1:0] = 00b:400MHz
    R_CPG->CPG_SPI_SSEL = reg;

    /* Divisor=1/4 */
    reg                 = 0;
    reg                |= G3S_CPG_SPI_DDIV_WE; // write enable
    reg                |= G3S_CPG_SPI_DDIV_4;  // DIVSPI_SET[2:0] = 010b:1/4
    R_CPG->CPG_SPI_DDIV = reg;

    /* Set XSPI IO Voltage Mode Control: 1.8V */
    R_BSP_XSPIVoltageModeCfg(BSP_XSPI_VOLTAGE_18);

    /* Select Controller to xSPI*/
    reg = G3S_SYSC_IPCONT_SEL_SPI;             // SEL_SPI_OCTA = 0:xSPI
    R_SYSC->SYS_IPCONT_SEL_SPI_OCTA = reg;

    /* Set XSPI/OCTA Output Enable Control  */
    reg = G3S_GPIO_SPI_OCTA_SORST_N_1;         // SORST_N = 1: Unlock Hi-Z
    R_GPIO->SPI_OCTA_RESET = reg;

    /* Set Driving Ability Control  */
    reg               = G3S_GPIO_IOLH_04_L_18; // XSPI_DS = XSPI_WP_N = XSPI_RESET_N = XSPI_SPCLK = 00b: 5.2mA[1.8V]
    R_GPIO->IOLH_04_L = reg;

    /* Set Driving Ability Control  */
    reg               = G3S_GPIO_IOLH_04_H_18; // XSPI_CS1_N = XSPI_CS0_N = 00b: 5.2mA[1.8V]
    R_GPIO->IOLH_04_H = reg;

    /* Set Driving Ability Control  */
    reg               = G3S_GPIO_IOLH_05_L_18; // XSPI_IO3 = XSPI_IO2 = XSPI_IO1 = XSPI_IO0 = 00b: 5.2mA[1.8V]
    R_GPIO->IOLH_05_L = reg;

    /* Set Driving Ability Control  */
    reg               = G3S_GPIO_IOLH_05_H_18; // XSPI_IO7 = XSPI_IO6 = XSPI_IO5 = XSPI_IO4 = 00b: 5.2mA[1.8V]
    R_GPIO->IOLH_05_H = reg;

    /* Set xSPI CS0 Start Address */
    reg = G3S_SYSC_MAP_XSPI_CS0_START;         // MAP_STAADD_CS0 = 0x20000000
    R_SYSC->SYS_XSPI_MAP_STAADD_CS0 = reg;

    /* Set xSPI CS0 End Address */
    reg = G3S_SYSC_MAP_XSPI_CS0_END;           // MAP_ENDADD_CS0 = 0x27FFFFFF
    R_SYSC->SYS_XSPI_MAP_ENDADD_CS0 = reg;

    /* Set xSPI CS1 Start Address */
    reg = G3S_SYSC_MAP_XSPI_CS1_START;         // MAP_STAADD_CS1 = 0x28000000
    R_SYSC->SYS_XSPI_MAP_STAADD_CS1 = reg;

    /* Set xSPI CS1 End Address */
    reg = G3S_SYSC_MAP_XSPI_CS1_END;           // MAP_ENDADD_CS1 = 0x2FFFFFFF
    R_SYSC->SYS_XSPI_MAP_ENDADD_CS1 = reg;

    /* Open xSPI driver */
    g_qspi0.p_api->open(g_qspi0.p_ctrl, g_qspi0.p_cfg);
}

/*******************************************************************************************************************//**
 * @brief  Pre-initialize function for r_xspi_qspi driver
 *
 * Specify this function to "Extra->Pre initialize function" of the SmartCconfigurator property of the r_xspi_qspi driver.
 *
 **********************************************************************************************************************/
fsp_err_t xspi_pre_init (spi_flash_api_t const * p_api, xspi_qspi_instance_ctrl_t * p_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api);
    FSP_PARAMETER_NOT_USED(p_ctrl);

    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Post-initialize function for r_xspi_qspi driver
 *
 * Specify this function to "Extra->Post initialize function" of the SmartCconfigurator property of the r_xspi_qspi driver.
 *
 **********************************************************************************************************************/
fsp_err_t xspi_post_init (spi_flash_api_t const * p_api, xspi_qspi_instance_ctrl_t * p_ctrl)
{
    FSP_PARAMETER_NOT_USED(p_api);
    FSP_PARAMETER_NOT_USED(p_ctrl);

    return FSP_SUCCESS;
}

void xspi_close (void)
{
    xspi_qspi_instance_ctrl_t * p_instance_ctrl = (xspi_qspi_instance_ctrl_t *) g_qspi0.p_ctrl;

    /* Issue dummy read (4Byte INCR) for both channel Accept response of dummy read */
    FSP_REGISTER_READ(*((uint32_t *) RZG3S_XSPI_BASE_ADDRESS));

    p_instance_ctrl->p_reg->BMCTL0 = 0;
    g_qspi0.p_api->close(p_instance_ctrl);

#if BSP_CFG_MCU_LAUNCH_CA55
    R_CPG->CPG_SPI_SSEL = CPG_SPI_SSEL_val;
    R_CPG->CPG_SPI_DDIV = CPG_SPI_DDIV_val;
#endif
    R_BSP_MODULE_RSTON(FSP_IP_XSPI, 0);
}
