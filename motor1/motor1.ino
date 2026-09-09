int A_PWM = 6;
int A_DIR = 7;
int B_PWM = 4;
int B_DIR = 5;

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
}

void loop() {
  // put your main code here, to run repeatedly:
  A_Motor(HIGH,125);
  B_Motor(HIGH,125);
  delay(1000);
  A_Motor(LOW,80);
  B_Motor(LOW,80);
  delay(1000);
}
