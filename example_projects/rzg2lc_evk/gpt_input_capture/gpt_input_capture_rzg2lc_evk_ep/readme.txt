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
    Software          : JLink RTT Viewer v7.96j

3. Hardware settings:
    Boot Mode:
    Boot mode 3 (1.8-V Single, Quad, or Octal serial flash memory)

    Board:
    RZ/G2LC Evaluation Kit (SMARC)

    Hardware Connection:

    (1) Set for DIP switches and jumpers as follow.

        +================+=================================+
        | Board setting  | RZ/G2LC Evaluation Kit (SMARC)  |
        +================+=================================+
        | Module board   | SW1-1  : OFF                    |
        |                | SW1-2  : Don't care             |
        |                | SW1-3  : Don't care             |
        |                | SW1-4  : Don't care             |
        |                | SW1-5  : Don't care             |
        |                | SW1-6  : Don't care             |
        +----------------+---------------------------------+
        | Carrier board  | SW1    : 2-3                    |
        |                | SW2    : Don't care             |
        |                | SW3    : Don't care             |
        |                | SW4    : Don't care             |
        |                | SW5    : Don't care             |
        |                | SW6    : Don't care             |
        |                | SW7    : Don't care             |
        |                | SW8    : Don't care             |
        |                | SW11-1 : OFF                    |
        |                | SW11-2 : OFF                    |
        |                | SW11-3 : OFF                    |
        |                | SW11-4 : ON                     |
        |                | CN4    : Jumper connects 1-3    |
        |                |          Jumper connects 2-4    |
        +----------------+---------------------------------+

    (2) Connect the J-Link Base and the connector on the SMARC Module Board with JTAG cable.
        When connecting the conversion adapter "J-Link 9-pin Cortex-M Adapter" made by SEGGER will be required.
    (3) RZ/G2LC Evaluation Kit (SMARC): connect PMOD0 PIN7 and PMOD1 PIN1 on SMARC Carrier Board.

NOTE:
1. Segger RTT block address is required to connect J-Link RTTViewer. 
   The RTT block address can be confirmed by searching "_SEGGER_RTT" in .map file 
   which is located in Debug folder and generated when building.