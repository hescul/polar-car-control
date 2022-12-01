//
// Created by Minh Nguyen on 12/1/2022.
//

#ifndef PID_CONTROL_H
#define PID_CONTROL_H

namespace ctr {
    bool ready();

    void process(float distance, float degree);

    void loop(bool debug = false);
}

#endif //PID_CONTROL_H
