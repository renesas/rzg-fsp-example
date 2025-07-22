/*
 * Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    The example project demonstrates typical use of the riic slave HAL module APIs.
    The project initializes riic slave and riic master module with standard rate and is made interfaced with loop-back 
    mechanism. It performs slave read and write operation continuously once initialization is successful. On successful
    i2c transaction (6 bytes), Data transceived is compared. Led blinks on data match else it is turned on as sign of 
    failure. Output message for both corresponding slave operations is displayed on RTT Viewer. Any API/event failure 
    message is also displayed.

2. Hardware and Software Requirements:
    External Hardware : Pmod LED
    Software          : JLink RTT Viewer v7.96j

3. Hardware settings:
    Boot Mode:
    Boot mode 3 (SCIF Downloading) with CA55 cold boot

    Board:
    RZ/G3E  Evaluation Kit (Smarc)

    Hardware Connection:

    (1) Set for DIP switches and jumpers as follow.

        +===============+=====================================+
        | Board setting | RZ/G3E Evaluation Board Kit         |
        +===============+=====================================+
        | Module board  | SW5-1  : OFF                        |
        |               | SW5-2  : OFF                        |
        |               | SW5-3  : OFF                        |
        |               | SW5-4  : OFF                        |
        |               | SW5-5  : OFF                        |
        |               | SW5-6  : OFF                        |
        +---------------+-------------------------------------+
        | Carrier board | SW_MODE-1    : OFF                  |
        |               | SW_MODE-2    : ON                   |
        |               | SW_MODE-3    : OFF                  |
        |               | SW_MODE-4    : ON                   |
        |               | PMOD_PWR_SEL  : Jumper connects 1-3 |
        |               | PMOD_PWR_SEL  : Jumper connects 2-4 |
        +---------------+-------------------------------------+

    (2) Connect the J-Link Base and the connector on the SMARC Module Board with JTAG cable.
        When connecting the conversion adapter "J-Link 9-pin Cortex-M Adapter" made by SEGGER will be required.

    (3) Connect Pin 7 (PMOD0_2A) to  Pin 4 (PMOD1_6A) on Smarc Carrier Board.
        Connect Pin 8 (PMOD0_2A) to  Pin 3 (PMOD1_6A) on Smarc Carrier Board.
    
    (4) Connect Pmod LED to PMOD1_3A (pin 7-12) on Smarc Carrier Board.

NOTE:
1. Segger RTT block address is required to connect J-Link RTTViewer.
   The RTT block address can be confirmed by searching "_SEGGER_RTT" in .map file
   which is located in Debug folder and generated when building.