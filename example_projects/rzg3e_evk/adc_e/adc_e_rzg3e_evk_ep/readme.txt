/*
 * Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    The example project demonstrates the function of r_adc_e driver.
    The example project demonstrates the typical use of the ADC HAL module APIs.
    The project initializes the ADC in single scan mode in accordance with FSP configuration.
    Result and ADC status is displayed on the JLink RTT Viewer.
	
2. Hardware/Software Requirement:
    Software          : JLink RTT Viewer v7.96j
    External Hardware : External Variable Power Supply Unit (Rheostats 10K).

3. Hardware Settings:
    Boot Mode:
    Boot mode 3 (SCIF Downloading) with CA55 cold boot

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
        +---------------+------------------------------------+

    (2) Connect the J-Link Base and the connector on the SMARC Module Board with JTAG cable.
        When connecting the conversion adapter "J-Link 9-pin Cortex-M Adapter" made by SEGGER will be required.

    (3) Connect ADC00, VDD_ADC and GND on RZ SMARC Series Breakout Adapter Board with External Variable Power Supply Unit (Rheostats 10K).

NOTE:
1. Segger RTT block address is required to connect J-Link RTTViewer.
   The RTT block address can be confirmed by searching "_SEGGER_RTT" in .map file
   which is located in Debug folder and generated when building.