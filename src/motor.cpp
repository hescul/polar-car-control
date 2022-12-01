//
// Created by Minh Nguyen on 11/30/2022.
//

#include "motor.h"
#include "config.h"
#include <Arduino.h>

void mtr::init() {
    pinMode(POWR, OUTPUT);
    pinMode(INL_1, OUTPUT);
    pinMode(INL_2, OUTPUT);
    pinMode(INR_1, OUTPUT);
    pinMode(INR_2, OUTPUT);

    turn(Wheel::LEFT, Direction::STATIC);
    turn(Wheel::RIGHT, Direction::STATIC);
    power(0);
}

void mtr::turn(const Wheel wheel, const Direction dir) {
    uint8_t in1;
    uint8_t in2;
    switch (wheel) {
        case Wheel::LEFT:
            in1 = INL_1;
            in2 = INL_2;
            break;
        case Wheel::RIGHT:
            in1 = INR_1;
            in2 = INR_2;
            break;
    }
    switch (dir) {
        case Direction::FORWARD:
            digitalWrite(in1, HIGH);
            digitalWrite(in2, LOW);
            break;
        case Direction::BACKWARD:
            digitalWrite(in1, LOW);
            digitalWrite(in2, HIGH);
            break;
        case Direction::STATIC:
            digitalWrite(in1, LOW);
            digitalWrite(in2, LOW);
            break;
    }
}

void mtr::power(const int val) {
    analogWrite(POWR, val);
}
