/*
 * The MIT License (MIT)
 * Copyright (c) 2018 Novel Bits
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */

#include "sdk_common.h"

#include "led_service_client.h"
#include "ble_db_discovery.h"
#include "ble_types.h"
#include "ble_srv_common.h"
#include "ble_gattc.h"
#define NRF_LOG_MODULE_NAME led_service_client
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define TX_BUFFER_MASK         0x07                  /**< TX Buffer mask, must be a mask of continuous zeroes, followed by continuous sequence of ones: 000...111. */
#define TX_BUFFER_SIZE         (TX_BUFFER_MASK + 1)  /**< Size of send buffer, which is 1 higher than the mask. */

#define WRITE_MESSAGE_LENGTH   BLE_CCCD_VALUE_LEN    /**< Length of the write message for CCCD. */
#define WRITE_MESSAGE_LENGTH   BLE_CCCD_VALUE_LEN    /**< Length of the write message for CCCD. */

typedef enum
{
    READ_REQ,  /**< Type identifying that this tx_message is a read request. */
    WRITE_REQ  /**< Type identifying that this tx_message is a write request. */
} tx_request_t;

/**@brief Structure for writing a message to the peer, i.e. CCCD.
 */
typedef struct
{
    uint8_t                  gattc_value[WRITE_MESSAGE_LENGTH];  /**< The message to write. */
    ble_gattc_write_params_t gattc_params;                       /**< GATTC parameters for this message. */
} write_params_t;

/**@brief Structure for holding data to be transmitted to the connected central.
 */
typedef struct
{
    uint16_t     conn_handle;  /**< Connection handle to be used when transmitting this message. */
    tx_request_t type;         /**< Type of this message, i.e. read or write message. */
    union
    {
        uint16_t       read_handle;  /**< Read request message. */
        write_params_t write_req;    /**< Write request message. */
    } req;
} tx_message_t;


static tx_message_t m_tx_buffer[TX_BUFFER_SIZE];  /**< Transmit buffer for messages to be transmitted to the central. */
static uint32_t     m_tx_insert_index = 0;        /**< Current index in the transmit buffer where the next message should be inserted. */
static uint32_t     m_tx_index = 0;               /**< Current index in the transmit buffer from where the next message to be transmitted resides. */


/**@brief Function for passing any pending request from the buffer to the stack.
 */
static void tx_buffer_process(void)
{
    if (m_tx_index != m_tx_insert_index)
    {
        uint32_t err_code;

        if (m_tx_buffer[m_tx_index].type == READ_REQ)
        {
            err_code = sd_ble_gattc_read(m_tx_buffer[m_tx_index].conn_handle,
                                         m_tx_buffer[m_tx_index].req.read_handle,
                                         0);
        }
        else
        {
            err_code = sd_ble_gattc_write(m_tx_buffer[m_tx_index].conn_handle,
                                          &m_tx_buffer[m_tx_index].req.write_req.gattc_params);
        }
        if (err_code == NRF_SUCCESS)
        {
            NRF_LOG_DEBUG("SD Read/Write API returns Success..");
            m_tx_index++;
            m_tx_index &= TX_BUFFER_MASK;
        }
        else
        {
            NRF_LOG_DEBUG("SD Read/Write API returns error. This message sending will be "
                "attempted again..");
        }
    }
}


/**@brief Function for handling write response events.
 *
 * @param[in] p_ble_led_service_client Pointer to the Led Service Client structure.
 * @param[in] p_ble_evt                Pointer to the BLE event received.
 */
static void on_write_rsp(ble_led_service_client_t * p_ble_led_service_client, ble_evt_t const * p_ble_evt)
{
    // Check if the event if on the link for this instance
    if (p_ble_led_service_client->conn_handle != p_ble_evt->evt.gattc_evt.conn_handle)
    {
        return;
    }
    // Check if there is any message to be sent across to the peer and send it.
    tx_buffer_process();
}


/**@brief Function for handling Disconnected event received from the SoftDevice.
 *
 * @details This function check if the disconnect event is happening on the link
 *          associated with the current instance of the module, if so it will set its
 *          conn_handle to invalid.
 *
 * @param[in] p_ble_led_service_client Pointer to the Led Service Client structure.
 * @param[in] p_ble_evt                Pointer to the BLE event received.
 */
static void on_disconnected(ble_led_service_client_t * p_ble_led_service_client, ble_evt_t const * p_ble_evt)
{
    if (p_ble_led_service_client->conn_handle == p_ble_evt->evt.gap_evt.conn_handle)
    {
        p_ble_led_service_client->conn_handle                    = BLE_CONN_HANDLE_INVALID;
        p_ble_led_service_client->peer_led_service_db.led2_handle         = BLE_GATT_HANDLE_INVALID;
    }
}


