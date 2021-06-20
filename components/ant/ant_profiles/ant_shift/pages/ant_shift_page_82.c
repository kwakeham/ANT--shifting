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
    NRF_LOG_INFO("operating time: %u, resolution: %u", p_page_data->battery.operating_time,p_page_data->battery.time_resolution);
}


void ant_shift_page_82_encode(uint8_t                      * p_page_buffer,
                             ant_shift_page82_data_t const * p_page_data)
{
    ant_shift_page82_data_layout_t * p_outcoming_data =
        (ant_shift_page82_data_layout_t *)p_page_buffer;

    p_outcoming_data->battery_identifier   = p_page_data->battery.identifier;
    p_outcoming_data->number_batteries   = p_page_data->battery.number;

    if(p_page_data->battery.operating_time > 33554431) //2^24 *2 seconds - 1 is max for 2 second time, so use 16 second
    {
        p_outcoming_data->battery_operating_time_msb = (p_page_data->battery.operating_time) >> 20;
        p_outcoming_data->battery_operating_time = (p_page_data->battery.operating_time) >> 12;
        p_outcoming_data->battery_operating_time_lsb = (p_page_data->battery.operating_time) >> 4;
        p_outcoming_data->battery_time_resolution = 0; //set to 0 for 16 second operating time
    }
    else //use 2 second so this is just one extra bit shift
    {
        p_outcoming_data->battery_operating_time_msb = (p_page_data->battery.operating_time) >> 17;
        p_outcoming_data->battery_operating_time = (p_page_data->battery.operating_time) >> 9;
        p_outcoming_data->battery_operating_time_lsb = (p_page_data->battery.operating_time) >> 1;
        p_outcoming_data->battery_time_resolution = 1; //set to 1 for 2 second operating time
    }


    page82_data_log(p_page_data);
}


void ant_shift_page_82_decode(uint8_t const          * p_page_buffer,
                             ant_shift_page82_data_t * p_page_data)
{
    ant_shift_page82_data_layout_t const * p_incoming_data =
        (ant_shift_page82_data_layout_t *)p_page_buffer;

    p_page_data->battery.identifier     = p_incoming_data->battery_identifier;
    p_page_data->battery.number     = p_incoming_data->number_batteries;
    p_page_data->battery.operating_time = (((p_incoming_data->battery_operating_time_msb)<<24)
                                            |((p_incoming_data->battery_operating_time)<<16)
                                            |((p_incoming_data->battery_operating_time_lsb)<<8))>>8;
    p_page_data->battery.time_resolution = p_incoming_data->battery_time_resolution;

    //rewrite the time based on it's resolution 1(true) = 2s, 0 (false) = 16 seconds
    if(p_page_data->battery.time_resolution)
    {
        p_page_data->battery.operating_time = p_page_data->battery.operating_time *2;
    } else
    {
        p_page_data->battery.operating_time = p_page_data->battery.operating_time * 16;
    }

    page82_data_log(p_page_data);
}

#endif // NRF_MODULE_ENABLED(ANT_SHIFT)
