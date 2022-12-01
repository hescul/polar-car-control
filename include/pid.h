//
// Created by Minh Nguyen on 11/30/2022.
//

#ifndef PID_PID_H
#define PID_PID_H

#include "wheel.h"

namespace pid {
    constexpr auto MIN_ERROR = 4;

    constexpr auto MAX_TORQUE = 32767;

    bool ready();

    void start(int target, bool inverse = false);

    void loop(bool debug = false);
}

#endif //PID_PID_H
