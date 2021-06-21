/**
 * Copyright (c) 2019 - 2021, Titan Lab Inc.
 * 
 */

#include "sdk_common.h"
#if NRF_MODULE_ENABLED(ANT_SHIFT)

#include "nrf_assert.h"
#include "app_error.h"
#include "ant_interface.h"
#include "ant_shift.h"

#define NRF_LOG_MODULE_NAME ant_shift
#if ANT_SHIFT_LOG_ENABLED
#define NRF_LOG_LEVEL       ANT_SHIFT_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  ANT_SHIFT_INFO_COLOR
#else // ANT_SHIFT_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // ANT_SHIFT_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

#define SHIFT_CALIB_INT_TIMEOUT ((ANT_CLOCK_FREQUENCY * SHIFT_CALIBRATION_TIMOUT_S) / SHIFT_MSG_PERIOD) // calibration timeout in ant message period's unit

// for torque sensor Minimum: Interleave every 9th message
#define SHIFT_PAGE_1_INTERVAL      5   // Preferred: Interleave every 5th message
#define SHIFT_PAGE_1_INTERVAL_OFS  2   // Permissible offset
#define COMMON_PAGE_80_INTERVAL    119 // Minimum: Interleave every 121 messages
#define COMMON_PAGE_81_INTERVAL    120 // Minimum: Interleave every 121 messages
#define AUTO_ZERO_SUPPORT_INTERVAL 120 // Minimum: Interleave every 121 messages

/**@brief Bicycle power message data layout structure. */
typedef struct
{
    uint8_t page_number;
    uint8_t page_payload[7];
} ant_shift_message_layout_t;


/**@brief Function for initializing the ANT Bicycle Power Profile instance.
 *
 * @param[in]  p_profile        Pointer to the profile instance.
 * @param[in]  p_channel_config Pointer to the ANT channel configuration structure.
 *
 * @retval     NRF_SUCCESS      If initialization was successful. Otherwise, an error code is returned.
 */
static ret_code_t ant_shift_init(ant_shift_profile_t         * p_profile,
                                ant_channel_config_t const * p_channel_config)
{
    p_profile->channel_number = p_channel_config->channel_number;

    p_profile->page_1  = DEFAULT_ANT_SHIFT_PAGE1();
    p_profile->page_80 = DEFAULT_ANT_COMMON_page80();
    p_profile->page_81 = DEFAULT_ANT_COMMON_page81();
    p_profile->page_82 = DEFAULT_ANT_SHIFT_PAGE82();
    p_profile->page_78 = DEFAULT_ANT_SHIFT_PAGE78();
    p_profile->page_79 = DEFAULT_ANT_SHIFT_PAGE79();

    NRF_LOG_INFO("ANT SHIFT channel %u init", p_profile->channel_number);
    return ant_channel_init(p_channel_config);
}


ret_code_t ant_shift_disp_init(ant_shift_profile_t           * p_profile,
                              ant_channel_config_t const   * p_channel_config,
                              ant_shift_disp_config_t const * p_disp_config)
{
    ASSERT(p_profile != NULL);
    ASSERT(p_channel_config != NULL);
    ASSERT(p_disp_config != NULL);
    ASSERT(p_disp_config->evt_handler != NULL);
    ASSERT(p_disp_config->p_cb != NULL);

    p_profile->evt_handler   = p_disp_config->evt_handler;
    // p_profile->_cb.p_disp_cb = p_disp_config->p_cb;

    // p_profile->_cb.p_disp_cb ->calib_timeout = 0;
    // p_profile->_cb.p_disp_cb ->calib_stat    = SHIFT_DISP_CALIB_NONE;

    return ant_shift_init(p_profile, p_channel_config);
}


