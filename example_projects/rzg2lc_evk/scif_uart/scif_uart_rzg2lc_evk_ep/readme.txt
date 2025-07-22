/*
 * Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    The example project demonstrates the typical use of the UART HAL module APIs.
    The project initializes the UART with Baud rate of 115200 bps and GTM module.
    Using a Terminal Program (like Tera Term) user can provide a value & press enter key to set the period 
    of the Pmod LED signal.
    The range of input values are displayed on the JLinkRTTViewer.
    Any failure will also be displayed using JLinkRTTViewer.
    To see user input values on Serial terminal, enable local echo option.

2. Hardware and Software Requirements:
    External Hardware : Pmod USBUART
                      : Pmod LED
    Software          : Serial Terminal/TeraTerm, JLink RTT Viewer v7.96j

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
        |                | SW1-3  : ON                     |
        |                | SW1-4  : Don't care             |
        |                | SW1-5  : Don't care             |
        |                | SW1-6  : Don't care             |
        +----------------+---------------------------------+
        | Carrier board  | SW1    : Don't care             |
        |                | SW2    : 2-3                    |
        |                | SW3    : 2-3                    |
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
    (3) Connect PMOD0 PIN7-12 on SMARC Carrier Board and Pmod LED.
        Connect Pmod USBUART and SMARC Carrier Board as follows.

        J2 (Pmod USBUART)            PMOD1 (SMARC Carrier Board)
        ---                          -------
        |1|---RTS                    |1   7|
        |2|---RXD  --->  SCIFx_TXD---|2   8|
        |3|---TXD  --->  SCIFx_RXD---|3   9|
        |4|---CTS                    |4  10|
        |5|---GND  --->  GND pin  ---|5  11|
        |6|---VCC  --->  VCC pin  ---|6  12|
        ---                          -------
        ( RZ/G2LC Evaluation Kit (SMARC) uses SCIF1 )

        Connect J1 on Pmod USBUART with PC.

NOTE:
1. Segger RTT block address is required to connect J-Link RTTViewer. 
   The RTT block address can be confirmed by searching "_SEGGER_RTT" in .map file
   which is located in Debug folder and generated when building.