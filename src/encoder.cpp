//
// Created by Minh Nguyen on 11/29/2022.
//

#include <Arduino.h>
#include "config.h"
#include "encoder.h"

static int posLft;
static int posRgt;

void irpLft();

void irpRgt();

void enc::init() {
    pinMode(ENCL_A, INPUT);
    pinMode(ENCL_B, INPUT);
    pinMode(ENCR_A, INPUT);
    pinMode(ENCR_B, INPUT);

    attachInterrupt(digitalPinToInterrupt(ENCL_A), irpLft, RISING);
    attachInterrupt(digitalPinToInterrupt(ENCR_A), irpRgt, RISING);

    reset();
}

void enc::reset() {
    posLft = 0;
    posRgt = 0;
}

void enc::reset(const Wheel wheel) {
    switch (wheel) {
        case Wheel::LEFT:
            posLft = 0;
            break;
        case Wheel::RIGHT:
            posRgt = 0;
            break;
        case Wheel::UNKNOWN:
            return;
    }
}

void irpLft() {
    const int b = digitalRead(ENCL_B);
    if (b > 0) {
        ++posLft;
    } else {
        --posLft;
    }
}

void irpRgt() {
    const int b = digitalRead(ENCR_B);
    if (b > 0) {
        --posRgt;
    } else {
        ++posRgt;
    }
}

int enc::getPos(const Wheel wheel) {
    switch (wheel) {
        case Wheel::LEFT:
            return posLft;
        case Wheel::RIGHT:
            return posRgt;
        case Wheel::UNKNOWN:
            return 0;
    }
}
