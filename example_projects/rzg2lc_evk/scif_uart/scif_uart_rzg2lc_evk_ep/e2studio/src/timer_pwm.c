/***********************************************************************************************************************
 * File Name    : timer_pwm.c
 * Description  : Contains timer functions definition.
 **********************************************************************************************************************/
/*
 * Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "common_utils.h"
#include "timer_pwm.h"
#include "uart_ep.h"

/*******************************************************************************************************************//**
 * @addtogroup r_scif_uart_ep
 * @{
 **********************************************************************************************************************/
extern bsp_leds_t g_bsp_leds;
uint32_t raw_counts_periodic = RESET_VALUE;
uint32_t clock_freq = RESET_VALUE;

/*******************************************************************************************************************//**
 * @brief       Initialize GTM in Periodic mode.
 * @param[in]   None
 * @retval      FSP_SUCCESS         Upon successful open of timer
 * @retval      Any Other Error code apart from FSP_SUCCESS  Unsuccessful open
 **********************************************************************************************************************/
fsp_err_t gtm_initialize(void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Open GTM module */
    err = R_GTM_Open (&g_timer_ctrl, &g_timer_cfg);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_TRAP(err);
    }
    return err;
}

/*******************************************************************************************************************//**
 * @brief       Start GTM in Periodic mode.
 * @param[in]   None
 * @retval      FSP_SUCCESS         Upon successful start of timer
 * @retval      Any Other Error code apart from FSP_SUCCESS  Unsuccessful start
 **********************************************************************************************************************/
fsp_err_t gtm_start(void)
{

    fsp_err_t err = FSP_SUCCESS;

    /* Start GTM module */
    err = R_GTM_Start (&g_timer_ctrl);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_TRAP(err);
    }
    return err;

}

/*******************************************************************************************************************//**
 * @brief     Set cycle of GTM 
 * @param[in] raw_count        Raw count value for cycle generation
 * @retval    FSP_SUCCESS      Upon Period set returns Successful.
 * @retval    Any Other Error code apart from FSP_SUCCES  Unsuccessful in setting Period
 **********************************************************************************************************************/
fsp_err_t set_cycle(uint32_t raw_count)
{
    fsp_err_t err     = FSP_SUCCESS;
    timer_info_t info = {(timer_direction_t)RESET_VALUE, RESET_VALUE, RESET_VALUE};

    /* Get the current cycle setting. */
    err = R_GTM_InfoGet(&g_timer_ctrl, &info);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_TRAP(err);
    }
    else
    {
        /* Depending on the user selected clock source, raw counts value can be calculated
         * for the user given time-cycle values */
        clock_freq = info.clock_frequency;
        raw_counts_periodic = (uint32_t)(raw_count * (clock_freq / 1000));

        /* Period Set API set the desired cycle on the on-board LED */
        err = R_GTM_PeriodSet(&g_timer_ctrl, raw_counts_periodic);
        if(FSP_SUCCESS != err)
        {
            APP_ERR_TRAP(err);
        }
    }
    return err;
}

/*******************************************************************************************************************//**
 * @brief       Close the GTM HAL driver before the project ends up in an Error Trap.
 * @param[in]   None
 * @retval      None
 **********************************************************************************************************************/
void timer_gtm_deinit(void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Close the GTM module */
    err = R_GTM_Close (&g_timer_ctrl);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_TRAP(err);
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

    /* Change LED state */
    fsp_err_t err = R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_bsp_leds.p_leds[0], led_level);

    /* Handle error */
    if (FSP_SUCCESS != err)
    {
        APP_ERR_TRAP(err);
    }

}
/*******************************************************************************************************************//**
 * @} (end addtogroup r_scif_uart_ep)
 **********************************************************************************************************************/
