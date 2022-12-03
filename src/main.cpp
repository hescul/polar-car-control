#include <Arduino.h>
#include "ble.h"
#include "encoder.h"
#include "motor.h"
#include "control.h"

constexpr int SERIAL_BR = 9600;

__attribute__((unused)) void setup() {
    Serial.begin(SERIAL_BR);

    ble::init();

    enc::init();

    mtr::init();
}

__attribute__((unused)) void loop() {
    if (ble::recv()) {
        float dist = 0.0f;
        float degr = 0.0f;
        bool const res = ble::read(&dist, &degr);
        if (res && ctr::ready()) {
            ctr::process(dist, degr);
        }
    }
    ctr::loop(true);
}