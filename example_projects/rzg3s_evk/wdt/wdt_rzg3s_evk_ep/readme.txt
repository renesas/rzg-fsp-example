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
    The example project demonstrates the use of WDT module with the collaboration of module IRQ, GTM, WDT
    and button/led.
    The operation of this example is as below:
      - Start GTM timer having a callback every 1 second, to refresh WDT and blink the led (LD2 on Pmod LED).
      - If the button BTN3 (on Pmod BUTTON) is pressed, IRQ is triggered to stop GTM timer, and after 2 seconds,
        WDT will reset MPU.

2. Hardware and Software Requirements:
    External Hardware : Pmod LED
                      : Pmod BUTTON
    Software          : J-Link RTT Viewer V7.94

3. Hardware settings:
    Boot Mode:
    Boot mode 2 (Serial Flash Memory (Single / Quad / Octal)) with CA55 cold boot
    Boot mode 3 (SCIF Downloading) with CA55 cold boot

    Board:
    RZ/G3S  Evaluation Kit (SMARC)

    Hardware Connection:

    (1) Set for DIP switches and jumpers as follow.

        +===============+========================================+
        | Board setting | RZ/G3S Evaluation Kit (SMARC)          |
        +===============+========================================+
        | Module board  | SW_CONFIG-1      : OFF                 |
        |               | SW_CONFIG-2      : OFF                 |
        |               | SW_CONFIG-3      : ON                  |
        |               | SW_CONFIG-4      : OFF                 |
        |               | SW_CONFIG-5      : OFF                 |
        |               | SW_CONFIG-6      : OFF                 |
        +---------------+----------------------------------------+
        | Carrier board | SW_PMOD0_PWR_SLP : 5-6                 |
        |               | PMOD_PWR_SEL     : Jumper connects 1-3 |
        |               |                  : Jumper connects 2-4 |
        |               |----------------------------------------|
        |               | #Boot mode 2#                          |
        |               |   SW_MODE-1      : OFF                 |
        |               |   SW_MODE-2      : OFF                 |
        |               |   SW_MODE-3      : OFF                 |
        |               |   SW_MODE-4      : ON                  |
        |               |----------------------------------------|
        |               | #Boot mode 3#                          |
        |               |   SW_MODE-1      : OFF                 |
        |               |   SW_MODE-2      : ON                  |
        |               |   SW_MODE-3      : OFF                 |
        |               |   SW_MODE-4      : ON                  |
        +---------------+----------------------------------------+

    (2) Connect the J-Link Base and the connector on the SMARC Module Board with JTAG cable.
        When connecting the conversion adapter "J-Link 9-pin Cortex-M Adapter" made by SEGGER will be required.

    (3) Connect PMOD0_2A PIN7-12 on SMARC Carrier Board and Pmod BUTTON.
        Connect PMOD1_3A PIN7-12 on SMARC Carrier Board and Pmod LED.

NOTE:
1. Segger RTT block address is required to connect J-Link RTTViewer. 
   The RTT block address can be confirmed by searching "_SEGGER_RTT" in .map file
   which is located in Debug folder and generated when building.

2. Please refer to the following steps to run this example:
     - After building, set the board to Boot mode 3,
     - Write the program binary file (.srec) to the flash memory on board by using flash writer.
     - Then change the board to Boot mode 2 and reset the board.
   When J-Link is connected to the board, welcome message will be printed out on J-Link RTT Viewer console.
   Please confirm FSP Example Project Usage Guide to get more detail about the WDT example.