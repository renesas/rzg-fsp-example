/***********************************************************************************************************************
 * File Name    : hal_entry.c
 * Description  : Contains data structures and functions used in hal_entry.c.
 **********************************************************************************************************************/
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

#include "common_utils.h"
#include "xspi_init.h"
#include "i2c_sensor.h"
#include "stdbool.h"
#include "stdint.h"

/*******************************************************************************************************************//**
 * @addtogroup r_riic_master_ep
 * @{
 **********************************************************************************************************************/

void R_BSP_WarmStart(bsp_warm_start_event_t event);
void SCL_Toggle(void);

void hal_entry(void)
{
    fsp_err_t err = FSP_SUCCESS;
    fsp_pack_version_t version = {RESET_VALUE};
    uint8_t xyz_axis[6]      = {RESET_VALUE};
    char flt_str[64]        = {RESET_VALUE};
    float x_axis            = 0.0f;
    float y_axis            = 0.0f;
    float z_axis            = 0.0f;

    /* version get API for FLEX pack information */
    R_FSP_VersionGet(&version);

    /* Example Project information printed on the Console */
    APP_PRINT(BANNER_1);
    APP_PRINT(BANNER_2);
    APP_PRINT(BANNER_3,EP_VERSION);
    APP_PRINT(BANNER_4,version.major, version.minor, version.patch);
    APP_PRINT(BANNER_5);
    APP_PRINT(BANNER_6);
    APP_PRINT("\nThis project utilizes PMOD ACL sensor as iic slave device\n");
    APP_PRINT("Upon successful initialization, MPU displays sensor axis data\n");
    APP_PRINT("\nIf SDA line is kept in LOW by any error \n");
    APP_PRINT("Please input 1 on J-Link RTT Viewer to Open bus.\n\n\n");

    /* Opening IIC master module and Initializing PMOD ACL sensor */
    err = init_sensor();

    if(FSP_SUCCESS != err)
    {
        /* Sensor init failed, so cleanup the sensor specific initialization */
        APP_ERR_PRINT("** SENSOR INIT FAILED ** \r\n");
        deinit_sensor();
        APP_ERR_TRAP(err);
    }

    /* Stay in forever loop and read the sensor data every 3 Seconds
     * If the Sensor data reading returns error, cleanup and break with TRAP.
     * Note: For Demonstration Purpose the failure ends up with TRAP.
     * Note: This can be handled in many ways as per the Application needs
     */
    while (true)
    {
        /* Read PMOD ACL sensor data */
        err =  read_sensor_data(xyz_axis);
        if(FSP_SUCCESS != err)
        {
            APP_ERR_PRINT("\r\n ** SENSOR READ DATA FAILED ** \r\n");
            deinit_sensor();
            APP_ERR_TRAP(err);
        }
        else
        {
             /*
              * X,Y,Z - axis data has to be evaluated so accessing particular array value,
              * shifting it by 8 bits obtains data value to float variable
              */
            x_axis = (float) (xyz_axis[0] | (xyz_axis[1] << BIT_SHIFT_8));   // X-axis value
            y_axis = (float) (xyz_axis[2] | (xyz_axis[3] << BIT_SHIFT_8));   // Y-axis value
            z_axis = (float) (xyz_axis[4] | (xyz_axis[5] << BIT_SHIFT_8));   // Z-axis value

            snprintf(flt_str,SIZE_64,"X-axis = %.02f, Y-axis = %.02f, Z-axis = %.02f",x_axis,y_axis,z_axis);
            APP_PRINT("%s \r\n",flt_str);

            /*Check SDA level*/
            if (!((g_i2c_master_ctrl.p_reg)->ICCR1 & R_RIIC0_ICCR1_SDAI_Msk))
            {
                APP_PRINT("\nSlave keep the SDA line in low level.\r");
                /*Check whether any user input */
                while(true)
                {
                if (APP_CHECK_DATA)
                {
                    unsigned char buf[16]       = {0x00};
                    APP_READ(buf);

                    /*Check the input */
                    if ((uint32_t) (atoi((char *)buf)) == 1)
                    {
                        SCL_Toggle();
                    }
                    /* Clear the buffer */
                    memset (buf,'\0',16U);
                    break;
                }
                }
            }

            /* 3 seconds wait time between successive readings */
            R_BSP_SoftwareDelay(SENSOR_READ_DELAY, BSP_DELAY_UNITS_SECONDS);
        }
    }
}

/*******************************************************************************************************************//**
 * This function create the extra SCL Clock cycle by controlling SCLO bit
 **********************************************************************************************************************/
void SCL_Toggle(void)
{
        uint32_t temp_iccr1 = 0 ;
        APP_PRINT("\nToggle the SCL bus.\r");

        for(uint8_t i = 24; i  > 0 ; i--)
        {
        /*Change the SDAO bit to 1 and SOWP to 0 */
        temp_iccr1 = (g_i2c_master_ctrl.p_reg)->ICCR1;
        temp_iccr1 &= ~R_RIIC0_ICCR1_SOWP_Msk;
        temp_iccr1 ^= R_RIIC0_ICCR1_SCLO_Msk;
        temp_iccr1 ^= R_RIIC0_ICCR1_SDAO_Msk;
        (g_i2c_master_ctrl.p_reg)->ICCR1 = (uint8_t) temp_iccr1;
        /* 2 microseconds delay*/
        R_BSP_SoftwareDelay(2, BSP_DELAY_UNITS_MICROSECONDS);
        }
}

/*******************************************************************************************************************//**
 * This function is called at various points during the startup process.  This implementation uses the event that is
 * called right before main() to set up the pins.
 *
 * @param[in]  event    Where at in the start up process the code is currently at
 **********************************************************************************************************************/
void R_BSP_WarmStart (bsp_warm_start_event_t event)
{
    if (BSP_WARM_START_RESET == event)
    {
    }

    if (BSP_WARM_START_POST_C == event)
    {
        /* C runtime environment and system clocks are setup. */

        /* Configure pins. */
        R_IOPORT_Open(&g_ioport_ctrl, &g_bsp_pin_cfg);

        if (0 == (R_SYSC_SYS_LSI_MODE_STAT_BOOTCPUSEL_Msk & R_SYSC->SYS_LSI_MODE))
        {
            xspi_open();
        }
    }
}
/*******************************************************************************************************************//**
 * @} (end addtogroup r_riic_master_ep)
 **********************************************************************************************************************/
