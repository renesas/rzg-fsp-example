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

1. Project Overview:
    The example project demonstrates the typical use of the IIC master HAL module APIs.
    The project initializes IIC master module with fast mode and interfaces with PmodACL™ Board for ADXL345.

    On power up after establishing the connection of sensor with the board, it displays accelerometer axis data on 
    RTTviewer. Any API/event failure will be displayed on RTTviewer.

2. Hardware and Software Requirements:
    External Hardware : Pmod ACL
    Software          : JLink RTT Viewer v7.94

3. Hardware Settings:
    Boot Mode:
    Boot mode 3 (1.8-V Single, Quad, or Octal serial flash memory)

    Board:
    RZ/G2L  Evaluation Kit (SMARC)
    RZ/G2LC Evaluation Kit (SMARC)
    RZ/G2UL Evaluation Kit (SMARC)

    Hardware Connection:

    (1) Set for DIP switches and jumpers as follow.

    +===============+===============================+================================+================================+
    | Board setting | RZ/G2L Evaluation Kit (SMARC) | RZ/G2LC Evaluation Kit (SMARC) | RZ/G2UL Evaluation Kit (SMARC) |
    +===============+===============================+================================+================================+
    | Module board  | SW1-1  : OFF                  | SW1-1  : OFF                   | SW1-1  : OFF                   |
    |               | SW1-2  : Don't care           | SW1-2  : Don't care            | SW1-2  : Don't care            |
    |               |                               | SW1-3  : Don't care            | SW1-3  : Don't care            |
    |               |                               | SW1-4  : Don't care            |                                |
    |               |                               | SW1-5  : Don't care            |                                |
    |               |                               | SW1-6  : Don't care            |                                |
    +---------------+-------------------------------+--------------------------------+--------------------------------+
    | Carrier board | SW1    : Don't care           | SW1    : Don't care            | SW1    : Don't care            |
    |               | SW2    : Don't care           | SW2    : Don't care            | SW2    : Don't care            |
    |               | SW3    : 1-2                  | SW3    : 1-2                   | SW3    : 1-2                   |
    |               | SW4    : 1-2                  | SW4    : 1-2                   | SW4    : 1-2                   |
    |               | SW5    : Don't care           | SW5    : Don't care            | SW5    : Don't care            |
    |               | SW6    : Don't care           | SW6    : Don't care            | SW6    : Don't care            |
    |               | SW7    : Don't care           | SW7    : Don't care            | SW7    : Don't care            |
    |               | SW8    : Don't care           | SW8    : Don't care            | SW8    : Don't care            |
    |               | SW11-1 : OFF                  | SW11-1 : OFF                   | SW11-1 : OFF                   |
    |               | SW11-2 : OFF                  | SW11-2 : OFF                   | SW11-2 : OFF                   |
    |               | SW11-3 : OFF                  | SW11-3 : OFF                   | SW11-3 : OFF                   |
    |               | SW11-4 : ON                   | SW11-4 : ON                    | SW11-4 : ON                    |
    |               | CN4    : Jumper connects 1-3  | CN4    : Jumper connects 1-3   | CN4    : Jumper connects 1-3   |
    |               |          Jumper connects 2-4  |          Jumper connects 2-4   |          Jumper connects 2-4   |
    +---------------+-------------------------------+--------------------------------+--------------------------------+

    (2) Connect the J-Link Base and the connector on the SMARC Module Board with JTAG cable.
        When connecting the conversion adapter "J-Link 9-pin Cortex-M Adapter" made by SEGGER will be required.
    (3) Connect Pmod ACL and SMARC Carrier Board as follows.
        Pmod ACL has two on board connectors, J2 is used for I2C communication.

        J2 (Pmod ACL)                   PMOD1 (SMARC Carrier Board)
                                        -------
                                        |1   7|
        ------                          |2   8|
        |1  5|---SCL  --->  RIICx_SCL---|3   9|
        |2  6|---SDA  --->  RIICx_SDA---|4  10|
        |3  7|---GND  --->  GND pin  ---|5  11|
        |4  8|---VCC  --->  VCC pin  ---|6  12|
        ------                          -------
        ( RZ/G2L  Evaluation Kit (SMARC) uses RIIC3
          RZ/G2LC Evaluation Kit (SMARC) uses RIIC2
          RZ/G2UL Evaluation Kit (SMARC) uses RIIC1 )

        JP1 on Pmod ACL should be set to position 1-2. (Connect SDO/ALTADDR and VCC.)

NOTE:
1. With the SDO/ALT ADDRESS pin high, the 7-bit I2C address for the device is 0x1D, followed by the R/W bit.
   An alternate I2C address of 0x53 (followed by the R/W bit) can be chosen by grounding the SDO/ALT ADDRESS pin.

2. Segger RTT block address is required to connect J-Link RTTViewer. 
   The RTT block address can be confirmed by searching "_SEGGER_RTT" in .map file 
   which is located in Debug folder and generated when building.