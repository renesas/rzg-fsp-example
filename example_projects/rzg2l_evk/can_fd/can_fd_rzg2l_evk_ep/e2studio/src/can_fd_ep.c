/***********************************************************************************************************************
 * File Name    : can_fd_ep.c
 * Description  : Contains data structures and functions used in can_fd_ep.c
 ***********************************************************************************************************************/
/***********************************************************************************************************************
* Copyright 2023 Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
*
* This software and documentation are supplied by Renesas Electronics Corporation and/or its affiliates and may only
* be used with products of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.
* Renesas products are sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for
* the selection and use of Renesas products and Renesas assumes no liability.  No license, express or implied, to any
* intellectual property right is granted by Renesas.  This software is protected under all applicable laws, including
* copyright laws. Renesas reserves the right to change or discontinue this software and/or this documentation.
* THE SOFTWARE AND DOCUMENTATION IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND
* TO THE FULLEST EXTENT PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY,
* INCLUDING WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE
* SOFTWARE OR DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.
* TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR
* DOCUMENTATION (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER,
* INCLUDING, WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY
* LOST PROFITS, OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE
* POSSIBILITY OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
**********************************************************************************************************************/

#include "common_utils.h"
#include "can_fd_ep.h"

/*******************************************************************************************************************//**
 * @addtogroup can_fd_ep
 * @{
 **********************************************************************************************************************/
 can_frame_t g_canfd_ch0_tx_frame;                      //CAN 0 transmit frame
 can_frame_t g_canfd_ch0_rx_frame;                      //CAN 0 receive frame

 can_frame_t g_canfd_ch1_tx_frame;                      //CAN 1 transmit frame
 can_frame_t g_canfd_ch1_rx_frame;                      //CAN 1 receive frame

 /* Variable to store rx frame status info of channel 0*/
 can_info_t can_ch0_rx_info =
 {
  .error_code  = RESET_VALUE,
  .error_count_receive = RESET_VALUE,
  .error_count_transmit = RESET_VALUE,
  .rx_fifo_status = RESET_VALUE,
  .rx_mb_status = RESET_VALUE,
  .status = RESET_VALUE,
 };

 /* Variable to store rx frame status info of channel 1*/
 can_info_t can_ch1_rx_info =
 {
  .error_code  = RESET_VALUE,
  .error_count_receive = RESET_VALUE,
  .error_count_transmit = RESET_VALUE,
  .rx_fifo_status = RESET_VALUE,
  .rx_mb_status = RESET_VALUE,
  .status = RESET_VALUE,
 };

/* Data to be loaded in Classic CAN and FD frames for transmission and acknowledgement */
uint8_t tx_data[SIZE_64] = "TX_MESG";
uint8_t rx_data[SIZE_64] = "RX_MESG";
uint8_t tx_fd_data[SIZE_64];
uint8_t rx_fd_data[SIZE_64];

extern bool b_canfd_ch0_tx_complete ;
extern bool b_canfd_ch0_rx_complete ;

extern bool b_canfd_ch1_tx_complete ;
extern bool b_canfd_ch1_rx_complete ;
extern bool b_canfd_err_status ;

extern bsp_leds_t g_leds;
extern uint32_t g_time_out;

/* User defined functions */
static void can_write_operation(canfd_instance_ctrl_t p_api_ctrl, can_frame_t can_transmit_frame);
static void can_fd_data_update(void);
static void can_data_check_operation(void);
void led_update(led_state_t led_state);


/*******************************************************************************************************************//**
 * @brief       This function is to transmit data after receiving user input and it performs subsequent operations
 * @param[in]   None
 * @return      None
 **********************************************************************************************************************/
void canfd_operation(void)
{
    /* Update transmit frame parameters */
    g_canfd_ch0_tx_frame.id = CAN_ID;
    g_canfd_ch0_tx_frame.id_mode = CAN_ID_MODE_EXTENDED;
    g_canfd_ch0_tx_frame.type = CAN_FRAME_TYPE_DATA;
    g_canfd_ch0_tx_frame.data_length_code = CAN_CLASSIC_FRAME_DATA_BYTES;
    g_canfd_ch0_tx_frame.options = ZERO;

    /* Update transmit frame data with message */
    memcpy((uint8_t*)&g_canfd_ch0_tx_frame.data[ZERO], (uint8_t*)&tx_data[ZERO], CAN_FD_DATA_LENGTH_CODE);

    APP_PRINT("\n 1. Transmission of data over classic CAN Frame\n");

    /* Transmission of data over classic CAN frame */
    can_write_operation(g_canfd_ch0_ctrl, g_canfd_ch0_tx_frame);

    APP_PRINT("\nClassic CAN transmission is successful");
}

