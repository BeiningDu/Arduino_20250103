int A_PWM = 6;
int A_DIR = 7;
int B_PWM = 5;
int B_DIR = 4;
#include <Servo.h>
Servo servo_11;

void A_Motor(int dir,int speed) {
  digitalWrite(A_DIR, dir);
  analogWrite(A_PWM, speed);
}

void B_Motor(int dir,int speed) {
  digitalWrite(B_DIR, dir);
  analogWrite(B_PWM, speed);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(A_DIR, OUTPUT);
  pinMode(A_PWM, OUTPUT);
  pinMode(B_DIR, OUTPUT);
  pinMode(B_PWM, OUTPUT);
  servo_11.attach(11);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*
  for (int i=1; i<=255; i++){
    B_Motor(HIGH,255-i);
    A_Motor(HIGH,i);
    delay(30);
    /*
    Serial.print(analogWrite(A_PWM));
    Serial.print('--');
    Serial.println(analogWrite(A_PWM));
    */
  servo_11.write(92);
  B_Motor(LOW,255);
  A_Motor(HIGH,255);
  delay(10000);
  B_Motor(LOW,0);
  A_Motor(HIGH,0);
  delay(1000);
}
