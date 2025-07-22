/*
 * Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    The example project shows the operation of CAN-FD running on Renesas RZ MPUs using channel 0 and channel 1 on board. 
    On pressing any key on the Terminal Emulator, data is transmitted from one channel to other.
    On 1st transmission, Channel 0 transmits data to Channel 1. Channel 1 displays the received data.
    On 2nd transmission, Channel 1 transmits updated data to Channel 0 as ACK. Channel 0 displays the received data.
    then Channel 0 changes CAN frame to CANFD frame and updates data
    On 3rd transmission, Channel 0 transmits updated data to Channel 1. Channel 1 displays the received data.
    then Channel 1 changes CAN frame to CANFD frame and updates data to transmits back to Channel 0 as ACK.
    On 4th transmission, Channel 1 transmits updated data to Channel 0 as ACK. Channel 0 displays the received data

2. Hardware and Software Requirements:
    External Hardware : Pmod LED
    Software          : JLink RTT Viewer v7.96j

3. Hardware settings:
    Boot Mode:
    Boot mode 3 (1.8-V Single, Quad, or Octal serial flash memory)

    Board:
    RZ/G2UL Evaluation Kit (SMARC)
     Board RZ/G Evaluation Board Kit - must have IC15 (to support CAN port) is on the carrier board.

   Hardware Connection:

    (1) Set for DIP switches and jumpers as follow.

        +================+=================================+
        | Board setting  | RZ/G2UL Evaluation Kit (SMARC)  | 
        +================+=================================+
        | Module board   | SW1-1  : OFF                    | 
        |                | SW1-2  : Don't care             | 
        |                | SW1-3  : OFF                    | 
        +----------------+---------------------------------+
        | Carrier board  | SW1    : Don't care             | 
        |                | SW2    : Don't care             | 
        |                | SW3    : Don't care             | 
        |                | SW4    : Don't care             | 
        |                | SW5    : Don't care             | 
        |                | SW6    : Don't care             | 
        |                | SW7    : 1-2                    | 
        |                | SW8    : 1-2                    | 
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
        Connect CN15 to CN16 (CAN_H, CAN_L, GND)

    (4) Connect (CN14) on Smarc Carrier Board with PC through USB Type-microB Connector.

NOTE:
1. Segger RTT block address is required to connect J-Link RTTViewer. 
   The RTT block address can be confirmed by searching "_SEGGER_RTT" in .map file
   which is located in Debug folder and generated when building.