/***********************************************************************************************************************
 * Copyright 2023 Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics Corporation and/or its affiliates and may only
 * be used with products of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.
 * Renesas products are sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for
 * the selection and use of Renesas products and Renesas assumes no liability.  No license, express or implied, to any
 * intellectual property right is granted by Renesas.  This software is protected under all applicable laws, including
 * copyright laws. Renesas reserves the right to change or discontinue this software and/or this documentation.
 * THE SOFTWARE AND DOCUMENTATION IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND
 * TO THE FULLEST EXTENT PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY,
 * INCLUDING WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE
 * SOFTWARE OR DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR
 * DOCUMENTATION (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER,
 * INCLUDING, WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY
 * LOST PROFITS, OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

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
    Software          : Serial Terminal/TeraTerm, JLink RTT Viewer v7.94

3. Hardware settings:
    Boot Mode:
    Boot mode 3 (1.8-V Single, Quad, or Octal serial flash memory)

    Board:
    RZ/G2L  Evaluation Kit (SMARC)
    RZ/G2LC Evaluation Kit (SMARC)

    Hardware Connection:

    (1) Set for DIP switches and jumpers as follow.

        +================+================================+=================================+
        | Board setting  | RZ/G2L Evaluation Kit (SMARC)  | RZ/G2LC Evaluation Kit (SMARC)  |
        +================+================================+=================================+
        | Module board   | SW1-1  : OFF                   | SW1-1  : OFF                    |
        |                | SW1-2  : Don't care            | SW1-2  : Don't care             |
        |                |                                | SW1-3  : ON                     |
        |                |                                | SW1-4  : Don't care             |
        |                |                                | SW1-5  : Don't care             |
        |                |                                | SW1-6  : Don't care             |
        +----------------+--------------------------------+---------------------------------+
        | Carrier board  | SW1    : Don't care            | SW1    : Don't care             |
        |                | SW2    : 2-3                   | SW2    : 2-3                    |
        |                | SW3    : 2-3                   | SW3    : 2-3                    |
        |                | SW4    : Don't care            | SW4    : Don't care             |
        |                | SW5    : Don't care            | SW5    : Don't care             |
        |                | SW6    : Don't care            | SW6    : Don't care             |
        |                | SW7    : Don't care            | SW7    : Don't care             |
        |                | SW8    : Don't care            | SW8    : Don't care             |
        |                | SW11-1 : OFF                   | SW11-1 : OFF                    |
        |                | SW11-2 : OFF                   | SW11-2 : OFF                    |
        |                | SW11-3 : OFF                   | SW11-3 : OFF                    |
        |                | SW11-4 : ON                    | SW11-4 : ON                     |
        |                | CN4    : Jumper connects 1-3   | CN4    : Jumper connects 1-3    |
        |                |          Jumper connects 2-4   |          Jumper connects 2-4    |
        +----------------+--------------------------------+---------------------------------+

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
        ( RZ/G2L  Evaluation Kit (SMARC) uses SCIF2
          RZ/G2LC Evaluation Kit (SMARC) uses SCIF1 )

        Connect J1 on Pmod USBUART with PC.

NOTE:
1. Segger RTT block address is required to connect J-Link RTTViewer. 
   The RTT block address can be confirmed by searching "_SEGGER_RTT" in .map file
   which is located in Debug folder and generated when building.