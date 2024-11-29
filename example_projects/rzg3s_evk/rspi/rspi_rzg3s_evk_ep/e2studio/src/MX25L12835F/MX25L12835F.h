/*********************************************************************************************************************** // @suppress("6.1a File naming")
 * File Name    : MX25L12835F.h
 * Description  : Driver for controlling the MX25L12835F.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <stdint.h>

#ifndef MX25L12835F_H
 #define MX25L12835F_H

 #ifdef __cplusplus
extern "C"
{
 #endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
 #define MX25L12835F_SECTOR_SIZE    (4096)
 #define MX25L12835F_PAGE_SIZE      (256)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* Error codes for the MX25L12835F. */
typedef enum
{
    MX25L12835F_SUCCESS = 0,
    MX25L12835F_ERROR,
    MX25L12835F_RDID_MISMATCH
} mx25l1235f_status_t;

/* Interface for communicating with the MX25L12835F. */
typedef struct
{
    mx25l1235f_status_t (* transfer)(uint8_t const * tx_data, uint8_t * rx_data, uint32_t length);
    void (* cs_assert)();
    void (* cs_deassert)();
} mx25l1235f_drv_t;

/***********************************************************************************************************************
 * Public APIs
 **********************************************************************************************************************/

mx25l1235f_status_t MX25L12835F_Setup(mx25l1235f_drv_t * const p_drv);

mx25l1235f_status_t MX25L12835F_EraseSector(mx25l1235f_drv_t * const p_drv, uint32_t addr);

mx25l1235f_status_t MX25L12835F_PageProgram(mx25l1235f_drv_t * const p_drv,
                                            uint32_t                 start_addr,
                                            uint8_t const          * data,
                                            uint32_t                 length);

mx25l1235f_status_t MX25L12835F_ReadData(mx25l1235f_drv_t * const p_drv,
                                         uint32_t                 start_addr,
                                         uint8_t                * data,
                                         uint32_t                 length);

mx25l1235f_status_t MX25L12835F_Teardown(mx25l1235f_drv_t * const p_drv);

 #ifdef __cplusplus
}
 #endif

#endif
