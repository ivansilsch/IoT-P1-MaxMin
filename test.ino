#include "serial_header.h"

int bits;
serial_class serial_obj;

void setup() {
  Serial.begin(115200);
}

void loop() {
    bits = serial_obj.get_data();  
    if (bits > 0) {
        serial_obj.post_data(bits);
    }
    delay(1000);
}
