/*
 * Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    The example project demonstrates typical use of GPT HAL module APIs.
    User has the provision to input value as per displayed menu through JLinkRTTViewer to select different GPT 
    supported modes (Periodic, PWM, One-Shot).
    In periodic mode, user can enter the time period within the permitted ranges to change the frequency of
    the user Pmod LED.
    In PWM mode, user can enter the duty cycle within the specified range to adjust the intensity of the user Pmod LED.
    In One-Shot mode, output will be displayed on JlinkRTTViewer.
    Any failure will also be displayed on JlinkRTTViewer.

2. Hardware and Software Requirements:
    External Hardware : Pmod LED
    Software          : JLink RTT Viewer v7.96j

3. Hardware Settings:
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
        |                | SW1-4  : ON                     |
        |                | SW1-5  : Don't care             |
        |                | SW1-6  : Don't care             |
        +----------------+---------------------------------+
        | Carrier board  | SW1    : Don't care             |
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
    (3) Connect PMOD0 PIN1-6 on SMARC Carrier Board and Pmod LED.

NOTE:
1. Timer period range in millisecond as per Example Project configuration:
    (1) RZ/G2LC  --      (0 to 42949) ms

2. User is expected to enter data of size not exceeding above 15 bytes.
   Operation is not guaranteed for any user input value other than integer (i.e. float, char, special char) through RTT.

3. Segger RTT block address is required to connect J-Link RTTViewer.
   The RTT block address can be confirmed by searching "_SEGGER_RTT" in .map file 
   which is located in Debug folder and generated when building.
