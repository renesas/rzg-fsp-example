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
    The Example Project demonstrates the functionality of GPT Input capture module. GPT4 is used to 
    generate periodic pulses of 500msec duration and provided as input to GPT Input capture (GPT3).
    GPT3 counts the event pulse received at its input.
    Based on the period and capture event, the time period of pulse is calculated and displayed on RTTViewer.

2. Software Requirement:
    Software          : JLink RTT Viewer v7.94

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
        |                |                                | SW1-3  : Don't care             |
        |                |                                | SW1-4  : Don't care             |
        |                |                                | SW1-5  : Don't care             |
        |                |                                | SW1-6  : Don't care             |
        +----------------+--------------------------------+---------------------------------+
        | Carrier board  | SW1    : Don't care            | SW1    : 2-3                    |
        |                | SW2    : Don't care            | SW2    : Don't care             |
        |                | SW3    : Don't care            | SW3    : Don't care             |
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
    (3) RZ/G2L  Evaluation Kit (SMARC): connect PMOD0 PIN7 and PMOD0 PIN9 on SMARC Carrier Board.
        RZ/G2LC Evaluation Kit (SMARC): connect PMOD0 PIN7 and PMOD1 PIN1 on SMARC Carrier Board.

NOTE:
1. Segger RTT block address is required to connect J-Link RTTViewer. 
   The RTT block address can be confirmed by searching "_SEGGER_RTT" in .map file 
   which is located in Debug folder and generated when building.