/*******************************************************************************************************************//**
 * @brief       This function is to  transmit data  on classic CAN or CANFD frame
 * @param[in]   can_transmit_frame        Data frame to be transmitted
 * @return      None
 **********************************************************************************************************************/
static void can_write_operation(canfd_instance_ctrl_t p_api_ctrl, can_frame_t can_transmit_frame)
{
    fsp_err_t err = FSP_SUCCESS;


    /* Transmit the data from mail box #0 with tx_frame */
    err = R_CANFD_Write(&p_api_ctrl, CAN_MAILBOX_NUMBER_0, &can_transmit_frame);
    /* Handle error */
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\nCANFD Write API FAILED");
        led_update(error);
        canfd_deinit();
        APP_ERR_TRAP(err);
    }

    led_update(transmitting);
    /* Wait here for an event from callback */
    while ((true != b_canfd_ch0_tx_complete) && (true != b_canfd_ch1_tx_complete))
    {
        g_time_out--;
        if (RESET_VALUE == g_time_out)
        {
           APP_ERR_PRINT("\nCAN transmission failed due to timeout");
           led_update(error);
           APP_ERR_TRAP(true);
           break;
        }
    }

    /* Reset flag bit */
    if(true == b_canfd_ch0_tx_complete )
    {
        b_canfd_ch0_tx_complete = false;
    }
    if(true == b_canfd_ch1_tx_complete )
    {
        b_canfd_ch1_tx_complete = false;
    }
}

/*******************************************************************************************************************//**
 * @brief       This function is to compare transmitted/received data and to send ACK accordingly
 * @param[in]   None
 * @return      None
 **********************************************************************************************************************/
