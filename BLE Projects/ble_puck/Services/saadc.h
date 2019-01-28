/*
 * Copyright (c) 2019, Team2
 *
 */

#ifndef SAADC_SERVICE_H
#define SAADC_SERVICE_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "nrf.h"
#include "nrf_drv_saadc.h"
#include "nrf_drv_ppi.h"
#include "nrf_drv_timer.h"
#include "boards.h"
#include "app_error.h"
#include "nrf_delay.h"
#include "app_util_platform.h"
#include "nrf_pwr_mgmt.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"


static const uint8_t SAADCValuesCharName[] = "SAADC Values";

/**@brief   Macro for defining a ble_saadc_service instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */

#define BLE_SAADC_SERVICE_BLE_OBSERVER_PRIO 2

#define BLE_SAADC_SERVICE_DEF(_name)                                                                          \
static ble_saadc_service_t _name;                                                                             \
NRF_SDH_BLE_OBSERVER(_name ## _obs,                                                                         \
                     BLE_SAADC_SERVICE_BLE_OBSERVER_PRIO,                                                     \
                     ble_saadc_service_on_ble_evt, &_name)

//   SAADC service:                 cc1d0001-7376-4bfa-aeea-1d69c69bb7f5
//   SAADC_values characteristic:   cc1d0002-7376-4bfa-aeea-1d69c69bb7f5

// The bytes are stored in little-endian format, meaning the
// Least Significant Byte is stored first
// (reversed from the order they're displayed as)

// Base UUID: cc1d0000-7376-4bfa-aeea-1d69c69bb7f5
#define BLE_UUID_SAADC_SERVICE_BASE_UUID  {0xF5, 0xB7, 0x9B, 0xC9, 0x69, 0x1D, 0xEA, 0xAE, 0xFA, 0x4B, 0x76, 0x73, 0x00, 0x00, 0x1D, 0xCC}

// Service & characteristics UUIDs
#define BLE_UUID_SAADC_SERVICE_UUID  0x0001
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




/**@brief Function for handling the application's BLE stack events.
 *
 * @details This function handles all events from the BLE stack that are of interest to the LED Service.
 *
 * @param[in] p_ble_evt  Event received from the BLE stack.
 * @param[in] p_context  SAADC Service structure.
 */
void ble_saadc_service_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context)
{
    ble_saadc_service_t * p_saadc_service = (ble_saadc_service_t *)p_context;

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            on_connect(p_saadc_service, p_ble_evt);
            break;

        case BLE_GATTS_EVT_WRITE:
            on_write(p_saadc_service, p_ble_evt);
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            on_disconnect(p_saadc_service, p_ble_evt);
            break;

        default:
            // No implementation needed.
            break;
    }
}

/**@brief Function for handling the Connect event.
 *
 * @param[in]   p_saadc_service  SAADC service structure.
 * @param[in]   p_ble_evt      Event received from the BLE stack.
 */
void on_connect(ble_saadc_service_t * p_saadc_service, ble_evt_t const * p_ble_evt)
{
    p_saadc_service->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
}

/**@brief Function for handling the Disconnect event.
 *
 * @param[in]   p_bas       SAADC service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
void on_disconnect(ble_saadc_service_t * p_saadc_service, ble_evt_t const * p_ble_evt)
{
    UNUSED_PARAMETER(p_ble_evt);
    p_saadc_service->conn_handle = BLE_CONN_HANDLE_INVALID;
}

/**@brief Function for handling the Write event.
 *
 * @param[in] p_saadc_service   SAADC Service structure.
 * @param[in] p_ble_evt       Event received from the BLE stack.
 */
void on_write(ble_saadc_service_t * p_saadc_service, ble_evt_t const * p_ble_evt)
{
    ble_gatts_evt_write_t const * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;

    if (   (p_evt_write->handle == p_saadc_service->saadc_char_handles.value_handle)
        && (p_evt_write->len == 1)
        && (p_saadc_service->saadc_write_handler != NULL))
    {
        p_saadc_service->saadc_write_handler(p_ble_evt->evt.gap_evt.conn_handle, p_saadc_service, p_evt_write->data[0]);
    }
}


/**@brief Function for adding the SAADC values characteristic.
 *
 */
static uint32_t saadc_values_char_add(ble_saadc_service_t * p_saadc_service)
{
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_t    attr_char_value;
    ble_gatts_attr_md_t attr_md;
    ble_uuid_t          ble_uuid;

    memset(&char_md, 0, sizeof(char_md));
    memset(&attr_md, 0, sizeof(attr_md));
    memset(&attr_char_value, 0, sizeof(attr_char_value));

    char_md.char_props.read          = 1;
    char_md.char_props.write         = 1;
    char_md.p_char_user_desc         = SAADCValuesCharName;
    char_md.char_user_desc_size      = sizeof(SAADCValuesCharName);
    char_md.char_user_desc_max_size  = sizeof(SAADCValuesCharName);
    char_md.p_char_pf                = NULL;
    char_md.p_user_desc_md           = NULL;
    char_md.p_cccd_md                = NULL;
    char_md.p_sccd_md                = NULL;

    // Define the SAADC Values Characteristic UUID
    ble_uuid.type = p_saadc_service->uuid_type;
    ble_uuid.uuid = BLE_UUID_SAADC_VALUES_CHAR_UUID;

    // Set permissions on the Characteristic value
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);

    // Attribute Metadata settings
    attr_md.vloc       = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth    = 0;
    attr_md.wr_auth    = 0;
    attr_md.vlen       = 0;

    // Attribute Value settings
    attr_char_value.p_uuid       = &ble_uuid;
    attr_char_value.p_attr_md    = &attr_md;
    attr_char_value.init_len     = sizeof(uint8_t);
    attr_char_value.init_offs    = 0;
    attr_char_value.max_len      = sizeof(uint8_t);
    attr_char_value.p_value      = NULL;

    return sd_ble_gatts_characteristic_add(p_saadc_service->service_handle, &char_md,
                                           &attr_char_value,
                                           &p_saadc_service->saadc_char_handles);
}

