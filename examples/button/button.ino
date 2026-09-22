extern "C" {
#include <gnl_button.h>
}

gnl_button_t* p_button_1 = NULL;
gnl_button_t* p_button_2 = NULL;

void setup() {
    Serial.begin(9600);

    p_button_1 = gnl_button_new_and_setup(1, 18, LOW);  // id: 1; pin: 18; Logic level for the pressed button state: LOW;
    p_button_2 = gnl_button_new_and_setup(2, 19, LOW);  // id: 2; pin: 19; Logic level for the pressed button state: LOW;

    /*
     * GNL_PULL_NONE - Do not use the internal resistor
     * GNL_PULL_UP   - Pull-up of an internal resistor to the positive rail
     * GNL_PULL_DOWN - Pull the internal resistor to ground (if the MCU supports it)
     * */
    gnl_button_begin(p_button_1, GNL_PULL_UP);
    gnl_button_begin(p_button_2, GNL_PULL_UP);
    
    Serial.println(F("button.ino"));
}

void callback(int8_t button_id, bool long_press, void* p_value) {
    int* p_counter = (int*)p_value;
    Serial.print("button id: ");
    Serial.print(button_id);
    Serial.print(" long_press: ");
    Serial.print(long_press);
    Serial.print(" counter:");
    Serial.println((*p_counter)++);
}

void loop() {
    static int counter = 0;
    gnl_button_update(p_button_1, &callback, &counter);
    gnl_button_update(p_button_2, &callback, &counter);
}
