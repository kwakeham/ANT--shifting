/**
 * Copyright (c) 2019 - 2021, Titan Lab Inc.
 * 
 */
#ifndef ANT_SHIFT_SIMULATOR_LOCAL_H__
#define ANT_SHIFT_SIMULATOR_LOCAL_H__

#include <stdint.h>
#include <stdbool.h>
#include "bsp.h"
#include "ant_shift.h"
#include "sensorsim.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @ingroup ant_sdk_shift_simulator
 * @brief SHIFT simulator control block structure. */
typedef struct
{
    bool              auto_change;             ///< Power will change automatically (if auto_change is set) or manually.
    uint32_t          tick_incr;               ///< Fractional part of tick increment.
    sensorsim_state_t current_gear_rear_state;   ///< Power state of the simulated sensor.
    sensorsim_cfg_t   current_gear_rear_cfg;     ///< Power configuration of the simulated sensor.
    sensorsim_state_t current_gear_front_state; ///< Cadence stated of the simulated sensor.
    sensorsim_cfg_t   current_gear_front_cfg;   ///< Cadence configuration of the simulated sensor.
}ant_shift_simulator_cb_t;



#ifdef __cplusplus
}
#endif

#endif // ANT_SHIFT_SIMULATOR_LOCAL_H__
