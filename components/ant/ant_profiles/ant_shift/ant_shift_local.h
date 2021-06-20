/**
* Copyright (c) 2019 - 2022, Titan Lab Inc.
 *
 */
#ifndef ANT_SHIFT_LOCAL_H__
#define ANT_SHIFT_LOCAL_H__

#include <stdint.h>
#include <stdbool.h>
#include "ant_shift.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup ant_shift
 * @{
 */

/** @brief Bicycle Shift Sensor control block. */
typedef struct
{
    uint8_t           message_counter;
} ant_shift_sens_cb_t;

/**@brief Bicycle Shift Sensor RX control block. */
typedef struct
{

} ant_shift_disp_cb_t;

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif // ANT_SHIFT_LOCAL_H__
