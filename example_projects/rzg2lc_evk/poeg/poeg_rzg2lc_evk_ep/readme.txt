/*
 * Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    This project demonstrates the basic functionalities of POEG driver on Renesas RZG MPUs based on Renesas FSP.
    RZG MPU is used to demonstrate the various operating modes of a POEG driver.
    GPT channels are configured to generate output via the GTIOCxA and GTIOCxB pins.
    The Port Output can be disabled using the below two options
    1. Using POEG software API - This mode supports disabling GPT output pins by R_POEG_OutputDisable() software API request
    2. Using POEG trigger GPT output level - This mode supports disabling GPT output pin using POEG trigger GPT output level
    3. Reset the POEG status - This option resets the POEG0 and POEG1 status 
    The Port Output can be enabled using the POEG Reset API.
    The status of each of the mode is displayed on J-Link RTT Viewer.

2. Software Requirement:
    Software           : JLink RTT Viewer v7.96j

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
        | Carrier board  | SW1    : 3-2                    |
        |                | SW2    : 3-2                    |
        |                | SW3    : 3-2                    |
        |                | SW4    : 3-2                    |
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
		
    (3) Connect PMOD0 PIN7-12 on SMARC Carrier Board and PMOD LED.
      
NOTE:
1. Segger RTT block address is required to connect J-Link RTTViewer. 
   The RTT block address can be confirmed by searching "_SEGGER_RTT" in .map file
   which is located in Debug folder and generated when building.
   