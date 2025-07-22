/*
 * Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    The Example Project demonstrates the functionality of GPT Input capture module. GPT4 is used to 
    generate periodic pulses of 500msec duration and provided as input to GPT Input capture (GPT3).
    GPT3 counts the event pulse received at its input.
    Based on the period and capture event, the time period of pulse is calculated and displayed on RTTViewer.

2. Software Requirement:
    Software : JLink RTT Viewer v7.96j

3. Hardware settings:
    Boot Mode:
    Boot mode 3 (SCIF Downloading) with CA55 cold boot

    Board:
    RZ/G3E  Evaluation Kit (SMARC)

    Hardware Connection:

    (1) Set for DIP switches and jumpers as follow.

        +===============+============================================+
        | Board setting | RZ/G3E Evaluation Kit (SMARC)              |
        +===============+============================================+
        | Module board  | SW5-1  : OFF                               |
        |               | SW5-2  : OFF                               |
        |               | SW5-3  : OFF                               |
        |               | SW5-4  : OFF                               |
        |               | SW5-5  : OFF                               |
        |               | SW5-6  : OFF                               |
        +---------------+--------------------------------------------+
        | Carrier board | SW_MODE-1        : OFF                     |
        |               | SW_MODE-2        : ON                      |
        |               | SW_MODE-3        : OFF                     |
        |               | SW_MODE-4        : ON                      |
        |               | SW_GPIO_CAN_PMOD : 3-2                     |
        |               | PMOD_PWR_SEL     : Jumper connects 1-3     |
        |               |                  : Jumper connects 2-4     |
        +---------------+--------------------------------------------+

    (2) Connect the J-Link Base and the connector on the SMARC Module Board with JTAG cable.
        When connecting the conversion adapter "J-Link 9-pin Cortex-M Adapter" made by SEGGER will be required.

    (3) RZ/G3E  Evaluation Kit (SMARC): connect PMOD1_6A PIN7 and PMOD0_2A PIN8 on SMARC Carrier Board.

NOTE:
1. User is expected to enter data of size not exceeding above 15 bytes.
   Operation is not guaranteed for any user input value other than integer (i.e. float, char, special char) through RTT.

2. Segger RTT block address is required to connect J-Link RTTViewer.
   The RTT block address can be confirmed by searching "_SEGGER_RTT" in .map file 
   which is located in Debug folder and generated when building.