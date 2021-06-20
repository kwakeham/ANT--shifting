/**
 * Copyright (c) 2019 - 2021, Titan Lab Inc.
 *
 */

/**
 * @file
 * @defgroup ant_shift Bicycle Shift profile
 * @{
 * @ingroup ant_sdk_profiles
 * @brief This module implements the Bicycle Shift profile.
 *
 */

 #ifndef ANT_BICYCLE_POWER_H__
 #define ANT_BICYCLE_POWER_H__

#include <stdint.h>
#include <stdbool.h>
#include "ant_parameters.h"
#include "nrf_sdh_ant.h"
#include "ant_channel_config.h"
#include "ant_shift_pages.h"
#include "sdk_errors.h"

#define SHIFT_DEVICE_TYPE            0x22u               ///< Device type reserved for ANT+ Shifting.
#define SHIFT_ANTPLUS_RF_FREQ        0x39u               ///< Frequency, decimal 57 (2457 MHz).
#define SHIFT_MSG_PERIOD             8192u               ///< Message period, decimal 8192 (4.000 Hz).

#define SHIFT_EXT_ASSIGN             0x00                ///< ANT ext assign (see Ext. Assign Channel Parameters in ant_parameters.h: @ref ant_parameters).
#define SHIFT_DISP_CHANNEL_TYPE      CHANNEL_TYPE_SLAVE  ///< Display Bicycle Shift channel type.
#define SHIFT_SENS_CHANNEL_TYPE      CHANNEL_TYPE_MASTER ///< Sensor Bicycle Shift channel type.


/**@brief Initialize an ANT channel configuration structure for the Bicycle Shift profile (Display).
 *
 * @param[in]  NAME                 Name of related instance.
 * @param[in]  CHANNEL_NUMBER       Number of the channel assigned to the profile instance.
 * @param[in]  TRANSMISSION_TYPE    Type of transmission assigned to the profile instance.
 * @param[in]  DEVICE_NUMBER        Number of the device assigned to the profile instance.
 * @param[in]  NETWORK_NUMBER       Number of the network assigned to the profile instance.
 */
#define SHIFT_DISP_CHANNEL_CONFIG_DEF(NAME,                                      \
                                     CHANNEL_NUMBER,                            \
                                     TRANSMISSION_TYPE,                         \
                                     DEVICE_NUMBER,                             \
                                     NETWORK_NUMBER)                            \
static const ant_channel_config_t   CONCAT_2(NAME, _channel_shift_disp_config) = \
    {                                                                           \
        .channel_number    = (CHANNEL_NUMBER),                                  \
        .channel_type      = SHIFT_DISP_CHANNEL_TYPE,                            \
        .ext_assign        = SHIFT_EXT_ASSIGN,                                   \
        .rf_freq           = SHIFT_ANTPLUS_RF_FREQ,                              \
        .transmission_type = (TRANSMISSION_TYPE),                               \
        .device_type       = SHIFT_DEVICE_TYPE,                                  \
        .device_number     = (DEVICE_NUMBER),                                   \
        .channel_period    = SHIFT_MSG_PERIOD,                                   \
        .network_number    = (NETWORK_NUMBER),                                  \
    }
#define SHIFT_DISP_CHANNEL_CONFIG(NAME) &CONCAT_2(NAME, _channel_shift_disp_config)

/**@brief Initialize an ANT channel configuration structure for the Bicycle Shift profile (Sensor).
 *
 * @param[in]  NAME                 Name of related instance.
 * @param[in]  CHANNEL_NUMBER       Number of the channel assigned to the profile instance.
 * @param[in]  TRANSMISSION_TYPE    Type of transmission assigned to the profile instance.
 * @param[in]  DEVICE_NUMBER        Number of the device assigned to the profile instance.
 * @param[in]  NETWORK_NUMBER       Number of the network assigned to the profile instance.
 */
#define SHIFT_SENS_CHANNEL_CONFIG_DEF(NAME,                                      \
                                     CHANNEL_NUMBER,                            \
                                     TRANSMISSION_TYPE,                         \
                                     DEVICE_NUMBER,                             \
                                     NETWORK_NUMBER)                            \
