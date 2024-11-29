/***********************************************************************************************************************
 * File Name    : sender_task.c
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
 **********************************************************************************************************************/
#include "sender_task.h"
#include "common_utils.h"
#include "freertos_ep.h"
#include "gtm_timer_initialize.h"

/* Flag to check Message Queue task completion */
static bool b_suspend_msqQ_task = false;

/* Sender Task entry function */
/* pvParameters contains TaskHandle_t */
void sender_task_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED (pvParameters);

    /* Variable to store task state */
    eTaskState Task_State = (eTaskState) RESET_VALUE;

    fsp_pack_version_t version = {RESET_VALUE};

    /* Initialize the message to send to Message Queue */
    msg_t message_to_task = {100 , "Sender_Task"};

    /* version get API for FLEX pack information */
    R_FSP_VersionGet (&version);

    /* Example Project information printed on the RTT */
    APP_PRINT (BANNER_INFO, EP_VERSION, version.major, version.minor, version.patch);
    APP_PRINT (EP_INFO);

    /* The rate at which the task waits on the Message availability. */
    TickType_t Queue_wait_ticks = pdMS_TO_TICKS ( WAIT_TIME );

    /* Initialize the variable used by the call to vTaskDelayUntil(). */
    TickType_t last_execution_time = xTaskGetTickCount ();

    /* Check the task state, if in running or ready state only,
     * suspend Semaphore task. Semaphore task will be resumed after
     * Message Queue task has completed execution */
    Task_State = eTaskGetState ( semaphore_task );
    if( (eBlocked == Task_State)  ||  (eRunning == Task_State)  || (eReady == Task_State) )
    {
        vTaskSuspend (semaphore_task);
    }

    APP_PRINT ("\r\n Sender_Task : Starting g_periodic_timer_msgq timer");
    /* Start GTM timer to start sending message to Message Queue periodically at 1sec from GTM callback */
    fsp_err_t fsp_err = gtm_timer_init ( &g_periodic_timer_msgq_ctrl , &g_periodic_timer_msgq_cfg );
    /* Handle error */
    if(FSP_SUCCESS != fsp_err)
    {
        APP_ERR_TRAP(fsp_err);
    }

    while (true)
    {
        /* Check if flag is set, to suspend Message Queue task. If not set,
         * continue sending messages to Message Queue at 500ms periodically. */
        if ( true != b_suspend_msqQ_task )
        {

            /* Send message to back of Message Queue */
            if ( pdPASS == xQueueSendToBack ( g_queue , &message_to_task , Queue_wait_ticks ) )
            {
                APP_PRINT ("\r\n Sender_Task : Message posted on Queue successfully");
                APP_PRINT ("\r\n Sender_Task : Going on delay for 500ms");

                /* Places the task into the Blocked state. The task
                 * will execute every 500ms once */
                vTaskDelayUntil ( &last_execution_time , WAIT_TIME );

                APP_PRINT ("\r\n Sender_Task : After delay of 500ms\r\n");
            }
        }
        else
        {
            /* Flush the message from the Queue before suspending the task */
            if ( pdPASS == xQueueReset (g_queue) )
            {
                APP_PRINT ("\r\nSender_Task : Message Queue reset \r\n");

                /* Suspend Message Queue tasks and resume Semaphore task for Execution */
                fsp_err = R_GTM_Stop (&g_periodic_timer_msgq_ctrl);
                /* Handle error */
                if ( FSP_SUCCESS != fsp_err )
                {
                    if ( FSP_SUCCESS != R_GTM_Close (&g_periodic_timer_msgq_ctrl))
                    {
                        /* Print out in case of error */
                        APP_ERR_PRINT ("\r\nSender_Task : GTM Timer Close API failed\r\n");
                    }
                    /* Print out in case of error */
                    APP_ERR_PRINT ("\r\nSender_Task : GTM Timer stop API failed\r\n");
                    APP_ERR_TRAP (fsp_err);
                }
                APP_PRINT ("\r\nSender_Task : GTM timer stopped\r\n");

                fsp_err = R_GTM_Close (&g_periodic_timer_msgq_ctrl);
                if ( FSP_SUCCESS != fsp_err )
                {
                    /* Print out in case of error */
                    APP_ERR_PRINT ("\r\nSender_Task : GTM Timer Close API failed\r\n");
                    APP_ERR_TRAP (fsp_err);
                }

                vTaskSuspend (receiver_task);
                APP_PRINT ("\r\nSender_Task : Receiver Task Suspended\r\n");

                /* Before suspending current task resume the semaphore task */
                vTaskResume (semaphore_task);
                APP_PRINT ("\r\nSender_Task : Semaphore Task Resumed\r\n");
                APP_PRINT ("\r\nSender_Task : Suspending Sender Task\r\n");

                /* Suspends calling task */
                vTaskSuspend (RESET_VALUE);
            }
        }
    }
}


/*******************************************************************************************************************//**
 * @brief      User defined GTM irq callback for Message Queue.
 *
 * @param[in]  timer_callback_args_t Callback function parameter data
 * @retval     None
 **********************************************************************************************************************/
void periodic_timer_msgq_cb(timer_callback_args_t *p_args)
{
    FSP_PARAMETER_NOT_USED (p_args);

    /* Counter to track task suspend count */
    static uint8_t msgQ_counter = RESET_VALUE;

    /* Variable is set to true if priority of unblocked task is higher
     * than the task that was in running state when interrupt occurred */
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    /* Initialize the message to send to Message Queue */
    static msg_t message_to_task = {200 , "GTM Callback"};

    /* If ISR is executed for 10sec then set the flag to suspend task */
    if( TASK_SUSPEND_COUNT == msgQ_counter )
    {
        /* Set flag to suspend Message Queue tasks */
        b_suspend_msqQ_task = true;
    }
    else
    {
        /* Send message to Message Queue */
        if ( pdPASS ==  xQueueSendToBackFromISR (g_queue , &message_to_task , &xHigherPriorityTaskWoken) )
        {
            /* Increment counter on successfully sending message */
            msgQ_counter++;
        }
    }
    /* A context switch will be performed if xHigherPriorityTaskWoken is equal to pdTRUE. */
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}
