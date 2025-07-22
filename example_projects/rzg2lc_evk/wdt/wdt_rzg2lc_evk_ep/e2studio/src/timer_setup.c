/***********************************************************************************************************************
 * File Name    : timer_setup.c
 * Description  : Contains data structures and functions used in timer_setup.c
 **********************************************************************************************************************/
/*
 * Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "common_utils.h"
#include "timer_setup.h"

/*******************************************************************************************************************//**
 * @addtogroup r_wdt_ep
 * @{
 **********************************************************************************************************************/

/*
 * External Global Variables
 */
/* LED Structure used to blink on board LED */
extern bsp_leds_t g_bsp_leds;

/*
 * Global Variables
 */
/* Variable to capture timer overflow counts and print WDT status */
volatile uint32_t g_timer_overflow_counter = RESET_VALUE;

/*******************************************************************************************************************//**
 * @brief     Initialize the GTM timer in Periodic mode.
 * @param[IN]   None
 * @retval FSP_SUCCESS                  Upon successful open
 * @retval Any Other Error code apart from FSP_SUCCES  Unsuccessful open
 ***********************************************************************************************************************/
fsp_err_t init_gtm_module(void)
{
    /* variable to track error and return values */
    fsp_err_t err = FSP_SUCCESS;

    /* Open GTM module */
    err = R_GTM_Open(&g_timer_ctrl, &g_timer_cfg);
    if (FSP_SUCCESS != err)
    {
        /* Print Error on J-Link RTT Viewer console */
        APP_ERR_PRINT ("\r\n ** R_GTM_TimerOpen API failed ** \r\n");
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief    Start the GTM HAL timer and return the error to the Application.
 * @param[IN]   None
 * @retval FSP_SUCCESS                 Timer driver closed successfully.
 * @retval Any Other Error code apart from FSP_SUCCES  Unsuccessful to start timer
 ***********************************************************************************************************************/
fsp_err_t timer_start(void)
{
    /* variable to track error and return values */
    fsp_err_t err = FSP_SUCCESS;

    /* Start GTM timer */
    err = R_GTM_Start(&g_timer_ctrl);
    if (FSP_SUCCESS != err)
    {
        /* Print Error on J-Link RTT Viewer console */
        APP_ERR_PRINT ("\r\n ** R_GTM_Start API failed ** \r\n");
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief    Close the GTM HAL driver and Handle the return closing API error, to the Application.
 * @param[IN]   None
 * @retval      None
 ***********************************************************************************************************************/
void deinit_gtm_module(void)
{
    /* variable to track error and return values */
    fsp_err_t err = FSP_SUCCESS;

    /* Close the GTM module */
    err=  R_GTM_Close(&g_timer_ctrl);
    /* handle error */
    if (FSP_SUCCESS != err)
    {
        /* Print Error on J-Link RTT Viewer console */
        APP_ERR_PRINT ("\r\n ** R_GTM_Close API failed ** \r\n");
    }
}

/*******************************************************************************************************************//**
 * This function is called when gtm timer's counter wrapped around.
 * @brief    Refresh WDT counter and toggle LED state.
 * @param[IN]   p_args   Callback function parameter data
 * @retval      None
 **********************************************************************************************************************/
void gtm_callback(timer_callback_args_t *p_args)
{
    /* variable to track error and return values */
    fsp_err_t err = FSP_SUCCESS;

    /* variable to toggle LED */
    static bsp_io_level_t level_led = BSP_IO_LEVEL_LOW;

    FSP_PARAMETER_NOT_USED(p_args);

    /* Refresh WDT, if user has not pressed the push button */
    err = R_WDT_Refresh(&g_wdt_ctrl);
    if (FSP_SUCCESS != err)
    {
        /* Turn ON LED to indicate error, along with output on J-Link RTT Viewer*/
        R_BSP_PinWrite((bsp_io_port_pin_t)g_bsp_leds.p_leds[0], BSP_IO_LEVEL_HIGH);

        /* Print Error on J-Link RTT Viewer console */
        APP_ERR_PRINT ("\r\n ** R_WDT_Refresh API failed ** \r\n");
    }
    else
    {
        /* Counter is used to count the number of times GTM callback triggered. */
        g_timer_overflow_counter++;

        /* Toggle LED */
        level_led ^= BSP_IO_LEVEL_HIGH;
        R_BSP_PinWrite((bsp_io_port_pin_t)g_bsp_leds.p_leds[0], level_led);
    }
}

/*******************************************************************************************************************//**
 * @} (end addtogroup r_wdt_ep)
 **********************************************************************************************************************/
