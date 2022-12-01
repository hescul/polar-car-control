//
// Created by Minh Nguyen on 12/1/2022.
//

#include "control.h"
#include "pid.h"

static Pid lftPid = Pid();
static Pid rgtPid = Pid();

bool ctr::ready() {
    return lftPid.ready() && rgtPid.ready();
}

void ctr::loop(const bool debug) {
    lftPid.loop(debug);
    rgtPid.loop(debug);
}

void ctr::process(const float distance, const float degree) {

}