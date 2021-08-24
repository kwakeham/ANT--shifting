/**
 * This software is subject to the ANT+ Shared Source License
 * www.thisisant.com/swlicenses
 * Copyright (c) Garmin Canada Inc. 2012
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 *    1) Redistributions of source code must retain the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer.
 *
 *    2) Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *
 *    3) Neither the name of Garmin nor the names of its
 *       contributors may be used to endorse or promote products
 *       derived from this software without specific prior
 *       written permission.
 *
 * The following actions are prohibited:
 *
 *    1) Redistribution of source code containing the ANT+ Network
 *       Key. The ANT+ Network Key is available to ANT+ Adopters.
 *       Please refer to http://thisisant.com to become an ANT+
 *       Adopter and access the key. 
 *
 *    2) Reverse engineering, decompilation, and/or disassembly of
 *       software provided in binary form under this license.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE HEREBY
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES(INCLUDING, 
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; DAMAGE TO ANY DEVICE, LOSS OF USE, DATA, OR 
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN 
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED 
 * OF THE POSSIBILITY OF SUCH DAMAGE. SOME STATES DO NOT ALLOW 
 * THE EXCLUSION OF INCIDENTAL OR CONSEQUENTIAL DAMAGES, SO THE
 * ABOVE LIMITATIONS MAY NOT APPLY TO YOU.
 *
 */
/**@file
 * @defgroup ant_shift_sensor_main ANT Bicycle Power sensor example
 * @{
 * @ingroup nrf_ant_bicycle_power
 *
 * @brief Example of ANT Bicycle Power profile display.
 *
 * Before compiling this example for NRF52, complete the following steps:
 * - Download the S212 SoftDevice from <a href="https://www.thisisant.com/developer/components/nrf52832" target="_blank">thisisant.com</a>.
 * - Extract the downloaded zip file and copy the S212 SoftDevice headers to <tt>\<InstallFolder\>/components/softdevice/s212/headers</tt>.
 * If you are using Keil packs, copy the files into a @c headers folder in your example folder.
 * - Make sure that @ref ANT_LICENSE_KEY in @c nrf_sdm.h is uncommented.
 */

#include <stdio.h>
#include "nrf.h"
#include "bsp.h"
#include "hardfault.h"
#include "app_error.h"
#include "app_timer.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_sdh.h"
#include "nrf_sdh_ant.h"
#include "ant_key_manager.h"
#include "ant_shift.h"
#include "ant_shift_simulator.h"
#include "ant_state_indicator.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#define MODIFICATION_TYPE_BUTTON 0 /* predefined value, MUST REMAIN UNCHANGED */
#define MODIFICATION_TYPE_AUTO   1 /* predefined value, MUST REMAIN UNCHANGED */

#if (MODIFICATION_TYPE != MODIFICATION_TYPE_BUTTON) \
    && (MODIFICATION_TYPE != MODIFICATION_TYPE_AUTO)
    #error Unsupported value of MODIFICATION_TYPE.
#endif

/** @snippet [ANT SHIFT TX Instance] */
void ant_shift_evt_handler(ant_shift_profile_t * p_profile, ant_shift_evt_t event);
void ant_shift_calib_handler(ant_shift_profile_t * p_profile, ant_shift_page1_data_t * p_page1);

SHIFT_SENS_CHANNEL_CONFIG_DEF(m_ant_shift,
                             SHIFT_CHANNEL_NUM,
                             CHAN_ID_TRANS_TYPE,
                             CHAN_ID_DEV_NUM,
                             ANTPLUS_NETWORK_NUM);
SHIFT_SENS_PROFILE_CONFIG_DEF(m_ant_shift,
                             ant_shift_evt_handler);

static ant_shift_profile_t m_ant_shift;


NRF_SDH_ANT_OBSERVER(m_ant_observer, ANT_SHIFT_ANT_OBSERVER_PRIO,
                     ant_shift_sens_evt_handler, &m_ant_shift);

/** @snippet [ANT SHIFT TX Instance] */

static ant_shift_simulator_t  m_ant_shift_simulator;

