/***********************************************************************************************************************
 * File Name    : ext_irq_setup.c
 * Description  : Contains data structures and functions used in ext_irq_setup.c
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics Corporation and/or its affiliates and may only
 * be used with products of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.
 * Renesas products are sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for
 * the selection and use of Renesas products and Renesas assumes no liability.  No license, express or implied, to any
 * intellectual property right is granted by Renesas.  This software is protected under all applicable laws, including
 * copyright laws. Renesas reserves the right to change or discontinue this software and/or this documentation.
 * THE SOFTWARE AND DOCUMENTATION IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND
 * TO THE FULLEST EXTENT PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY,
 * INCLUDING WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE
 * SOFTWARE OR DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR
 * DOCUMENTATION (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER,
 * INCLUDING, WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY
 * LOST PROFITS, OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "common_utils.h"
#include "ext_irq_setup.h"
/*******************************************************************************************************************//**
 * @addtogroup r_wdt_ep
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief     Initialize the IRQ module.
 * @param[IN]   None
 * @retval FSP_SUCCESS                  Upon successful open
 * @retval Any Other Error code apart from FSP_SUCCES  Unsuccessful open
 ***********************************************************************************************************************/
fsp_err_t init_irq_module(void)
{
    /* variable to track error and return values */
    fsp_err_t err = FSP_SUCCESS;

    /* Open IRQ module */
    err = R_INTC_IRQ_ExternalIrqOpen(&g_external_irq_ctrl, &g_external_irq_cfg);
    if (FSP_SUCCESS != err)
    {
        /* Print Error on J-Link RTT Viewer console */
        APP_ERR_PRINT ("\r\n ** R_INTC_IRQ_ExternalIrqOpen API Failed ** \r\n");
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief    Enable the User Push Button and return the error to the Application.
 * @param[IN]   None
 * @retval FSP_SUCCESS                 Push Button enabled successfully.
 * @retval Any Other Error code apart from FSP_SUCCES  Unsuccessful to enable push button
 ***********************************************************************************************************************/
fsp_err_t enable_irq_module(void)
{
    /* variable to track error and return values */
    fsp_err_t err = FSP_SUCCESS;

    /* Enable external irq */
    err = R_INTC_IRQ_ExternalIrqEnable(&g_external_irq_ctrl);
    if (FSP_SUCCESS != err)
    {
        /* Print Error on J-Link RTT Viewer console */
        APP_ERR_PRINT ("\r\n ** R_IRQ_ExternalIrqEnable API Failed ** \r\n");
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief    Close the IRQ HAL driver and Handle the return closing API error, to the Application.
 * @param[IN]   None
 * @retval None
 ***********************************************************************************************************************/
void deinit_irq_module(void)
{
    /* variable to track error and return values */
    fsp_err_t err = FSP_SUCCESS;

    /* Close the IRQ module */
    err=  R_INTC_IRQ_ExternalIrqClose(&g_external_irq_ctrl);
    /* handle error */
    if (FSP_SUCCESS != err)
    {
        /* Print Error on J-Link RTT Viewer console */
        APP_ERR_PRINT("\r\n ** R_IRQ_ExternalIrqClose API failed ** \r\n");
        return;
    }
}

/*******************************************************************************************************************//**
 * This function is called when user presses the push button.
 * @brief This functions is used to stop the gtm timer.
 * @param[IN] p_args    external irq callback argument
 * @retval    None
 **********************************************************************************************************************/
void ext_irq_callback(external_irq_callback_args_t *p_args)
{
    /* variable to track error and return values */
    fsp_err_t err = FSP_SUCCESS;

    FSP_PARAMETER_NOT_USED(p_args);

    /* By pressing push button, gtm timer will stops running */
    err = R_GTM_Stop(&g_timer_ctrl);
    if (FSP_SUCCESS != err)
    {
        /* Print Error on J-Link RTT Viewer console */
        APP_ERR_PRINT("\r\n ** R_GTM_Stop API failed ** \r\n");
        return;
    }
    APP_PRINT ("Push button is pressed.\r\nGTM timer stopped.\r\n");
}

/*******************************************************************************************************************//**
 * @} (end addtogroup r_wdt_ep)
 **********************************************************************************************************************/
