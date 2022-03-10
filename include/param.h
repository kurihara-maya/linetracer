#ifndef __PARAM_H__
#define __PARAM_H__

#define PI 3.14159265359
#define SUMPLING_TIME_US \
  10000  // タイマー割り込み周期 kHzオーダーつまり1000が理想
#define SERIAL_SUMPLING_TIME_US \
  20000  // タイマー割り込み周期 kHzオーダーつまり1000が理想
#define PERIOD 1000  // PWM制御のパルス幅 μs

#define EN_RESOLUTION_WHEEL0 200  // エンコーダーの分解能(車輪)
#define EN_RESOLUTION_WHEEL1 200  // エンコーダーの分解能(回転テーブル)
#define WHEEL_R 0.0635            // タイヤの半径 m
#define PWM_LIMIT_WHEEL0 0.90
#define PWM_LIMIT_WHEEL1 0.90
#define INTEGRAL_LIMIT 50.0  // PID制御のIの値の発散防止

#define Kp_WHEEL0 9.5
#define Ki_WHEEL0 0.3
#define Kd_WHEEL0 0.1

#define Kp_WHEEL1 9.5
#define Ki_WHEEL1 0.3
#define Kd_WHEEL1 0.1

#define PIN_GATE_DRIVER_ENABLE_WHEEL0 PB_5
#define PIN_PWM_P_WHEEL0 PA_10
#define PIN_PWM_N_WHEEL0 PA_11_ALT0

#define PIN_GATE_DRIVER_ENABLE_WHEEL1 PB_4
#define PIN_PWM_P_WHEEL1 PB_0_ALT0
#define PIN_PWM_N_WHEEL1 PB_1_ALT0

#define PIN_ENA_WHEEL0 PA_8
#define PIN_ENB_WHEEL0 PA_9

#define PIN_ENA_WHEEL1 PA_6
#define PIN_ENB_WHEEL1 PA_7

#endif  //__PARAM_H__