void ble_led_service_on_db_disc_evt(ble_led_service_client_t * p_ble_led_service_client, ble_db_discovery_evt_t const * p_evt)
{
    // Check if the Led Button Service was discovered.
    if (p_evt->evt_type == BLE_DB_DISCOVERY_COMPLETE &&
        p_evt->params.discovered_db.srv_uuid.uuid == BLE_UUID_LED_SERVICE_UUID &&
        p_evt->params.discovered_db.srv_uuid.type == p_ble_led_service_client->uuid_type)
    {
        ble_led_service_client_evt_t evt;

        evt.evt_type    = BLE_LED_SERVICE_CLIENT_EVT_DISCOVERY_COMPLETE;
        evt.conn_handle = p_evt->conn_handle;

        for (uint32_t i = 0; i < p_evt->params.discovered_db.char_count; i++)
        {
            const ble_gatt_db_char_t * p_char = &(p_evt->params.discovered_db.charateristics[i]);
            switch (p_char->characteristic.uuid.uuid)
            {
                case BLE_UUID_LED_2_CHAR_UUID:
                    evt.peer_db.led2_handle = p_char->characteristic.handle_value;
                    break;


                default:
                    break;
            }
        }

        NRF_LOG_DEBUG("Led Service discovered at peer.");
        //If the instance has been assigned prior to db_discovery, assign the db_handles
        if (p_ble_led_service_client->conn_handle != BLE_CONN_HANDLE_INVALID)
        {
            if (p_ble_led_service_client->peer_led_service_db.led2_handle         == BLE_GATT_HANDLE_INVALID)
            {
                p_ble_led_service_client->peer_led_service_db = evt.peer_db;
            }
        }

        p_ble_led_service_client->evt_handler(p_ble_led_service_client, &evt);

    }
}


uint32_t ble_led_service_client_init(ble_led_service_client_t * p_ble_led_service_client, ble_led_service_client_init_t * p_ble_led_service_client_init)
{
    uint32_t      err_code;
    ble_uuid_t    led_service_uuid;
    ble_uuid128_t led_service_base_uuid = {BLE_UUID_LED_SERVICE_BASE_UUID};

    VERIFY_PARAM_NOT_NULL(p_ble_led_service_client);
    VERIFY_PARAM_NOT_NULL(p_ble_led_service_client_init);
    VERIFY_PARAM_NOT_NULL(p_ble_led_service_client_init->evt_handler);

    p_ble_led_service_client->peer_led_service_db.led2_handle   = BLE_GATT_HANDLE_INVALID;
    p_ble_led_service_client->conn_handle                      = BLE_CONN_HANDLE_INVALID;
    p_ble_led_service_client->evt_handler                      = p_ble_led_service_client_init->evt_handler;

    err_code = sd_ble_uuid_vs_add(&led_service_base_uuid, &p_ble_led_service_client->uuid_type);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    VERIFY_SUCCESS(err_code);

    led_service_uuid.type = p_ble_led_service_client->uuid_type;
    led_service_uuid.uuid = BLE_UUID_LED_SERVICE_UUID;

    return ble_db_discovery_evt_register(&led_service_uuid);
}

void ble_led_service_client_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context)
{
    if ((p_context == NULL) || (p_ble_evt == NULL))
    {
        return;
    }

    ble_led_service_client_t * p_ble_led_service_client = (ble_led_service_client_t *)p_context;

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GATTC_EVT_WRITE_RSP:
            on_write_rsp(p_ble_led_service_client, p_ble_evt);
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            on_disconnected(p_ble_led_service_client, p_ble_evt);
            break;

        default:
            break;
    }
}


uint32_t ble_led_service_led2_setting_send(ble_led_service_client_t * p_ble_led_service_client, uint8_t status)
{
    VERIFY_PARAM_NOT_NULL(p_ble_led_service_client);

    if (p_ble_led_service_client->conn_handle == BLE_CONN_HANDLE_INVALID)
    {
        return NRF_ERROR_INVALID_STATE;
    }

    NRF_LOG_DEBUG("writing LED2 status 0x%x", status);

    tx_message_t * p_msg;

    p_msg              = &m_tx_buffer[m_tx_insert_index++];
    m_tx_insert_index &= TX_BUFFER_MASK;

    p_msg->req.write_req.gattc_params.handle   = p_ble_led_service_client->peer_led_service_db.led2_handle;
    p_msg->req.write_req.gattc_params.len      = sizeof(status);
    p_msg->req.write_req.gattc_params.p_value  = p_msg->req.write_req.gattc_value;
    p_msg->req.write_req.gattc_params.offset   = 0;
    p_msg->req.write_req.gattc_params.write_op = BLE_GATT_OP_WRITE_CMD;
    p_msg->req.write_req.gattc_value[0]        = status;
    p_msg->conn_handle                         = p_ble_led_service_client->conn_handle;
    p_msg->type                                = WRITE_REQ;

    tx_buffer_process();
    return NRF_SUCCESS;
}

uint32_t ble_led_service_client_handles_assign(ble_led_service_client_t    * p_ble_led_service_client,
                                               uint16_t                      conn_handle,
                                               const led_service_db_t      * p_peer_handles)
{
    VERIFY_PARAM_NOT_NULL(p_ble_led_service_client);

    p_ble_led_service_client->conn_handle = conn_handle;
    if (p_peer_handles != NULL)
    {
        p_ble_led_service_client->peer_led_service_db = *p_peer_handles;
    }
    return NRF_SUCCESS;
}

