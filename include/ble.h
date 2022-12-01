//
// Created by Minh Nguyen on 11/30/2022.
//

#ifndef PID_BLE_H
#define PID_BLE_H

#include <Arduino.h>

namespace ble {
    void init();

    bool recv();

    /**
     * Parses the incoming polar coordinates. The expected form is "d:a#" where d is the distance and a is the
     * angle, both in float.
     * @param distance - out parameter for the parsed distance value.
     * @param degree - out parameter for the parsed degree value.
     * @return a boolean indicates if the reading is success (i.e. the values of distance and degree are valid).
     */
    bool read(float *distance, float *degree);
}

#endif //PID_BLE_H
