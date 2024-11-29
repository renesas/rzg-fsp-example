/***********************************************************************************************************************
 * File Name    : i2c_sensor.h
 * Description  : Contains data structures and functions used in i2c_sensor.h/c
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

#ifndef I2C_SENSOR_H_
#define I2C_SENSOR_H_

#define ONE_BYTE                (0x01)
#define TWO_BYTE                (0x02)

#define MEASURE_PAYLOAD_SIZE    (0x03)        //measurement enable data length
#define ACCELERO_DELAY          (0xC8)
#define SENSOR_READ_DELAY       (0x03)
#define ENABLE_BIT              (0x08)
#define DATA_REGISTERS          (0x06)

/* Accelerometer internal register whichever consumed here */
#define DEVICE_ID_REG           (0x00)
#define DEVICE_SIGNATURE        (0xE5)
#define POWER_CTL_REG           (0x2D)
#define AXIS_DATA               (0x32)

#define SENSOR_DATA_SIZE        (0x06)

/*
 * function declarations
 */
fsp_err_t init_sensor(void);
void deinit_sensor(void);
fsp_err_t read_sensor_data(uint8_t *xyz_data);



#endif /* I2C_SENSOR_H_ */
