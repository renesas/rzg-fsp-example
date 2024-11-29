/***********************************************************************************************************************
 * File Name    : spi_ep.h
 * Description  : Contains declarations of data structures and functions used in spi_ep.c.
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

#ifndef SPI_EP_H_
#define SPI_EP_H_

/*******************************************************************************************************************//**
 * @ingroup spi_ep
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Macros for commands to be received through RTT input */
#define WRITE           (1)
#define READ            (2)
#define EXIT            (3)

/* Macro for miscellaneous */
#define DELAY_ONE_SEC   (1)

/* Array indexing MACRO */
#define ARRAY_INDEX      (0)

/* MACRO for checking if no byte is received */
#define BYTES_RECEIVED_ZERO  (0)

/* SPI buffer length */
#define BUFF_LEN (32)

/* Max wait count for time-out operation */
#define MAX_COUNT (0xFFFFFF)

/* Min wait count for time-out operation */
#define MIN_COUNT (0)

/* MACRO for checking if two buffers are equal */
#define BUFF_EQUAL (0)

/* MACRO for null character */
#define NULL_CHAR  ('\0')

/* Macro to convert 32 bits into bytes */
#define BITS_TO_BYTES   (4U)

#define MX25L12835F_SECTOR_SIZE    (4096)
#define MX25L12835F_PAGE_SIZE      (256)

/***********************************************************************************************************************
 * User-defined APIs
 **********************************************************************************************************************/
#define MX25L12835F_SSL_PIN         (BSP_IO_PORT_15_PIN_03)
#define MX25L12835F_ADDRESS         (0x1000000U)

/*
 * function declarations
 */
fsp_err_t spi_init(void);
fsp_err_t spi_write(void);
fsp_err_t spi_read(void);
fsp_err_t spi_exit_demo(void);
void spi_clean_up(void);

/** @} */

#endif /* SPI_EP_H_ */
