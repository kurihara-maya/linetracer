#include <mbed.h>

DigitalOut AIN1(PA_11);  // 1入力で前転
DigitalOut AIN2(PA_8);
PwmOut PWMA(PB_0);

DigitalOut BIN1(PB_4);  //前転
DigitalOut BIN2(PB_5);
PwmOut PWMB(PB_1);
int i = 0;
int j = 0;

DigitalOut Buzzer(PA_0);
DigitalIn push(PA_12);
DigitalIn dip1(PA_10);
DigitalIn dip2(PA_9);

int d1 = 0;
int d2 = 0;

AnalogIn s1(PA_7);
AnalogIn s2(PA_6);
AnalogIn s3(PA_5);
AnalogIn s4(PA_4);
AnalogIn s5(PA_3);
AnalogIn s6(PA_1);
int voltage_now1 = 0;
int voltage_now2 = 0;
int voltage_now3 = 0;
int voltage_now4 = 0;
int voltage_now5 = 0;
int voltage_now6 = 0;

int main(void) {
  Buzzer = 1;
  wait_us(1000000);
  Buzzer = 0;  //開始後一秒鳴らす
  wait_us(1000000);

  push.mode(PullUp);
  dip1.mode(PullUp);
  dip2.mode(PullUp);

  while (1) {
    AIN1 = 1;
    AIN2 = 0;
    BIN1 = 1;
    BIN2 = 0;
    PWMA = 0.1;
    PWMB = 0.1;
    printf("moving/n");
  }
}

//   while (1) {
//     voltage_now1 = s1.read_u16();
//     voltage_now2 = s2.read_u16();
//     voltage_now3 = s3.read_u16();
//     voltage_now4 = s4.read_u16();
//     voltage_now5 = s5.read_u16();
//     voltage_now6 = s6.read_u16();
//     //  printf("%u\n",voltage_now1);
//     if (voltage_now4 > 300 && voltage_now5 > 300) {
//       AIN1 = 1;
//       AIN2 = 0;
//       BIN1 = 1;
//       BIN2 = 0;
//       PWMA = 0.1;
//       PWMB = 0.1;  //直進
//       printf("front,%u,%u\n", voltage_now5, voltage_now4);
//     } else if (voltage_now3 > 300) {
//       AIN1 = 1;
//       AIN2 = 0;
//       BIN1 = 1;
//       BIN2 = 0;
//       PWMA = 0.2;
//       PWMB = 0.3;  //右
//       printf("right\n");
//     } else if (voltage_now6 > 300) {
//       AIN1 = 1;
//       AIN2 = 0;
//       BIN1 = 1;
//       BIN2 = 0;
//       PWMA = 0.3;
//       PWMB = 0.2;  //左
//       printf("left%u\n", voltage_now6);
//     } else {
//       AIN1 = 0;
//       AIN2 = 1;
//       BIN1 = 0;
//       BIN2 = 1;
//       PWMA = 0.1;
//       PWMB = 0.1;  //ゆっくり後退
//       printf("back\n");
//     }
//   }
// }

// while (1) {

// int d1=dip1.read();
// int d2=dip2.read();
// printf("%d,%d\n", d1, d2);
// if (push.read() == 0 && dip1.read() == 0 && dip2.read() == 1) {
//   printf("omg\n");
//   Buzzer = 1;
//   wait_us(500000);
//   Buzzer = 0;
//   wait_us(100000);  //１High 2low　短１
// } else if (push.read() == 0 && dip1.read() == 1 && dip2.read() == 0) {
//   Buzzer = 1;
//   wait_us(500000);
//   Buzzer = 0;
//   wait_us(100000);
//   Buzzer = 1;
//   wait_us(500000);
//   Buzzer = 0;
//   wait_us(100000);  // 1low ２High 短２
// } else if (push.read() == 0 && dip1.read() == 0 && dip2.read() == 0) {
//   Buzzer = 1;
//   wait_us(1000000);
//   Buzzer = 0;
//   wait_us(100000);  //１High ２HIGH 長１
// } else {
//   Buzzer = 0;
//   wait_us(100);  //無音
// }
// }
