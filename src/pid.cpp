#include "pid.h"

#include "param.h"

PID::PID(float KP, float KI, float KD) : _Kp(KP), _Ki(KI), _Kd(KD) {
  p = i = d = 0;
  d_speed[0] = d_speed[1] = 0;
  integral = 0;
}

float PID::calc(float target_value, float current_value) {
  d_speed[0] = d_speed[1];
  d_speed[1] = target_value - current_value;
  integral += (d_speed[1] + d_speed[0]) / 2.0f *
              ((float)SUMPLING_TIME_US / (float)1000000);
  if (integral > INTEGRAL_LIMIT)
    integral = INTEGRAL_LIMIT;
  else if (integral < -INTEGRAL_LIMIT)
    integral = -INTEGRAL_LIMIT;
  p = _Kp * d_speed[1];
  i = _Ki * integral;
  d = _Kd * (d_speed[0] - d_speed[1]) /
      ((float)SUMPLING_TIME_US / (float)1000000);
  return p + i + d;
}
