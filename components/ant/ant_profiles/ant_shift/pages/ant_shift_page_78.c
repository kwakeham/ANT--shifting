/**
 * Copyright (c) 2019 - 2021, Titan Lab Inc.
 * 
 */
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(ANT_SHIFT)

#include "ant_shift_page_78.h"

#define NRF_LOG_MODULE_NAME ant_shift_page_78
#if ANT_SHIFT_PAGE_78_LOG_ENABLED
#define NRF_LOG_LEVEL       ANT_SHIFT_PAGE_78_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  ANT_SHIFT_PAGE_78_INFO_COLOR
#else // ANT_SHIFT_PAGE_78_LOG_ENABLED
#define NRF_LOG_LEVEL       0
#endif // ANT_SHIFT_PAGE_78_LOG_ENABLED
#include "nrf_log.h"
NRF_LOG_MODULE_REGISTER();

/**@brief bicycle shift page 78 data layout structure. */
typedef struct
{
    uint8_t page78_reserved;    ///< Reserved: 0xFF, to be used in future
    uint8_t number_components                    : 4;
    uint8_t component_identifier                  : 4;
    uint8_t hw_revision;
    uint8_t mfg_id_lsb;
    uint8_t mfg_id_msb;
    uint8_t model_number_lsb;
    uint8_t model_number_msb;

}ant_shift_page78_data_layout_t;



static void page78_data_log(ant_shift_page78_data_t const * p_page_data)
{
    NRF_LOG_INFO("num components:            %u, component ident: %u", p_page_data->component.number,p_page_data->component.identifier);
    NRF_LOG_INFO("num components:            %u", p_page_data->component.hw_revision);
    NRF_LOG_INFO("num components:            %u", p_page_data->component.mfg_id);
    NRF_LOG_INFO("num components:            %u", p_page_data->component.model_number);
}


void ant_shift_page_78_encode(uint8_t                      * p_page_buffer,
                             ant_shift_page78_data_t const * p_page_data)
{
    ant_shift_page78_data_layout_t * p_outcoming_data =
        (ant_shift_page78_data_layout_t *)p_page_buffer;

    p_outcoming_data->component_identifier  = p_page_data->component.identifier;
    p_outcoming_data->number_components     = p_page_data->component.number;
    p_outcoming_data->hw_revision           = p_page_data->component.hw_revision;
    p_outcoming_data->mfg_id_lsb            = p_page_data->component.mfg_id;
    p_outcoming_data->mfg_id_msb            = ((p_page_data->component.mfg_id)>>8);
    p_outcoming_data->model_number_lsb      = p_page_data->component.model_number;
    p_outcoming_data->model_number_msb      = ((p_page_data->component.model_number)>>8);

    page78_data_log(p_page_data);
}


void ant_shift_page_78_decode(uint8_t const          * p_page_buffer,
                             ant_shift_page78_data_t * p_page_data)
{
    ant_shift_page78_data_layout_t const * p_incoming_data =
        (ant_shift_page78_data_layout_t *)p_page_buffer;

    p_page_data->component.identifier   = p_incoming_data->component_identifier;
    p_page_data->component.number       = p_incoming_data->number_components;
    p_page_data->component.hw_revision  = p_incoming_data->hw_revision;
    p_page_data->component.mfg_id       = ((p_incoming_data->mfg_id_msb) <<8)| (p_incoming_data->mfg_id_lsb);
    p_page_data->component.model_number = ((p_incoming_data->model_number_msb) <<8)| (p_incoming_data->model_number_lsb);

    page78_data_log(p_page_data);
}

#endif // NRF_MODULE_ENABLED(ANT_SHIFT)