static void can_data_check_operation(void)
{
    /*Update data to be compared with data transmitted/received over FD frame */
    can_fd_data_update();

    if(RESET_VALUE == strncmp((char*)&g_canfd_ch1_rx_frame.data[ZERO], (char*)&tx_data[ZERO], CAN_CLASSIC_FRAME_DATA_BYTES))
    {
        /* Cleaning receive frame */
        memset(&g_canfd_ch1_rx_frame.data[ZERO], NULL_CHAR, CAN_CLASSIC_FRAME_DATA_BYTES);

        APP_PRINT("\nReceived 'TX__MESG' on classic frame.");
        APP_PRINT("\n 2. Responding with 'RX__MESG' using classic CAN frame\n");

        /* Update transmit frame parameters */
        g_canfd_ch1_tx_frame.id = CAN_ID;
        g_canfd_ch1_tx_frame.id_mode = CAN_ID_MODE_EXTENDED;
        g_canfd_ch1_tx_frame.type = CAN_FRAME_TYPE_DATA;
        g_canfd_ch1_tx_frame.data_length_code = CAN_CLASSIC_FRAME_DATA_BYTES;
        g_canfd_ch1_tx_frame.options = ZERO;

        /* Update transmit frame data with message */
        memcpy(&g_canfd_ch1_tx_frame.data, &rx_data, CAN_CLASSIC_FRAME_DATA_BYTES);

        /* Transmission of data as acknowledgement */
        can_write_operation(g_canfd_ch1_ctrl, g_canfd_ch1_tx_frame);

        APP_PRINT("\nCAN transmission after receive is successful. Sent back the ACK using classic CAN frame");

    }
    else if(RESET_VALUE == strncmp((char*)&g_canfd_ch0_rx_frame.data[ZERO], (char*)&rx_data[ZERO], CAN_CLASSIC_FRAME_DATA_BYTES))
    {
        /* Cleaning receive frame */
        memset(&g_canfd_ch0_rx_frame.data[ZERO], NULL_CHAR, CAN_CLASSIC_FRAME_DATA_BYTES);

        APP_PRINT("\nReceived Acknowledgement for Classic CAN Frame transmission.\nCAN operation Successful. Data length = %d\n", g_canfd_ch0_rx_frame.data_length_code);
        APP_PRINT("\n 3. Data transmission over FD frame\n");

        /* Updating FD frame parameters for channel 0*/
        g_canfd_ch0_tx_frame.id = CAN_ID;
        g_canfd_ch0_tx_frame.id_mode = CAN_ID_MODE_EXTENDED;
        g_canfd_ch0_tx_frame.data_length_code = CAN_FD_DATA_LENGTH_CODE;
        g_canfd_ch0_tx_frame.options = CANFD_FRAME_OPTION_FD | CANFD_FRAME_OPTION_BRS;

        /* Fill frame data that is to be sent in FD frame */
        for( uint16_t j = 0; j < SIZE_64; j++)
        {
            g_canfd_ch0_tx_frame.data[j] = (uint8_t) (j + 1);
        }

        /* Transmission of data as over FD frame */
        can_write_operation(g_canfd_ch0_ctrl, g_canfd_ch0_tx_frame);

        APP_PRINT("\nCAN transmission on FD Frame after receiving classic frame ACK is successful");

    }
    else if(RESET_VALUE == strncmp((char*)&g_canfd_ch1_rx_frame.data[ZERO], (char*)&tx_fd_data[ZERO], CAN_FD_DATA_LENGTH_CODE)) // acknowledging for second transmission
    {
        /* Cleaning receive frame */
        memset(&g_canfd_ch1_rx_frame.data[ZERO], NULL_CHAR, CAN_CLASSIC_FRAME_DATA_BYTES);

        APP_PRINT("\nReceived data over FD Frame.\nCAN operation Successful. Data length = %d\n", g_canfd_ch1_rx_frame.data_length_code);
        APP_PRINT("\n 4. Sending modified data over FD Frame now as acknowledgement for received FD data.\n");

        /* Updating FD frame parameters for channel 1*/
        g_canfd_ch1_tx_frame.id = CAN_ID;
        g_canfd_ch1_tx_frame.id_mode = CAN_ID_MODE_EXTENDED;
        g_canfd_ch1_tx_frame.data_length_code = CAN_FD_DATA_LENGTH_CODE;
        g_canfd_ch1_tx_frame.options = CANFD_FRAME_OPTION_FD | CANFD_FRAME_OPTION_BRS;

        /* Fill frame data that is to be sent in FD frame */
        for( uint16_t j = 0; j < SIZE_64; j++)
        {
            g_canfd_ch1_tx_frame.data[j] = (uint8_t) (j + 5);
        }

        /* Transmission of data as acknowledgement */
        can_write_operation(g_canfd_ch1_ctrl, g_canfd_ch1_tx_frame);

        APP_PRINT("\nCAN transmission on FD Frame as acknowledgement is successful");

    }
    else if(RESET_VALUE == strncmp((char*)&g_canfd_ch0_rx_frame.data[ZERO], (char*)&rx_fd_data[ZERO], CAN_FD_DATA_LENGTH_CODE)) // acknowledgement for second transmission
    {
        /* Cleaning receive frame */
        memset(&g_canfd_ch0_rx_frame.data[ZERO], NULL_CHAR, CAN_CLASSIC_FRAME_DATA_BYTES);

        APP_PRINT("\nReceived Acknowledgement for FD Frame.\nCAN operation Successful. Data length = %d\n\n", g_canfd_ch0_rx_frame.data_length_code);
        APP_PRINT("\nPlease enter any key on Terminal Emulator to initiate CAN transmission.\n");
    }
    else /* Wrong MSG Received */
    {
        APP_ERR_PRINT("\nCAN data mismatch\r\nCAN operation failed");
        led_update(error);
        APP_ERR_TRAP(true);
    }
}

/*******************************************************************************************************************//**
 * @brief       This function is to read Channel status info and read data.
 * @param[in]   None
 * @return      None
 **********************************************************************************************************************/
