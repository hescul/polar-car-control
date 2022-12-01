//
// Created by Minh Nguyen on 11/30/2022.
//

#ifndef PID_PID_H
#define PID_PID_H

#include "wheel.h"

class Pid {
public:
    void reset();

    bool ready() const;

    void start(int target, Wheel wheel);

    void loop(bool debug = false);

private:
    // keep track of pid variables between calculating iterations
    long prevT_ = 0l;    // for computing delta T
    float ePrev_ = 0.0f;  // for computing delta error
    float eIntg_ = 0.0f;  // estimates integral of error

    // states
    bool working_ = false;
    int target_ = 0;
    Wheel wheel_ = Wheel::UNKNOWN;

    // PID constants
    static constexpr auto kp = 1.0f;
    static constexpr auto ki = 0.0f;
    static constexpr auto kd = 0.025f;    // prevent overshoot

    // accepted error
    static constexpr auto MIN_ERROR = 1;
};

#endif //PID_PID_H
