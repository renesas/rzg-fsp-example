/*
 * Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
     The example project demonstrates the typical use of the RSPI HAL module APIs. The project configures 
     RSPI channels (Channel 0 and Channel 1) in Master and Slave mode. Once the module is initialized and the 
     channels are configured, Master and Slave can transmit and receive data based on commands from the user sent through 
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
    RZ/G2L Evaluation Kit (SMARC)

    Hardware Connection:

    (1) Set for DIP switches and jumpers as follows.

        +================+================================+
        | Board setting  | RZ/G2L Evaluation Kit (SMARC)  |
        +================+================================+
        | Module board   | SW1-1  : OFF                   |
        |                | SW1-2  : Don't care            |
        +----------------+--------------------------------+
        | Carrier board  | SW1    : Don't care            |
        |                | SW2    : Don't care            |
        |                | SW3    : Don't care            |
        |                | SW4    : Don't care            |
        |                | SW5    : Don't care            |
        |                | SW6    : Don't care            |
        |                | SW7    : Don't care            |
        |                | SW8    : Don't care            |
        |                | SW11-1 : OFF                   |
        |                | SW11-2 : OFF                   |
        |                | SW11-3 : OFF                   |
        |                | SW11-4 : ON                    |
        |                | CN4    : Jumper connects 1-3   |
        |                |          Jumper connects 2-4   |
        +----------------+--------------------------------+

    (2) Connect the J-Link Base and the connector on the SMARC Module Board with a JTAG cable.
        When connecting, the conversion adapter "J-Link 9-pin Cortex-M Adapter" made by SEGGER will be required.
    (3) Connect pins with jumper as follows.

        PMOD1 (SMARC Carrier Board)     PMOD0 (SMARC Carrier Board)
        ------------------              ------------------
        |6  5  4  3  2  1|              |6  5  4  3  2  1|
        |12 11 10 9  8  7|              |12 11 10 9  8  7|
        ------------------              ------------------

        RZ/G2L Evaluation Kit (SMARC):
                    Slave (RSPI1)       Master (RSPI0)
        MISO  ----> P44_2(PMOD0 PIN3) - P43_2(PMOD0 PIN8)
        MOSI  ----> P44_1(PMOD0 PIN2) - P43_1(PMOD0 PIN10)
        CK    ----> P44_0(PMOD0 PIN4) - P43_0(PMOD0 PIN7)
        SSL   ----> P44_3(PMOD0 PIN1) - GND  (PMOD0 PIN11)

NOTE:
1. User is expected to enter data of size not exceeding 64 bytes.
   As RSPI bit width is set to 32 bits, each 4 bytes of user data input will be transferred in a single RSPI transmission.
   The bytes sent for master should be bigger than the bytes sent for slave when using WriteRead operation.
   Operation is not guaranteed for any user input value other than integer, char (i.e., float, special char) through RTT.

2. Segger RTT block address is required to connect J-Link RTTViewer. 
   The RTT block address can be confirmed by searching "_SEGGER_RTT" in the .map file 
   which is located in the Debug folder and generated when building.