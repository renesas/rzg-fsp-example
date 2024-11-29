/***********************************************************************************************************************
 * File Name    : uart_ep.c
 * Description  : Contains UART functions definition.
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
#include "uart_ep.h"
#include "timer_pwm.h"
#include "stdbool.h"
#include "stdint.h"

/*******************************************************************************************************************//**
 * @addtogroup r_scif_uart_ep
 * @{
 **********************************************************************************************************************/

/*
 * Private function declarations
 */

/*
 * Private global variables
 */
/* Temporary buffer to save data from receive buffer for further processing */
static uint8_t g_temp_buffer[DATA_LENGTH] = {RESET_VALUE};

/* Counter to update g_temp_buffer index */
static volatile uint8_t g_counter_var = RESET_VALUE;

/* Flag to check whether data is received or not */
static volatile uint8_t g_data_received_flag = false;

/* Flag for user callback */
static volatile uint8_t g_uart_event = RESET_VALUE;

/*****************************************************************************************************************
 *  @brief       UART Example project to demonstrate the functionality
 *  @param[in]   None
 *  @retval      FSP_SUCCESS     Upon success
 *  @retval      Any Other Error code apart from FSP_SUCCESS
 ****************************************************************************************************************/
fsp_err_t uart_ep_demo(void)
{
    fsp_err_t err = FSP_SUCCESS;
    volatile bool b_valid_data = true;

    while (true)
    {
        if(g_data_received_flag)
        {
            g_data_received_flag  = false;

            uint8_t input_length = RESET_VALUE;
            volatile uint32_t cycle = RESET_VALUE;

            /* Calculate g_temp_buffer length */
            input_length = ((uint8_t)(strlen((char *) &g_temp_buffer)));

            /* Check if input data length is in limit */
            if (DATA_LENGTH > (uint8_t)input_length)
            {
                /* This loop validates input data byte by byte to filter out decimals. (floating point input)
                 * Any such data will be considered as invalid. */
                for(int buf_index = RESET_VALUE; buf_index < input_length; buf_index++)
                {
                    if(ZERO_ASCII <= g_temp_buffer[buf_index] && NINE_ASCII >= g_temp_buffer[buf_index])
                    {
                        /* Set b_valid_data Flag as data is valid */
                        b_valid_data = true;
                    }
                    else
                    {
                        /* Clear data_valid flag as data is not valid, Clear the buffer and break the loop */
                        memset(g_temp_buffer, RESET_VALUE, DATA_LENGTH);
                        b_valid_data = false;
                        break;
                    }
                }

                /* All bytes in data are integers, convert input to integer value to set cycle. */
                cycle = ((uint32_t)(atoi((char *) &g_temp_buffer)));

                /* Validation input data is in 1 - 2000 range. */
                if(MAX_CYCLE < cycle || RESET_VALUE == cycle)
                {
                    /* Resetting the g_temp_buffer as data is out of limit */
                    memset(g_temp_buffer, RESET_VALUE, DATA_LENGTH);
                    b_valid_data = false;

                    /* Application is being run on Serial terminal hence transmitting error message to the same */
                    err = uart_print_user_msg((uint8_t *)"\r\nInvalid input. Input range is from 1 - 2000\r\n");
                    if (FSP_SUCCESS != err)
                    {
                        APP_ERR_PRINT ("\r\n **  UART WRITE FAILED  ** \r\n");
                        return err;
                    }
                }
            }
            else
            {
                /* Clear data_valid flag as data is not valid, Clear the g_temp_buffer */
                memset(g_temp_buffer, RESET_VALUE, DATA_LENGTH);
                b_valid_data = false;

                err = uart_print_user_msg((uint8_t *)"\r\nInvalid input. Input range is from 1 - 2000\r\n");
                if (FSP_SUCCESS != err)
                {
                    APP_ERR_PRINT ("\r\n **  UART WRITE FAILED  ** \r\n");
                    return err;
                }
            }

            /* Set intensity only for valid data */
            if(b_valid_data)
            {
                /* Change intensity of LED */
                err = set_cycle(cycle);
                if (FSP_SUCCESS != err)
                {
                    APP_ERR_PRINT ("\r\n** GTM failed while changing intensity ** \r\n");
                    return err;
                }
                /* Resetting the temporary buffer */
                memset(g_temp_buffer, RESET_VALUE, DATA_LENGTH);
                b_valid_data = false;
                err = uart_print_user_msg((uint8_t *)"\r\nAccepted value, the led is blinking with that value\r\n");
                err = uart_print_user_msg((uint8_t *)"Please set the next value\r\n");
                if (FSP_SUCCESS != err)
                {
                    return err;
                }
            }
        } 
    }
}

