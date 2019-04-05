/**
 * Copyright (c) 2019, Team2
 *
 * To be included in "boards.h"
 * Header file for pinout of BT840F chip
 * Contains layout of pins connecting accelerometer, gyro and battery
 */

#ifndef BT840F_H
#define BT840F_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nrf_gpio.h"

// define pins for accelerometer (anaolg)
#define ACCEL_X                     2     // pin 5 on BT840F  (AIN 0)
#define ACCEL_Y                     3     // pin 6 on BT840F  (AIN 1)
#define ACCEL_Z                     29    // pin A2 on BT840F (AIN 5)


// define pins for gyroscope (digital GPIO)
#define GYRO_SDA_SDI                NRF_GPIO_PIN_MAP(0,8)     // pin B5 on BT840F
#define GYRO_SCLK                   NRF_GPIO_PIN_MAP(0,15)    // pin C4 on BT840F
#define GYRO_CS                     NRF_GPIO_PIN_MAP(0,25)    // pin B1 on BT840F
#define GYRO_ADD_SDO                NRF_GPIO_PIN_MAP(0,31)    // pin B3 on BT840F

// define pins for battery charger IC (digital GPIO)
#define CHARGER_STAT                NRF_GPIO_PIN_MAP(1,5)     // pin D6 on BT840F


#define RX_PIN_NUMBER  8
#define TX_PIN_NUMBER  6
#define CTS_PIN_NUMBER 7
#define RTS_PIN_NUMBER 5
#define HWFC           true
/*
#define BSP_QSPI_SCK_PIN   19
#define BSP_QSPI_CSN_PIN   17
#define BSP_QSPI_IO0_PIN   20
#define BSP_QSPI_IO1_PIN   21
#define BSP_QSPI_IO2_PIN   22
#define BSP_QSPI_IO3_PIN   23


// serialization APPLICATION board - temp. setup for running serialized MEMU tests
#define SER_APP_RX_PIN              NRF_GPIO_PIN_MAP(1,13)    // UART RX pin number.
#define SER_APP_TX_PIN              NRF_GPIO_PIN_MAP(1,14)    // UART TX pin number.
#define SER_APP_CTS_PIN             NRF_GPIO_PIN_MAP(0,2)     // UART Clear To Send pin number.
#define SER_APP_RTS_PIN             NRF_GPIO_PIN_MAP(1,15)    // UART Request To Send pin number.

#define SER_APP_SPIM0_SCK_PIN       NRF_GPIO_PIN_MAP(0,27)     // SPI clock GPIO pin number.
#define SER_APP_SPIM0_MOSI_PIN      NRF_GPIO_PIN_MAP(0,2)      // SPI Master Out Slave In GPIO pin number
#define SER_APP_SPIM0_MISO_PIN      NRF_GPIO_PIN_MAP(0,26)     // SPI Master In Slave Out GPIO pin number
#define SER_APP_SPIM0_SS_PIN        NRF_GPIO_PIN_MAP(1,13)     // SPI Slave Select GPIO pin number
#define SER_APP_SPIM0_RDY_PIN       NRF_GPIO_PIN_MAP(1,15)     // SPI READY GPIO pin number
#define SER_APP_SPIM0_REQ_PIN       NRF_GPIO_PIN_MAP(1,14)     // SPI REQUEST GPIO pin number

// serialization CONNECTIVITY board
#define SER_CON_RX_PIN              NRF_GPIO_PIN_MAP(1,14)    // UART RX pin number.
#define SER_CON_TX_PIN              NRF_GPIO_PIN_MAP(1,13)    // UART TX pin number.
#define SER_CON_CTS_PIN             NRF_GPIO_PIN_MAP(1,15)    // UART Clear To Send pin number. Not used if HWFC is set to false.
#define SER_CON_RTS_PIN             NRF_GPIO_PIN_MAP(0,2)     // UART Request To Send pin number. Not used if HWFC is set to false.


#define SER_CON_SPIS_SCK_PIN        NRF_GPIO_PIN_MAP(0,27)    // SPI SCK signal.
#define SER_CON_SPIS_MOSI_PIN       NRF_GPIO_PIN_MAP(0,2)     // SPI MOSI signal.
#define SER_CON_SPIS_MISO_PIN       NRF_GPIO_PIN_MAP(0,26)    // SPI MISO signal.
#define SER_CON_SPIS_CSN_PIN        NRF_GPIO_PIN_MAP(1,13)    // SPI CSN signal.
#define SER_CON_SPIS_RDY_PIN        NRF_GPIO_PIN_MAP(1,15)    // SPI READY GPIO pin number.
#define SER_CON_SPIS_REQ_PIN        NRF_GPIO_PIN_MAP(1,14)    // SPI REQUEST GPIO pin number.

#define SER_CONN_CHIP_RESET_PIN     NRF_GPIO_PIN_MAP(1,1)    // Pin used to reset connectivity chip

*/
#ifdef __cplusplus
}
#endif

#endif // BT840F_H