uint32_t ble_saadc_service_init(ble_saadc_service_t * p_saadc_service, const ble_saadc_service_init_t * p_saadc_service_init)
{
    uint32_t   err_code;
    ble_uuid_t ble_uuid;

    // Initialize service structure
    p_saadc_service->conn_handle = BLE_CONN_HANDLE_INVALID;

    // Initialize service structure.
    p_saadc_service->saadc_write_handler = p_saadc_service_init->saadc_write_handler;

    // Add service UUID
    ble_uuid128_t base_uuid = {BLE_UUID_SAADC_SERVICE_BASE_UUID};
    err_code = sd_ble_uuid_vs_add(&base_uuid, &p_saadc_service->uuid_type);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // Set up the UUID for the service (base + service-specific)
    ble_uuid.type = p_saadc_service->uuid_type;
    ble_uuid.uuid = BLE_UUID_SAADC_SERVICE_UUID;

    // Set up and add the service
    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &ble_uuid, &p_saadc_service->service_handle);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // Add the different characteristics in the service:
    //   Values press characteristic:   cc1d0002-7376-4bfa-aeea-1d69c69bb7f5
    err_code = saadc_values_char_add(p_saadc_service);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    return NRF_SUCCESS;
}





// FROM SAADC EXAMPLE (not service)


#define SAMPLES_IN_BUFFER 6   // Buffer size is multiple of number of ADC channels (3)
volatile uint8_t state = 1;

static const nrf_drv_timer_t m_timer = NRF_DRV_TIMER_INSTANCE(4);   // Softdevice uses TIMER0 -> Use TIMER4 instead
static nrf_saadc_value_t     m_buffer_pool[2][SAMPLES_IN_BUFFER];
static nrf_ppi_channel_t     m_ppi_channel;
static uint32_t              m_adc_evt_counter;


void timer_handler(nrf_timer_event_t event_type, void * p_context)
{

}


void saadc_sampling_event_init(void)
{
    ret_code_t err_code;

    err_code = nrf_drv_ppi_init();
    APP_ERROR_CHECK(err_code);

    nrf_drv_timer_config_t timer_cfg = NRF_DRV_TIMER_DEFAULT_CONFIG;
    timer_cfg.bit_width = NRF_TIMER_BIT_WIDTH_32;
    err_code = nrf_drv_timer_init(&m_timer, &timer_cfg, timer_handler);
    APP_ERROR_CHECK(err_code);

    /* setup m_timer for compare event every 400ms */
    uint32_t ticks = nrf_drv_timer_ms_to_ticks(&m_timer, 400);
    nrf_drv_timer_extended_compare(&m_timer,
                                   NRF_TIMER_CC_CHANNEL0,
                                   ticks,
                                   NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK,
                                   false);
    nrf_drv_timer_enable(&m_timer);

    uint32_t timer_compare_event_addr = nrf_drv_timer_compare_event_address_get(&m_timer,
                                                                                NRF_TIMER_CC_CHANNEL0);
    uint32_t saadc_sample_task_addr   = nrf_drv_saadc_sample_task_get();

    /* setup ppi channel so that timer compare event is triggering sample task in SAADC */
    err_code = nrf_drv_ppi_channel_alloc(&m_ppi_channel);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_ppi_channel_assign(m_ppi_channel,
                                          timer_compare_event_addr,
                                          saadc_sample_task_addr);
    APP_ERROR_CHECK(err_code);
}


void saadc_sampling_event_enable(void)
{
    ret_code_t err_code = nrf_drv_ppi_channel_enable(m_ppi_channel);

    APP_ERROR_CHECK(err_code);
}


void saadc_callback(nrf_drv_saadc_evt_t const * p_event)
{
    if (p_event->type == NRF_DRV_SAADC_EVT_DONE)
    {
        ret_code_t err_code;

        err_code = nrf_drv_saadc_buffer_convert(p_event->data.done.p_buffer, SAMPLES_IN_BUFFER);
        APP_ERROR_CHECK(err_code);

        int i;
        NRF_LOG_INFO("ADC event number: %d", (int)m_adc_evt_counter);

        for (i = 0; i < SAMPLES_IN_BUFFER; i++)
        {
            NRF_LOG_INFO("%d", p_event->data.done.p_buffer[i]);
        }
        m_adc_evt_counter++;
    }
}


void saadc_init(void)
{
    ret_code_t err_code;
    nrf_saadc_channel_config_t channel_config =
        NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN0);

    err_code = nrf_drv_saadc_init(NULL, saadc_callback);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_saadc_channel_init(0, &channel_config);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_saadc_buffer_convert(m_buffer_pool[0], SAMPLES_IN_BUFFER);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_saadc_buffer_convert(m_buffer_pool[1], SAMPLES_IN_BUFFER);
    APP_ERROR_CHECK(err_code);

}


/**
 * @brief Function for main application entry.
 */
int perform_adc(void)
{
    uint32_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);

    NRF_LOG_DEFAULT_BACKENDS_INIT();

    ret_code_t ret_code = nrf_pwr_mgmt_init();
    APP_ERROR_CHECK(ret_code);

    saadc_init();
    saadc_sampling_event_init();
    saadc_sampling_event_enable();
    NRF_LOG_INFO("SAADC HAL simple example started.");

    while (1)
    {
        nrf_pwr_mgmt_run();
        NRF_LOG_FLUSH();
    }
    
}

#endif /* SAADC_SERVICE_H */
