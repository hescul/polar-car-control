//
// Created by Minh Nguyen on 11/30/2022.
//

#ifndef PID_MOTOR_H
#define PID_MOTOR_H

#include "wheel.h"

namespace mtr {
    void init();

    void set(Wheel wheel, Direction dir, int val);
}

#endif //PID_MOTOR_H
