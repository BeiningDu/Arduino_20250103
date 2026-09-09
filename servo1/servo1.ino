#include<Servo.h>
Servo servo_11;

void setup() {
  // put your setup code here, to run once:
  servo_11.attach(11);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=85; i<=95; i++){
    servo_11.write(i);
    delay(300);
  }
  for (int i=95; i>=85; i--){
    servo_11.write(i);
    delay(300);
  }
}
