//
// Created by Minh Nguyen on 11/29/2022.
//

#ifndef PID_CONFIG_H
#define PID_CONFIG_H

#include <stdint-gcc.h>

constexpr uint8_t ENCL_A = 2;   // hardware interrupt
constexpr uint8_t ENCL_B = 4;

constexpr uint8_t ENCR_A = 3;   // hardware interrupt
constexpr uint8_t ENCR_B = 5;

constexpr long BLE_BR = 9600;
constexpr uint8_t BLE_TX = 13;  // software serial
constexpr uint8_t BLE_RX = 12;  // software serial

constexpr uint8_t PWML = 10;    // PWM
constexpr uint8_t INL_1 = 7;
constexpr uint8_t INL_2 = 6;

constexpr uint8_t PWMR = 11;    // PWM
constexpr uint8_t INR_1 = 9;
constexpr uint8_t INR_2 = 8;

#endif //PID_CONFIG_H
