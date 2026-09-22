/*
 * gnl_button.h
 *
 * Created on: Apr 14, 2026
 *     Author: Gnoolson
 *    Version: 2.0.0
 */
#ifndef GNL_BUTTON_H_
#define GNL_BUTTON_H_

#include <Arduino.h>

typedef enum {
    GNL_PULL_NONE = 0,  
    GNL_PULL_UP,
    GNL_PULL_DOWN
} gnl_button_pull_mode_t;

typedef struct {
    int8_t id;
    uint8_t dev_pin;
    uint32_t pressed_ts;
    uint32_t last_action_ts;
    bool state;
    uint8_t logic_level;
    uint16_t long_press_ms;
    uint16_t debounce_ms;
} gnl_button_t;

/*
 * 
 * 
 * */
gnl_button_t* gnl_button_new_and_setup(int8_t id, uint8_t dev_pin, uint8_t logic_level);
void gnl_button_setup(gnl_button_t* p_button, int8_t id, uint8_t dev_pin, uint8_t logic_level);
void gnl_button_set_time_settings(gnl_button_t* p_button, uint16_t long_press_ms, uint16_t debounce_ms);
void gnl_button_delete(gnl_button_t* p_button);
void gnl_button_begin(gnl_button_t* p_button, gnl_button_pull_mode_t pull_mode);
void gnl_button_update(gnl_button_t* p_button, void (*p_button_callback)(int8_t button_id, bool long_press, void* p_value), void* p_value);

#endif /* GNL_BUTTON_H_ */