static const ant_channel_config_t   CONCAT_2(NAME, _channel_shift_sens_config) = \
    {                                                                           \
        .channel_number    = (CHANNEL_NUMBER),                                  \
        .channel_type      = SHIFT_SENS_CHANNEL_TYPE,                            \
        .ext_assign        = SHIFT_EXT_ASSIGN,                                   \
        .rf_freq           = SHIFT_ANTPLUS_RF_FREQ,                              \
        .transmission_type = (TRANSMISSION_TYPE),                               \
        .device_type       = SHIFT_DEVICE_TYPE,                                  \
        .device_number     = (DEVICE_NUMBER),                                   \
        .channel_period    = SHIFT_MSG_PERIOD,                                   \
        .network_number    = (NETWORK_NUMBER),                                  \
    }
#define SHIFT_SENS_CHANNEL_CONFIG(NAME) &CONCAT_2(NAME, _channel_shift_sens_config)

/**@brief Initialize an ANT profile configuration structure for the SHIFT profile (Display).
 *
 * @param[in]  NAME                 Name of related instance.
 * @param[in]  EVT_HANDLER          Event handler to be called for handling events in the SHIFT profile.
 */
#define SHIFT_DISP_PROFILE_CONFIG_DEF(NAME,                                          \
                                     EVT_HANDLER)                                   \
static ant_shift_disp_cb_t            CONCAT_2(NAME, _shift_disp_cb);                 \
static const ant_shift_disp_config_t  CONCAT_2(NAME, _profile_shift_disp_config) =    \
    {                                                                               \
        .p_cb               = &CONCAT_2(NAME, _shift_disp_cb),                       \
        .evt_handler        = (EVT_HANDLER),                                        \
    }
#define SHIFT_DISP_PROFILE_CONFIG(NAME) &CONCAT_2(NAME, _profile_shift_disp_config)


/**@brief Initialize an ANT profile configuration structure for the SHIFT profile (Sensor).
 *
 * @param[in]  NAME                 Name of related instance.
 * @param[in]  TORQUE_USED          Determines whether the torque page is included.
 * @param[in]  CALIB_HANDLER        Event handler to be called for handling calibration requests.
 * @param[in]  EVT_HANDLER          Event handler to be called for handling events in the SHIFT profile.
 */
#define SHIFT_SENS_PROFILE_CONFIG_DEF(NAME,                                          \
                                     TORQUE_USED,                                   \
                                     CALIB_HANDLER,                                 \
                                     EVT_HANDLER)                                   \
static ant_shift_sens_cb_t            CONCAT_2(NAME, _shift_sens_cb);                 \
static const ant_shift_sens_config_t  CONCAT_2(NAME, _profile_shift_sens_config) =    \
    {                                                                               \
        .torque_use         = (TORQUE_USED),                                        \
        .calib_handler      = (CALIB_HANDLER),                                      \
        .p_cb               = &CONCAT_2(NAME, _shift_sens_cb),                       \
        .evt_handler        = (EVT_HANDLER),                                        \
    }
#define SHIFT_SENS_PROFILE_CONFIG(NAME) &NAME##_profile_shift_sens_config



/**@brief Shift page number type. */
typedef enum
{
    ANT_SHIFT_PAGE_1  = 1,  ///< Shift System Status.
    ANT_SHIFT_PAGE_78 = 78, //Multi-component System Manufacturer’s Information (0x4E)
    ANT_SHIFT_PAGE_79 = 79, //Multi-component System Product Information (0x4F)
    ANT_SHIFT_PAGE_80 = ANT_COMMON_PAGE_80,
    ANT_SHIFT_PAGE_81 = ANT_COMMON_PAGE_81,
    ANT_SHIFT_PAGE_82 = 82, //Battery Status (0x52)
} ant_shift_page_t;

/**@brief SHIFT profile event type. */
typedef enum
{
    ANT_SHIFT_PAGE_1_UPDATED  = ANT_SHIFT_PAGE_1,  ///< Data page 1 and speed have been updated (Display) or sent (Sensor).
    ANT_SHIFT_PAGE_78_UPDATED = ANT_SHIFT_PAGE_78, ///< Data page 78 (muticomponent mfg info) has been updated (Display) or sent (Sensor).
    ANT_SHIFT_PAGE_79_UPDATED = ANT_SHIFT_PAGE_79, ///< Data page 79 (multi component prod info) has been updated (Display) or sent (Sensor).
    ANT_SHIFT_PAGE_80_UPDATED = ANT_SHIFT_PAGE_80, ///< Data page 80 has been updated (Display) or sent (Sensor).
    ANT_SHIFT_PAGE_81_UPDATED = ANT_SHIFT_PAGE_81, ///< Data page 81 has been updated (Display) or sent (Sensor).
    ANT_SHIFT_PAGE_82_UPDATED = ANT_SHIFT_PAGE_82, ///< Data page (battery info) 82 has been updated (Display) or sent (Sensor).
} ant_shift_evt_t;

