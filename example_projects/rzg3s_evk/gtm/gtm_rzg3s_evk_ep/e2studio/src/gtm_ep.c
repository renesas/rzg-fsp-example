/***********************************************************************************************************************
 * File Name    : gtm_ep.c
 * Description  : Contains data structures and functions used in gtm_ep.c.
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
 **********************************************************************************************************************/

#include "common_utils.h"
#include "gtm_ep.h"

/*******************************************************************************************************************//**
 * @addtogroup gtm_ep
 * @{
 **********************************************************************************************************************/

extern bsp_leds_t g_bsp_leds;
extern volatile uint8_t g_periodic_timer_flag ;
extern volatile uint32_t g_error_flag ;
/*******************************************************************************************************************//**
 * @brief       This functions initializes GTM module.
 * @param[IN]   None
 * @retval      FSP_SUCCESS                  Upon successful open of GTM module
 * @retval      Any Other Error code apart from FSP_SUCCESS  Unsuccessful open
 **********************************************************************************************************************/
fsp_err_t gtm_init(void)
{
    fsp_err_t err = FSP_SUCCESS;     // Error status

    /* Open Timer0 in One Shot Mode */
    err = R_GTM_Open(&g_timer_one_shot_ctrl, &g_timer_one_shot_cfg);
    /* Handle error */
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT ("\r\nGTM2 timer open failed.\r\nRestart the Application\r\n");
        return err;
    }

    /* Open Timer1 in Periodic mode */
    err = R_GTM_Open(&g_timer_periodic_ctrl, &g_timer_periodic_cfg);
    /* Handle error */
    if (FSP_SUCCESS != err)
    {
        /* Close Timer0 in One Shot Mode */
        if ( (FSP_SUCCESS != R_GTM_Close(&g_timer_one_shot_ctrl)))
        {
            APP_ERR_PRINT ("\r\nOne shot timer close failed.\r\nRestart the Application\r\n");
        }
        APP_ERR_PRINT ("\r\nGTM1 timer open failed.\r\nRestart the Application\r\n");
    }
    return err;
}

/*******************************************************************************************************************//**
 * @brief       This functions starts GTM2 in one-shot mode.
 * @param[IN]   None
 * @retval      FSP_SUCCESS                  Timer started successfully
 * @retval      Any Other Error code apart from FSP_SUCCESS  
 **********************************************************************************************************************/
fsp_err_t gtm_start_oneshot_timer(void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Start Timer0 in one-shot mode */
    err = R_GTM_Start(&g_timer_one_shot_ctrl);
    /* Handle error */
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n GTM2 timer start failed.\r\n");
    }
    return err;
}

/*******************************************************************************************************************//**
 * @brief This function is callback for one-shot mode timer and starts GTM1 timer in Periodic mode.
 *
 * @param[in] (timer_callback_args_t *)
 **********************************************************************************************************************/
void one_shot_timer_callback(timer_callback_args_t *p_args)
{
    (void) p_args;
    fsp_err_t err = FSP_SUCCESS;
    timer_status_t periodic_timer_status;

    /* Retrieve the status of timer running in periodic mode */
    err = R_GTM_StatusGet(&g_timer_periodic_ctrl, &periodic_timer_status);
    if (FSP_SUCCESS != err)
    {
        g_error_flag = SET_FLAG;
    }
    else
    {
        if (TIMER_STATE_COUNTING != periodic_timer_status.state)
        {
            /* Start the timer in periodic mode only if the timer is in stopped state */
            err = R_GTM_Start(&g_timer_periodic_ctrl);
            /* Handle error */
            if (FSP_SUCCESS != err)
            {
                g_error_flag = SET_FLAG;
                APP_ERR_PRINT("\r\nGTM1 Cannot be started in Periodic mode");
            }
            else
            {
                g_periodic_timer_flag = SET_FLAG;   //Set the flag since timer1 is started in periodic mode
            }
        }
        else
        {
            g_periodic_timer_flag = ALREADY_RUNNING;
        }
    }
}

/*******************************************************************************************************************//**
 * @brief This function is callback for periodic timer and blinks LED periodically.
 *
 * @param[in] (timer_callback_args_t *)
 **********************************************************************************************************************/
void periodic_timer_callback(timer_callback_args_t *p_args)
{
    (void) p_args;
    static volatile bsp_io_level_t led_level = BSP_IO_LEVEL_HIGH;

    /* Change the state of the LED write value */
    led_level ^= BSP_IO_LEVEL_HIGH;

    /* Change LED state connected to Pmod0 pin 7 */
    fsp_err_t err = R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_bsp_leds.p_leds[0], led_level); // [0] for Pmod0 pin 7
    /* Handle error */
    if (FSP_SUCCESS != err)
    {
        g_error_flag = SET_FLAG;
        APP_ERR_PRINT("\r\nLED_PIN state cannot be toggled");
        return;
    }
}

/*******************************************************************************************************************//**
 * @brief This function closes opened GTM module before the project ends up in an Error Trap.
 * @param[IN]   None
 * @retval      None
 **********************************************************************************************************************/
void gtm_deinit(void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Close GTM2 module */
    err = R_GTM_Close(&g_timer_one_shot_ctrl);
    /* handle error */
    if (FSP_SUCCESS != err)
    {
        /* GTM2 Close failure message */
        APP_ERR_PRINT("** R_GTM_Close API for channel 2 failed **  \r\n");
    }

    /* Close GTM1 module */
    err = R_GTM_Close(&g_timer_periodic_ctrl);
    /* handle error */
    if (FSP_SUCCESS != err)
    {
        /* GTM1 Close failure message */
        APP_ERR_PRINT("** R_GTM_Close API for channel 1 failed **  \r\n");
    }

}

/*******************************************************************************************************************//**
 * @} (end addtogroup gtm_ep)
 **********************************************************************************************************************/
