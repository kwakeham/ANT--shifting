/**
 * Copyright (c) 2019 - 2022, Titan Lab Inc.
 * 
 */
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(ANT_SHIFT)

#include "ant_shift_page_1.h"

#define NRF_LOG_MODULE_NAME ant_shift_page_1
#if ANT_SHIFT_PAGE_1_LOG_ENABLED
#define NRF_LOG_LEVEL       ANT_SHIFT_PAGE_1_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  ANT_SHIFT_PAGE_1_INFO_COLOR
#else // ANT_SHIFT_PAGE_1_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // ANT_SHIFT_PAGE_1_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

/**@brief bicycle shift page 1 data layout structure. */
typedef struct
{
    uint8_t update_event_count;
    uint8_t reserved;
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

}ant_shift_page1_data_layout_t;



static void page1_data_log(ant_shift_page1_data_t const * p_page_data)
{
    NRF_LOG_INFO("event count:                        %u", p_page_data->update_event_count);
    NRF_LOG_INFO("gear f/r: %u // %u", p_page_data->current_gear_front, p_page_data->current_gear_rear);
    NRF_LOG_INFO("total f/r: %u // %u", p_page_data->total_gear_front, p_page_data->total_gear_rear);
    NRF_LOG_INFO("Invalid rear in/out: %u // %u, front: %u // %u", p_page_data->invalid_inboard_shift_count_rear,
        p_page_data->invalid_outboard_shift_count_rear,
        p_page_data->invalid_inboard_shift_count_front,
        p_page_data->invalid_outboard_shift_count_front);
    NRF_LOG_INFO("failed f/r: %u // %u", p_page_data->shift_failure_count_front, p_page_data->shift_failure_count_rear);
}


void ant_shift_page_1_encode(uint8_t                      * p_page_buffer,
                             ant_shift_page1_data_t const * p_page_data)
{
    ant_shift_page1_data_layout_t * p_outcoming_data =
        (ant_shift_page1_data_layout_t *)p_page_buffer;

    p_outcoming_data->update_event_count   = p_page_data->update_event_count;

    p_outcoming_data->current_gear_rear     = p_page_data->current_gear_rear;
    p_outcoming_data->current_gear_front    = p_page_data->current_gear_front;
    p_outcoming_data->total_gear_rear       = p_page_data->total_gear_rear;
    p_outcoming_data->total_gear_front      = p_page_data->total_gear_front;

    p_outcoming_data->invalid_inboard_shift_count_rear      = p_page_data->invalid_inboard_shift_count_rear;
    p_outcoming_data->invalid_outboard_shift_count_rear     = p_page_data->invalid_outboard_shift_count_rear;
    p_outcoming_data->invalid_inboard_shift_count_front     = p_page_data->invalid_inboard_shift_count_front;
    p_outcoming_data->invalid_outboard_shift_count_front    = p_page_data->invalid_outboard_shift_count_front; 
    p_outcoming_data->shift_failure_count_rear              = p_page_data->shift_failure_count_rear;
    p_outcoming_data->shift_failure_count_front             = p_page_data->shift_failure_count_front;

    page1_data_log(p_page_data);
}


void ant_shift_page_1_decode(uint8_t const          * p_page_buffer,
                             ant_shift_page1_data_t * p_page_data)
{
    ant_shift_page1_data_layout_t const * p_incoming_data =
        (ant_shift_page1_data_layout_t *)p_page_buffer;

    p_page_data->update_event_count     = p_incoming_data->update_event_count;
    p_page_data->current_gear_rear      = p_incoming_data->current_gear_rear;
    p_page_data->current_gear_front     = p_incoming_data->current_gear_front;
    p_page_data->total_gear_rear        = p_incoming_data->total_gear_rear;
    p_page_data->total_gear_front       = p_incoming_data->total_gear_front;

    p_page_data->invalid_inboard_shift_count_rear       = p_incoming_data->invalid_inboard_shift_count_rear;
    p_page_data->invalid_outboard_shift_count_rear      = p_incoming_data->invalid_outboard_shift_count_rear;
    p_page_data->invalid_inboard_shift_count_front      = p_incoming_data->invalid_inboard_shift_count_front;
    p_page_data->invalid_outboard_shift_count_front     = p_incoming_data->invalid_outboard_shift_count_front;
    p_page_data->shift_failure_count_rear               = p_incoming_data->shift_failure_count_rear;
    p_page_data->shift_failure_count_front               = p_incoming_data->shift_failure_count_front;

    page1_data_log(p_page_data);
}

#endif // NRF_MODULE_ENABLED(ANT_SHIFT)