// Forward declaration of the ant_shift_profile_t type.
typedef struct ant_shift_profile_s ant_shift_profile_t;

/**@brief SHIFT event handler type. */
typedef void (* ant_shift_evt_handler_t) (ant_shift_profile_t *, ant_shift_evt_t);


#include "ant_shift_local.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Bicycle Shift Sensor configuration structure. */
typedef struct
{
    ant_shift_sens_cb_t     * p_cb;          ///< Pointer to the data buffer for internal use.
    ant_shift_evt_handler_t   evt_handler;   ///< Event handler to be called for handling events in the SHIFT profile.
} ant_shift_sens_config_t;

/**@brief Bicycle Shift Display configuration structure. */
typedef struct
{
    ant_shift_disp_cb_t   * p_cb;            ///< Pointer to the data buffer for internal use.
    ant_shift_evt_handler_t evt_handler;     ///< Event handler to be called for handling events in the SHIFT profile.
} ant_shift_disp_config_t;

/**@brief Bicycle Shift profile structure. */
struct ant_shift_profile_s
{
    uint8_t                  channel_number; ///< Channel number assigned to the profile.
    union {
        ant_shift_disp_cb_t * p_disp_cb;
        ant_shift_sens_cb_t * p_sens_cb;
    } _cb;                                ///< Pointer to internal control block.
    ant_shift_evt_handler_t   evt_handler;    ///< Event handler to be called for handling events in the SHIFT profile.
    ant_shift_page1_data_t    page_1;         ///< Page 1.
    ant_common_page80_data_t page_80;        ///< Page 80.
    ant_common_page81_data_t page_81;        ///< Page 81.
    ant_shift_common_data_t   common;         ///< SHIFT common data.
    ant_shift_page82_data_t  page_82;         ///< Page 1. Battery
};

/** @name Defines for accessing ant_shift_profile_t member variables
   @{ */
#define SHIFT_PROFILE_current_gear_rear                     page_1.current.gear_rear
#define SHIFT_PROFILE_current_gear_front                    page_1.current.gear_front
#define SHIFT_PROFILE_current_total_rear                    page_1.total.gear_rear 
#define SHIFT_PROFILE_current_total_front                   page_1.total.gear_front        
#define SHIFT_PROFILE_invalid_inboard_shift_count_rear      page_1.invalid.rear.inboard_shift_count
#define SHIFT_PROFILE_invalid_outboard_shift_count_rear     page_1.invalid.rear.outboard_shift_count
#define SHIFT_PROFILE_invalid_inboard_shift_count_front     page_1.invalid.front.inboard_shift_count
#define SHIFT_PROFILE_invalid_outboard_shift_count_front    page_1.invalid.front.outboard_shift_count
#define SHIFT_PROFILE_shift_failure_count_rear              page_1.shift_failure_count.rear
#define SHIFT_PROFILE_shift_failure_count_front             page_1.shift_failure_count.front

#define SHIFT_PROFILE_number_batteries                      page_82.battery.number
#define SHIFT_PROFILE_battery_identifier                    page_82.battery.identifier
#define SHIFT_PROFILE_battery_operating_time                page_82.battery.operating_time
#define SHIFT_PROFILE_battery_voltage                       page_82.battery.voltage
#define SHIFT_PROFILE_battery_status                        page_82.battery.status
#define SHIFT_PROFILE_time_resolution                       page_82.battery.time_resolution

#define SHIFT_PROFILE_manuf_id                    page_80.manuf_id
#define SHIFT_PROFILE_hw_revision                 page_80.hw_revision
#define SHIFT_PROFILE_manufacturer_id             page_80.manufacturer_id
#define SHIFT_PROFILE_model_number                page_80.model_number
#define SHIFT_PROFILE_sw_revision_minor           page_81.sw_revision_minor
#define SHIFT_PROFILE_sw_revision_major           page_81.sw_revision_major
#define SHIFT_PROFILE_serial_number               page_81.serial_number
/** @} */

