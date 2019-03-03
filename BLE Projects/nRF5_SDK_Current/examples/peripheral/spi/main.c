/**
 * Copyright (c) 2015 - 2018, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include "nrf_drv_spi.h"
#include "app_util_platform.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "boards.h"
#include "app_error.h"
#include <string.h>
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#define SPI_INSTANCE  0 /**< SPI instance index. */
static const nrf_drv_spi_t spi = NRF_DRV_SPI_INSTANCE(SPI_INSTANCE);  /**< SPI instance. */
static volatile bool spi_xfer_done;  /**< Flag used to indicate that SPI instance completed the transfer. */

//#define TEST_STRING "Nordic"
//static uint8_t       m_tx_buf[] = TEST_STRING;           /**< TX buffer. */
//static uint8_t       m_rx_buf[sizeof(TEST_STRING) + 1];    /**< RX buffer. */
//static const uint8_t m_length = sizeof(m_tx_buf);        /**< Transfer length. */



////////////////////////////
// ITG3701 Gyro Registers //
////////////////////////////
// From ITG3701 Register Map and Descriptions
// https://www.invensense.com/products/motion-tracking/3-axis/itg-3701/
//
#define ITG3701_XG_OFFS_TC_H     0x04
#define ITG3701_XG_OFFS_TC_L     0x05
#define ITG3701_YG_OFFS_TC_H     0x07
#define ITG3701_YG_OFFS_TC_L     0x08
#define ITG3701_ZG_OFFS_TC_H     0x0A
#define ITG3701_ZG_OFFS_TC_L     0x0B
#define ITG3701_XG_OFFS_USRH     0x13  // User-defined trim values for gyroscope
#define ITG3701_XG_OFFS_USRL     0x14
#define ITG3701_YG_OFFS_USRH     0x15
#define ITG3701_YG_OFFS_USRL     0x16
#define ITG3701_ZG_OFFS_USRH     0x17
#define ITG3701_ZG_OFFS_USRL     0x18
#define ITG3701_SMPLRT_DIV       0x19
#define ITG3701_CONFIG           0x1A
#define ITG3701_GYRO_CONFIG      0x1B
#define ITG3701_FIFO_EN          0x23
#define ITG3701_INT_PIN_CFG      0x37
#define ITG3701_INT_ENABLE       0x38
#define ITG3701_INT_STATUS       0x3A
#define ITG3701_TEMP_OUT_H       0x41
#define ITG3701_TEMP_OUT_L       0x42
#define ITG3701_GYRO_XOUT_H      0x43
#define ITG3701_GYRO_XOUT_L      0x44
#define ITG3701_GYRO_YOUT_H      0x45
#define ITG3701_GYRO_YOUT_L      0x46
#define ITG3701_GYRO_ZOUT_H      0x47
#define ITG3701_GYRO_ZOUT_L      0x48
#define ITG3701_USER_CTRL        0x6A  
#define ITG3701_PWR_MGMT_1       0x6B // Device defaults to the SLEEP mode
#define ITG3701_PWR_MGMT_2       0x6C
#define ITG3701_FIFO_COUNTH      0x72
#define ITG3701_FIFO_COUNTL      0x73
#define ITG3701_FIFO_R_W         0x74
#define ITG3701_WHO_AM_I         0x75 // Should return 0x68



static uint8_t       m_config_buf1[] = {((uint8_t)0x20),((uint8_t)0x1F)};           /**< TX buffer. */ //,((uint8_t)0x24),((uint8_t)0x40),((uint8_t)0x2E),((uint8_t)0x40)
static uint8_t       m_config_buf2[] = {((uint8_t)0x24),((uint8_t)0x40)}; 
static uint8_t       m_config_buf3[] = {((uint8_t)0x2E),((uint8_t)0x00)}; 

static uint8_t       m_tx_rx_buf1[] = {((uint8_t)0xA0)}; //,((uint8_t)0xA4),((uint8_t)0xAE)
static uint8_t       m_tx_rx_buf2[] = {((uint8_t)0xA4)};
static uint8_t       m_tx_rx_buf3[] = {((uint8_t)0xAE)};

static uint8_t       m_rx_buf1[sizeof(((uint8_t)0xA4)) + 1];    /**< RX buffer. */
static uint8_t       m_rx_buf2[sizeof(((uint8_t)0xA4)) + 1];
static uint8_t       m_rx_buf3[sizeof(((uint8_t)0xA4)) + 1];

