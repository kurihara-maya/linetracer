#include "comm.h"

Comm::Comm(Mbedserial &Ms) : _Ms(Ms) {
  _target_velocity0 = 0;
  _target_velocity1 = 0;
  _current_value[0] = 0;
  _current_value[1] = 0;
}

void Comm::receive() {
  _target_velocity0 = _Ms.getfloat[0];
  _target_velocity1 = _Ms.getfloat[1];
}

void Comm::send() {
  /*
  _current_value[0] = _target_velocity;
  _current_value[1] = _target_theta;
  */
  _Ms.float_write(_current_value, 2);
}