/*********************************************************************************************************************** // @suppress("6.1a File naming")
 * File Name    : MX25L12835F.h
 * Description  : Driver for controlling the MX25L12835F.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <stddef.h>
#include "MX25L12835F.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/** MX25 series command hex code definition. */

/* ID commands */
#define    FLASH_CMD_RDID          (0x9F)     ///< RDID (Read Identification)
#define    FLASH_CMD_RES           (0xAB)     ///< RES (Read Electronic ID)
#define    FLASH_CMD_REMS          (0x90)     ///< REMS (Read Electronic & Device ID)
#define    FLASH_CMD_QPIID         (0xAF)     ///< QPIID (QPI ID Read)

/* Register commands */
#define    FLASH_CMD_WRSR          (0x01)     ///< WRSR (Write Status Register)
#define    FLASH_CMD_RDSR          (0x05)     ///< RDSR (Read Status Register)
#define    FLASH_CMD_WRSCUR        (0x2F)     ///< WRSCUR (Write Security Register)
#define    FLASH_CMD_RDSCUR        (0x2B)     ///< RDSCUR (Read Security Register)
#define    FLASH_CMD_RDCR          (0x15)     ///< RDCR (Read Configuration Register)
#define    FLASH_CMD_RDFBR         (0x16)     ///< RDFBR (read fast boot Register)
#define    FLASH_CMD_WRFBR         (0x17)     ///< WRFBR (write fast boot Register)
#define    FLASH_CMD_ESFBR         (0x18)     ///< ESFBR (erase fast boot Register)
#define    FLASH_CMD_WRLR          (0x2C)     ///< WRLR (write lock Register)
#define    FLASH_CMD_RDLR          (0x2D)     ///< RDLR (read lock Register)
#define    FLASH_CMD_RDSPB         (0xE2)     ///< RDSPB (read SPB status)
#define    FLASH_CMD_WRSPB         (0xE3)     ///< WRSPB (write SPB bit)
#define    FLASH_CMD_EFSPB         (0xE4)     ///< EFSPB (erase all SPB status)
#define    FLASH_CMD_SPBLK         (0xA6)     ///< SPBLK (SPB lock set)
#define    FLASH_CMD_RDSPBLK       (0xA7)     ///< SPBLK (read SPB lock register)
#define    FLASH_CMD_WRPASS        (0x28)     ///< WRPASS (write password Register)
#define    FLASH_CMD_RDPASS        (0x27)     ///< RDPASS (read password Register)
#define    FLASH_CMD_PASSULK       (0x29)     ///< RDPASS (password unlock)
#define    FLASH_CMD_RDDPB         (0xE0)     ///< RDDPB (read DPB register)
#define    FLASH_CMD_WRDPB         (0xE1)     ///< WRDPB (write DPB register)

/* READ commands */
#define    FLASH_CMD_READ          (0x03)     ///< READ (1 x I/O)
#define    FLASH_CMD_2READ         (0xBB)     ///< 2READ (2 x I/O)
#define    FLASH_CMD_4READ         (0xEB)     ///< 4READ (4 x I/O)
#define    FLASH_CMD_FASTREAD      (0x0B)     ///< FAST READ (Fast read data).
#define    FLASH_CMD_DREAD         (0x3B)     ///< DREAD (1In/2 Out fast read)
#define    FLASH_CMD_QREAD         (0x6B)     ///< QREAD (1In/4 Out fast read)
#define    FLASH_CMD_RDSFDP        (0x5A)     ///< RDSFDP (Read SFDP)

/* Program commands */
#define    FLASH_CMD_WREN          (0x06)     ///< WREN (Write Enable)
#define    FLASH_CMD_WRDI          (0x04)     ///< WRDI (Write Disable)
#define    FLASH_CMD_PP            (0x02)     ///< PP (page program)
#define    FLASH_CMD_4PP           (0x38)     ///< 4PP (Quad page program)