/**@brief Function for initializing the ANT Bicycle Shift Display profile instance.
 *
 * @param[in]  p_profile        Pointer to the profile instance.
 * @param[in]  p_channel_config Pointer to the ANT channel configuration structure.
 * @param[in]  p_disp_config    Pointer to the Bicycle Shift Display configuration structure.
 *
 * @retval     NRF_SUCCESS      If initialization was successful. Otherwise, an error code is returned.
 */
ret_code_t ant_shift_disp_init(ant_shift_profile_t           * p_profile,
                              ant_channel_config_t const   * p_channel_config,
                              ant_shift_disp_config_t const * p_disp_config);

/**@brief Function for initializing the ANT Bicycle Shift Sensor profile instance.
 *
 * @param[in]  p_profile        Pointer to the profile instance.
 * @param[in]  p_channel_config Pointer to the ANT channel configuration structure.
 * @param[in]  p_sens_config    Pointer to the Bicycle Shift Sensor configuration structure.
 *
 * @retval     NRF_SUCCESS      If initialization was successful. Otherwise, an error code is returned.
 */
ret_code_t ant_shift_sens_init(ant_shift_profile_t           * p_profile,
                              ant_channel_config_t const   * p_channel_config,
                              ant_shift_sens_config_t const * p_sens_config);

/**@brief Function for opening the profile instance channel for ANT SHIFT Display.
 *
 * Before calling this function, pages should be configured.
 *
 * @param[in]  p_profile        Pointer to the profile instance.
 *
 * @retval     NRF_SUCCESS      If the channel was successfully opened. Otherwise, an error code is returned.
 */
ret_code_t ant_shift_disp_open(ant_shift_profile_t * p_profile);

/**@brief Function for opening the profile instance channel for ANT SHIFT Sensor.
 *
 * Before calling this function, pages should be configured.
 *
 * @param[in]  p_profile        Pointer to the profile instance.
 *
 * @retval     NRF_SUCCESS      If the channel was successfully opened. Otherwise, an error code is returned.
 */
ret_code_t ant_shift_sens_open(ant_shift_profile_t * p_profile);

/** @name Functions: Sensor calibration API
 * @{
 */

/** @brief Function for initializing the response for a calibration request.
 *
 *  This function should be used to signal the status of the calibration procedure to the ANT profile layer .
 *
 *  @param[in] p_profile   Pointer to the profile instance.
 */
void ant_shift_calib_response(ant_shift_profile_t * p_profile);
/** @} */


/**@brief Function for handling the Sensor ANT events.
 *
 * @details This function handles all events from the ANT stack that are of interest to the Bicycle Shift Display profile.
 *
 * @param[in]   p_ant_evt     Event received from the ANT stack.
 * @param[in]   p_context       Pointer to the profile instance.
 */
void ant_shift_sens_evt_handler(ant_evt_t * p_ant_evt, void * p_context);

/**@brief Function for handling the Display ANT events.
 *
 * @details This function handles all events from the ANT stack that are of interest to the Bicycle Shift Display profile.
 *
 * @param[in]   p_ant_evt     Event received from the ANT stack.
 * @param[in]   p_context       Pointer to the profile instance.
 */
void ant_shift_disp_evt_handler(ant_evt_t * p_ant_evt, void * p_context);

/** @name Functions: Display calibration API
 * @{
 */

/**@brief Function for initializing the calibration request process from the Bicycle Shift Display side.
 *
 * @details This function requests a transfer to the Sensor and starts watching for the calibration response.
 * If a calibration response has already been requested, the function ignores the new request and returns NRF_SUCCESS.
 *
 * @param [in]   p_profile       Pointer to the profile instance.
 * @param [in]   p_page_1        Pointer to the prepared page 1.
 *
 * @return Values returned by the @ref sd_ant_acknowledge_message_tx SVC callback.
 */
uint32_t ant_shift_calib_request(ant_shift_profile_t * p_profile, ant_shift_page1_data_t * p_page_1);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif // ANT_BICYCLE_POWER_H__

