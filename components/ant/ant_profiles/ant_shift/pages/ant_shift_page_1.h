/**
 * Copyright (c) 2015 - 2019, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#ifndef ANT_SHIFT_PAGE_1_H__
#define ANT_SHIFT_PAGE_1_H__

/** @file
 *
 * @defgroup ant_sdk_profiles_shift_page16 Bicycle Power profile page 16
 * @{
 * @ingroup ant_sdk_profiles_shift_pages
 */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Data structure for Shift  data page 1.
 *
 * @note This structure implements only page 1 specific data.
 */

// typedef struct
// {
//     uint8_t  update_event_count;    ///< Event counter increments with each shift event.
//     uint8_t  page1_reserved;    ///< Reserved: 0xFF, to be used in future
//     union
//     {
//         union
//         {
//             struct
//             {
//                 uint8_t rear : 5;       ///< Current gear of rear derailleur. 31 = Unknown Current Gear / Error
//                 uint8_t front : 3;      ///< Current gear of front derailleur. 7 = Unknown Current Gear / Error
//             } items;
//             uint8_t byte;
//         }current;
//         union
//         {
//             struct
//             {
//                 uint8_t rear : 5;       ///< Total number of gears in front derailleur. 0 = Unknown Gear Count / Error
//                 uint8_t front : 3;      ///< Total number of gears in rear derailleur. 0 = Unknown Gear Count / Error
//             } items;
//             uint8_t byte;
//         }total;
        
//         struct
//         {
//             uint8_t inboard : 4;    ///< Rear Derailleur Over Inboard Shift Count
//             uint8_t outboard : 4;   ///< Rear Derailleur Over Outboard Shift Count
//         } invalid_shift_count_rear;

//         struct
//         {
//             uint8_t inboard : 4;    ///< Front Derailleur Over Inboard Shift Count
//             uint8_t outboard : 4;   ///< Front Derailleur Over Outboard Shift Count
//         } invalid_shift_count_front;

//         struct
//         {
//             uint8_t front : 4;      ///< Rear Derailleur Shift Failure Count
//             uint8_t rear : 4;       ///< Front Derailleur Shift Failure Count
//         } shift_failure_count;
//     } gear;


// } ant_shift_page1_data_t;
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


/**@brief Initialize page 16.
 */

#define DEFAULT_ANT_SHIFT_PAGE13()                               \
    (ant_shift_page1_data_t)                                    \
    {                                                           \
        .update_event_count                      = 0,           \
        .page1_reserved                          = 0xFF,        \
        .gear.current.items.rear                  = 0,           \
        .gear.current.items.front                 = 0,           \
        .gear.total.items.rear                    = 0,           \
        .gear.total.items.front                   = 0,           \
        .gear.invalid_shift_count_rear.inboard   = 0,           \
        .gear.invalid_shift_count_rear.outboard  = 0,           \
        .gear.invalid_shift_count_front.inboard  = 0,           \
        .gear.invalid_shift_count_front.outboard = 0,           \
        .gear.shift_failure_count.rear = 0,                     \
        .gear.shift_failure_count.front = 0,                    \
    }
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