/* Erase commands */
#define    FLASH_CMD_SE            (0x20)     ///< SE (Sector Erase)
#define    FLASH_CMD_BE32K         (0x52)     ///< BE32K (Block Erase 32kb)
#define    FLASH_CMD_BE            (0xD8)     ///< BE (Block Erase)
#define    FLASH_CMD_CE            (0x60)     ///< CE (Chip Erase) hex code: 60 or C7

/* Mode setting commands */
#define    FLASH_CMD_DP            (0xB9)     ///< DP (Deep Power Down)
#define    FLASH_CMD_RDP           (0xAB)     ///< RDP (Release form Deep Power Down)
#define    FLASH_CMD_ENSO          (0xB1)     ///< ENSO (Enter Secured OTP)
#define    FLASH_CMD_EXSO          (0xC1)     ///< EXSO  (Exit Secured OTP)
#define    FLASH_CMD_EQIO          (0x35)     ///< EQIO (Enable Quad I/O)
#define    FLASH_CMD_WPSEL         (0x68)     ///< WPSEL (Enable block protect mode)
#ifdef SBL_CMD_0x77
 #define    FLASH_CMD_SBL          (0x77)     ///< SBL (Set Burst Length), new: 0x77
#else
 #define    FLASH_CMD_SBL          (0xC0)     ///< SBL (Set Burst Length), old: 0xC0
#endif

/* Reset commands */
#define    FLASH_CMD_RSTEN         (0x66)     ///< RSTEN (Reset Enable)
#define    FLASH_CMD_RST           (0x99)     ///< RST (Reset Memory)
#define    FLASH_CMD_RSTQIO        (0xF5)     ///< RSTQIO (Reset Quad I/O)

/* Security commands */
#define    FLASH_CMD_GBLK          (0x7E)     ///< GBLK (Gang Block Lock)
#define    FLASH_CMD_GBULK         (0x98)     ///< GBULK (Gang Block Unlock)

/* Suspend/Resume commands */
#ifdef PGM_ERS_0xB0
 #define    FLASH_CMD_PGM_ERS_S    (0xB0)     ///< PGM/ERS Suspend (Suspends Program/Erase) old: 0xB0
 #define    FLASH_CMD_PGM_ERS_R    (0x30)     ///< PGM/ERS Erase (Resumes Program/Erase) old: 0x30
#else
 #define    FLASH_CMD_PGM_ERS_S    (0x75)     ///< PGM/ERS Suspend (Suspends Program/Erase) old: 0xB0
 #define    FLASH_CMD_PGM_ERS_R    (0x7A)     ///< PGM/ERS Erase (Resumes Program/Erase) old: 0x30
#endif

#define    FLASH_CMD_NOP           (0x00)     ///< NOP (No Operation)

#define MX25L12835F_RDID           (0x20BA19) ///< Expected RDID value

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function declarations
 **********************************************************************************************************************/
static mx25l1235f_status_t cmd_rdid(mx25l1235f_drv_t * const p_drv, uint32_t * id);
static mx25l1235f_status_t cmd_wren(mx25l1235f_drv_t * const p_drv);
static mx25l1235f_status_t cmd_rdsr(mx25l1235f_drv_t * const p_drv, uint8_t * status);
static mx25l1235f_status_t cmd_erase(mx25l1235f_drv_t * const p_drv, uint32_t addr);
static mx25l1235f_status_t cmd_read(mx25l1235f_drv_t * const p_drv, uint32_t addr, uint8_t * data, uint32_t length);
static mx25l1235f_status_t cmd_page_program(mx25l1235f_drv_t * const p_drv,
                                            uint32_t                 addr,
                                            uint8_t const          * data,
                                            uint32_t                 length);

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Read the chip id and verify that the flash module is connected properly.
 * @param      p_drv           Driver for communicating with the MX25L12835F.
 **********************************************************************************************************************/
