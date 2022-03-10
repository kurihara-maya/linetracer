#ifndef __COMM_H
#define __COMM_H

#include "mbed.h"
#include "mbedserial.h"
#include "param.h"

class Comm {
 public:
  Comm(Mbedserial &Ms);
  void receive(void);
  void send(void);
  void AttachCurrentVelocity0(float velocity) { _current_value[0] = velocity; };
  void AttachCurrentVelocity1(float velocity) { _current_value[1] = velocity; };
  float getTargetVelocity0(void) { return _target_velocity0; };
  float getTargetVelocity1(void) { return _target_velocity1; };

 private:
  Mbedserial &_Ms;
  float _target_velocity0;
  float _target_velocity1;
  float _current_value[2];
};

#endif