/*******************************************************************************************************************//**
 * @brief       Initialize  UART.
 * @param[in]   None
 * @retval      FSP_SUCCESS         Upon successful open and start of timer
 * @retval      Any Other Error code apart from FSP_SUCCESS  Unsuccessful open
 ***********************************************************************************************************************/
fsp_err_t uart_initialize(void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Initialize UART channel with baud rate 115200 */
    err = R_SCIF_UART_Open (&g_uart_ctrl, &g_uart_cfg);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT ("\r\n**  R_SCIF_UART_Open API failed  **\r\n");
        APP_ERR_TRAP(err);
    }
    return err;
}

/*****************************************************************************************************************
 *  @brief       print user message to terminal
 *  @param[in]   p_msg
 *  @retval      FSP_SUCCESS                Upon success
 *  @retval      FSP_ERR_TRANSFER_ABORTED   Upon event failure
 *  @retval      Any Other Error code apart from FSP_SUCCESS,  Unsuccessful write operation
 ****************************************************************************************************************/
fsp_err_t uart_print_user_msg(uint8_t *p_msg)
{
    fsp_err_t err   = FSP_SUCCESS;
    uint8_t msg_len = RESET_VALUE;
    uint64_t local_timeout = (DATA_LENGTH * UINT32_MAX);
    char *p_temp_ptr = (char *)p_msg;

    /* Calculate length of message received */
    msg_len = ((uint8_t)(strlen(p_temp_ptr)));

    /* Reset callback capture variable */
    g_uart_event = RESET_VALUE;

    /* Writing to terminal */
    err = R_SCIF_UART_Write (&g_uart_ctrl, p_msg, msg_len);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT ("\r\n**  R_SCIF_UART_Write API Failed  **\r\n");
        return err;
    }

    /* Check for event transfer complete */
    while ((UART_EVENT_TX_COMPLETE != g_uart_event) && (--local_timeout))
    {
        /* Check if any error event occurred */
        if (UART_ERROR_EVENTS == g_uart_event)
        {
            APP_ERR_PRINT ("\r\n**  UART Error Event Received  **\r\n");
            return FSP_ERR_TRANSFER_ABORTED;
        }
    }
    if(RESET_VALUE == local_timeout)
    {
        err = FSP_ERR_TIMEOUT;
    }
    return err;
}

/*******************************************************************************************************************//**
 *  @brief       Deinitialize SCIF UART module
 *  @param[in]   None
 *  @retval      None
 **********************************************************************************************************************/
void deinit_uart(void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Close module */
    err =  R_SCIF_UART_Close (&g_uart_ctrl);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT ("\r\n**  R_SCIF_UART_Close API failed  ** \r\n");
        APP_ERR_TRAP(err);
    }
}

/*****************************************************************************************************************
 *  @brief      UART user callback
 *  @param[in]  p_args
 *  @retval     None
 ****************************************************************************************************************/
void user_uart_callback(uart_callback_args_t *p_args)
{
    /* Logged the event in global variable */
    g_uart_event = (uint8_t)p_args->event;

    /* Reset g_temp_buffer index if it exceeds than buffer size */
    if(DATA_LENGTH == g_counter_var)
    {
        g_counter_var = RESET_VALUE;
    }

    if(UART_EVENT_RX_CHAR == p_args->event)
    {
        switch (p_args->data)
        {
            /* If Enter is pressed by user, set flag to process the data */
            case LINEFEED_ASCII:
            {
                g_counter_var = RESET_VALUE;
                g_data_received_flag  = true;
                break;
            }
            case CARRIAGE_ASCII:
            {
               g_counter_var = RESET_VALUE;
               g_data_received_flag  = true;
               break;
             }


            /* Read all data provided by user until enter button is pressed */
            default:
            {
                g_temp_buffer[g_counter_var++] = (uint8_t ) p_args->data;
                break;
            }
        }
    }
}

/*******************************************************************************************************************//**
 * @} (end addtogroup r_scif_uart_ep)
 **********************************************************************************************************************/