mx25l1235f_status_t MX25L12835F_Setup (mx25l1235f_drv_t * const p_drv)
{
    /* Get the chip id. */
    uint32_t            id  = 0;
    mx25l1235f_status_t err = cmd_rdid(p_drv, &id);

    /* Verify that the id is correct. */
    if (MX25L12835F_RDID != id)
    {
        return MX25L12835F_RDID_MISMATCH;
    }

    return err;
}

/*******************************************************************************************************************//**
 * Erase an entire sector on the device.
 *
 * @param      p_drv           Driver for communicating with the MX25L12835F.
 * @param[in]  addr            The address of the sector to erase.
 *
 * @retval     MX25L12835F_SUCCESS  The sector was erased correctly.
 * @retval     MX25L12835F_ERROR    An error occurred.
 **********************************************************************************************************************/
mx25l1235f_status_t MX25L12835F_EraseSector (mx25l1235f_drv_t * const p_drv, uint32_t addr)
{
    uint8_t status;
    uint8_t WEL = 0;

    do
    {
        /* Send the write enable command. */
        if (MX25L12835F_SUCCESS != cmd_wren(p_drv))
        {
            return MX25L12835F_ERROR;
        }

        /* Send the read status register command. */
        if (MX25L12835F_SUCCESS != cmd_rdsr(p_drv, &status))
        {
            return MX25L12835F_ERROR;
        }

        /* Check if the write enable latch bit is set. */
        WEL = status & 0x02;
    } while (0 == WEL);

    /* Send the erase command. */
    if (MX25L12835F_SUCCESS != cmd_erase(p_drv, addr))
    {
        return MX25L12835F_ERROR;
    }

    uint8_t WIP = 1;
    do
    {
        /* Send the read status command. */
        if (MX25L12835F_SUCCESS != cmd_rdsr(p_drv, &status))
        {
            return MX25L12835F_ERROR;
        }

        /* Check the write in process bit. */
        WIP = status & 0x01;
    } while (0 != WIP);

    return MX25L12835F_SUCCESS;
}

/*******************************************************************************************************************//**
 * Programs a page on the device.
 *
 * @param      p_drv           Driver for communicating with the MX25L12835F.
 * @param[in]  start_addr      The start address
 * @param      data            Pointer to data to be written to the page.
 * @param[in]  length          The number of bytes to write .
 *                             (if length is greater than PAGE_SIZE, the data will wrap to the beginning of the page)
 *
 * @retval     MX25L12835F_SUCCESS  The sector was erased correctly.
 * @retval     MX25L12835F_ERROR    An error occurred.
 **********************************************************************************************************************/
mx25l1235f_status_t MX25L12835F_PageProgram (mx25l1235f_drv_t * const p_drv,
                                             uint32_t                 start_addr,
                                             uint8_t const          * data,
                                             uint32_t                 length)
{
    uint8_t status;
    uint8_t WEL = 0;

    do
    {
        /* Send the write enable command. */
        if (MX25L12835F_SUCCESS != cmd_wren(p_drv))
        {
            return MX25L12835F_ERROR;
        }

        /* Send the read status register command. */
        if (MX25L12835F_SUCCESS != cmd_rdsr(p_drv, &status))
        {
            return MX25L12835F_ERROR;
        }

        /* Check if the write enable latch bit is set. */
        WEL = status & 0x02;
    } while (0 == WEL);

    /* Send the page program command. */
    if (MX25L12835F_SUCCESS != cmd_page_program(p_drv, start_addr, data, length))
    {
        return MX25L12835F_ERROR;
    }

    uint8_t WIP = 1;
    do
    {
        /* Send the read status command. */
        if (MX25L12835F_SUCCESS != cmd_rdsr(p_drv, &status))
        {
            return MX25L12835F_ERROR;
        }

        /* Check the write in process bit. */
        WIP = status & 0x01;
    } while (0 != WIP);

    return MX25L12835F_SUCCESS;
}