/**@brief Function for handling bsp events.
 */
/** @snippet [ANT SHIFT simulator button] */
void bsp_evt_handler(bsp_event_t event)
{
    switch (event)
    {
        case BSP_EVENT_KEY_0:
            ant_shift_simulator_increment(&m_ant_shift_simulator);
            break;

        case BSP_EVENT_KEY_1:
            ant_shift_simulator_decrement(&m_ant_shift_simulator);
            break;

        case BSP_EVENT_KEY_2:
            ant_shift_calib_response(&m_ant_shift);
            break;

        default:
            break;
    }
}
/** @snippet [ANT SHIFT simulator button] */

/**@brief Function for handling ANT SHIFT events.
 */
/** @snippet [ANT SHIFT simulator call] */
void ant_shift_evt_handler(ant_shift_profile_t * p_profile, ant_shift_evt_t event)
{
    nrf_pwr_mgmt_feed();

    switch (event)
    {
        case ANT_SHIFT_PAGE_1_UPDATED:
            /* fall through */
        case ANT_SHIFT_PAGE_78_UPDATED:
            /* fall through */
        case ANT_SHIFT_PAGE_79_UPDATED:
            /* fall through */
        case ANT_SHIFT_PAGE_80_UPDATED:
            /* fall through */
        case ANT_SHIFT_PAGE_81_UPDATED:
            /* fall through */
        case ANT_SHIFT_PAGE_82_UPDATED:
            /* fall through */
            // ant_shift_simulator_one_iteration(&m_ant_shift_simulator, event);
            break;

        default:
            break;
    }
}
/** @snippet [ANT SHIFT simulator call] */

// /**@brief Function for handling ANT SHIFT events.
//  */
// /** @snippet [ANT SHIFT calibration] */
// void ant_shift_calib_handler(ant_shift_profile_t * p_profile, ant_shift_page1_data_t * p_page1)
// {
//     switch (p_page1->calibration_id)
//     {
//         case ANT_SHIFT_CALIB_ID_MANUAL:
//             m_ant_shift.SHIFT_PROFILE_calibration_id     = ANT_SHIFT_CALIB_ID_MANUAL_SUCCESS;
//             m_ant_shift.SHIFT_PROFILE_general_calib_data = CALIBRATION_DATA;
//             break;

//         case ANT_SHIFT_CALIB_ID_AUTO:
//             m_ant_shift.SHIFT_PROFILE_calibration_id     = ANT_SHIFT_CALIB_ID_MANUAL_SUCCESS;
//             m_ant_shift.SHIFT_PROFILE_auto_zero_status   = p_page1->auto_zero_status;
//             m_ant_shift.SHIFT_PROFILE_general_calib_data = CALIBRATION_DATA;
//             break;

//         case ANT_SHIFT_CALIB_ID_CUSTOM_REQ:
//             m_ant_shift.SHIFT_PROFILE_calibration_id = ANT_SHIFT_CALIB_ID_CUSTOM_REQ_SUCCESS;
//             memcpy(m_ant_shift.SHIFT_PROFILE_custom_calib_data, p_page1->data.custom_calib,
//                    sizeof (m_ant_shift.SHIFT_PROFILE_custom_calib_data));
//             break;

//         case ANT_SHIFT_CALIB_ID_CUSTOM_UPDATE:
//             m_ant_shift.SHIFT_PROFILE_calibration_id = ANT_SHIFT_CALIB_ID_CUSTOM_UPDATE_SUCCESS;
//             memcpy(m_ant_shift.SHIFT_PROFILE_custom_calib_data, p_page1->data.custom_calib,
//                    sizeof (m_ant_shift.SHIFT_PROFILE_custom_calib_data));
//             break;

//         default:
//             break;
//     }
// }
// /** @snippet [ANT SHIFT calibration] */

/**
 * @brief Function for setup all thinks not directly associated with ANT stack/protocol.
 * @desc Initialization of: @n
 *         - app_timer, pre-setup for bsp.
 *         - bsp for signaling LEDs and user buttons.
 */
