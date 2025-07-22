/*
 * Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    The example project demonstrates the typical use of the INTC IRQ module APIs.
    The project initializes the IRQ interrupt in Interrupt Controller 
    User is requested to press the USER_SW1 push button on Carrier Board to trigger the external irq and this then will start toggling of user LED.

2. Hardware and Software Requirements:
    External Hardware : Pmod LED
    Software          : JLink RTT Viewer v7.96j

3. Hardware settings:
    Boot Mode:
    Boot mode 3 (SCIF Downloading) with CA55 cold boot

    Board:
    RZ/G3E  Evaluation Kit (SMARC)

    Hardware Connection:

    (1) Set for DIP switches and jumpers as follow.

        +===============+====================================+
        | Board setting | RZ/G3E Evaluation Kit (SMARC)      |
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

    (3) Connect PMOD1_6A PIN9 on SMARC Carrier Board and Pmod LED.

Note:
1. Segger RTT block address is required to connect J-Link RTTViewer. 
   The RTT block address can be confirmed by searching "_SEGGER_RTT" in .map file 
   which is located in Debug folder and generated when building.
