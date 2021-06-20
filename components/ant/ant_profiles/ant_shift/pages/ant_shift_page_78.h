/**
* Copyright (c) 2019 - 2021, Titan Lab Inc.
 *
 */
#ifndef ANT_SHIFT_PAGE_78_H__
#define ANT_SHIFT_PAGE_78_H__

/** @file
 *
 * @defgroup ant_sdk_profiles_shift_page78 Shift profile page 78
 * @{
 * @ingroup ant_sdk_profiles_shift_pages
 */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    uint8_t page78_reserved;    ///< Reserved: 0xFF, to be used in future
    struct
    {
        uint8_t number                    : 4;
        uint8_t identifier                : 4;
        uint8_t hw_revision;
        uint16_t mfg_id;
        uint16_t model_number;
    }component;

} ant_shift_page78_data_t;


/**@brief Initialize page 78.
 */
#define DEFAULT_ANT_SHIFT_PAGE78()                              \
    (ant_shift_page78_data_t)                                   \
    {                                                          \
        .component.number                      = 1,           \
        .component.identifier                  = 0,           \
        .component.hw_revision                 = 0,           \
        .component.mfg_id                      = 0,           \
        .component.model_number                = 0,           \
    }


/**@brief Function for encoding page 16.
 *
 * @param[in]  p_page_data      Pointer to the page data.
 * @param[out] p_page_buffer    Pointer to the data buffer.
 */
void ant_shift_page_78_encode(uint8_t                      * p_page_buffer,
                             ant_shift_page78_data_t const * p_page_data);

/**@brief Function for decoding page 16.
 *
 * @param[in]  p_page_buffer    Pointer to the data buffer.
 * @param[out] p_page_data      Pointer to the page data.
 */
void ant_shift_page_78_decode(uint8_t const          * p_page_buffer,
                             ant_shift_page78_data_t * p_page_data);


#ifdef __cplusplus
}
#endif

#endif // ANT_SHIFT_PAGE_16_H__
/** @} */