/*******************************************************************************************************************//**
 * Read data from the device.
 *
 * @param      p_drv           Driver for communicating with the MX25L12835F.
 * @param[in]  start_addr      The address to start reading data.
 * @param      data            Pointer to store the data in.
 * @param[in]  length          Number of bytes to read.
 *
 * @retval     MX25L12835F_SUCCESS  The sector was erased correctly.
 * @retval     MX25L12835F_ERROR    An error occurred.
 **********************************************************************************************************************/
mx25l1235f_status_t MX25L12835F_ReadData (mx25l1235f_drv_t * const p_drv,
                                          uint32_t                 start_addr,
                                          uint8_t                * data,
                                          uint32_t                 length)
{

    /* Send the read data command. */
    return cmd_read(p_drv, start_addr, data, length);
}

/*******************************************************************************************************************//**
 * Restore the driver to its initial state.
 *
 * @param      p_drv           Driver for communicating with the MX25L12835F.
 *
 * @retval     MX25L12835F_SUCCESS  The sector was erased correctly.
 * @retval     MX25L12835F_ERROR    An error occurred.
 **********************************************************************************************************************/
mx25l1235f_status_t MX25L12835F_Teardown (mx25l1235f_drv_t * const p_drv)
{
    (void) p_drv;

    return MX25L12835F_SUCCESS;
}

/*******************************************************************************************************************//**
 * Send the rdid command in order to retrieve the chip id.
 *
 * @param      p_drv           Driver for communicating with the MX25L12835F.
 * @param      id              Pointer to the id variable to store the chip id.
 *
 * @retval     MX25L12835F_SUCCESS  The sector was erased correctly.
 * @retval     MX25L12835F_ERROR    An error occurred.
 **********************************************************************************************************************/
static mx25l1235f_status_t cmd_rdid (mx25l1235f_drv_t * const p_drv, uint32_t * id)
{
    uint8_t rdid_tx[4] = {0};
    uint8_t rdid_rx[4];

    /* Set the command id. */
    rdid_tx[0] = FLASH_CMD_RDID;

    /* Send the command using the spi interface. */
    p_drv->cs_assert();
    mx25l1235f_status_t err = p_drv->transfer(rdid_tx, rdid_rx, 4);
    p_drv->cs_deassert();

    /* Decode the received data. */
    *id = (uint32_t) ((rdid_rx[1] << 16U) | (rdid_rx[2] << 8U) | (rdid_rx[3] << 0U));

    return err;
}

/*******************************************************************************************************************//**
 * Send the wren command in order to set the write enable latch.
 *
 * @param      p_drv           Driver for communicating with the MX25L12835F.
 *
 * @retval     MX25L12835F_SUCCESS  The sector was erased correctly.
 * @retval     MX25L12835F_ERROR    An error occurred.
 **********************************************************************************************************************/
static mx25l1235f_status_t cmd_wren (mx25l1235f_drv_t * const p_drv)
{
    /* Set the command id. */
    uint8_t wren_tx = FLASH_CMD_WREN;

    /* Send the command using the spi interface. */
    p_drv->cs_assert();
    mx25l1235f_status_t err = p_drv->transfer(&wren_tx, NULL, 1);
    p_drv->cs_deassert();

    return err;
}

/*******************************************************************************************************************//**
 * Send the rdsr command in order to read the status register.
 *
 * @param      p_drv           Driver for communicating with the MX25L12835F.
 * @param      status          Pointer to the variable to store the status register in.
 *
 * @retval     MX25L12835F_SUCCESS  The sector was erased correctly.
 * @retval     MX25L12835F_ERROR    An error occurred.
 **********************************************************************************************************************/
static mx25l1235f_status_t cmd_rdsr (mx25l1235f_drv_t * const p_drv, uint8_t * status)
{
    uint8_t rdsr_tx[2] = {0};
    uint8_t rdsr_rx[2];

    /* Set the command id. */
    rdsr_tx[0] = FLASH_CMD_RDSR;

    /* Send the command using the spi interface. */
    p_drv->cs_assert();
    mx25l1235f_status_t err = p_drv->transfer(rdsr_tx, rdsr_rx, 2);
    p_drv->cs_deassert();

    /* Store the status register value. */
    *status = rdsr_rx[1];

    return err;
}

