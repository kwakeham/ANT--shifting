/**
* Copyright (c) 2019 - 2021, Titan Lab Inc.
 *
 */
#ifndef ANT_SHIFT_PAGE_82_H__
#define ANT_SHIFT_PAGE_82_H__

/** @file
 *
 * @defgroup ant_sdk_profiles_shift_page82 Shift profile page 82
 * @{
 * @ingroup ant_sdk_profiles_shift_pages
 */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Shift profile battery status.
 *
 * This enum represents possible battery status values for the ANT SHIFT profile.
 */typedef enum
{
    RESERVED0                 = 0,    ///< Reserved.
    SHIFT_BAT_STATUS_NEW      = 1,    ///< Battery status: new.
    SHIFT_BAT_STATUS_GOOD     = 2,    ///< Battery status: good.
    SHIFT_BAT_STATUS_OK       = 3,    ///< Battery status: ok.
    SHIFT_BAT_STATUS_LOW      = 4,    ///< Battery status: low.
    SHIFT_BAT_STATUS_CRITICAL = 5,    ///< Battery status: critical.
    SHIFT_BAT_STATUS_CHARGING = 6,    ///< Battery status: Charging
    SHIFT_BAT_STATUS_INVALID  = 7     ///< Invalid battery status.
} ant_shift_bat_status_t;

typedef struct
{
    uint8_t page82_reserved;    ///< Reserved: 0xFF, to be used in future
    struct
    {
        uint8_t number                    : 4;
        uint8_t identifier                : 4;
        uint32_t operating_time;                    //operating time in seconds, NOT the ANT+ time
        uint16_t voltage;                           //1/256volts
        uint8_t status                    : 3;
        bool time_resolution              : 1;      //Leaving this in incase of checks
    }battery;

} ant_shift_page82_data_t;


/**@brief Initialize page 82.
 */
#define DEFAULT_ANT_SHIFT_PAGE82()                              \
    (ant_shift_page82_data_t)                                   \
    {                                                          \
        .battery.number                         = 1,           \
        .battery.identifier                     = 0,           \
        .battery.operating_time                 = 0,           \
        .battery.voltage                        = 0,           \
        .battery.status                         = 0,           \
        .battery.time_resolution                = 0,           \
    }


/**@brief Function for encoding page 16.
 *
 * @param[in]  p_page_data      Pointer to the page data.
 * @param[out] p_page_buffer    Pointer to the data buffer.
 */
void ant_shift_page_82_encode(uint8_t                      * p_page_buffer,
                             ant_shift_page82_data_t const * p_page_data);

/**@brief Function for decoding page 16.
 *
 * @param[in]  p_page_buffer    Pointer to the data buffer.
 * @param[out] p_page_data      Pointer to the page data.
 */
void ant_shift_page_82_decode(uint8_t const          * p_page_buffer,
                             ant_shift_page82_data_t * p_page_data);


#ifdef __cplusplus
}
#endif

#endif // ANT_SHIFT_PAGE_16_H__
/** @} */
