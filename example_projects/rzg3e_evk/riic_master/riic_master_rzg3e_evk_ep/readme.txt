/*
 * Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    The example project demonstrates the typical use of the RIIC master HAL module APIs.
    The project initializes RIIC master module with fast mode and interfaces with PmodACL™ Board for ADXL345.

    On power up after establishing the connection of sensor with the board, it displays accelerometer axis data on 
    RTTviewer. Any API/event failure will be displayed on RTTviewer.

2. Hardware and Software Requirements:
    External Hardware : Pmod ACL
    Software : JLink RTT Viewer v7.96j

3. Hardware Settings:
    Boot Mode:
    Boot mode 3 (SCIF Downloading) with CA55 cold boot

    Board:
    RZ/G3E  Evaluation Kit (Smarc)

    Hardware Connection:

    (1) Set for DIP switches and jumpers as follow.

        +===============+====================================+
        | Board setting | RZ/G3E Evaluation Board Kit        |
        +===============+====================================+
        | Module board  | SW5-1  : OFF                       |
        |               | SW5-2  : OFF                       |
        |               | SW5-3  : OFF                       |
        |               | SW5-4  : OFF                       |
        |               | SW5-5  : OFF                       |
        |               | SW5-6  : OFF                       |
        +---------------+------------------------------------+
        | Carrier board | SW_MODE-1    : OFF                 |
        |               | SW_MODE-2    : ON                  |
        |               | SW_MODE-3    : OFF                 |
        |               | SW_MODE-4    : ON                  |
        |               | PMOD_PWR_SEL : Jumper connects 2-4 |
        +---------------+------------------------------------+

    (2) Connect the J-Link Base and the connector on the SMARC Module Board with JTAG cable.
        When connecting the conversion adapter "J-Link 9-pin Cortex-M Adapter" made by SEGGER will be required.

    (3) Connect Pmod ACL and Smarc Carrier Board as follows.
        Pmod ACL has two on board connectors, J2 is used for I2C communication.

        J2 (Pmod ACL)                   PMOD1_6A (Smarc Carrier Board)
                                        -------
                                        |1   7|
        ------                          |2   8|
        |1  5|---SCL  --->  RIICx_SCL---|3   9|
        |2  6|---SDA  --->  RIICx_SDA---|4  10|
        |3  7|---GND  --->  GND pin  ---|5  11|
        |4  8|---VCC  --->  VCC pin  ---|6  12|
        ------                          -------

NOTE:
1. With the SDO/ALT ADDRESS pin high, the 7-bit I2C address for the device is 0x1D, followed by the R/W bit.
   An alternate I2C address of 0x53 (followed by the R/W bit) can be chosen by grounding the SDO/ALT ADDRESS pin.

2. Segger RTT block address is required to connect J-Link RTTViewer.
   The RTT block address can be confirmed by searching "_SEGGER_RTT" in .map file
   which is located in Debug folder and generated when building.