/**
 * Copyright (c) 2019 - 2022, Titan Lab Inc.
 * 
 */
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(ANT_SHIFT)

#include "ant_shift_page_1.h"

#define NRF_LOG_MODULE_NAME ant_shift_page_82
#if ANT_SHIFT_PAGE_82_LOG_ENABLED
#define NRF_LOG_LEVEL       ANT_SHIFT_PAGE_82_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  ANT_SHIFT_PAGE_82_INFO_COLOR
#else // ANT_SHIFT_PAGE_82_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // ANT_SHIFT_PAGE_82_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

/**@brief bicycle power page 16 data layout structure. */
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

    
    // if (p_page_data->pedal_power.byte != 0xFF)
    // {
    //     NRF_LOG_INFO("pedal power:                        %u %%",
    //                p_page_data->pedal_power.items.distribution);
    // }
    // else
    // {
    //     NRF_LOG_INFO("pedal power:                        --");
    // }

    // NRF_LOG_INFO("accumulated power:                  %u W", p_page_data->accumulated_power);
    // NRF_LOG_INFO("instantaneous power:                %u W", p_page_data->instantaneous_power);
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
