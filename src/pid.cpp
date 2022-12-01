//
// Created by Minh Nguyen on 11/30/2022.
//

#include <Arduino.h>
#include "pid.h"
#include "encoder.h"
#include "motor.h"

// =========== Principle ===========
// u(t) = kp * e(t) + ki * integral[e(t).dt] + kd * de/dt
// integral[e(t).dt] ~ eIntg + e * deltaT
// de/dt ~ (e - ePrev) deltaT
// ==================================

void Pid::reset() {
    prevT_ = 0l;
    ePrev_ = 0.0f;
    eIntg_ = 0.0f;
    target_ = 0;
    wheel_ = Wheel::UNKNOWN;
    working_ = false;
}

bool Pid::ready() const {
    return !working_;
}

void Pid::start(const int target, const Wheel wheel) {
    target_ = target;
    wheel_ = wheel;
    working_ = true;
}

void Pid::loop(const bool debug) {
    if (working_ && wheel_ != Wheel::UNKNOWN && target_ != enc::getPos(wheel_)) {
        // delta T
        const long currT = static_cast<long>(micros());
        const auto deltaT = static_cast<float>((static_cast<float>(currT - prevT_)) / 1.0e6);
        prevT_ = currT;

        // error term (try swapping the sign if the algorithm is not working)
        const int e = target_ - enc::getPos(wheel_);

        // derivative
        const float devt = (e - ePrev_) / deltaT;

        // integral
        eIntg_ += e * deltaT;

        // control signal
        const float u = kp * e + ki * eIntg_ + kd * devt;

        // motor power
        auto pwr = static_cast<float>(fabs(static_cast<double>(u)));
        if (pwr > 255) {
            pwr = 255;
        }

        // motor direction
        Direction dir = Direction::FORWARD;
        if (u < 0) {
            dir = Direction::BACKWARD;
        } else if (abs(e) <= MIN_ERROR) {
            dir = Direction::STATIC;
        }

        // signal motor
        mtr::set(wheel_, dir, static_cast<int>(pwr));

        // store previous error
        ePrev_ = e;

        if (debug) {
            Serial.print("Wheel ");
            Serial.print(static_cast<int>(wheel_));
            Serial.print(":\t");
            Serial.print(target_);
            Serial.print("\t");
            Serial.print(enc::getPos(wheel_));
            Serial.println();
        }

        // reset states when reached the target
        if (dir == Direction::STATIC) {
            reset();
            enc::reset(wheel_);
        }
    }
}
