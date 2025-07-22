/*
 * Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
     The example project demonstrates the typical use of the RSPI HAL module APIs. The project configures 
     RSPI channels (Channel 0 and Channel 1) in Master and Slave mode. Once the module is initialised and the 
     channels are configured, Master and Slave can transmit and receive data based on commands from user sent through 
     JLinkRTTViewer.

     This project supports the DMAC feature. In cases where this feature is not used in the application,
     please invalid the DMAC feature by the following steps.
     - Set DMAC Support to Disabled on the main stack of the driver in FSP Configuration. 
     - Remove the DMAC sub stacks that linked to the main stack.

2. Software Requirement:
    Software          : JLink RTT Viewer v7.96j

3. Hardware settings:
    Boot Mode:
    Boot mode 3 (1.8-V Single, Quad, or Octal serial flash memory)

    Board:
    RZ/G2UL Evaluation Kit (SMARC)

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
        |                | SW5    : 1-2                    |
        |                | SW6    : 1-2                    |
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
    (3) Connect pins with jumper as follows.

        PMOD1 (SMARC Carrier Board)     PMOD0 (SMARC Carrier Board)
        ------------------              ------------------
        |6  5  4  3  2  1|              |6  5  4  3  2  1|
        |12 11 10 9  8  7|              |12 11 10 9  8  7|
        ------------------              ------------------

        RZ/G2UL Evaluation Kit (SMARC):
                    Master (RSPI1)     Slave (RSPI0)
        MISO  ----> P4_2(PMOD0 PIN3) - P2_3(PMOD1 PIN8)
        MOSI  ----> P4_1(PMOD0 PIN2) - P2_2(PMOD1 PIN7)
        CK    ----> P4_0(PMOD0 PIN4) - P1_0(PMOD0 PIN8)
        SSL   ----> P4_3(PMOD0 PIN1) - P1_3(PMOD0 PIN9)

NOTE:
1. User is expected to enter data of size not exceeding 64 bytes.
   As RSPI bit width is set to 32 bits, each 4 bytes of user data input will be transferred in single RSPI transmission.
   The bytes sent for master should be bigger than the bytes sent for slave when using WriteRead operation.
   Operation is not guaranteed for any user input value other than integer, char (i.e. float, special char) through RTT.

2. Segger RTT block address is required to connect J-Link RTTViewer. 
   The RTT block address can be confirmed by searching "_SEGGER_RTT" in .map file 
   which is located in Debug folder and generated when building.