ret_code_t ant_shift_sens_init(ant_shift_profile_t           * p_profile,
                              ant_channel_config_t const   * p_channel_config,
                              ant_shift_sens_config_t const * p_sens_config)
{
    ASSERT(p_profile != NULL);
    ASSERT(p_channel_config != NULL);
    ASSERT(p_sens_config != NULL);
    ASSERT(p_sens_config->p_cb != NULL);
    ASSERT(p_sens_config->evt_handler != NULL);
    // ASSERT(p_sens_config->calib_handler != NULL);

    p_profile->evt_handler   = p_sens_config->evt_handler;
    // p_profile->_cb.p_sens_cb = p_sens_config->p_cb;

    // p_profile->_cb.p_sens_cb->calib_handler   = p_sens_config->calib_handler;
    // p_profile->_cb.p_sens_cb->calib_stat      = SHIFT_SENS_CALIB_NONE;
    // p_profile->_cb.p_sens_cb->message_counter = 0;

    return ant_shift_init(p_profile, p_channel_config);
}



/**@brief Function for getting next page number to send.
 *
 * @param[in]  p_profile        Pointer to the profile instance.
 *
 * @return     Next page number.
 */
static ant_shift_page_t next_page_number_get(ant_shift_profile_t * p_profile)
{
    ant_shift_sens_cb_t * p_shift_cb = p_profile->_cb.p_sens_cb;
    ant_shift_page_t      page_number;

    // if (p_shift_cb->calib_stat == SHIFT_SENS_CALIB_READY)
    // {
    //     page_number           = ANT_SHIFT_PAGE_1;
    //     p_shift_cb->calib_stat = SHIFT_SENS_CALIB_NONE; // mark event as processed
    // }
    // else if ((p_profile->SHIFT_PROFILE_auto_zero_status != ANT_SHIFT_AUTO_ZERO_NOT_SUPPORTED)
    //          && (p_shift_cb->message_counter == AUTO_ZERO_SUPPORT_INTERVAL))
    // {
    //     page_number                            = ANT_SHIFT_PAGE_1;
    //     p_profile->SHIFT_PROFILE_calibration_id = ANT_SHIFT_CALIB_ID_AUTO_SUPPORT;
    //     p_shift_cb->message_counter++;
    // }
    if (p_shift_cb->message_counter >= COMMON_PAGE_81_INTERVAL)
    {
        page_number                = ANT_SHIFT_PAGE_81;
        p_shift_cb->message_counter = 0;
    }
    else
    {
        if (p_shift_cb->message_counter == COMMON_PAGE_80_INTERVAL)
        {
            page_number = ANT_SHIFT_PAGE_80;
        }
        else
        {
                page_number = ANT_SHIFT_PAGE_1;
        }
        p_shift_cb->message_counter++;
    }

    return page_number;
}


/**@brief Function for encoding Bicycle Power Sensor message.
 *
 * @note Assume to be call each time when Tx window will occur.
 */
static void sens_message_encode(ant_shift_profile_t * p_profile, uint8_t * p_message_payload)
{
    ant_shift_message_layout_t * p_shift_message_payload =
        (ant_shift_message_layout_t *)p_message_payload;

    p_shift_message_payload->page_number = next_page_number_get(p_profile);

    NRF_LOG_INFO("SHIFT tx page: %u", p_shift_message_payload->page_number);

    switch (p_shift_message_payload->page_number)
    {
        case ANT_SHIFT_PAGE_1:
            ant_shift_page_1_encode(p_shift_message_payload->page_payload, &(p_profile->page_1));
            break;

        case ANT_SHIFT_PAGE_78:
            ant_shift_page_78_encode(p_shift_message_payload->page_payload, &(p_profile->page_78));
            break;

        case ANT_SHIFT_PAGE_79:
            ant_shift_page_79_encode(p_shift_message_payload->page_payload, &(p_profile->page_79));
            break;

        case ANT_COMMON_PAGE_80:
            ant_common_page_80_encode(p_shift_message_payload->page_payload, &(p_profile->page_80));
            break;

        case ANT_COMMON_PAGE_81:
            ant_common_page_81_encode(p_shift_message_payload->page_payload, &(p_profile->page_81));
            break;

        case ANT_SHIFT_PAGE_82:
            ant_shift_page_82_encode(p_shift_message_payload->page_payload, &(p_profile->page_82));
            break;

        default:
            return;
    }

    p_profile->evt_handler(p_profile, (ant_shift_evt_t)p_shift_message_payload->page_number);

}


