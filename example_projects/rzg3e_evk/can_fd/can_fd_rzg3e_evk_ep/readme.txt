/*
 * Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    The example project shows the operation of CAN-FD running on Renesas RZ MPUs using channel 4 and channel 1 on board. 
    On pressing any key on the Terminal Emulator, data is transmitted from one channel to other.
    On 1st transmission, Channel 4 transmits data to Channel 1. Channel 1 displays the received data.
    On 2nd transmission, Channel 1 transmits updated data to Channel 4 as ACK. Channel 4 displays the received data.
    then Channel 4 changes CAN frame to CANFD frame and updates data
    On 3rd transmission, Channel 4 transmits updated data to Channel 1. Channel 1 displays the received data.
    then Channel 1 changes CAN frame to CANFD frame and updates data to transmits back to Channel 4 as ACK.
    On 4th transmission, Channel 1 transmits updated data to Channel 4 as ACK. Channel 4 displays the received data

2. Hardware and Software Requirements:
    External Hardware : Pmod LED
    Software          : JLink RTT Viewer v7.96j

3. Hardware settings:
    Boot Mode:
    Boot mode 3 (SCIF Downloading) with CA55 cold boot

    Board:
    RZ/G3E  Evaluation Kit (SMARC)
     Board RZ/G Evaluation Board Kit - must have IC41 (to support CAN port) is on the carrier board.

    Hardware Connection:

    (1) Set for DIP switches and jumpers as follow.

        +===============+========================================+
        | Board setting | RZ/G3E Evaluation Kit (SMARC)          |
        +===============+========================================+
        | Module board  | SW_CONFIG-1      : OFF                 |
        |               | SW_CONFIG-2      : OFF                 |
        |               | SW_CONFIG-3      : OFF                 |
        |               | SW_CONFIG-4      : OFF                 |
        |               | SW_CONFIG-5      : OFF                 |
        |               | SW_CONFIG-6      : OFF                 |
        +---------------+----------------------------------------+
        | Carrier board | SW_MODE-1        : OFF                 |
        |               | SW_MODE-2        : ON                  |
        |               | SW_MODE-3        : OFF                 |
        |               | SW_MODE-4        : ON                  |
        |               | SW_M2_DIS-4      : ON                  |
        |               | SW_GPIO_CAN_PMOD : 2-3                 |
        |               |                  : 5-6                 |
        |               | PMOD_PWR_SEL     : Jumper connects 1-3 |
        |               |                  : Jumper connects 2-4 |
        +---------------+----------------------------------------+

    (2) Connect the J-Link Base and the connector on the SMARC Module Board with JTAG cable.
        When connecting the conversion adapter "J-Link 9-pin Cortex-M Adapter" made by SEGGER will be required.

    (3) Connect Pmod LED to PMOD1-3A PIN7-12 on SMARC Carrier Board.
        Connect CAN0 to CAN1(CAN_H, CAN_L, GND)SMARC Carrier Board.

NOTE:
1. Segger RTT block address is required to connect J-Link RTTViewer. 
   The RTT block address can be confirmed by searching "_SEGGER_RTT" in .map file
   which is located in Debug folder and generated when building.