#include <Arduino.h>
#include "ble.h"
#include "encoder.h"
#include "motor.h"
#include "control.h"

__attribute__((unused)) void setup() {
    Serial.begin(9600);

    ble::init();

    enc::init();

    mtr::init();
}

__attribute__((unused)) void loop() {
    if (ble::recv()) {
        float dist = 0.0f;
        float degr = 0.0f;
        bool res = ble::read(&dist, &degr);
        if (res && ctr::ready()) {
            ctr::process(dist, degr);
        }
    }
    ctr::loop(true);
}