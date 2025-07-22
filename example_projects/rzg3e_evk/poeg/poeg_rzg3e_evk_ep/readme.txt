/*
 * Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    This project demonstrates the basic functionalities of POEG driver on Renesas RZG MPUs based on Renesas FSP.
    RZG MPUs is used to demonstrate the various operating modes of a POEG driver.
    GPT channels are configured to generate output via the GTIOCxA and GTIOCxB pins.
    The Port Output can be disabled using the below three options
    1. Using POEG trigger pin - This mode supports disabling GPT output pins based on GTETRG input pin level
    2. Using POEG software API - This mode supports disabling GPT output pins by R_POEG_OutputDisable() software API request
    3. Using POEG trigger GPT output level - This mode supports disabling GPT output pin using POEG trigger GPT output level
    4. Reset the POEG status - This option resets the POEG0 and POEG6 status 
    The Port Output can be enabled using the POEG Reset API.
    The status of each of the mode is displayed on J-Link RTT Viewer.

2. Software Requirement:
    Software           : JLink RTT Viewer v7.96j

3. Hardware Settings:
    Boot Mode:
    Boot mode 3 (SCIF Downloading) with CA55 cold boot
    External Hardware : Pmod LED

    Board:
    RZ/G3E  Evaluation Kit (SMARC)

    Hardware Connection:
    (1) Set for DIP switches and jumpers as follow.
        +===============+====================================+
        | Board setting | RZ/G3E Evaluation Board Kit        |
        +===============+====================================+
        | Module board  | SW5-1  : OFF                       |
        |               | SW5-2  : OFF                       |
        |               | SW5-3  : OFF                       |
        |               | SW5-4  : OFF                       |
        |               | SW5-5  : OFF                       |
        |               | SW5-6  : OFF                       |
        +---------------+------------------------------------+
        | Carrier board | SW_MODE-1    : OFF                 |
        |               | SW_MODE-2    : ON                  |
        |               | SW_MODE-3    : OFF                 |
        |               | SW_MODE-4    : ON                  |
        |               | PMOD_PWR_SEL  : Jumper connects 1-3|
        |               | PMOD_PWR_SEL  : Jumper connects 2-4|
        +---------------+------------------------------------+

    (2) Connect the J-Link Base and the connector on the SMARC Module Board with JTAG cable.
        When connecting the conversion adapter "J-Link 9-pin Cortex-M Adapter" made by SEGGER will be required.    

    (3) Connect PMOD LED to bottom row of PMOD1_3a
	
    (4) Connect PMOD0_2a PIN9 to PMOD0_2a PIN7 on SMARC Carrier Board

NOTE:
1. Segger RTT block address is required to connect J-Link RTTViewer.
   The RTT block address can be confirmed by searching "_SEGGER_RTT" in .map file
   which is located in Debug folder and generated when building.
