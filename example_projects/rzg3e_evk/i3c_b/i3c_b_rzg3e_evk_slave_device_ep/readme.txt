/*
 * Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    This example project demonstrates the typical use of the I3C Driver on Renesas RZ MPUs based on Renesas FSP.
    The I3C master on RZ/G3E demonstrates operations associated with an I3C slave running on another RZ/G3E board.
    Once initialization is successful, I3C Master device assigns slave address to I3C slave device through 
    DAA (dynamic address assignment) using I3C common command code (CCC). Once Dynamic Address Assignment is completed,
    the Master EP performs write/read operations, and displays slave device information based on user input.
    If the on-board switch is pressed on the slave side, it will initiate an IBI transfer request.
    Error and info messages will be printed on Jlink RTTViewer.

2. Software Requirement:
    Software : JLink RTT Viewer v7.96j

3. Hardware settings:
    Boot Mode:
    Boot mode 3 (SCIF Downloading) with CA55 cold boot

    Board:
    RZ/G3E  Evaluation Kit (SMARC)

    Hardware Connection:
    (1) Set for DIP switches and jumpers as follow.
        +===============+=====================================+
        | Board setting | RZ/G3E Evaluation Board Kit         |
        +===============+=====================================+
        | Module board  | SW5-1  : OFF                        |
        |               | SW5-2  : OFF                        |
        |               | SW5-3  : OFF                        |
        |               | SW5-4  : OFF                        |
        |               | SW5-5  : OFF                        |
        |               | SW5-6  : OFF                        |
        +---------------+-------------------------------------+
        | Carrier board | SW_MODE-1     : OFF                 |
        |               | SW_MODE-2     : ON                  |
        |               | SW_MODE-3     : OFF                 |
        |               | SW_MODE-4     : ON                  |
        |               | PMOD_PWR_SEL  : Jumper connects 2-4 |
        +---------------+-------------------------------------+
		
    (2) Connect the J-Link Base and the connector on the SMARC Module Board with JTAG cable.
        When connecting the conversion adapter "J-Link 9-pin Cortex-M Adapter" made by SEGGER will be required.

    (3) Connect the PMOD LED to bottom row of PMOD1_3A.
	
    (4) Connect Pins on CN1 on RZ Smarc Breakout between Master board and Slave board as follows:
                CN1 (Master board)      |       CN1 (Slave board)
        ----------------------------    |    ---------------------------
                    |2|<---------------GND------------->|2|
                    |3|<---------------SCL------------->|3|
                    |4|<---------------SDA------------->|4|

        ----------------------------         ---------------------------

NOTE:
1. Segger RTT block address is required to connect J-Link RTTViewer.
   The RTT block address can be confirmed by searching "_SEGGER_RTT" in .map file
   which is located in Debug folder and generated when building.