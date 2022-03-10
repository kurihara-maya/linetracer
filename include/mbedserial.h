// mbedserial.h
// serial communication : mbed <-> ROS

#ifndef _MBEDSERIAL_
#define _MBEDSERIAL_

#include <mbed.h>
#include <stdio.h>
#include <string.h>

#include <chrono>

// mbedserial class
class Mbedserial {
 private:
  char msg_buf[64];
  int bufsize;
  char endmsg;
  int lost_time_threshold;
  std::chrono::system_clock::time_point last_rcv_time;
  BufferedSerial &rospc;

 public:
  float getfloat[4];
  int floatarraysize;
  Mbedserial(BufferedSerial &);
  void float_write(float *array, int arraysize);
  bool isRecieved();
  void rcv_callback();
};

#endif