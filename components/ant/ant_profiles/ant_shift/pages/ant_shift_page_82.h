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
    uint8_t  page1_reserved;    ///< Reserved: 0xFF, to be used in future
    uint8_t current_gear_rear                   : 5;
    uint8_t current_gear_front                  : 3;

    uint8_t total_gear_rear                     : 5;
    uint8_t total_gear_front                    : 3;

    uint8_t invalid_inboard_shift_count_rear    : 4;
    uint8_t invalid_outboard_shift_count_rear   : 4;

    uint8_t invalid_inboard_shift_count_front   : 4;
    uint8_t invalid_outboard_shift_count_front  : 4;

    uint8_t shift_failure_count_rear   : 4;
    uint8_t shift_failure_count_front  : 4;

} ant_shift_page1_data_t;


/**@brief Initialize page 1.
 */
#define DEFAULT_ANT_SHIFT_PAGE1()                               \
    (ant_shift_page1_data_t)                                    \
    {                                                           \
        .update_event_count                      = 0,           \
        .page1_reserved                          = 0xFF,        \
        .current_gear_rear                  = 0,           \
        .current_gear_front                 = 0,           \
        .total_gear_rear                    = 0,           \
        .total_gear_front                   = 0,           \
        .invalid_inboard_shift_count_rear   = 0,           \
        .invalid_outboard_shift_count_rear  = 0,           \
        .invalid_inboard_shift_count_front  = 0,           \
        .invalid_outboard_shift_count_front = 0,           \
        .shift_failure_count_rear = 0,                     \
        .shift_failure_count_front = 0,                    \
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
