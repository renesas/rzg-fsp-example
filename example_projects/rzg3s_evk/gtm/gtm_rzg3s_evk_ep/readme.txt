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
    This Example Project demonstrates the functionality of GTM in periodic mode and one-shot mode. On providing any 
    input on the RTTviewer, GTM channel 2 starts in one-shot mode. GTM channel 1 starts in periodic mode when 
    GTM channel 2 expires. Timer in periodic mode expires periodically at a time period specified by user and toggles
    the LD2 on Pmod LED.

2. Hardware and Software Requirements:
    External Hardware : Pmod LED
    Software          : JLink RTT Viewer v7.94

3. Hardware settings:
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
        |               | SW_M2_DIS-4  : ON                  |
        |               | PMOD_PWR_SEL : Jumper connects 2-4 |
        +---------------+------------------------------------+

    (2) Connect the J-Link Base, JTAG cable and the connector on the SMARC Module Board with SMARC JTAG Adapter.
        When connecting the conversion adapter "J-Link 9-pin Cortex-M Adapter" made by SEGGER will be required.

    (3) Connect PMOD1_3A PIN7-12 on SMARC Carrier Board and Pmod LED.

NOTE:
1. User is expected to enter data of size not exceeding above 15 bytes.
   Operation is not guaranteed for any user input value other than integer, char (i.e. float, special char) through RTT.

2. Segger RTT block address is required to connect J-Link RTTViewer.
   The RTT block address can be confirmed by searching "_SEGGER_RTT" in .map file 
   which is located in Debug folder and generated when building.