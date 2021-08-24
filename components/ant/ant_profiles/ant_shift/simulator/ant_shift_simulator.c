/**
 * Copyright (c) 2019 - 2021, Titan Lab Inc.
 * 
 */
#include "ant_shift_simulator.h"
#include "app_util.h"
#include "nordic_common.h"

#define REAR_GEAR_MIN  0
#define REAR_GEAR_MAX  12
#define REAR_GEAR_INCR 1

#define FRONT_GEAR_MIN  0
#define FRONT_GEAR_MAX  2
#define FRONT_GEAR_INCR 1

#define SIMULATOR_TIME_INCREMENT SHIFT_MSG_PERIOD


void ant_shift_simulator_init(ant_shift_simulator_t           * p_simulator,
                             ant_shift_simulator_cfg_t const * p_config,
                             bool                             auto_change)
{
    p_simulator->p_profile      = p_config->p_profile;
    p_simulator->_cb.auto_change = auto_change;
    p_simulator->_cb.tick_incr   = 0;

    p_simulator->_cb.current_gear_rear_cfg.min          = REAR_GEAR_MIN;
    p_simulator->_cb.current_gear_rear_cfg.max          = REAR_GEAR_MAX;
    p_simulator->_cb.current_gear_rear_cfg.incr         = REAR_GEAR_INCR;
    p_simulator->_cb.current_gear_rear_cfg.start_at_max = false;

    p_simulator->_cb.current_gear_front_cfg.min          = FRONT_GEAR_MIN;
    p_simulator->_cb.current_gear_front_cfg.max          = FRONT_GEAR_MAX;
    p_simulator->_cb.current_gear_front_cfg.incr         = FRONT_GEAR_INCR;
    p_simulator->_cb.current_gear_front_cfg.start_at_max = false;


    // p_simulator->p_profile->SHIFT_PROFILE_pedal_power.differentiation = 0x01; // right

    sensorsim_init(&(p_simulator->_cb.current_gear_rear_state),
                   &(p_simulator->_cb.current_gear_rear_cfg));
    sensorsim_init(&(p_simulator->_cb.current_gear_front_state),
                   &(p_simulator->_cb.current_gear_front_cfg));

}


