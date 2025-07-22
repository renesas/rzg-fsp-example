/***********************************************************************************************************************
 * File Name    : receiver_task.c
 * Description  : Contains function definition.
 **********************************************************************************************************************/
/*
 * Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "receiver_task.h"
#include "common_utils.h"
#include "freertos_ep.h"
#include "gtm_timer_initialize.h"

/* Receiver Task entry function */
/* pvParameters contains TaskHandle_t */
void receiver_task_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED (pvParameters);

    /* Message variable to receive message */
    msg_t message_from_task = {RESET_VALUE, (char *)NULL};

    while (true)
    {
        /* Receive messages until queue is empty and print same */
        if ( pdPASS == xQueueReceive (g_queue , &message_from_task , portMAX_DELAY  ) )
        {
            APP_PRINT ("\r\nReceiver Task : Message received Successfully");
            APP_PRINT ("\r\n    Data   : %d  \r\n    Sender : %s\r\n", message_from_task.data, message_from_task.task_name);
        }
    }
}