void can_read_operation(void)
{
    fsp_err_t err = FSP_SUCCESS;

    if (b_canfd_ch0_rx_complete == true)
    {
        /* Get the status information for CAN transmission */
        err = R_CANFD_InfoGet (&g_canfd_ch0_ctrl, &can_ch0_rx_info);
        /* Handle error */
        if (FSP_SUCCESS != err)
        {
            APP_ERR_PRINT("\nCAN InfoGet API FAILED");
            led_update (error);
            canfd_deinit ();
            APP_ERR_TRAP(err);
        }
        /* Check if the data is received in FIFO */
        if (can_ch0_rx_info.rx_mb_status)
        {
            /* Read the input frame received */
            err = R_CANFD_Read (&g_canfd_ch0_ctrl, ZERO, &g_canfd_ch0_rx_frame);
            /* Handle error */
            if (FSP_SUCCESS != err)
            {
                APP_ERR_PRINT("\nCAN Read API FAILED");
                led_update (error);
                canfd_deinit ();
                APP_ERR_TRAP(err);
            }

            /* Reset flag bit */
            b_canfd_ch0_rx_complete = false;

            /*Check if the transmitted and received data are same and send ACK accordingly */
            can_data_check_operation();
        }
        else
        {
            /* Do Nothing */
        }

    }
    else if (b_canfd_ch1_rx_complete == true)
    {
        /* Get the status information for CAN transmission */
        err = R_CANFD_InfoGet (&g_canfd_ch1_ctrl, &can_ch1_rx_info);
        /* Handle error */
        if (FSP_SUCCESS != err)
        {
            APP_ERR_PRINT("\nCAN InfoGet API FAILED");
            led_update (error);
            canfd_deinit ();
            APP_ERR_TRAP(err);
        }

        /* Check if the data is received in FIFO */
        if (can_ch1_rx_info.rx_mb_status)
        {
            /*/* Read the input frame received */
            err = R_CANFD_Read (&g_canfd_ch1_ctrl, ZERO, &g_canfd_ch1_rx_frame);
            /* Handle error */
            if (FSP_SUCCESS != err)
            {
                APP_ERR_PRINT("\nCAN Read API FAILED");
                led_update (error);
                canfd_deinit ();
                APP_ERR_TRAP(err);
            }

            /* Reset flag bit */
            b_canfd_ch1_rx_complete = false;

            /*Check if the transmitted and received data are same and send ACK accordingly */
            can_data_check_operation();
        }
        else
        {
            /* Do Nothing */
        }
    }
    else
    {
        /* Do Nothing */
    }

    led_update(successful);
}

/*******************************************************************************************************************//**
 * @brief       This function is to update data buffer that is to be compared with transmitted FD frame data
 * @param[in]   None
 * @return      None
 **********************************************************************************************************************/
static void can_fd_data_update(void)
{
    /* Fill frame data to be compared with data transmitted on CANFD frame*/
    for( uint16_t i = 0; i < SIZE_64; i++)
    {
        tx_fd_data[i]          = (uint8_t) (i + 1);
    }
    for(uint16_t j = 0; j < SIZE_64; j++)
    {
        rx_fd_data[j] = (uint8_t) (j + 5);
    }
}

/*******************************************************************************************************************//**
 * @brief This function updates led state as per operation status
 * @param[in]  led_state      Select LED states according to operations.
 * @retval     None
 **********************************************************************************************************************/
void led_update(led_state_t led_state)
{
    switch(led_state)
    {
        case error:
        {
            /* PMOD LED will high to show error state */
            R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_leds.p_leds[LED_LED1], BSP_IO_LEVEL_HIGH);
            R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_leds.p_leds[LED_LED2], BSP_IO_LEVEL_HIGH);
            R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_leds.p_leds[LED_LED3], BSP_IO_LEVEL_HIGH);
            R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_leds.p_leds[LED_LED4], BSP_IO_LEVEL_HIGH);
            break;
        }
        case successful:
        {
            /* Holds level to set for pins */
            static bsp_io_level_t pin_level = BSP_IO_LEVEL_LOW;

            /* Toggle level for next write */
            if (BSP_IO_LEVEL_LOW == pin_level)
            {
                pin_level = BSP_IO_LEVEL_HIGH;
            }
            else
            {
                pin_level = BSP_IO_LEVEL_LOW;
            }

            /* PMOD LED will blink to show successful state */
            R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_leds.p_leds[LED_LED1], pin_level);
            R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_leds.p_leds[LED_LED2], pin_level);
            R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_leds.p_leds[LED_LED3], pin_level);
            R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_leds.p_leds[LED_LED4], pin_level);

            /* Delay */
            R_BSP_SoftwareDelay(WAIT_TIME, BSP_DELAY_UNITS_MILLISECONDS);

            break;
        }
        case transmitting:
        {
            /* Set the LED pin state low */
            R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_leds.p_leds[LED_LED1], BSP_IO_LEVEL_LOW);
            R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_leds.p_leds[LED_LED2], BSP_IO_LEVEL_LOW);
            R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_leds.p_leds[LED_LED3], BSP_IO_LEVEL_LOW);
            R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_leds.p_leds[LED_LED4], BSP_IO_LEVEL_LOW);

            for(int i = 0; i < 4; i ++)
            {
                R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_leds.p_leds[i], BSP_IO_LEVEL_HIGH);
                /* Delay */
                R_BSP_SoftwareDelay(WAIT_TIME/10, BSP_DELAY_UNITS_MILLISECONDS);
            }

            for(int j = 0; j < 4; j ++)
            {
                R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_leds.p_leds[j], BSP_IO_LEVEL_LOW);
                /* Delay */
                R_BSP_SoftwareDelay(WAIT_TIME/10, BSP_DELAY_UNITS_MILLISECONDS);
            }

            break;
        }
        default:
        {
            break;
        }
    }

}

