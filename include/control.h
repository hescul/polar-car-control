//
// Created by Minh Nguyen on 12/1/2022.
//

#ifndef PID_CONTROL_H
#define PID_CONTROL_H

namespace ctr {
    bool ready();

    /**
     * Control the car motion to reach the point at (distance, degree) in polar coordinate. The relative origin is at
     * the center of the car.
     * @param distance - distance in meter.
     * @param degree - angle in degree [0; 360].
     */
    void process(float distance, float degree);

    void loop(bool debug = false);
}

#endif //PID_CONTROL_H
