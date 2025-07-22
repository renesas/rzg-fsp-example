/*
 * Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    The example project demonstrates the use of WDT module with the collaboration of module IRQ, GTM, WDT
    and button/led.
    The operation of this example is as below:
      - Start GTM timer having a callback every 1 second, to refresh WDT and blink the led (LD1 on Pmod LED).
      - The WDT timeout is configured to 2 seconds.
      - If the button BTN0 (on Pmod BUTTON) is pressed, the WDT reset will issued.

2. Hardware and Software Requirements:
    External Hardware : Pmod LED
                      : Pmod BUTTON
    Software          : J-Link RTT Viewer V7.96j

3. Hardware settings:
    Boot Mode:
    Boot mode 3 (1.8-V Single, Quad, or Octal serial flash memory)

    Board:
    RZ/G2LC  Evaluation Kit (SMARC)

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
        | Carrier board  | SW1    : Don't care             |
        |                | SW2    : Don't care             |
        |                | SW3    : Don't care             |
        |                | SW4    : Don't care             |
        |                | SW5    : 3-2                    |
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

    (3) Connect PMOD0 PIN7-12 on SMARC Carrier Board and Pmod LED.
        Connect PMOD1 PIN7-12 on SMARC Carrier Board and Pmod BUTTON.

NOTE:
1. Segger RTT block address is required to connect J-Link RTTViewer. 
   The RTT block address can be confirmed by searching "_SEGGER_RTT" in .map file
   which is located in Debug folder and generated when building.