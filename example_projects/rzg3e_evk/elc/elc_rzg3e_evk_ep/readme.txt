/*
 * Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    The example project demonstrates the typical use of the ELC HAL module APIs.
    ELC Software Event, GPT0 and GPT1 events are linked using ELC. The start source for GPT0 and GPT1 is ELC
    Software Event and the stop source for GPT0 is GPT1 counter overflow. GPT0 runs in PWM mode and GPT1 runs
    in one-shot mode. On giving valid RTT input, an ELC Software Event is generated that triggers LED blinking.
    LED stops blinking after 5 sec when GPT0 expires.

2. Hardware and Software Requirement:
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
        +---------------+-------------------------------------+

    (2) Connect the J-Link Base and the connector on the SMARC Module Board with JTAG cable.
        When connecting the conversion adapter "J-Link 9-pin Cortex-M Adapter" made by SEGGER will be required.

    (3) Connect PMOD0_2A (PIN7-12) on Smarc Carrier Board and Pmod LED.

NOTE:
1. Segger RTT block address is required to connect J-Link RTTViewer.
   The RTT block address can be confirmed by searching "_SEGGER_RTT" in .map file
   which is located in Debug folder and generated when building.