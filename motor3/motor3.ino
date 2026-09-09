class Electrical_Machinery {
  public:
    int pinDIR, pinSPD;                                  ////电机组引脚
    int Speed[5];                                        ////速度档位
    void Motor (int, int);                               ////驱动函数
} L_EM, R_EM;                                            ////声明左舵机L_EM和右舵机R_EM

void Electrical_Machinery :: Motor (int dir, int speed) {
  digitalWrite (pinDIR, dir);
  analogWrite (pinSPD, speed);
}

void Project_Defined (int angel, int speed, int time) {  ////项目1——定义行驶
  L_EM.Motor (LOW, speed);                               ////左轮驱动
  R_EM.Motor (LOW, speed);                               ////右轮驱动

  if (time != 0) delay (time);
}

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
