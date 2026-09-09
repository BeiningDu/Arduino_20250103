#include <Servo.h>                                                           /////////  头文件，调用舵机类Servo

//////////////////////////////////////////////////////////////////////////////////////  传感器  /////////////////////////////////////////////
class Sensor{
  public:
    int pinSensor[5];                                   ////传感器引脚
    int brightness[5];                                  ////传感数据储存
    int threshold[5];                                   ////感应阈值
    int test_order[5];                                  ////传感器读取顺序
    void sRead ();                                      ////读取传感数据
    void sPrint (int);                                  ////输出调试函数    
} sensor;                                               ////声明传感器sensor

void Sensor :: sRead () {
  for (int i = 0; i < 5; i ++) brightness[i] = analogRead (pinSensor[i]);
}

void Sensor :: sPrint (int time) {                      ////（输出间隔）
  for (int i = 0; i < 4; i ++) {
    Serial.print (brightness[i]);
    Serial.print ("--");
  }
  Serial.println (brightness[4]);
  delay (time);
}

///////////////////////////////////////////////////////////////////////////////////////  舵机（原舵机类Servo的公有派生）  ////////////////////
class Improved_Servo : public Servo {
  public:
    int serial = 2;                                     ////档位（赋初始值为2）
    int stdAngel;                                       ////角度标准值（直线）
    int rotate[5];                                      ////舵机旋转角度档位
    void getSerial ();                                  ////获取档位数据
    void Rotate ();                                     ////舵机旋转
} servo;                                                ////声明舵机servo

void Improved_Servo :: getSerial () {
  for (int i = 0; i < 5; i ++) {
    if (sensor.brightness[sensor.test_order[i]] < sensor.threshold[sensor.test_order[i]]) serial = sensor.test_order[i];
  }
}

void Improved_Servo :: Rotate () {
  write (stdAngel + rotate[serial]);
}

////////////////////////////////////////////////////////////////////////////////////////  电机组  //////////////////////////////////////////
class Electrical_Machinery {
  public:
    int pinDIR, pinSPD;                                  ////电机组引脚
    int Speed[5];                                        ////速度档位
    void Motor (int, int);                               ////驱动函数
} L_EM, R_EM;                                            ////声明左舵机L_EM和右舵机R_EM

void Electrical_Machinery :: Motor (int dir, int speed) {////（方向，速度档位）
  digitalWrite (pinDIR, dir);
  analogWrite (pinSPD, speed);
}

////////////////////////////////////////////////////////////////////////////////////////  项目  ////////////////////////////////////////////
void Project_Defined (int angel, int speed, int time) {  ////项目1——定义行驶
  servo.write (servo.stdAngel + angel);                  ////设置舵机角度为标准值

  L_EM.Motor (HIGH, speed);                               ////左轮驱动
  R_EM.Motor (LOW, speed);                               ////右轮驱动

  if (time != 0) delay (time);
}

void Project_Patrol_Line () {                            ////项目2——巡线行驶
  sensor.sRead ();                                       ////读取数据

  servo.getSerial ();                                    ////获取档位
  servo.Rotate ();                                       ////舵机旋转

  L_EM.Motor (HIGH, L_EM.Speed[servo.serial]);            ////左轮驱动
  R_EM.Motor (LOW, R_EM.Speed[servo.serial]);            ////右轮驱动
}

////////////////////////////////////////////////////////////////////////////////////////  主程序  ///////////////////////////////////////////
void setup () {
  Serial.begin (9600);                                   ////设置串口波特率（调试需要串口通信）

  sensor.pinSensor[0] = A0;                              ////设置传感器引脚
  sensor.pinSensor[1] = A1;
  sensor.pinSensor[2] = A2;
  sensor.pinSensor[3] = A3;
  sensor.pinSensor[4] = A4;

  sensor.threshold[0] = 370;                             ////设置阈值
  sensor.threshold[1] = 290;
  sensor.threshold[2] = 580;
  sensor.threshold[3] = 580;
  sensor.threshold[4] = 430;

  sensor.test_order[0] = 2;                              ////设置传感器读取顺序
  sensor.test_order[1] = 1;
  sensor.test_order[2] = 3;
  sensor.test_order[3] = 0;
  sensor.test_order[4] = 4;

  servo.stdAngel = 90;                                  ////设置标准值
  servo.attach (11);                                     ////设置舵机引脚10
  servo.write (servo.stdAngel);                          ////设置舵机初始角度
  servo.rotate[0] = -67;                                 ////设置舵机旋转角度
  servo.rotate[1] = -32;
  servo.rotate[2] = 0;
  servo.rotate[3] = 20;
  servo.rotate[4] = 48;

  L_EM.pinDIR = 7;                                       ////设置电机引脚
  L_EM.pinSPD = 6;
  R_EM.pinDIR = 4;
  R_EM.pinSPD = 5;

  pinMode (L_EM.pinDIR, OUTPUT);                         ////设置电机引脚为输出
  pinMode (L_EM.pinSPD, OUTPUT);
  pinMode (R_EM.pinDIR, OUTPUT);
  pinMode (R_EM.pinSPD, OUTPUT);  

  L_EM.Speed [0] = 255;                                  ////设置左轮速度档位
  L_EM.Speed [1] = 255;
  L_EM.Speed [2] = 255;
  L_EM.Speed [3] = 210;
  L_EM.Speed [4] = 150;

  R_EM.Speed [0] = 190;                                  ////设置右轮速度档位
  R_EM.Speed [1] = 225;
  R_EM.Speed [2] = 255;
  R_EM.Speed [3] = 255;
  R_EM.Speed [4] = 255;
}

void loop () {
  //                 调试
  /*
  sensor.sRead ();
  sensor.sPrint (500);
  /*
  //                 直线行驶
  /*
  Project_Defined (0, 255, 0);
  */
  //                 巡线行驶
  /*
  Project_Patrol_Line ();
  */
  Project_Patrol_Line ();
}