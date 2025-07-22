/***********************************************************************************************************************
 * File Name    : poeg_ep.c
 * Description  : Contains functions
 ***********************************************************************************************************************/
/*
 * Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "common_utils.h"
#include "poeg_ep.h"

/*******************************************************************************************************************//**
 * @addtogroup poeg_ep
 * @{
 **********************************************************************************************************************/


/*******************************************************************************************************************//**
 * @brief     This function de-initialize the Timer module
 * @param[in] timer_ctrl_t * const p_timer_ctl
 * @retval    None
 **********************************************************************************************************************/
void deinit_gpt_timer(timer_ctrl_t * const p_timer_ctl)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Timer Close API call*/
    err = R_GPT_Close(p_timer_ctl);
    /* Handle error */
    if (FSP_SUCCESS != err)
    {
        /* GPT Close failure message */
        APP_ERR_PRINT ("\r\nR_GPT_Close failed\r\n");
    }
    else
    {
        APP_PRINT ("\r\nR_GPT_Close success\r\n");
    }
}


/*******************************************************************************************************************//**
 * @brief init_gpt_timer_pwm1
 * This function initialize the GPT PWM1 module
 * @param[in] None
 * @retval      FSP_SUCCESS                  Upon successful GPT Open
 * @retval      Any Other Error code apart from FSP_SUCCESS  Upon Unsuccessful
 **********************************************************************************************************************/
fsp_err_t init_gpt_timer_pwm1(void)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_GPT_Open(&g_timer_pwm1_ctrl, &g_timer_pwm1_cfg);
    return (err);
}

/*******************************************************************************************************************//**
 * @brief     This function initialize the GPT PWM2 module
 * @param[in] None
 * @retval      FSP_SUCCESS                  Upon successful GPT Open
 * @retval      Any Other Error code apart from FSP_SUCCESS  Upon Unsuccessful
 **********************************************************************************************************************/
fsp_err_t init_gpt_timer_pwm2(void)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_GPT_Open(&g_timer_pwm2_ctrl, &g_timer_pwm2_cfg);
    return (err);
}


/*******************************************************************************************************************//**
 * @brief     This function initialize the POEG0 module
 * @param[in] None
 * @retval      FSP_SUCCESS                  Upon successful POEG0 Open
 * @retval      Any Other Error code apart from FSP_SUCCESS  Upon Unsuccessful
 **********************************************************************************************************************/
fsp_err_t init_poeg0_module(void)
{
    fsp_err_t err = FSP_SUCCESS;
    /* Initializes the POEG. */
    err = R_POEG_Open(&g_poeg0_ctrl, &g_poeg0_cfg);
    return err;
}


/*******************************************************************************************************************//**
 * @brief     This function de-initialize the POEG0 module
 * @param[in] None
 * @retval      FSP_SUCCESS                  Upon successful POEG0 Close
 * @retval      Any Other Error code apart from FSP_SUCCESS  Upon Unsuccessful
 **********************************************************************************************************************/
fsp_err_t deinit_poeg0_module(void)
{
    fsp_err_t err = FSP_SUCCESS;
    /* Initializes the POEG. */
    err = R_POEG_Close(&g_poeg0_ctrl);
    /* Handle error */
    if(FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("POEG 0 de-initialization failed\r\n");
    }
    else
    {
        APP_PRINT("POEG 0 de-initialization success\r\n");
    }
    return err;
}


/*******************************************************************************************************************//**
 * @brief     This function initialize the POEG1 module
 * @param[in] None
 * @retval      FSP_SUCCESS                  Upon successful POEG1 Open
 * @retval      Any Other Error code apart from FSP_SUCCESS  Upon Unsuccessful
 **********************************************************************************************************************/
fsp_err_t init_poeg1_module(void)
{
    fsp_err_t err = FSP_SUCCESS;
    /* Initializes the POEG. */
    err = R_POEG_Open(&g_poeg1_ctrl, &g_poeg1_cfg);
    return err;
}


/*******************************************************************************************************************//**
 * @brief     This function de-initialize the POEG1 module
 * @param[in] None
 * @retval      FSP_SUCCESS                  Upon successful POEG1 Close
 * @retval      Any Other Error code apart from FSP_SUCCESS  Upon Unsuccessful
 **********************************************************************************************************************/
fsp_err_t deinit_poeg1_module(void)
{
    fsp_err_t err = FSP_SUCCESS;
    /* Initializes the POEG. */
    err = R_POEG_Close(&g_poeg1_ctrl);
    /* Handle error */
    if(FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("POEG 1 de-initialization failed\r\n");
    }
    else
    {
        APP_PRINT("POEG 1 de-initialization success\r\n");
    }
    return err;
}


/*******************************************************************************************************************//**
 * @} (end addtogroup poeg_ep)
 **********************************************************************************************************************/
