//
// Created by Minh Nguyen on 11/29/2022.
//

#ifndef PID_ENCODER_H
#define PID_ENCODER_H

#include "wheel.h"

namespace enc {
    /**
     * Initializes encoder pinouts.
     */
    void init();

    /**
     * Resets the states of the encoders.
     */
    void reset();

    /**
     * Returns the current position value of the encoder.
     * @param encoder - the Encoder to be queried.
     */
    int getPos(Wheel);
}

#endif //PID_ENCODER_H
