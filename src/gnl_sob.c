/*
 * gnl_sob.c
 *
 * Created on: Apr 15, 2026
 *     Author: Gnoolson
 *    Version: 1.0.0
 */
#include "gnl_sob.h"

static void button_callback(int8_t button_id, bool long_press, void* p_value) {
    gnl_sob_t* p_sob = (gnl_sob_t*)p_value;

    if (p_sob->p_timer->active == false) {
        gnl_timer_start(p_sob->p_timer);
    }

    for (int i = 0; i < p_sob->length; i++) {
        gnl_button_info_t* p_info = p_sob->p_infos[i];

        if (p_info->button_id == button_id) {
            p_info->state = long_press ? GNL_BS_LONG_PRESS : GNL_BS_PRESSED;
        }
    }
}

/*
 *
 *
 * */
void gnl_sob_setup(gnl_sob_t* p_sob, uint8_t length, uint8_t logic_level) {
    p_sob->length = length;
    p_sob->logic_level = logic_level;
    p_sob->delay = 100;
    p_sob->index = 0;
    p_sob->p_buttons = malloc(sizeof(void*) * length);
    p_sob->p_infos = malloc(sizeof(void*) * length);
}

void gnl_sob_delete(gnl_sob_t* p_sob) {
    gnl_timer_delete(p_sob->p_timer);

    for (int i = 0; i < p_sob->length; i++) {
        gnl_button_delete(p_sob->p_buttons[i]);
        free(p_sob->p_infos[i]);
    }

    free(p_sob->p_buttons);
    free(p_sob->p_infos);
    free(p_sob);
}

gnl_sob_t* gnl_sob_new_and_setup(uint8_t length, uint8_t logic_level) {
    gnl_sob_t* p_sob = malloc(sizeof(gnl_sob_t));
    gnl_sob_setup(p_sob, length, logic_level);

    return p_sob;
}

bool gnl_sob_add_button(gnl_sob_t* p_sob, int8_t button_id, uint8_t dev_pin) {
    if (p_sob->index == p_sob->length)
        return false;

    p_sob->p_buttons[p_sob->index] = gnl_button_new_and_setup(button_id, dev_pin, p_sob->logic_level);
    p_sob->p_infos[p_sob->index] = malloc(sizeof(gnl_button_info_t));
    p_sob->p_infos[p_sob->index]->button_id = button_id;
    p_sob->p_infos[p_sob->index]->state = GNL_BS_IDLE;
    p_sob->index++;

    return true;
}

void gnl_sob_begin(gnl_sob_t* p_sob) {
    p_sob->p_timer = gnl_timer_new_and_setup(p_sob->delay, false);

    for (int i = 0; i < p_sob->length; i++) {
        gnl_button_begin(p_sob->p_buttons[i]);
    }
}

void gnl_sob_update(gnl_sob_t* p_sob, void (*callback)(gnl_button_info_t** p_infos, uint8_t length, void* p_value), void* p_value) {
    for (int i = 0; i < p_sob->length; i++) {
        gnl_button_update(p_sob->p_buttons[i], button_callback, p_sob);
    }

    gnl_timer_t* p_timer = p_sob->p_timer;
    if (gnl_timer_check(p_timer)) {
        gnl_timer_stop(p_timer);
        callback(p_sob->p_infos, p_sob->length, p_value);

        for (int i = 0; i < p_sob->length; i++) {
            gnl_button_info_t* p_info = p_sob->p_infos[i];
            p_info->state = GNL_BS_IDLE;
        }
    }
}
