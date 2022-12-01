//
// Created by Minh Nguyen on 11/30/2022.
//

#include <SoftwareSerial.h>
#include "config.h"
#include "ble.h"

SoftwareSerial bleSerial(BLE_TX, BLE_RX);

void ble::init() {
    bleSerial.begin(BLE_BR);
}

bool ble::recv() {
    return bleSerial.available();
}

bool ble::read(float *distance, float *degree) {
    String data = bleSerial.readStringUntil('#');
    int sep = data.indexOf(':');
    if (sep < 0) {
        return false;
    }
    String d = data.substring(0, sep);
    float distValue = d.toFloat();
    if (distValue <= 0) {
        return false;
    }
    String a = data.substring(sep + 1);
    float degValue = a.toFloat();
    *distance = distValue;
    *degree = degValue;
    return true;
}