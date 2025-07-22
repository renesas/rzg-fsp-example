/*
 * Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    The example project demonstrates the typical use of the RSPI HAL module APIs. The project configure 
    RSPI channel 0 in Master and Pmod SF3 in Slave. Once the module is initialised and the channels are 
    configured, Master can write data to Slave and read it back based on commands from user sent through 
    JLink RTT Viewer.

    This project supports the DMAC feature. In cases where this feature is not used in the application,
    please invalid the DMAC feature by the following steps.
    - Set DMAC Support to Disabled on the main stack of the driver in FSP Configuration. 
    - Remove the DMAC sub stacks that linked to the main stack.

2. Hardware and Software Requirements:
    External Hardware : Pmod SF3
    Software          : JLink RTT Viewer v7.96j

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
        |               | PMOD_PWR_SEL : Jumper connects 1-3 |
        +---------------+------------------------------------+

    (2) Connect the J-Link Base and the connector on the SMARC Module Board with JTAG cable.
        When connecting the conversion adapter "J-Link 9-pin Cortex-M Adapter" made by SEGGER will be required.

    (3) Connect Pmod SF3 to PMOD0_2A on the carrier board.

        RZ/G3S  Evaluation Kit (SMARC):
                    Master (RSPI0)      Slave (Pmod SF3)
        MISO  ----> P15_2(PMOD0 PIN3) - Pin 3(PMOD0_2A PIN3)
        MOSI  ----> P15_1(PMOD0 PIN2) - Pin 2(PMOD0_2A PIN2)
        CK    ----> P15_0(PMOD0 PIN4) - Pin 4(PMOD0_2A PIN4)
        SSL   ----> P15_3(PMOD0 PIN1) - Pin 1(PMOD0_2A PIN1)

NOTE:
1. User is expected to enter data of size not exceeding 254 bytes.
   Operation is not guaranteed for any user input value other than integer, char (i.e. float, special char) through RTT.

2. Segger RTT block address is required to connect J-Link RTTViewer. 
   The RTT block address can be confirmed by searching "_SEGGER_RTT" in .map file 
   which is located in Debug folder and generated when building.