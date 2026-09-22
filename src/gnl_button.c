/*
 * gnl_button.c
 *
 * Created on: Apr 14, 2026
 *     Author: Gnoolson
 *    Version: 2.0.0
 */
#include "gnl_button.h"

static bool is_debounce_after_release(gnl_button_t* p_button) {
    uint32_t now = millis();
    return now - p_button->last_action_ts < p_button->debounce_ms;
}

static bool has_button_state_changed(gnl_button_t* p_button, bool actual_button_state) {
    return p_button->state != actual_button_state;
}

static bool is_debounce_after_press(gnl_button_t* p_button) {
    uint32_t now = millis();
    return now - p_button->debounce_ms < p_button->pressed_ts;
}

static bool has_press_started(gnl_button_t* p_button) {
    return p_button->state;
}

static bool is_button_released(bool actual_button_state) {
    return actual_button_state == false;
}

static bool should_execute_callback(gnl_button_t* p_button) {
    uint32_t now = millis();
    return now - p_button->pressed_ts < p_button->long_press_ms;
}

static void execute_callback(gnl_button_t* p_button, void (*p_button_callback)(int8_t button_id, bool long_press, void* p_value), void* p_value) {
    p_button_callback(p_button->id, false, p_value);
}

static bool should_start_press(gnl_button_t* p_button, bool actual_button_state) {
    return actual_button_state && !p_button->state;
}

static void start_press(gnl_button_t* p_button) {
    uint32_t now = millis();
    p_button->state = true;
    p_button->pressed_ts = now;
}

static bool should_start_release(gnl_button_t* p_button, bool actual_button_state) {
    return !actual_button_state && p_button->state;
}

static void start_release(gnl_button_t* p_button) {
    uint32_t now = millis();
    p_button->state = false;
    p_button->last_action_ts = now;
}

static bool should_execute_callback_long_press(gnl_button_t* p_button) {
    uint32_t now = millis();
    return now - p_button->pressed_ts > p_button->long_press_ms;
}

static void execute_callback_long_press(gnl_button_t* p_button, void (*p_button_callback)(int8_t button_id, bool long_press, void* p_value), void* p_value) {
    p_button_callback(p_button->id, true, p_value);
}

static bool read_state(gnl_button_t* p_button) {
    bool flag = (bool)digitalRead(p_button->dev_pin);
    if (!p_button->logic_level) {
        flag = !flag;
    }
    return flag;
}

/*
 *
 *
 * */
void gnl_button_setup(gnl_button_t* p_button, int8_t id, uint8_t dev_pin, uint8_t logic_level) {
    p_button->id = id;
    p_button->dev_pin = dev_pin;
    p_button->pressed_ts = 0;
    p_button->last_action_ts = 0;
    p_button->state = false;
    p_button->logic_level = logic_level;
    p_button->long_press_ms = 1000;
    p_button->debounce_ms = 200;
}

gnl_button_t* gnl_button_new_and_setup(int8_t id, uint8_t dev_pin, uint8_t logic_level) {
    gnl_button_t* p_button = malloc(sizeof(gnl_button_t));
    gnl_button_setup(p_button, id, dev_pin, logic_level);
    return p_button;
}

void gnl_button_set_time_settings(gnl_button_t* p_button, uint16_t long_press_ms, uint16_t debounce_ms) {
    p_button->long_press_ms = long_press_ms;
    p_button->debounce_ms = debounce_ms;
}

void gnl_button_delete(gnl_button_t* p_button) {
    free(p_button);
}

void gnl_button_begin(gnl_button_t* p_button, gnl_button_pull_mode_t pull_mode) {
    if (pull_mode == GNL_PULL_UP) {
        pinMode(p_button->dev_pin, INPUT_PULLUP);
    } else if (pull_mode == GNL_PULL_DOWN) {
        pinMode(p_button->dev_pin, INPUT_PULLDOWN);
    } else {
        pinMode(p_button->dev_pin, INPUT);
    }
}

void gnl_button_update(gnl_button_t* p_button, void (*p_button_callback)(int8_t button_id, bool long_press, void* p_value), void* p_value) {
    if (is_debounce_after_release(p_button))
        return;

    bool actual_button_state = read_state(p_button);

    if (has_button_state_changed(p_button, actual_button_state)) {
        if (is_debounce_after_press(p_button)) {
            return;
        }

        if (has_press_started(p_button) && is_button_released(actual_button_state) && should_execute_callback(p_button)) {
            execute_callback(p_button, p_button_callback, p_value);
        }

        if (should_start_press(p_button, actual_button_state)) {
            start_press(p_button);
        } else if (should_start_release(p_button, actual_button_state)) {
            start_release(p_button);
        }
    } else {
        if (has_press_started(p_button) && should_execute_callback_long_press(p_button)) {
            execute_callback_long_press(p_button, p_button_callback, p_value);
        }
    }
}
