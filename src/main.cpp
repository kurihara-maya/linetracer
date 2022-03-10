#include <mbed.h>

DigitalOut AIN1(PA_11);  // 1入力で前転
DigitalOut AIN2(PA_8);
PwmOut PWMA(PB_0);

DigitalOut BIN1(PB_4);  //前転
DigitalOut BIN2(PB_5);
PwmOut PWMB(PB_1);
int i = 0;
int j = 0;

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
  while (1) {
    PWMA.period_us(20000);
    PWMB.period_us(20000);
    voltage_now1 = s1.read_u16();
    voltage_now2 = s2.read_u16();
    voltage_now3 = s3.read_u16();
    voltage_now4 = s4.read_u16();
    voltage_now5 = s5.read_u16();
    voltage_now6 = s6.read_u16();
    //  printf("%u\n",voltage_now1);
    if (voltage_now4 > 500 || voltage_now5 > 500) {
      AIN1 = 1;
      AIN2 = 0;
      BIN1 = 1;
      BIN2 = 0;
      PWMA = 0.05;
      PWMB = 0.05;  //直進
      printf("front,%u,%u\n",voltage_now5, voltage_now4);
    } else if (voltage_now3 > 500) {
      AIN1 = 1;
      AIN2 = 0;
      BIN1 = 1;
      BIN2 = 0;
      PWMA = 0.05;
      PWMB = 0.07;  //右
      printf("right\n");
    } else if (voltage_now6 > 500) {
      AIN1 = 1;
      AIN2 = 0;
      BIN1 = 1;
      BIN2 = 0;
      PWMA = 0.07;
      PWMB = 0.05;  //左
      printf("left%u\n", voltage_now6);
    } else {
      AIN1 = 0;
      AIN2 = 1;
      BIN1 = 0;
      BIN2 = 1;
      PWMA = 0.05;
      PWMB = 0.05;  //ゆっくり後退
      printf("back\n");
    }
  }
}