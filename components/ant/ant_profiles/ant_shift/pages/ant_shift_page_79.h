/**
* Copyright (c) 2019 - 2021, Titan Lab Inc.
 *
 */
#ifndef ANT_SHIFT_PAGE_79_H__
#define ANT_SHIFT_PAGE_79_H__

/** @file
 *
 * @defgroup ant_sdk_profiles_shift_page79 Shift profile page 79
 * @{
 * @ingroup ant_sdk_profiles_shift_pages
 */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    struct
    {
        uint8_t number                    : 4;
        uint8_t identifier                : 4;
        uint8_t sw_revision_supplemental;
        uint8_t sw_revision_main;
        uint32_t serial_number;
    }component;

} ant_shift_page79_data_t;


/**@brief Initialize page 79.
 */
#define DEFAULT_ANT_SHIFT_PAGE79()                              \
    (ant_shift_page79_data_t)                                   \
    {                                                          \
        .component.number                      = 1,           \
        .component.identifier                  = 0,           \
        .component.sw_revision_supplemental    = 0,           \
        .component.sw_revision_main            = 0,           \
        .component.serial_number               = 0,           \
    }


/**@brief Function for encoding page 16.
 *
 * @param[in]  p_page_data      Pointer to the page data.
 * @param[out] p_page_buffer    Pointer to the data buffer.
 */
void ant_shift_page_79_encode(uint8_t                      * p_page_buffer,
                             ant_shift_page79_data_t const * p_page_data);

/**@brief Function for decoding page 16.
 *
 * @param[in]  p_page_buffer    Pointer to the data buffer.
 * @param[out] p_page_data      Pointer to the page data.
 */
void ant_shift_page_79_decode(uint8_t const          * p_page_buffer,
                             ant_shift_page79_data_t * p_page_data);


#ifdef __cplusplus
}
#endif

#endif // ANT_SHIFT_PAGE_16_H__
/** @} */
