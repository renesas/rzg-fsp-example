/*
 * Copyright (c) 2023 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef XSPI_INIT_H_
#define XSPI_INIT_H_

/* generic headers */
#include "hal_data.h"

/*
 * function declarations
 */
FSP_CPP_HEADER

void      xspi_open(void);
void      xspi_close(void);
fsp_err_t xspi_pre_init(spi_flash_api_t const * p_api, xspi_qspi_instance_ctrl_t * p_ctrl);
fsp_err_t xspi_post_init(spi_flash_api_t const * p_api, xspi_qspi_instance_ctrl_t * p_ctrl);

FSP_CPP_FOOTER

#endif                                 /* XSPI_INIT_H_ */
