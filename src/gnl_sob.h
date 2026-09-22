/*
 * gnl_sob.h
 *
 * Created on: Apr 15, 2026
 *     Author: Gnoolson
 *    Version: 2.0.0
 */
#ifndef GNL_SET_OF_BUTTONS_H_
#define GNL_SET_OF_BUTTONS_H_

#include <Arduino.h>
#include <gnl_timer.h>
#include "gnl_button.h"

typedef enum { GNL_BS_IDLE = 0, GNL_BS_PRESSED = 1, GNL_BS_LONG_PRESS = 2 } gnl_button_state_t;

typedef struct {
    int8_t button_id;
    gnl_button_state_t state;
} gnl_button_info_t;

typedef struct {
    uint8_t logic_level;
    gnl_button_t** p_buttons;
    gnl_button_info_t** p_infos;
    gnl_timer_t* p_timer;
    uint8_t length;
    uint8_t index;
    uint16_t delay_ms;
} gnl_sob_t;

/*
 *
 *
 * */
void gnl_sob_setup(gnl_sob_t* p_sob, uint8_t length, uint8_t logic_level);
gnl_sob_t* gnl_sob_new_and_setup(uint8_t length, uint8_t logic_level);
void gnl_sob_set_time_settings(gnl_sob_t* p_sob, uint16_t long_press_ms, uint16_t debounce_ms, uint16_t delay_ms);
void gnl_sob_delete(gnl_sob_t* p_sob);
bool gnl_sob_add_button(gnl_sob_t* p_sob, int8_t button_id, uint8_t dev_pin);
void gnl_sob_begin(gnl_sob_t* p_sob, gnl_button_pull_mode_t pull_mode);
void gnl_sob_update(gnl_sob_t* p_sob, void (*callback)(gnl_button_info_t** p_infos, uint8_t length, void* p_value), void* p_value);

#endif /* GNL_SET_OF_BUTTONS_H_ */