/**@brief Function for decoding messages received by Bicycle Power sensor message.
 *
 * @note Assume to be call each time when Rx window will occur.
 */
static void sens_message_decode(ant_shift_profile_t * p_profile, uint8_t * p_message_payload)
{
    const ant_shift_message_layout_t * p_shift_message_payload =
        (ant_shift_message_layout_t *)p_message_payload;
    ant_shift_page1_data_t page1;

    switch (p_shift_message_payload->page_number)
    {
        case ANT_SHIFT_PAGE_1:
            ant_shift_page_1_decode(p_shift_message_payload->page_payload, &page1);
            break;

        default:
            break;
    }
}


/**@brief Function for decoding messages received by Bicycle Power display message.
 *
 * @note Assume to be call each time when Rx window will occur.
 */
static void disp_message_decode(ant_shift_profile_t * p_profile, uint8_t * p_message_payload)
{
    const ant_shift_message_layout_t * p_shift_message_payload =
        (ant_shift_message_layout_t *)p_message_payload;

    NRF_LOG_INFO("SHIFT rx page: %u", p_shift_message_payload->page_number);

    switch (p_shift_message_payload->page_number)
    {
        case ANT_SHIFT_PAGE_1:
            ant_shift_page_1_decode(p_shift_message_payload->page_payload, &(p_profile->page_1));
            break;

        case ANT_SHIFT_PAGE_78:
            ant_shift_page_78_decode(p_shift_message_payload->page_payload, &(p_profile->page_78));
            break;

        case ANT_SHIFT_PAGE_79:
            ant_shift_page_79_decode(p_shift_message_payload->page_payload, &(p_profile->page_79));
            break;

        case ANT_COMMON_PAGE_80:
            ant_common_page_80_decode(p_shift_message_payload->page_payload, &(p_profile->page_80));
            break;

        case ANT_COMMON_PAGE_81:
            ant_common_page_81_decode(p_shift_message_payload->page_payload, &(p_profile->page_81));
            break;
        
        case ANT_SHIFT_PAGE_82:
            ant_shift_page_82_decode(p_shift_message_payload->page_payload, &(p_profile->page_82));
            break;

        default:
            return;
    }

    p_profile->evt_handler(p_profile, (ant_shift_evt_t)p_shift_message_payload->page_number);
}


ret_code_t ant_shift_calib_request(ant_shift_profile_t * p_profile, ant_shift_page1_data_t * p_page_1)
{
    ant_shift_message_layout_t shift_message_payload;

    // if (p_profile->_cb.p_disp_cb->calib_stat == SHIFT_DISP_CALIB_REQUESTED)
    // {
    //     return NRF_SUCCESS; // calibration in progress, so omit this request
    // }

    shift_message_payload.page_number = ANT_SHIFT_PAGE_1;
    ant_shift_page_1_encode(shift_message_payload.page_payload, p_page_1);

    uint32_t err_code = sd_ant_acknowledge_message_tx(p_profile->channel_number,
                                                      sizeof (shift_message_payload),
                                                      (uint8_t *) &shift_message_payload);

    if (err_code == NRF_SUCCESS)
    {
        // p_profile->_cb.p_disp_cb->calib_timeout = SHIFT_CALIB_INT_TIMEOUT; // initialize watch on calibration's time-out
        // p_profile->_cb.p_disp_cb->calib_stat    = SHIFT_DISP_CALIB_REQUESTED;
        NRF_LOG_INFO("Start calibration process");
    }
    return err_code;
}


void ant_shift_calib_response(ant_shift_profile_t * p_profile)
{
    // if (p_profile->_cb.p_sens_cb->calib_stat != SHIFT_SENS_CALIB_READY) // abort if callback request is in progress
    // {
    //     p_profile->_cb.p_sens_cb->calib_stat = SHIFT_SENS_CALIB_READY; // calibration respond
    // }
}


/**@brief Function for hangling calibration events.
 */
