/**
 * Copyright (c) 2019 - 2022, Titan Lab Inc.
 * 
 */
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(ANT_SHIFT)

#include "ant_shift_page_82.h"

#define NRF_LOG_MODULE_NAME ant_shift_page_82
#if ANT_SHIFT_PAGE_82_LOG_ENABLED
#define NRF_LOG_LEVEL       ANT_SHIFT_PAGE_82_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  ANT_SHIFT_PAGE_82_INFO_COLOR
#else // ANT_SHIFT_PAGE_82_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // ANT_SHIFT_PAGE_82_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

/**@brief bicycle shift page 82 data layout structure. */
typedef struct
{
    uint8_t  page82_reserved;    ///< Reserved: 0xFF, to be used in future
    uint8_t number_batteries                    : 4;
    uint8_t battery_identifier                  : 4;
    uint8_t battery_operating_time_lsb;
    uint8_t battery_operating_time;
    uint8_t battery_operating_time_msb;
    uint8_t battery_fractional_voltage;
    uint8_t battery_coarse_voltage              : 4;
    uint8_t battery_status                      : 3;
    bool battery_time_resolution                : 1;

}ant_shift_page82_data_layout_t;



static void page82_data_log(ant_shift_page82_data_t const * p_page_data)
{
    NRF_LOG_INFO("num batteries: %u, battery ident: %u", p_page_data->battery.number,p_page_data->battery.identifier);
    // NRF_LOG_INFO("gear f/r: %u // %u", p_page_data->current_gear_front, p_page_data->current_gear_rear);
    // NRF_LOG_INFO("total f/r: %u // %u", p_page_data->total_gear_front, p_page_data->total_gear_rear);
    // NRF_LOG_INFO("Invalid rear in/out: %u // %u, front: %u // %u", p_page_data->invalid_inboard_shift_count_rear,
    //     p_page_data->invalid_outboard_shift_count_rear,
    //     p_page_data->invalid_inboard_shift_count_front,
    //     p_page_data->invalid_outboard_shift_count_front);
    // NRF_LOG_INFO("failed f/r: %u // %u", p_page_data->shift_failure_count_front, p_page_data->shift_failure_count_rear);

    
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


void ant_shift_page_82_encode(uint8_t                      * p_page_buffer,
                             ant_shift_page82_data_t const * p_page_data)
{
    ant_shift_page82_data_layout_t * p_outcoming_data =
        (ant_shift_page82_data_layout_t *)p_page_buffer;

    p_outcoming_data->battery_identifier   = p_page_data->battery.identifier;
    p_outcoming_data->number_batteries   = p_page_data->battery.number;

    // p_outcoming_data->current_gear_rear     = p_page_data->current_gear_rear;
    // p_outcoming_data->current_gear_front    = p_page_data->current_gear_front;
    // p_outcoming_data->total_gear_rear       = p_page_data->total_gear_rear;
    // p_outcoming_data->total_gear_front      = p_page_data->total_gear_front;

    // p_outcoming_data->invalid_inboard_shift_count_rear      = p_page_data->invalid_inboard_shift_count_rear;
    // p_outcoming_data->invalid_outboard_shift_count_rear     = p_page_data->invalid_outboard_shift_count_rear;
    // p_outcoming_data->invalid_inboard_shift_count_front     = p_page_data->invalid_inboard_shift_count_front;
    // p_outcoming_data->invalid_outboard_shift_count_front    = p_page_data->invalid_outboard_shift_count_front; 
    // p_outcoming_data->shift_failure_count_rear              = p_page_data->shift_failure_count_rear;
    // p_outcoming_data->shift_failure_count_front             = p_page_data->shift_failure_count_front;

    page82_data_log(p_page_data);
}


void ant_shift_page_82_decode(uint8_t const          * p_page_buffer,
                             ant_shift_page82_data_t * p_page_data)
{
    ant_shift_page82_data_layout_t const * p_incoming_data =
        (ant_shift_page82_data_layout_t *)p_page_buffer;

    p_page_data->battery.identifier     = p_incoming_data->battery_identifier;
    p_page_data->battery.number     = p_incoming_data->number_batteries;
    // p_page_data->current_gear_rear      = p_incoming_data->current_gear_rear;
    // p_page_data->current_gear_front     = p_incoming_data->current_gear_front;
    // p_page_data->total_gear_rear        = p_incoming_data->total_gear_rear;
    // p_page_data->total_gear_front       = p_incoming_data->total_gear_front;

    // p_page_data->invalid_inboard_shift_count_rear       = p_incoming_data->invalid_inboard_shift_count_rear;
    // p_page_data->invalid_outboard_shift_count_rear      = p_incoming_data->invalid_outboard_shift_count_rear;
    // p_page_data->invalid_inboard_shift_count_front      = p_incoming_data->invalid_inboard_shift_count_front;
    // p_page_data->invalid_outboard_shift_count_front     = p_incoming_data->invalid_outboard_shift_count_front;
    // p_page_data->shift_failure_count_rear               = p_incoming_data->shift_failure_count_rear;
    // p_page_data->shift_failure_count_front               = p_incoming_data->shift_failure_count_front;

    page82_data_log(p_page_data);
}

#endif // NRF_MODULE_ENABLED(ANT_SHIFT)
