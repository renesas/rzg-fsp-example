/***********************************************************************************************************************
 * File Name    : i2c_slave.h
 * Description  : Contains data structures and functions used in i2c_slave.h
 **********************************************************************************************************************/
/*
 * Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef I2C_SLAVE_H_
#define I2C_SLAVE_H_

/*
 * Define the Pin on board LED
 */
#define LED_0               (BSP_IO_PORT_06_PIN_05)
#define LED_1               (BSP_IO_PORT_05_PIN_06)
#define LED_2               (BSP_IO_PORT_06_PIN_06)
#define LED_3               (BSP_IO_PORT_06_PIN_04)

/* macro definition */
/* for on board LED */
#define LED_ON             (BSP_IO_LEVEL_HIGH)
#define LED_OFF            (BSP_IO_LEVEL_LOW)

/* MACRO for checking if two buffers are equal */
#define BUFF_EQUAL         (0U)

/* buffer size for slave and master data */
#define BUF_LEN            (0x06)

/* Human eye noticeable LED toggle delay */
#define TOGGLE_DELAY       (500U)
#define TIME_DELAY         (1000U)

#define EP_INFO    "\r\nThis EP demonstrates riic slave operation using two riic channels." \
        "\r\nIt performs slave read and write operation continuously once " \
        "\r\ninitialization is successful. On successful riic transaction " \
        "\r\n(6 bytes), Data transceived is compared. Led blinks on data " \
        "\r\nmatch else it is turned ON as sign of failure. For both cases " \
        "\r\ncorresponding slave operation message is displayed on RTT. " \
        "\r\nAny API/event failure message is also displayed.\n\n\n\n"

/*
 *  Global functions
 */
fsp_err_t init_i2C_driver(void);
fsp_err_t process_slave_WriteRead(void);
void deinit_i2c_driver(void);
void set_led(bsp_io_level_t led_state);


#endif /* I2C_SLAVE_H_ */