/*******************************************************************************************************************//**
 * Send the erase command to erase a sector on the module.
 *
 * @param      p_drv           Driver for communicating with the MX25L12835F.
 * @param[in]  addr            Address if the sector to erase.
 *
 * @retval     MX25L12835F_SUCCESS  The sector was erased correctly.
 * @retval     MX25L12835F_ERROR    An error occurred.
 **********************************************************************************************************************/
static mx25l1235f_status_t cmd_erase (mx25l1235f_drv_t * const p_drv, uint32_t addr)
{
    /* Create a erase command packet. */
    uint8_t erase_tx[4] = {FLASH_CMD_SE, (addr >> 16) & 0xFF, (addr >> 8) & 0xFF, (addr >> 0) & 0xFF}; // NOLINT(readability-magic-numbers)

    /* Send the command using the spi interface. */
    p_drv->cs_assert();
    mx25l1235f_status_t err = p_drv->transfer(erase_tx, NULL, 4);
    p_drv->cs_deassert();

    return err;
}

/*******************************************************************************************************************//**
 * Send the read command in order to get data from the flash module.
 *
 * @param      p_drv           Driver for communicating with the MX25L12835F.
 * @param[in]  addr            Start address to get data from the MX25L12835F.
 * @param      data            Pointer to store data in.
 * @param[in]  length          Number of bytes to read.
 *
 * @retval     MX25L12835F_SUCCESS  The sector was erased correctly.
 * @retval     MX25L12835F_ERROR    An error occurred.
 **********************************************************************************************************************/
static mx25l1235f_status_t cmd_read (mx25l1235f_drv_t * const p_drv, uint32_t addr, uint8_t * data, uint32_t length)
{
    /* Create a read command packet. */
    uint8_t read_tx[4] = {FLASH_CMD_READ, (addr >> 16) & 0xFF, (addr >> 8) & 0xFF, (addr >> 0) & 0xFF}; // NOLINT(readability-magic-numbers)

    /* Send the command using the spi interface. */
    p_drv->cs_assert();

    if (MX25L12835F_SUCCESS != p_drv->transfer(read_tx, NULL, 4))
    {
        return MX25L12835F_ERROR;
    }

    /* Read the data using the spi interface. */
    mx25l1235f_status_t err = p_drv->transfer(NULL, data, length);

    p_drv->cs_deassert();

    return err;
}

/*******************************************************************************************************************//**
 * Send a page program command in order to write a single page of data.
 *
 * @param      p_drv           Driver for communicating with the MX25L12835F.
 * @param[in]  addr            Start address of the page to program.
 * @param      data            Pointer to the data to write to the page.
 * @param[in]  length          Number of bytes to program,
 *
 * @retval     MX25L12835F_SUCCESS  The sector was erased correctly.
 * @retval     MX25L12835F_ERROR    An error occurred.
 **********************************************************************************************************************/
static mx25l1235f_status_t cmd_page_program (mx25l1235f_drv_t * const p_drv,
                                             uint32_t                 addr,
                                             uint8_t const          * data,
                                             uint32_t                 length)
{
    /* Create a write command packet. */
    uint8_t cmd_tx[4] = {FLASH_CMD_PP, (addr >> 16) & 0xFF, (addr >> 8) & 0xFF, (addr >> 0) & 0xFF}; // NOLINT(readability-magic-numbers)

    p_drv->cs_assert();

    /* Send the command using the spi interface. */
    if (MX25L12835F_SUCCESS != p_drv->transfer(cmd_tx, NULL, 4))
    {
        return MX25L12835F_ERROR;
    }

    /* Send the data using the spi interface. */
    mx25l1235f_status_t err = p_drv->transfer(data, NULL, length);

    p_drv->cs_deassert();

    return err;
}
