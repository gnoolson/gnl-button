extern "C" {
#include <gnl_sob.h>
}

gnl_sob_t* p_sob = NULL;

void setup() {
    Serial.begin(9600);

    p_sob = gnl_sob_new_and_setup(2, LOW);  // buttons: 2x; logic level: LOW;

    gnl_sob_add_button(p_sob, 1, 18);  // id: 1; pin: 18;
    gnl_sob_add_button(p_sob, 2, 19);  // id: 2; pin: 19;
    gnl_sob_begin(p_sob);
}

void callback(gnl_button_info_t** p_infos, uint8_t length, void* p_value) {
    Serial.println(">>");
    for (int i = 0; i < length; i++) {
        Serial.print("button id: ");
        Serial.print(p_infos[i]->button_id);
        Serial.print(" state: ");
        Serial.print(p_infos[i]->state);
        Serial.print('\n');
    }
    Serial.println("<<");
}

void loop() {
    static int x = 0;
    gnl_sob_update(p_sob, &callback, &x);
}
