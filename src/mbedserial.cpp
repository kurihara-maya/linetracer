// mbedserial.cpp
// serial communication : mbed <-> ROS

#include "mbedserial.h"

/***********************init***********************/
void _nullfunc() { ; };

Mbedserial::Mbedserial(BufferedSerial &pc) : rospc(pc) {
  bufsize = 0;
  endmsg = '\n';
  floatarraysize = 0;
  lost_time_threshold = 2000;

  last_rcv_time = std::chrono::system_clock::now();
}

/**********************receive**********************/

// メモ
// Mbedserial内でやり取りされるデータはリトルエンディアンであることに注意

void Mbedserial::rcv_callback() {
  while (true) {
    ThisThread::yield();
    char tmp_buf[16] = {0};
    if (!rospc.readable()) continue;
    int recv_num = rospc.read(tmp_buf, 16);

    // 1つも受信しておらず、今受信したデータの頭がfの時のみ受信結果を保存する
    if (bufsize == 0 && tmp_buf[0] != 'f') {
      continue;
    }
    memcpy(msg_buf + bufsize, tmp_buf, recv_num);
    bufsize += recv_num;

    // 保存した受信結果の末尾がendmsgならparseを開始する
    if (msg_buf[bufsize - 1] != endmsg) continue;

    // このプログラムではfloat2つしか送らないはずなので2個*4Byte + 6Byte
    constexpr int correct_msg_size = 2 * 4 + 6;

    // 受信するデータの大きさは決まっているので、後ろからその分を切り出してゴミを消す
    char trimed[correct_msg_size] = {0};
    memcpy(trimed, msg_buf + (bufsize - correct_msg_size), correct_msg_size);

    if (trimed[0] == 'f') {
      floatarraysize = *(int *)(&trimed[1]);
      if (floatarraysize != 2) {
        const char *msg = "floatarraysize is not 2\n";
        rospc.write(msg, strlen(msg));
        bufsize = 0;
        continue;
      }
      // bufsizeがこの値より大きいことは上で切り出しをしているのでない
      if (bufsize < floatarraysize * 4 + 6) {
        char msg[50];
        sprintf(msg, "received length isn't correct: %d", bufsize);
        rospc.write(msg, strlen(msg));
        bufsize = 0;
        continue;
      }

      for (int i = 0; i < floatarraysize; i++) {
        getfloat[i] = *(float *)(&trimed[i * 4 + 5]);
        // memcpy(&getfloat[i], &msg_buf[i * 4 + 5], 4);
      }
    }
    bufsize = 0;
    last_rcv_time = std::chrono::system_clock::now();
  }
}

bool Mbedserial::isRecieved() {
  auto current_time = std::chrono::system_clock::now();
  const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                           current_time - last_rcv_time)
                           .count();

  if (elapsed < lost_time_threshold) {
    return true;
  } else {
    return false;
  }
}

/***********************send***********************/

int pub_wait_time = 8;  // ms

void Mbedserial::float_write(float array[], int arraysize) {
  // send data type
  char msg_type = 'f';
  rospc.write(&msg_type, 1);

  // send array size
  char arraysize_c[4];
  *(int *)arraysize_c = arraysize;
  // memcpy(arraysize_c, &arraysize, 4);
  rospc.write(arraysize_c, 4);

  // send float data
  char array_c[4];
  for (int i = 0; i < arraysize; i++) {
    *(float *)array_c = array[i];
    // memcpy(array_c, &array[i], 4);
    rospc.write(array_c, 4);
  }

  // send end message
  rospc.write(&endmsg, 1);
  // wait_ms(pub_wait_time);
}