//Buffers for gyro data
static uint8_t       m_x_axis_buf1[] = {((uint8_t)0xA9)};
static uint8_t       m_x_rx_buf1[sizeof(((uint8_t)0xA9)) + 1]; 

//static const uint8_t m_length_config = sizeof(m_config_buf1);        /**< Transfer length. */
static const uint8_t m_length_rx = sizeof(m_tx_rx_buf1);        /**< Transfer length. */


void config_gyro()
{
    APP_ERROR_CHECK(nrf_drv_spi_transfer(&spi, m_config_buf1, sizeof(m_config_buf1), NULL, NULL));//change 3rd param from m_rx_buf to NULL & 4th from m_length to NULL 
    nrf_delay_ms(20);
    APP_ERROR_CHECK(nrf_drv_spi_transfer(&spi, m_config_buf2, sizeof(m_config_buf2), NULL, NULL));
    nrf_delay_ms(20);
    APP_ERROR_CHECK(nrf_drv_spi_transfer(&spi, m_config_buf3, sizeof(m_config_buf3), NULL, NULL));
    nrf_delay_ms(20);
}


/**
 * @brief SPI user event handler.
 * @param event
 */
void spi_event_handler(nrf_drv_spi_evt_t const * p_event,
                       void *                    p_context)
{
    spi_xfer_done = true;
    NRF_LOG_INFO("Transfer completed.");
    /*if (m_rx_buf[0] != 0)
    {
        NRF_LOG_INFO(" Received:");
        NRF_LOG_HEXDUMP_INFO(m_rx_buf, strlen((const char *)m_rx_buf));
    }
    */

    if (m_rx_buf1[0] != 0||m_rx_buf2[0] != 0||m_rx_buf3[0] != 0||m_x_rx_buf1[0] != 0)
    {
        NRF_LOG_INFO(" Received:");
        NRF_LOG_HEXDUMP_INFO(m_rx_buf1, strlen((const char *)m_rx_buf1));
        NRF_LOG_HEXDUMP_INFO(m_rx_buf2, strlen((const char *)m_rx_buf2));
        NRF_LOG_HEXDUMP_INFO(m_rx_buf3, strlen((const char *)m_rx_buf3));
    }
}


int main(void)
{
    bsp_board_init(BSP_INIT_LEDS);

    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();

    //SPI setings
    nrf_drv_spi_config_t spi_config = NRF_DRV_SPI_DEFAULT_CONFIG;
    //pins defined in sdk_config.h
    spi_config.ss_pin   = SPI_SS_PIN;   //35
    spi_config.miso_pin = SPI_MISO_PIN; //40
    spi_config.mosi_pin = SPI_MOSI_PIN; //36
    spi_config.sck_pin  = SPI_SCK_PIN;  //27

    APP_ERROR_CHECK(nrf_drv_spi_init(&spi, &spi_config, spi_event_handler, NULL));

    NRF_LOG_INFO("SPI example started.");

    while (1)
    {
        // Reset rx buffer and transfer done flag
        /*memset(m_rx_buf, 0, m_length);
        spi_xfer_done = false;
        */
        memset(m_rx_buf1, 0, m_length_rx);
        memset(m_rx_buf2, 0, m_length_rx);
        memset(m_rx_buf3, 0, m_length_rx);
        spi_xfer_done = false;

        config_gyro();

        APP_ERROR_CHECK(nrf_drv_spi_transfer(&spi, m_tx_rx_buf1, m_length_rx, m_rx_buf1, m_length_rx));
        nrf_delay_ms(200);
        APP_ERROR_CHECK(nrf_drv_spi_transfer(&spi, m_tx_rx_buf2, m_length_rx, m_rx_buf2, m_length_rx));
        nrf_delay_ms(200);
        APP_ERROR_CHECK(nrf_drv_spi_transfer(&spi, m_tx_rx_buf3, m_length_rx, m_rx_buf3, m_length_rx));
        nrf_delay_ms(200);

        APP_ERROR_CHECK(nrf_drv_spi_transfer(&spi,m_x_axis_buf1, m_length_rx, m_rx_buf1, m_length_rx));



        // APP_ERROR_CHECK(nrf_drv_spi_transfer(&spi, m_tx_buf, m_length, m_rx_buf, m_length));

        while (!spi_xfer_done)
        {
            __WFE();
        }

        NRF_LOG_FLUSH();
        

        bsp_board_led_invert(BSP_BOARD_LED_0);
        nrf_delay_ms(1000);

    }
}
