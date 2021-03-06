/**
 * Copyright (c) 2019 - 2021, Titan Lab Inc.
 *
 */
#ifndef ANT_SHIFT_PAGE_1_H__
#define ANT_SHIFT_PAGE_1_H__

/** @file
 *
 * @defgroup ant_sdk_profiles_shift_page1 shift profile page 1
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
    struct 
    {
        uint8_t gear_rear                   : 5;
        uint8_t gear_front                  : 3;
    }current;
    struct 
    {
        uint8_t gear_rear                     : 5;
        uint8_t gear_front                    : 3;
    }total;
    struct 
    {
        struct 
        {
            uint8_t inboard_shift_count    : 4;
            uint8_t outboard_shift_count   : 4;
        }rear;
        struct 
        {
            uint8_t inboard_shift_count   : 4;
            uint8_t outboard_shift_count  : 4;
        }front;
    }invalid;

    struct 
    {
    uint8_t rear   : 4;
    uint8_t front  : 4;
    }shift_failure_count;
} ant_shift_page1_data_t;


/**@brief Initialize page 1.
 */
#define DEFAULT_ANT_SHIFT_PAGE1()                               \
    (ant_shift_page1_data_t)                                    \
    {                                                           \
        .update_event_count                      = 0,           \
        .page1_reserved                          = 0xFF,        \
        .current.gear_rear                  = 0,           \
        .current.gear_front                 = 0,           \
        .total.gear_rear                    = 0,           \
        .total.gear_front                   = 0,           \
        .invalid.rear.inboard_shift_count   = 0,           \
        .invalid.rear.outboard_shift_count  = 0,           \
        .invalid.front.inboard_shift_count  = 0,           \
        .invalid.front.outboard_shift_count = 0,           \
        .shift_failure_count.rear = 0,                     \
        .shift_failure_count.front = 0,                    \
    }

/**@brief Function for encoding page 1.
 *
 * @param[in]  p_page_data      Pointer to the page data.
 * @param[out] p_page_buffer    Pointer to the data buffer.
 */
void ant_shift_page_1_encode(uint8_t                      * p_page_buffer,
                             ant_shift_page1_data_t const * p_page_data);

/**@brief Function for decoding page 1.
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
