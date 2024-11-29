/***********************************************************************************************************************
 * File Name    : gpt_timer.h
 * Description  : Contains Macros and function declarations.
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

#ifndef GPT_TIMER_H_
#define GPT_TIMER_H_

/* Macros definitions */
#define GPT_MAX_PERCENT          (100U)          /* Max Duty Cycle percentage */
#define BUF_SIZE                 (16U)           /* Size of buffer for RTT input data */
#define PERIODIC_MODE_TIMER      (1U)            /* To perform GPT Timer in Periodic mode */
#define PWM_MODE_TIMER           (2U)            /* To perform GPT Timer in PWM mode */
#define ONE_SHOT_MODE_TIMER      (3U)            /* To perform GPT Timer in ONE-SHOT mode */
#define INITIAL_VALUE            ('\0')
#define TIMER_UNITS_MILLISECONDS  (1000U)        /* timer unit in millisecond */
#define CLOCK_TYPE_SPECIFIER      (1ULL)         /* type specifier */

/* GPT Timer Pin for boards */
#define TIMER_PIN           (GPT_IO_PIN_GTIOCB)

#define GPT_MAX_PERIOD_COUNT     (0XFFFFFFFF)    /* Max Period Count for 32-bit Timer*/

#define PERIODIC_MODE	   (1U)                  /* To check status of GPT Timer in Periodic mode */
#define PWM_MODE	       (2U)                  /* To check status of GPT Timer in PWM mode */
#define ONE_SHOT_MODE      (3U)                  /* To check status of GPT Timer in oNE-SHOT mode */

#define EP_INFO    "\r\nThe project initializes GPT module in Periodic, PWM or One-shot" \
        "\r\nmode based on user input from the displayed menu options." \
        "\r\nIn periodic mode, user can enter the time period within the "\
        "\r\npermitted ranges to change the frequency of the user LED." \
        "\r\nIn PWM mode, user can enter the duty cycle within the "\
        "\r\nspecified range to adjust the intensity of the user LED." \
        "\r\nIn ONE SHOT mode, Output will be displayed on JlinkRTTViewer"\
        "\r\nwhen timer expires.\r\n "

/* Function declaration */
fsp_err_t init_gpt_timer(timer_ctrl_t * const p_timer_ctl, timer_cfg_t const * const p_timer_cfg, uint8_t timer_mode);
fsp_err_t start_gpt_timer (timer_ctrl_t * const p_timer_ctl);
fsp_err_t set_timer_duty_cycle(uint8_t duty_cycle_percent);
uint32_t  process_input_data(void);
void deinit_gpt_timer(timer_ctrl_t * const p_timer_ctl);
void print_timer_menu(void);

#endif /* GPT_TIMER_H_ */