void ant_shift_simulator_one_iteration(ant_shift_simulator_t * p_simulator, ant_shift_evt_t event)
{
    switch (event)
    {
        case ANT_SHIFT_PAGE_1_UPDATED:

            // if (p_simulator->_cb.auto_change)
            // {
            //     UNUSED_PARAMETER(sensorsim_measure(&(p_simulator->_cb.power_sensorsim_state),
            //                                        &(p_simulator->_cb.power_sensorsim_cfg)));
            //     UNUSED_PARAMETER(sensorsim_measure(&(p_simulator->_cb.cadence_sensorsim_state),
            //                                        &(p_simulator->_cb.cadence_sensorsim_cfg)));
            //     UNUSED_PARAMETER(sensorsim_measure(&(p_simulator->_cb.pedal_sensorsim_state),
            //                                        &(p_simulator->_cb.pedal_sensorsim_cfg)));
            // }

            // p_simulator->p_profile->SHIFT_PROFILE_instantaneous_power =
            //     p_simulator->_cb.power_sensorsim_state.current_val;
            // p_simulator->p_profile->SHIFT_PROFILE_accumulated_power +=
            //     p_simulator->_cb.power_sensorsim_state.current_val;

            // if (p_simulator->p_profile->SHIFT_PROFILE_accumulated_power == UINT16_MAX)
            // {
            //     p_simulator->p_profile->SHIFT_PROFILE_accumulated_power = 0;
            // }
            // p_simulator->p_profile->SHIFT_PROFILE_instantaneous_cadence =
            //      p_simulator->_cb.cadence_sensorsim_state.current_val;
            // p_simulator->p_profile->SHIFT_PROFILE_pedal_power.distribution =
            //     p_simulator->_cb.pedal_sensorsim_state.current_val;
            // p_simulator->p_profile->SHIFT_PROFILE_power_update_event_count++;
            break;

        case ANT_SHIFT_PAGE_78_UPDATED:

            // if (p_simulator->_cb.auto_change)
            // {
            //     UNUSED_PARAMETER(sensorsim_measure(&(p_simulator->_cb.cadence_sensorsim_state),
            //                                        &(p_simulator->_cb.cadence_sensorsim_cfg)));
            // }
            // p_simulator->p_profile->SHIFT_PROFILE_instantaneous_cadence =
            //      p_simulator->_cb.cadence_sensorsim_state.current_val;
            // p_simulator->p_profile->SHIFT_PROFILE_wheel_period += TORQUE_PERIOD;
            // p_simulator->_cb.tick_incr                        +=
            //     SIMULATOR_TIME_INCREMENT;
            // p_simulator->p_profile->SHIFT_PROFILE_wheel_tick +=
            //     p_simulator->_cb.tick_incr / (TORQUE_PERIOD * 16);
            // p_simulator->_cb.tick_incr =
            //     p_simulator->_cb.tick_incr % (TORQUE_PERIOD * 16);
            // p_simulator->p_profile->SHIFT_PROFILE_wheel_accumulated_torque += TORQUE_INCR;
            // p_simulator->p_profile->SHIFT_PROFILE_wheel_update_event_count++;
            break;

        case ANT_SHIFT_PAGE_79_UPDATED:

            // if (p_simulator->_cb.auto_change)
            // {
            //     UNUSED_PARAMETER(sensorsim_measure(&(p_simulator->_cb.cadence_sensorsim_state),
            //                                        &(p_simulator->_cb.cadence_sensorsim_cfg)));
            // }
            // p_simulator->p_profile->SHIFT_PROFILE_instantaneous_cadence =
            //      p_simulator->_cb.cadence_sensorsim_state.current_val;
            // p_simulator->p_profile->SHIFT_PROFILE_crank_period = TORQUE_PERIOD;
            // p_simulator->_cb.tick_incr                        +=
            //     SIMULATOR_TIME_INCREMENT;
            // p_simulator->p_profile->SHIFT_PROFILE_crank_tick +=
            //     p_simulator->_cb.tick_incr / (TORQUE_PERIOD * 16);
            // p_simulator->_cb.tick_incr =
            //     p_simulator->_cb.tick_incr % (TORQUE_PERIOD * 16);
            // p_simulator->p_profile->SHIFT_PROFILE_crank_accumulated_torque += TORQUE_INCR;
            // p_simulator->p_profile->SHIFT_PROFILE_crank_update_event_count++;
            break;

        default:
            break;
    }
}


void ant_shift_simulator_increment(ant_shift_simulator_t * p_simulator)
{
    if (!p_simulator->_cb.auto_change)
    {
        // sensorsim_increment(&(p_simulator->_cb.power_sensorsim_state),
        //                     &(p_simulator->_cb.power_sensorsim_cfg));
        // sensorsim_increment(&(p_simulator->_cb.cadence_sensorsim_state),
        //                     &(p_simulator->_cb.cadence_sensorsim_cfg));
        // sensorsim_increment(&(p_simulator->_cb.pedal_sensorsim_state),
        //                     &(p_simulator->_cb.pedal_sensorsim_cfg));
    }
}


void ant_shift_simulator_decrement(ant_shift_simulator_t * p_simulator)
{
    if (!p_simulator->_cb.auto_change)
    {
        // sensorsim_decrement(&(p_simulator->_cb.power_sensorsim_state),
        //                     &(p_simulator->_cb.power_sensorsim_cfg));
        // sensorsim_decrement(&(p_simulator->_cb.cadence_sensorsim_state),
        //                     &(p_simulator->_cb.cadence_sensorsim_cfg));
        // sensorsim_decrement(&(p_simulator->_cb.pedal_sensorsim_state),
        //                     &(p_simulator->_cb.pedal_sensorsim_cfg));
    }
}


