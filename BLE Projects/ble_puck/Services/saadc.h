/*
 * Copyright (c) 2019, Team2
 *
 * This is the custom service for the SAADC.
 * The user can manually start and stop sampling using the SAADC
 * by sending 1 or 0 to the SAADC_values characteristic of the SAADC service (defined in main.c)
 * 
 */


#ifndef SAADC_SERVICE_H
#define SAADC_SERVICE_H

#include <stdint.h>
#include "boards.h"
#include "ble.h"
#include "ble_srv_common.h"
#include "nrf_sdh_ble.h"


/**@brief   Macro for defining a ble_saadc_service instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */

#define BLE_SAADC_SERVICE_BLE_OBSERVER_PRIO 2

#define BLE_SAADC_SERVICE_DEF(_name)                                                                          \
static ble_saadc_service_t _name;                                                                             \
NRF_SDH_BLE_OBSERVER(_name ## _obs,                                                                           \
                     BLE_SAADC_SERVICE_BLE_OBSERVER_PRIO,                                                     \
                     ble_saadc_service_on_ble_evt, &_name)


// Define UUIDs

// SAADC service:                 cc1d0001-7376-4bfa-aeea-1d69c69bb7f5
// SAADC_values characteristic:   cc1d0002-7376-4bfa-aeea-1d69c69bb7f5

// The Least Significant Byte is stored first
// Base UUID: cc1d0000-7376-4bfa-aeea-1d69c69bb7f5
#define BLE_UUID_SAADC_SERVICE_BASE_UUID  {0xF5, 0xB7, 0x9B, 0xC9, 0x69, 0x1D, 0xEA, 0xAE, 0xFA, 0x4B, 0x76, 0x73, 0x00, 0x00, 0x1D, 0xCC}

// Service & characteristics UUIDs
#define BLE_UUID_SAADC_SERVICE_UUID       0x0001
#define BLE_UUID_SAADC_VALUES_CHAR_UUID   0x0002


// Forward declaration of the custom_service_t type.
typedef struct ble_saadc_service_s ble_saadc_service_t;


typedef void (*ble_saadc_service_saadc_write_handler_t) (uint16_t conn_handle, ble_saadc_service_t * p_saadc_service, uint8_t new_state);


/** @brief SAADC Service init structure. This structure contains all options and data needed for
 *        initialization of the service.*/
typedef struct
{
    ble_saadc_service_saadc_write_handler_t saadc_write_handler; /**< Event handler to be called when the SAADC Characteristic is written. */
} ble_saadc_service_init_t;


/**@brief SAADC Service structure.
 *        This contains various status information
 *        for the service.
 */
typedef struct ble_saadc_service_s
{
    uint16_t                                   conn_handle;
    uint16_t                                   service_handle;
    uint8_t                                    uuid_type;
    ble_gatts_char_handles_t                   saadc_char_handles;
    ble_saadc_service_saadc_write_handler_t    saadc_write_handler;

} ble_saadc_service_t;


// Function Declerations

/**@brief Function for initializing the SAADC Service.
 *
 * @param[out]  p_led_service  SAADC Service structure. This structure will have to be supplied by
 *                                the application. It will be initialized by this function, and will later
 *                                be used to identify this particular service instance.
 *
 * @return      NRF_SUCCESS on successful initialization of service, otherwise an error code.
 */
uint32_t ble_saadc_service_init(ble_saadc_service_t * p_saadc_service, const ble_saadc_service_init_t * p_saadc_service_init);


/**@brief Function for handling the application's BLE stack events.
 *
 * @details This function handles all events from the BLE stack that are of interest to the SAADC Service.
 *
 * @param[in] p_ble_evt  Event received from the BLE stack.
 * @param[in] p_context  SAADC Service structure.
 */
void ble_saadc_service_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context);


#endif /* SAADC_SERVICE_H */
