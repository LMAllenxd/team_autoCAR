// 馬達控制腳位
const int ENA = 3;
const int IN1 = 2;
const int IN2 = 4;
const int ENB = 5;
const int IN3 = 6;
const int IN4 = 7;
const int Trig = 11, Echo = 10;

// 紅外線感測器腳位
const int IR_Left = 8;
const int IR_Right = 9;

// 基本速度設定
int leftSpeed = 85;
int rightSpeed = 85;
int rotateSpeedBuff = 37;

// 轉彎時加速速度
int Rrightspeed;
int Rleftspeed;

void setup() {
// 設定腳位模式
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IR_Left, INPUT);
  pinMode(IR_Right, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);

  // 計算轉彎速度
  Rrightspeed = rightSpeed + rotateSpeedBuff;
  Rleftspeed = leftSpeed + rotateSpeedBuff;

  // 初始化序列埠
  Serial.begin(9600);
  Serial.println("啟動完成");
}

// 前進
void moveForward(int speedL, int speedR) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speedL);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speedR);

  Serial.println("前進");
}

// 停止
void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  Serial.println("停止");
}

// 弧形左轉（右輪前進、左輪停）
void turnLeft(int speedL, int speedR) {
  digitalWrite(IN1, LOW);  // 左輪停止
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);

  digitalWrite(IN3, HIGH); // 右輪前進
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speedR);

  Serial.println("左轉（弧形）");
}

// 弧形右轉（左輪前進、右輪停）
void turnRight(int speedL, int speedR) {
  digitalWrite(IN1, HIGH); // 左輪前進
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speedL);

  digitalWrite(IN3, LOW);  // 右輪停止
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);

  Serial.println("右轉（弧形）");
}

void loop() {
  int leftIR = digitalRead(IR_Left);
  int rightIR = digitalRead(IR_Right);

  // 超音波測距
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  long duration = pulseIn(Echo, HIGH);
  float distance = duration / 58.0;

  Serial.print("距離: ");
  Serial.print(distance);
  Serial.println(" cm");

  // 碰到障礙物就停止
  if (distance < 15) {
  Serial.println("障礙物偵測！暫停直到清除");
  stopMotors();
  while (distance < 15) {
    // 不斷重新測距直到障礙物離開
    digitalWrite(Trig, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig, LOW);
    duration = pulseIn(Echo, HIGH);
    distance = duration / 58.0;

    Serial.print("等待距離恢復中... ");
    Serial.println(distance);
    delay(300);
  }
  Serial.println("障礙物清除，繼續行進");
}

  // 紅外線循跡控制
  if (leftIR == LOW && rightIR == LOW) {
    moveForward(leftSpeed, rightSpeed);
    delay(40);
    stopMotors();
    delay(20);
  }
  else if (leftIR == LOW && rightIR == HIGH) {
    Serial.println("偵測右偏，左轉修正");
    turnLeft(leftSpeed, Rrightspeed);
    delay(100);
    stopMotors();
  }
  else if (leftIR == HIGH && rightIR == LOW) {
    Serial.println("偵測左偏，右轉修正");
    turnRight(Rleftspeed, rightSpeed);
    delay(100);
    stopMotors();
  }
  else {
    stopMotors();
  }

  delay(27); // loop 間隔
