/*
 * Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    This Example Project demonstrates the functionality of GTM in periodic mode and one-shot mode. On providing any 
    input on the RTTviewer, GTM channel 2 starts in one-shot mode. GTM channel 1 starts in periodic mode when 
    GTM channel 2 expires. Timer in periodic mode expires periodically at a time period specified by user and toggles
    the LED on Pmod LED.

2. Hardware and Software Requirements:
    External Hardware : Pmod LED
    Software          : JLink RTT Viewer v7.96j

3. Hardware settings:
    Boot Mode:
    Boot mode 3 (1.8-V Single, Quad, or Octal serial flash memory)

    Board:
    RZ/G2UL Evaluation Kit (SMARC)

    Hardware Connection:

    (1) Set for DIP switches and jumpers as follow.

     +===============+================================+
     | Board setting | RZ/G2UL Evaluation Kit (SMARC) |
     +===============+================================+
     | Module board  | SW1-1  : OFF                   |
     |               | SW1-2  : Don't care            |
     |               | SW1-3  : Don't care            |
     |               |                                |
     |               |                                |
     |               |                                |
     +---------------+--------------------------------+
     | Carrier board | SW1    : Don't care            |
     |               | SW2    : Don't care            |
     |               | SW3    : Don't care            |
     |               | SW4    : Don't care            |
     |               | SW5    : Don't care            |
     |               | SW6    : Don't care            |
     |               | SW7    : Don't care            |
     |               | SW8    : Don't care            |
     |               | SW11-1 : OFF                   |
     |               | SW11-2 : OFF                   |
     |               | SW11-3 : OFF                   |
     |               | SW11-4 : ON                    |
     |               | CN4    : Jumper connects 1-3   |
     |               |          Jumper connects 2-4   |
     +---------------+--------------------------------+

    (2) Connect the J-Link Base and the connector on the SMARC Module Board with JTAG cable.
        When connecting the conversion adapter "J-Link 9-pin Cortex-M Adapter" made by SEGGER will be required.
    (3) Connect PMOD0 PIN7-12 on SMARC Carrier Board and Pmod LED.

NOTE:
1. User is expected to enter data of size not exceeding above 15 bytes.
   Operation is not guaranteed for any user input value other than integer, char (i.e. float, special char) through RTT.

2. Segger RTT block address is required to connect J-Link RTTViewer.
   The RTT block address can be confirmed by searching "_SEGGER_RTT" in .map file 
   which is located in Debug folder and generated when building.