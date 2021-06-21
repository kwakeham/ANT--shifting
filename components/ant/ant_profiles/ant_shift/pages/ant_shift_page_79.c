/**
 * Copyright (c) 2019 - 2021, Titan Lab Inc.
 * 
 */
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(ANT_SHIFT)

#include "ant_shift_page_79.h"

#define NRF_LOG_MODULE_NAME ant_shift_page_79
#if ANT_SHIFT_PAGE_79_LOG_ENABLED
#define NRF_LOG_LEVEL       ANT_SHIFT_PAGE_79_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  ANT_SHIFT_PAGE_79_INFO_COLOR
#else // ANT_SHIFT_PAGE_79_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // ANT_SHIFT_PAGE_79_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

/**@brief bicycle shift page 79 data layout structure. */
typedef struct
{
    uint8_t number_components                    : 4;
    uint8_t component_identifier                  : 4;
    uint8_t sw_revision_supplemental;
    uint8_t sw_revision_main;
    uint8_t serial_number_lsb;
    uint8_t serial_number_8_15;
    uint8_t serial_number_16_23;
    uint8_t serial_number_msb;

}ant_shift_page79_data_layout_t;



static void page79_data_log(ant_shift_page79_data_t const * p_page_data)
{
    NRF_LOG_INFO("num components:            %u, component ident: %u", p_page_data->component.number,p_page_data->component.identifier);
    NRF_LOG_INFO("sw revision supplemental:  %u", p_page_data->component.sw_revision_supplemental);
    NRF_LOG_INFO("sw revision main:          %u", p_page_data->component.sw_revision_main);
    NRF_LOG_INFO("serial number :            %u", p_page_data->component.serial_number);
}


void ant_shift_page_79_encode(uint8_t                      * p_page_buffer,
                             ant_shift_page79_data_t const * p_page_data)
{
    ant_shift_page79_data_layout_t * p_outcoming_data =
        (ant_shift_page79_data_layout_t *)p_page_buffer;

    p_outcoming_data->component_identifier  = p_page_data->component.identifier;
    p_outcoming_data->number_components     = p_page_data->component.number;

    p_outcoming_data->sw_revision_supplemental    = p_page_data->component.sw_revision_supplemental;
    p_outcoming_data->sw_revision_main            = ((p_page_data->component.sw_revision_main)>>8);

    p_outcoming_data->serial_number_lsb     = p_page_data->component.serial_number;
    p_outcoming_data->serial_number_8_15    = ((p_page_data->component.serial_number)>>8);
    p_outcoming_data->serial_number_16_23   = ((p_page_data->component.serial_number)>>16);
    p_outcoming_data->serial_number_msb     = ((p_page_data->component.serial_number)>>24);

    page79_data_log(p_page_data);
}


void ant_shift_page_79_decode(uint8_t const          * p_page_buffer,
                             ant_shift_page79_data_t * p_page_data)
{
    ant_shift_page79_data_layout_t const * p_incoming_data =
        (ant_shift_page79_data_layout_t *)p_page_buffer;

    p_page_data->component.identifier   = p_incoming_data->component_identifier;
    p_page_data->component.number       = p_incoming_data->number_components;

    p_page_data->component.sw_revision_supplemental  = p_incoming_data->sw_revision_supplemental;
    p_page_data->component.sw_revision_main  = p_incoming_data->sw_revision_main;

    p_page_data->component.serial_number = ((p_incoming_data->serial_number_msb) <<24)
                                            | ((p_incoming_data->serial_number_16_23) <<16)
                                            | ((p_incoming_data ->serial_number_8_15) <<8)
                                            | (p_incoming_data->serial_number_lsb);

    page79_data_log(p_page_data);
}

#endif // NRF_MODULE_ENABLED(ANT_SHIFT)
