/**
* Copyright (c) 2019 - 2022, Titan Lab Inc.
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
typedef struct
{
    uint8_t  update_event_count;    ///< Event counter increments with each shift event.
    uint8_t  page82_reserved;    ///< Reserved: 0xFF, to be used in future
    uint8_t number_batteries                    : 4;
    uint8_t battery_identifier                  : 4;

    uint8_t battery_operating_time_lsb;
    uint8_t battery_operating_time;
    uint8_t battery_operating_time_msb;
    uint8_t battery_fractional_voltage;
    uint8_t battery_descriptive_field  : 4;

} ant_shift_page1_data_t;


/**@brief Initialize page 1.
 */
#define DEFAULT_ANT_SHIFT_PAGE1()                              \
    (ant_shift_page1_data_t)                                   \
    {                                                          \
        .update_event_count                     = 0,           \
        .page82_reserved                        = 0xFF,        \
        .number_batteries                       = 1,           \
        .battery_identifier                     = 0,           \
        .battery_operating_time_lsb             = 0,           \
        .battery_operating_time                 = 0,           \
        .battery_operating_time_msb             = 0,           \
        .battery_fractional_voltage             = 0,           \
        .battery_descriptive_field              = 0,           \

    }


/**@brief Function for encoding page 16.
 *
 * @param[in]  p_page_data      Pointer to the page data.
 * @param[out] p_page_buffer    Pointer to the data buffer.
 */
void ant_shift_page_1_encode(uint8_t                      * p_page_buffer,
                             ant_shift_page1_data_t const * p_page_data);

/**@brief Function for decoding page 16.
 *
 * @param[in]  p_page_buffer    Pointer to the data buffer.
 * @param[out] p_page_data      Pointer to the page data.
 */
void ant_shift_page_1_decode(uint8_t const          * p_page_buffer,
                             ant_shift_page1_data_t * p_page_data);


#ifdef __cplusplus
}
#endif

#endif // ANT_SHIFT_PAGE_16_H__
/** @} */
