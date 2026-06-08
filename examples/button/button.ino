extern "C" {
#include <gnl_button.h>
}

gnl_button_t* p_button_1 = NULL;
gnl_button_t* p_button_2 = NULL;

void setup() {
    Serial.begin(9600);

    p_button_1 = gnl_button_new_and_setup(1, 18, LOW);  // id: 1; pin: 18; logic level: LOW;
    p_button_2 = gnl_button_new_and_setup(2, 19, LOW);  // id: 2; pin: 19; logic level: LOW;

    gnl_button_begin(p_button_1);
    gnl_button_begin(p_button_2);
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
