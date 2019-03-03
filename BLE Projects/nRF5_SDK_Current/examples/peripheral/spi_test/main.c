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

#include <stdint.h>

#define SPI_INSTANCE  0 /**< SPI instance index. */
static const nrf_drv_spi_t peripheral = NRF_DRV_SPI_INSTANCE(SPI_INSTANCE);       /**< SPI instance */
const nrf_drv_spi_t *p_spi_instance = &peripheral;
static volatile bool spi_xfer_done;                                             /**< Flag used to indicate that SPI instance completed the transfer */


static volatile bool *p_spi_xfer_done;                                           /**< Pointer to SPI_xfer_done flag */
static uint8_t m_tx_buf[2] = {};                                                /**< TX buffer */
static uint8_t m_rx_buf[sizeof(m_tx_buf) + 1];                                  /**< RX buffer */
static const int8_t tx_length = sizeof(m_tx_buf);                               /**< Transfer length */
static const int8_t rx_length = sizeof(m_rx_buf);                               /**< Transfer length */

/**@brief Reads data from a register
 */
static void register_read(peripheral_registers_t register_to_access, int rx_length)
{
  peripheral_result_codes_t result;
  uint8_t command;

  memset(m_tx_buf, 0, tx_length);
  memset(m_rx_buf, 0, rx_length);
  *p_spi_xfer_done = false;

  m_tx_buf[0] = command_byte_set(register_to_access, read);    //Left shift 3 & set 2nd bit 0
  APP_ERROR_CHECK(nrf_drv_spi_transfer(p_spi_instance, m_tx_buf, 1, m_rx_buf, rx_length + 1));      //p_spi_instance = 0x0003be04

  while (!*p_spi_xfer_done)     //I get into an endless loop here
  {
    __WFE();
  }
}

/**@brief Writes data to a register
 */
static void register_write(peripheral_registers_t register_to_access, uint8_t data, int tx_length)
{
  peripheral_result_codes_t result;
  uint8_t command;

  memset(m_tx_buf, 0, tx_length);
  memset(m_rx_buf, 0, rx_length);
  *p_spi_xfer_done = false;

  m_tx_buf[0] = command_byte_set(register_to_access, write);    //Left shift 3 & set 2nd bit 1
  m_tx_buf[1] = data;         //append data to buffer

  APP_ERROR_CHECK(nrf_drv_spi_transfer(p_spi_instance, m_tx_buf, tx_length + 1, m_rx_buf, 1));

  while (!*p_spi_xfer_done)
  {
    __WFE();
  }
}

void spi_event_handler(nrf_drv_spi_evt_t const * p_event,
                       void *                    p_context)
{
    *p_spi_xfer_done = true;
    NRF_LOG_INFO("Transfer completed.");
    if (m_rx_buf[0] != 0)
    {
        NRF_LOG_INFO(" Received:");
        NRF_LOG_HEXDUMP_INFO(m_rx_buf, strlen((const char *)m_rx_buf));
    }
}
void (*p_spi_event_handler) = &spi_event_handler;       //Function pointer declared in main.c

/**@brief Initialize peripheral at startup
 */
void peripheral_init(volatile bool *spi_xfer_done)
{
  p_spi_xfer_done = spi_xfer_done;

  register_init(17, 0, 0, 0, 1, 1, 0, 1, 0);        //creates byte with configuration value and calls register_write
}

static void register_init(peripheral_registers_t register_to_access,
                     uint8_t bit_value7,
                     uint8_t bit_value6,
                     uint8_t bit_value5,
                     uint8_t bit_value4,
                     uint8_t bit_value3,
                     uint8_t bit_value2,
                     uint8_t bit_value1,
                     uint8_t bit_value0)
{
  uint8_t register_value = 0;
  uint8_t bit_value_array[8] = {bit_value0, bit_value1, bit_value2, bit_value3, bit_value4, bit_value5, bit_value6, bit_value7};   //Array and binary MSB/LSB are reverse in order!

  for(int8_t bit_shift = 7; bit_shift >= 0; bit_shift--)
  {
    //Shift configuration bit into the right place of the register value
    register_value |= shift_bit(register_value, bit_value_array[bit_shift], bit_shift);
  }
  register_write(register_to_access, register_value, 1);
}

/**@brief Read register 17 on button press
 */
void peripheral_read_17(void)
{
  uint8_t result;
  register_read(17, 1);
}






extern void *p_spi_event_handler;
void spi_config(void)
{
  nrf_drv_spi_config_t spi_config = NRF_DRV_SPI_DEFAULT_CONFIG;
  spi_config.sck_pin  = SPI_SCK_PIN;
  spi_config.miso_pin = SPI_MISO_PIN;
  spi_config.mosi_pin = SPI_MOSI_PIN;
  spi_config.ss_pin = SPI_SS_PIN != NRF_DRV_SPI_PIN_NOT_USED ? SPI_SS_PIN : NRF_DRV_SPI_PIN_NOT_USED;
  APP_ERROR_CHECK(nrf_drv_spi_init(p_spi_instance, &spi_config, p_spi_event_handler, NULL));
}

int main(void)
{
    //SPI configuration
    spi_config();
    //Peripheral initialization
    peripheral_init(&spi_xfer_done);

    // Enter main loop.
    for (;;)
    {
        idle_state_handle();
    }
}