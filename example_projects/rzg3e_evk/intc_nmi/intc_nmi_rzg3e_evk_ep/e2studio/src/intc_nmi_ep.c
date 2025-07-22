/***********************************************************************************************************************
 * File Name    : intc_nmi_ep.c
 * Description  : Contains function definition.
 **********************************************************************************************************************/
/*
 * Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "common_utils.h"
#include "intc_nmi_ep.h"

/*******************************************************************************************************************//**
 * @addtogroup intc_nmi_ep
 * @{
 **********************************************************************************************************************/

/* Boolean flag to determine switch is pressed or not.*/
volatile bool g_sw_press = false;

/*******************************************************************************************************************//**
 * @brief       This functions initializes INTC_NMI driver.
 * @param[IN]   None
 * @retval      FSP_SUCCESS                  Upon successful open of INTC_NMI driver
 * @retval      Any Other Error code apart from FSP_SUCCESS  Unsuccessful open
 **********************************************************************************************************************/
fsp_err_t intc_nmi_init(void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Open INTC_NMI driver */
    err = R_INTC_NMI_ExternalIrqOpen(&g_external_irq_ctrl, &g_external_irq_cfg);
    /* Handle error */
    if (FSP_SUCCESS != err)
    {
        /* INTC_NMI Open failure message */
        APP_ERR_PRINT ("\r\n**R_INTC_NMI_ExternalIrqOpen API FAILED**\r\n");
    }
    return err;
}

/*******************************************************************************************************************//**
 * @brief       This function enables external interrupt for specified channel.
 * @param[IN]   None
 * @retval      FSP_SUCCESS                  Upon successful enable of INTC_NMI driver
 * @retval      Any Other Error code apart from FSP_SUCCESS  Unsuccessful open
 **********************************************************************************************************************/
fsp_err_t intc_nmi_enable(void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Enable INTC_NMI driver */
    err = R_INTC_NMI_ExternalIrqEnable(&g_external_irq_ctrl);
    /* Handle error */
    if (FSP_SUCCESS != err)
    {
        /* INTC_NMI Enable failure message */
        APP_ERR_PRINT ("\r\n**R_INTC_NMI_ExternalIrqEnable API FAILED**\r\n");
    }
    return err;
}


/*******************************************************************************************************************//**
 * @brief       This function closes opened INTC_NMI driver before the project ends up in an Error Trap.
 * @param[IN]   None
 * @retval      None
 **********************************************************************************************************************/
void intc_nmi_deinit(void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Close INTC_NMI driver */
    err = R_INTC_NMI_ExternalIrqClose(&g_external_irq_ctrl);
    /* Handle error */
    if (FSP_SUCCESS != err)
    {
        /* INTC_NMI Close failure message */
        APP_ERR_PRINT("\r\n**R_INTC_NMI_ExternalIrqClose API FAILED**\r\n");
    }
}

/*******************************************************************************************************************//**
 * @brief      User defined external irq callback.
 * @param[IN]  p_args
 * @retval     None
 **********************************************************************************************************************/
void nmi_ep_callback(external_irq_callback_args_t *p_args)
{
    /* Make sure it's the right interrupt*/
    if(USER_SW_IRQ_NUMBER == p_args->channel)
    {
        g_sw_press = true;
    }
}

/*******************************************************************************************************************//**
 * @} (end addtogroup intc_nmi_ep)
 **********************************************************************************************************************/