// static void service_calib(ant_shift_profile_t * p_profile, uint8_t event)
// {
//     ant_shift_evt_t       shift_event;

//     if (p_profile->_cb.p_disp_cb->calib_stat == SHIFT_DISP_CALIB_REQUESTED)
//     {
//         switch (event)
//         {
//             case EVENT_RX:
//             /* fall through */
//             case EVENT_RX_FAIL:

//                 if (p_profile->_cb.p_disp_cb->calib_timeout-- == 0)
//                 {
//                     shift_event = ANT_SHIFT_CALIB_TIMEOUT;
//                     break;
//                 }
//                 else
//                 {
//                     return;
//                 }

//             case EVENT_TRANSFER_TX_FAILED:
//                 shift_event = ANT_SHIFT_CALIB_REQUEST_TX_FAILED;
//                 break;

//             case EVENT_RX_SEARCH_TIMEOUT:
//                 shift_event = ANT_SHIFT_CALIB_TIMEOUT;
//                 break;

//             default:
//                 return;
//         }

//         NRF_LOG_INFO("End calibration process");
//         p_profile->_cb.p_disp_cb->calib_stat = SHIFT_DISP_CALIB_NONE;

//         p_profile->evt_handler(p_profile, shift_event);
//     }
// }


static void ant_message_send(ant_shift_profile_t * p_profile)
{
    uint32_t err_code;
    uint8_t  p_message_payload[ANT_STANDARD_DATA_PAYLOAD_SIZE];

    sens_message_encode(p_profile, p_message_payload);
    err_code =
        sd_ant_broadcast_message_tx(p_profile->channel_number,
                                    sizeof (p_message_payload),
                                    p_message_payload);
    APP_ERROR_CHECK(err_code);
}


ret_code_t ant_shift_disp_open(ant_shift_profile_t * p_profile)
{
    NRF_LOG_INFO("ANT SHIFT %u open", p_profile->channel_number);
    return sd_ant_channel_open(p_profile->channel_number);
}


ret_code_t ant_shift_sens_open(ant_shift_profile_t * p_profile)
{
    // Fill tx buffer for the first frame
    ant_message_send(p_profile);

    NRF_LOG_INFO("ANT SHIFT %u open", p_profile->channel_number);
    return sd_ant_channel_open(p_profile->channel_number);
}


void ant_shift_sens_evt_handler(ant_evt_t * p_ant_event, void * p_context)
{
    ant_shift_profile_t * p_profile = ( ant_shift_profile_t *)p_context;

    if (p_ant_event->channel == p_profile->channel_number)
    {
        switch (p_ant_event->event)
        {
            case EVENT_TX:
                ant_message_send(p_profile);
                break;

            case EVENT_RX:
                if (p_ant_event->message.ANT_MESSAGE_ucMesgID == MESG_ACKNOWLEDGED_DATA_ID)
                {
                    sens_message_decode(p_profile, p_ant_event->message.ANT_MESSAGE_aucPayload);
                }
                break;

            default:
                // No implementation needed
                break;
        }
    }
}


void ant_shift_disp_evt_handler(ant_evt_t * p_ant_event, void * p_context)
{
    ant_shift_profile_t * p_profile = ( ant_shift_profile_t *)p_context;

    if (p_ant_event->channel == p_profile->channel_number)
    {
        switch (p_ant_event->event)
        {
            case EVENT_RX:

                if (p_ant_event->message.ANT_MESSAGE_ucMesgID == MESG_BROADCAST_DATA_ID
                 || p_ant_event->message.ANT_MESSAGE_ucMesgID == MESG_ACKNOWLEDGED_DATA_ID
                 || p_ant_event->message.ANT_MESSAGE_ucMesgID == MESG_BURST_DATA_ID)
                {
                    disp_message_decode(p_profile, p_ant_event->message.ANT_MESSAGE_aucPayload);
                }
                break;

            default:
                break;
        }
        // service_calib(p_profile, p_ant_event->event);
    }
}

#endif // NRF_MODULE_ENABLED(ANT_SHIFT)