static void utils_setup(void)
{
    // Initialize and start a single continuous mode timer, which is used to update the event time
    // on the main data page.
    ret_code_t err_code = app_timer_init();
    APP_ERROR_CHECK(err_code);

    err_code = nrf_pwr_mgmt_init();
    APP_ERROR_CHECK(err_code);

    err_code = bsp_init(BSP_INIT_LEDS | BSP_INIT_BUTTONS,
                        bsp_evt_handler);
    APP_ERROR_CHECK(err_code);

    err_code = ant_state_indicator_init(m_ant_shift.channel_number, SHIFT_SENS_CHANNEL_TYPE);
    APP_ERROR_CHECK(err_code);
}

/**
 *@brief Function for initializing logging.
 */
static void log_init(void)
{
    ret_code_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);

    NRF_LOG_DEFAULT_BACKENDS_INIT();
}

/**@brief Function for the SHIFT simulator initialization.
 */
void simulator_setup(void)
{
    /** @snippet [ANT SHIFT simulator init] */
    const ant_shift_simulator_cfg_t simulator_cfg =
    {
        .p_profile   = &m_ant_shift,
        .sensor_type = (ant_shift_torque_t)(SENSOR_TYPE),
    };
    /** @snippet [ANT SHIFT simulator init] */

#if MODIFICATION_TYPE == MODIFICATION_TYPE_AUTO
    /** @snippet [ANT SHIFT simulator auto init] */
    ant_shift_simulator_init(&m_ant_shift_simulator, &simulator_cfg, true);
    /** @snippet [ANT SHIFT simulator auto init] */
#else
    /** @snippet [ANT SHIFT simulator button init] */
    ant_shift_simulator_init(&m_ant_shift_simulator, &simulator_cfg, false);
    /** @snippet [ANT SHIFT simulator button init] */
#endif
}

/**
 * @brief Function for ANT stack initialization.
 *
 * @details Initializes the SoftDevice and the ANT event interrupt.
 */
static void softdevice_setup(void)
{
    ret_code_t err_code = nrf_sdh_enable_request();
    APP_ERROR_CHECK(err_code);

    ASSERT(nrf_sdh_is_enabled());

    err_code = nrf_sdh_ant_enable();
    APP_ERROR_CHECK(err_code);

    err_code = ant_plus_key_set(ANTPLUS_NETWORK_NUM);
    APP_ERROR_CHECK(err_code);
}

/**
 * @brief Function for Bicycle Power profile initialization.
 *
 * @details Initializes the Bicycle Power profile and open ANT channel.
 */
static void profile_setup(void)
{
/** @snippet [ANT SHIFT TX Profile Setup] */
    ret_code_t err_code;

    err_code = ant_shift_sens_init(&m_ant_shift,
                                  SHIFT_SENS_CHANNEL_CONFIG(m_ant_shift),
                                  SHIFT_SENS_PROFILE_CONFIG(m_ant_shift));
    APP_ERROR_CHECK(err_code);

    // fill manufacturer's common data page.
    m_ant_shift.page_80 = ANT_COMMON_page80(SHIFT_HW_REVISION,
                                           SHIFT_MANUFACTURER_ID,
                                           SHIFT_MODEL_NUMBER);
    // fill product's common data page.
    m_ant_shift.page_81 = ANT_COMMON_page81(SHIFT_SW_REVISION_MAJOR,
                                           SHIFT_SW_REVISION_MINOR,
                                           SHIFT_SERIAL_NUMBER);

    err_code = ant_shift_sens_open(&m_ant_shift);
    APP_ERROR_CHECK(err_code);

    err_code = ant_state_indicator_channel_opened();
    APP_ERROR_CHECK(err_code);
/** @snippet [ANT SHIFT TX Profile Setup] */
}

/**@brief Function for application main entry, does not return.
 */
int main(void)
{
    log_init();
    utils_setup();
    softdevice_setup();
    simulator_setup();
    profile_setup();

    NRF_LOG_INFO("ANT+ Bicycle Power TX example started.");

    for (;;)
    {
        NRF_LOG_FLUSH();
        nrf_pwr_mgmt_run();
    }
}
