//
// Created by Minh Nguyen on 11/29/2022.
//

#include <Arduino.h>
#include "config.h"
#include "encoder.h"
#include <util/atomic.h>

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
    int pos;
    switch (wheel) {
        case Wheel::LEFT:
            // Read the position in an atomic block to avoid a potential
            // misread if the interrupt coincides with this code running
            ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
                pos = posLft;
            }
            return pos;
        case Wheel::RIGHT:
            ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
                pos = posRgt;
            }
            return pos;
        case Wheel::UNKNOWN:
            pos = 0;
            return pos;
    }
}
