/***********************************************************************************************************************
 * File Name    : poeg_ep.h
 * Description  : Contains macros and functions declaration
 ***********************************************************************************************************************/
/*
 * Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef POEG_EP_H_
#define POEG_EP_H_
#include "common_utils.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
/* Macros for commands to be received through RTT input */
#define POEG_OUTPUT_DISABLE_SOFTWARE_API (1U)
#define POEG_OUTPUT_DISABLE_REQUEST_FROM_GPT (2U)
#define POEG_RESET (3U)

#define POEG_CHANNEL_0 (1U)
#define POEG_CHANNEL_1 (2U)


/* Macro definition */
#define LED_PIN_POEG0 (BSP_IO_PORT_43_PIN_02)
#define LED_PIN_POEG1 (BSP_IO_PORT_41_PIN_00)

#define SET_FLAG    (1)
#define CLEAR_FLAG  (0)
#define NULL_CHAR   ('\0')

#define EP_INFO                "\r\nThe example project demonstrates the basic functionalities of "\
                               "\r\nPOEG driver on Renesas RZG MPUs based on Renesas FSP.RZG MPUs is "\
                               "\r\nused to demonstrate the various operating modes of a POEG driver."\
                               "\r\nThe example project demonstrates the modes of POEG module"\
                               "\r\n1.POEG Software API mode-GPT Output disable by software API"\
                               "\r\n2.POEG Trigger Output Level mode-GPT Output disable from the GPT"\
                               "\r\n3.Enable Port output using POEG_Reset API."\
                               "\r\nUsing RTT input, user can choose the POEG method.\r\n"\

#define MENU_INFO              "\r\nPOEG Application Menu\r\n"\
                               "1 :  Disable GPT output pin using POEG software API\r\n"\
                               "2 :  Disable GPT output pin using POEG trigger GPT output level\r\n"\
                               "3 :  Reset the POEG Channel\r\n"\
                               "** Reset of application is needed prior to continuous selection of the\r\n"\
                               "menu option 1 **\r\n"\
                               "User Input :  "

#define RESET_MENU_INFO         "\r\nPOEG RESET Menu\r\n"\
                               "1 :  RESET POEG Channel 0 \r\n"\
                               "2 :  RESET POEG Channel 1 \r\n"\
                               "User Input :  "

void deinit_gpt_timer(timer_ctrl_t * const p_timer_ctl);
fsp_err_t init_poeg0_module(void);
fsp_err_t init_poeg1_module(void);
fsp_err_t init_gpt_timer_pwm1(void);
fsp_err_t init_gpt_timer_pwm2(void);
fsp_err_t deinit_poeg0_module(void);
fsp_err_t deinit_poeg1_module(void);

fsp_err_t poeg_ouput_disable_and_reset_options(void);
fsp_err_t reset_poeg_module(void);

/** Array of Pmod LED on bottom row of Pmod0. */
static const uint16_t g_prv_leds[] =
{
    (uint16_t) BSP_IO_PORT_43_PIN_02,  ///< LED2
    (uint16_t) BSP_IO_PORT_41_PIN_00,  ///< LED3
};

/** Available user-controllable LEDs on this board. These enums can be can be used to index into the array of LED pins
 * found in the bsp_leds_t structure. */
typedef enum e_led
{
    LED_LED2,                      ///< LED2
    LED_LED3,                      ///< LED3
} led_t;

#endif /* POEG_EP_H_ */

