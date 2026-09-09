#include <Servo.h>

class LineSensor {
  public:
    int pins[5];
    int values[5];
    int thresholds[5];
    int priority[5];
    void readValues();
} lineSensor;

void LineSensor::readValues() {
  for (int i = 0; i < 5; i++) values[i] = analogRead(pins[i]);
}

class CustomServo : public Servo {
  public:
    int selectedIndex = 2;
    int baseAngle;
    int adjustments[5];
    void determineIndex();
    void rotateToTarget();
} motorServo;

void CustomServo::determineIndex() {
  for (int i = 0; i < 5; i++) {
    if (lineSensor.values[lineSensor.priority[i]] < lineSensor.thresholds[lineSensor.priority[i]])
      selectedIndex = lineSensor.priority[i];
  }
}

void CustomServo::rotateToTarget() {
  write(baseAngle + adjustments[selectedIndex]);
}

class MotorControl {
  public:
    int pinDirection, pinSpeed;
    int speeds[5];
    void setSpeed(int direction, int speed);
} leftMotor, rightMotor;

void MotorControl::setSpeed(int direction, int speed) {
  digitalWrite(pinDirection, direction);
  analogWrite(pinSpeed, speed);
}

void straightDrive(int angle, int speed, int duration) {
  motorServo.write(motorServo.baseAngle + angle);
  leftMotor.setSpeed(HIGH, speed);
  rightMotor.setSpeed(LOW, speed);
  if (duration > 0) delay(duration);
}

void lineFollowingDrive() {
  lineSensor.readValues();
  motorServo.determineIndex();
  motorServo.rotateToTarget();
  leftMotor.setSpeed(HIGH, leftMotor.speeds[motorServo.selectedIndex]);
  rightMotor.setSpeed(LOW, rightMotor.speeds[motorServo.selectedIndex]);
}

void setup() {
  Serial.begin(9600);

  int sensorPins[] = {A0, A1, A2, A3, A4};
  int sensorThresholds[] = {350, 270, 550, 550, 400};
  int sensorPriority[] = {2, 1, 3, 0, 4};

  for (int i = 0; i < 5; i++) {
    lineSensor.pins[i] = sensorPins[i];
    lineSensor.thresholds[i] = sensorThresholds[i];
    lineSensor.priority[i] = sensorPriority[i];
  }

  motorServo.baseAngle = 92;
  motorServo.attach(11);
  motorServo.write(motorServo.baseAngle);
  int servoAdjustments[] = {-63, -30, 0, 20, 48};
  for (int i = 0; i < 5; i++) motorServo.adjustments[i] = servoAdjustments[i];

  leftMotor.pinDirection = 7;
  leftMotor.pinSpeed = 6;
  rightMotor.pinDirection = 4;
  rightMotor.pinSpeed = 5;

  pinMode(leftMotor.pinDirection, OUTPUT);
  pinMode(leftMotor.pinSpeed, OUTPUT);
  pinMode(rightMotor.pinDirection, OUTPUT);
  pinMode(rightMotor.pinSpeed, OUTPUT);

  int leftMotorSpeeds[] = {255, 255, 255, 215, 165};
  int rightMotorSpeeds[] = {190, 225, 255, 255, 255};
  for (int i = 0; i < 5; i++) {
    leftMotor.speeds[i] = leftMotorSpeeds[i];
    rightMotor.speeds[i] = rightMotorSpeeds[i];
  }
}

void loop() {
  //straightDrive(0,255,30000)
  lineFollowingDrive();
}