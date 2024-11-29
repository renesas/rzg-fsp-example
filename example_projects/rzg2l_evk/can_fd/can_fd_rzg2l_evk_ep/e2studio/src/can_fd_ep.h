/***********************************************************************************************************************
 * File Name    : can_fd_ep.h
 * Description  : Contains declarations of data structures and functions used in hal_entry.c.
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
 ***********************************************************************************************************************/

#ifndef CAN_FD_EP_H_
#define CAN_FD_EP_H_

#define CAN_MAILBOX_NUMBER_0            (0U)               //mail box number
#define CAN_CLASSIC_FRAME_DATA_BYTES    (8U)               //Data Length code for classic frame
#define CAN_FD_DATA_LENGTH_CODE         (16)               //Data Length code for FD frame
#define CAN_ID                          (0x1100)           //ID to be updated in transmit frame
/* Acceptance filter array parameters */
#define CANFD_FILTER_ID                 (0x00001000)
#define MASK_ID                         (0x1FFFF000)
#define MASK_ID_MODE                    (1)
#undef BUFFER_SIZE_UP
#define BUFFER_SIZE_UP                  (2048)
#define ZERO                            (0U)               //Array Index value
#define NULL_CHAR                       ('\0')             //MACRO for null character
#define WAIT_TIME                       (500U)             //Wait time value
#define EP_INFO                        "\n This Example Project demonstrates CAN FD operations on Renesas RZ MCUs using 1 RZ/G board."\
                                       "\nOn pressing any key on the RTT Viewer, data is transmitted from one channel to other."\
                                       "\nOn 1st transmission, Channel 0 transmits data to Channel 1. Channel 1 displays the received data."\
                                       "\nOn 2nd transmission, Channel 1 transmits updated data to Channel 0 as ACK. Channel 0 displays the received data,"\
                                       "\nthen Channel 0 changes CAN frame to CANFD frame and updates data."\
                                       "\nOn 3rd transmission, Channel 0 transmits updated data to Channel 1. Channel 1 displays the received data,"\
                                       "\nthen Channel 1 changes CAN frame to CANFD frame and updates data to transmits back to Channel 0 as ACK."\
                                       "\nOn 4th transmission, Channel 1 transmits updated data to Channel 0 as ACK. Channel 0 displays the received data.\n"

/* Enum to select LD that is to be made high */
typedef enum
{
   error = 1,
   successful = 2,
   transmitting = 3,
} led_state_t;

void canfd_operation(void);
void can_read_operation(void);
void canfd_deinit(void);

/** Array of Pmod LED on bottom row of Pmod0. */
#if defined BOARD_RZG2L_SMARC
static const uint16_t g_prv_leds[] =
{
    (uint16_t) BSP_IO_PORT_43_PIN_00,  ///< LED1
    (uint16_t) BSP_IO_PORT_43_PIN_02,  ///< LED2
    (uint16_t) BSP_IO_PORT_41_PIN_00,  ///< LED3
    (uint16_t) BSP_IO_PORT_43_PIN_01,  ///< LED4
};
#elif defined(BOARD_RZG2UL_SMARC)
static const uint16_t g_prv_leds[] =
{
    (uint16_t) BSP_IO_PORT_18_PIN_04,  ///< LED1
    (uint16_t) BSP_IO_PORT_01_PIN_00,  ///< LED2
    (uint16_t) BSP_IO_PORT_01_PIN_03,  ///< LED3
    (uint16_t) BSP_IO_PORT_01_PIN_04,  ///< LED4
};
#endif

/** Available user-controllable LEDs on this board. These enums can be can be used to index into the array of LED pins
 * found in the bsp_leds_t structure. */
typedef enum e_led
{
    LED_LED1,                      ///< LED1
    LED_LED2,                      ///< LED2
    LED_LED3,                      ///< LED3
    LED_LED4,                      ///< LED4
} led_t;


#endif /* CAN_FD_EP_H_ */
