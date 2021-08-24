/**
 * Copyright (c) 2019 - 2021, Titan Lab Inc.
 * 
 */
#ifndef ANT_SHIFT_SIMULATOR_H__
#define ANT_SHIFT_SIMULATOR_H__

/** @file
 *
 * @defgroup ant_sdk_simulators ANT simulators
 * @ingroup ant_sdk_utils
 * @brief Modules that simulate sensors.
 *
 * @defgroup ant_sdk_shift_simulator ANT SHIFT simulator
 * @{
 * @ingroup ant_sdk_simulators
 * @brief ANT SHIFT simulator module.
 *
 * @details This module simulates power for the ANT SHIFT profile. The module calculates
 * abstract values, which are handled by the SHIFT pages data model to ensure that they are
 * compatible. It provides a handler for changing the power value manually and functionality
 * for changing the power automatically.
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include "bsp.h"
#include "ant_shift.h"
#include "sensorsim.h"
#include "ant_shift_simulator_local.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief SHIFT simulator configuration structure. */
typedef struct
{
    ant_shift_profile_t * p_profile;   ///< Related profile.
} ant_shift_simulator_cfg_t;

/**@brief SHIFT simulator structure. */
typedef struct
{
    ant_shift_profile_t      * p_profile;    ///< Related profile.
    ant_shift_simulator_cb_t   _cb;          ///< Internal control block.
} ant_shift_simulator_t;


/**@brief Function for initializing the ANT SHIFT simulator instance.
 *
 * @param[in]  p_simulator      Pointer to the simulator instance.
 * @param[in]  p_config         Pointer to the simulator configuration structure.
 * @param[in]  auto_change      Enable or disable automatic changes of the power.
 */
void ant_shift_simulator_init(ant_shift_simulator_t           * p_simulator,
                             ant_shift_simulator_cfg_t const * p_config,
                             bool                             auto_change);

/**@brief Function for simulating a device event.
 *
 * @details Based on this event, the transmitter data is simulated.
 *
 * This function should be called in the SHIFT TX event handler.
 */
void ant_shift_simulator_one_iteration(ant_shift_simulator_t * p_simulator, ant_shift_evt_t event);

/**@brief Function for incrementing the power value.
 *
 * @param[in]  p_simulator      Pointer to the simulator instance.
 */
void ant_shift_simulator_increment(ant_shift_simulator_t * p_simulator);

/**@brief Function for decrementing the power value.
 *
 * @param[in]  p_simulator      Pointer to the simulator instance.
 */
void ant_shift_simulator_decrement(ant_shift_simulator_t * p_simulator);


#ifdef __cplusplus
}
#endif

#endif // ANT_SHIFT_SIMULATOR_H__
/** @} */
