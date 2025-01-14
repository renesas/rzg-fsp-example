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
    Software          : JLink RTT Viewer v7.94

3. Hardware Settings:
    Boot Mode:
    Boot mode 3 (SCIF Downloading) with CA55 cold boot

    Board:
    RZ/G3S  Evaluation Kit (SMARC)

    Hardware Connection:

    (1) Set for DIP switches and jumpers as follow.

        +===============+====================================+
        | Board setting | RZ/G3S Evaluation Kit (SMARC)      |
        +===============+====================================+
        | Module board  | SW_CONFIG-1  : OFF                 |
        |               | SW_CONFIG-2  : OFF                 |
        |               | SW_CONFIG-3  : ON                  |
        |               | SW_CONFIG-4  : OFF                 |
        |               | SW_CONFIG-5  : OFF                 |
        |               | SW_CONFIG-6  : OFF                 |
        +---------------+------------------------------------+
        | Carrier board | SW_MODE-1    : OFF                 |
        |               | SW_MODE-2    : ON                  |
        |               | SW_MODE-3    : OFF                 |
        |               | SW_MODE-4    : ON                  |
        |               | PMOD_PWR_SEL : Jumper connects 1-3 |
        +---------------+------------------------------------+

    (2) Connect the J-Link Base, JTAG cable and the connector on the SMARC Module Board with SMARC JTAG Adapter.
        When connecting the conversion adapter "J-Link 9-pin Cortex-M Adapter" made by SEGGER will be required.

    (3) Connect PMOD0_2A PIN1-6 on SMARC Carrier Board and Pmod LED.

NOTE:
1. Timer period range in millisecond as per Example Project configuration:
    (1) RZ/G3S   --      (0 to 42949) ms

2. User is expected to enter data of size not exceeding above 15 bytes.
   Operation is not guaranteed for any user input value other than integer (i.e. float, char, special char) through RTT.

3. Segger RTT block address is required to connect J-Link RTTViewer.
   The RTT block address can be confirmed by searching "_SEGGER_RTT" in .map file 
   which is located in Debug folder and generated when building.