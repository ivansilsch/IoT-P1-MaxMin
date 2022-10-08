#include "serial_header.h"  

serial_class serial_obj;

void setup() {
  Serial.begin(115200);
}

void loop() {
    if ( Serial.available() && serial_obj.get_data() ) {
      serial_obj.post_data();
    }
}