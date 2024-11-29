/***********************************************************************************************************************
 * File Name    : gtm_timer_initialize.c
 * Description  : Contains function definition.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * Copyright 2023 Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
 ***********************************************************************************************************************/
#include "common_utils.h"
#include "gtm_timer_initialize.h"

/*******************************************************************************************************************//**
 * @addtogroup freertos_ep
 * @{
 **********************************************************************************************************************/
 
/*******************************************************************************************************************//**
 * @brief      Initialize and start the GTM timer instance
 *
 * @param[in]  p_timer_ctrl  Timer instance control structure
 * @param[in]  p_timer_cfg   Timer instance config structure
 * @retval     FSP_SUCCESS or any other error value.
 **********************************************************************************************************************/
fsp_err_t gtm_timer_init(gtm_instance_ctrl_t * p_timer_ctrl, const timer_cfg_t * p_timer_cfg)
{
    fsp_err_t fsp_err = FSP_SUCCESS;

    /* Open GTM timer instance */
    fsp_err = R_GTM_Open (p_timer_ctrl, p_timer_cfg);
    /* Handle error */
    if ( FSP_SUCCESS != fsp_err )
    {
        /* Print out in case of error */
        APP_ERR_PRINT ("\r\nGTM Timer open API failed\r\n");
        return fsp_err;
    }


    /* Start GTM Timer instance */
    fsp_err = R_GTM_Start (p_timer_ctrl);
    /* Handle error */
    if (FSP_SUCCESS != fsp_err)
    {
        /* Close timer if failed to start */
        if ( FSP_SUCCESS  != R_GTM_Close (p_timer_ctrl) )
        {
            /* Print out in case of error */
            APP_ERR_PRINT ("\r\nGTM Timer Close API failed\r\n");
        }

        APP_ERR_PRINT ("\r\nGTM Timer Start API failed\r\n");
        return fsp_err;
    }
    else
    {
        APP_PRINT ("\r\nGTM Timer Started successfully\r\n");
    }
    return FSP_SUCCESS;
}
/*******************************************************************************************************************//**
 * @} (end addtogroup freertos_ep)
 **********************************************************************************************************************/
