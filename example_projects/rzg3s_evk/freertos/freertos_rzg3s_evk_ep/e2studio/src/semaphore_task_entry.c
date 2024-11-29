/***********************************************************************************************************************
 * File Name    : semaphore_task.c
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
#include "semaphore_task.h"
#include "common_utils.h"
#include "freertos_ep.h"
#include "gtm_timer_initialize.h"

/* Semaphore Task entry function */
/* pvParameters contains TaskHandle_t */
/* Flag to suspend Semaphore task  */
static bool b_suspend_semphr_task = false;

/* Semaphore Task entry function */
/* pvParameters contains TaskHandle_t */
void semaphore_task_entry (void *pvParameters)
{
    FSP_PARAMETER_NOT_USED(pvParameters);

    /* The rate at which the task waits on the Semaphore availability. */
    TickType_t Semphr_wait_ticks = pdMS_TO_TICKS ( WAIT_TIME );

    APP_PRINT ("\r\n Semaphore Task : Starting g_periodic_timer_sem timer");
    /* Start GTM timer to 'Give' Semaphore periodically at 1sec for semaphore_task */
    fsp_err_t fsp_err = gtm_timer_init ( &g_periodic_timer_sem_ctrl , &g_periodic_timer_sem_cfg );
    /* Handle error */
    if(FSP_SUCCESS != fsp_err)
    {
        APP_ERR_TRAP(fsp_err);
    }

    while (true)
    {
        if ( true != b_suspend_semphr_task )
        {
            APP_PRINT ("\r\n Semaphore Task : Waiting for GTM ISR to release semaphore \r\n");

            if ( pdPASS == xSemaphoreTake ( g_binary_semaphore , Semphr_wait_ticks ) )
            {
                /* Print if the semaphore is acquired successfully */
                APP_PRINT ("\r\n Semaphore Task : Acquired semaphore successfully\r\n");
            }
        }
        else
        {
            /* Stop the GTM timer */
            fsp_err = R_GTM_Stop (&g_periodic_timer_sem_ctrl);
            /* Handle error */
            if ( FSP_SUCCESS != fsp_err )
            {
                if (FSP_SUCCESS != R_GTM_Close (&g_periodic_timer_sem_ctrl))
                {
                    /* Print out in case of error */
                    APP_ERR_PRINT ("\r\nSemaphore Task : GTM Timer Close API failed\r\n");
                }
                /* Print out in case of error */
                APP_ERR_PRINT ("\r\nSemaphore Task : GTM Timer stop API failed\r\n");
                APP_ERR_TRAP (fsp_err);
            }
            APP_PRINT ("\r\nSemaphore Task : GTM timer stopped\r\n");

            fsp_err = R_GTM_Close ( &g_periodic_timer_sem_ctrl );
            if ( FSP_SUCCESS != fsp_err )
            {
                /* Print out in case of error */
                APP_ERR_PRINT ("\r\nSemaphore Task : GTM Timer Close API failed\r\n");
                APP_ERR_TRAP (fsp_err);
            }

            APP_PRINT ("\r\nSemaphore Task : Suspending Semaphore Task\r\n");
            APP_PRINT ("\r\nSemaphore Task : Application ends here. Restart to run the application again\r\n");
            /* Suspends calling task */
            vTaskSuspend (RESET_VALUE);
        }
    }
}


/*******************************************************************************************************************//**
 * @brief      User defined GTM irq callback for Semaphore.
 *
 * @param[in]  timer_callback_args_t  Callback function parameter data
 * @retval     None
 **********************************************************************************************************************/
void periodic_timer_semphr_cb(timer_callback_args_t *p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);

    /* Counter to track task suspend count */
    static uint8_t semphr_counter = RESET_VALUE;

    /* Variable is set to true if priority of unblocked task is higher
     * than the task that was in running state when interrupt occurred */
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    /* If ISR is executed for 10sec then set the flag to suspend task */
    if( TASK_SUSPEND_COUNT == semphr_counter )
    {
        /* Set flag to suspend Semaphore tasks */
        b_suspend_semphr_task = true;
    }
    else
    {
        /* Release semaphore  */
        xSemaphoreGiveFromISR ( g_binary_semaphore , &xHigherPriorityTaskWoken );

        /* Increment counter to suspend task */
        semphr_counter++;
    }

    /* context switch will be performed if xHigherPriorityTaskWoken is equal to pdTRUE.  */
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}