/*******************************************************************************************************************//**
 * @brief CAN FD callback function.
 * @param[in]  p_args
 * @retval     None
 **********************************************************************************************************************/
void canfd_ch0_callback(can_callback_args_t *p_args)
{
    switch (p_args->event)
    {
        case CAN_EVENT_TX_COMPLETE:
        {
            b_canfd_ch0_tx_complete = true;     // set flag bit
            break;
        }
        case CAN_EVENT_RX_COMPLETE:
        {
            b_canfd_ch0_rx_complete = true;     // set flag bit
            break;
        }
        case CAN_EVENT_ERR_WARNING:             // error warning event
        case CAN_EVENT_ERR_PASSIVE:             // error passive event
        case CAN_EVENT_ERR_BUS_OFF:             // error Bus Off event
        case CAN_EVENT_BUS_RECOVERY:            // Bus recovery error event
        case CAN_EVENT_MAILBOX_MESSAGE_LOST:    // overwrite/overrun error event
        case CAN_EVENT_ERR_BUS_LOCK:            // Bus lock detected (32 consecutive dominant bits).
        case CAN_EVENT_ERR_CHANNEL:             // Channel error has occurred.
        case CAN_EVENT_TX_ABORTED:              // Transmit abort event.
        case CAN_EVENT_ERR_GLOBAL:              // Global error has occurred.
        case CAN_EVENT_TX_FIFO_EMPTY:           // Transmit FIFO is empty.
        case CAN_EVENT_FIFO_MESSAGE_LOST:       // Receive FIFO overrun.
        {
            b_canfd_err_status = true;          // set flag bit
            break;
        }

    }
}

void canfd_ch1_callback(can_callback_args_t *p_args)
{
    switch (p_args->event)
    {
        case CAN_EVENT_TX_COMPLETE:
        {
            b_canfd_ch1_tx_complete = true;     // set flag bit
            break;
        }
        case CAN_EVENT_RX_COMPLETE:
        {
            b_canfd_ch1_rx_complete = true;     // set flag bit
            break;
        }
        case CAN_EVENT_ERR_WARNING:             // error warning event
        case CAN_EVENT_ERR_PASSIVE:             // error passive event
        case CAN_EVENT_ERR_BUS_OFF:             // error Bus Off event
        case CAN_EVENT_BUS_RECOVERY:            // Bus recovery error event
        case CAN_EVENT_MAILBOX_MESSAGE_LOST:    // overwrite/overrun error event
        case CAN_EVENT_ERR_BUS_LOCK:            // Bus lock detected (32 consecutive dominant bits).
        case CAN_EVENT_ERR_CHANNEL:             // Channel error has occurred.
        case CAN_EVENT_TX_ABORTED:              // Transmit abort event.
        case CAN_EVENT_ERR_GLOBAL:              // Global error has occurred.
        case CAN_EVENT_TX_FIFO_EMPTY:           // Transmit FIFO is empty.
        case CAN_EVENT_FIFO_MESSAGE_LOST:       // Receive FIFO overrun.
        {
            b_canfd_err_status = true;          // set flag bit
            break;
        }
    }
}
/*******************************************************************************************************************//**
 * @brief       This function is to de-initializes the CANFD module
 * @param[in]   None
 * @return      None
 **********************************************************************************************************************/
void canfd_deinit(void)
{
    fsp_err_t err = FSP_SUCCESS;
    /* Close CANFD channel */
    err = R_CANFD_Close(&g_canfd_ch0_ctrl);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\n**CANFD Close API failed**");
    }

    /* Close CANFD channel */
    err = R_CANFD_Close(&g_canfd_ch1_ctrl);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\n**CANFD Close API failed**");
    }
}

/*******************************************************************************************************************//**
 * @} (end addtogroup can_fd_ep)
 **********************************************************************************************************************/


