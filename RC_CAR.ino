#include <SoftwareSerial.h>
SoftwareSerial HC05(3,4);
int LED_Pin = 7;
int speedPin_A = 6;
int speedPin_B = 5;
int trigPin = 8;
int echoPin = 13;
int soundPin = 2;

int mspeed = 160;
int tspeed = 150;
int gear = 1;
float duration, distance;

void setup() {
  HC05.begin(9600);
  Serial.begin(9600);
  pinMode(LED_Pin, OUTPUT); // 전조등
  pinMode(trigPin, OUTPUT); // 후방 센서
  pinMode(echoPin, INPUT);
  pinMode(soundPin, OUTPUT); // 클락션 및 후방센서 소리 출력
  pinMode(speedPin_A, OUTPUT); // 우측 바퀴 속도 제어
  pinMode(speedPin_B, OUTPUT); // 좌측 바퀴 속도 제어
  pinMode(9, OUTPUT); //오후
  pinMode(10, OUTPUT); //오직
  pinMode(11, OUTPUT); //왼직
  pinMode(12, OUTPUT); //왼후
}

void loop()
{
  String myString = "";
  while (HC05.available() > 0)
  {
    char HC05_Value = HC05.read();
    myString += HC05_Value;
    delay(10);
  }
  
  if (!myString.equals("")) {
    Serial.println(myString);
  }

  // 기어
  // 최저 속도 150. 최대 속도 255. 150미만의 속도로는 움직이지 않음.
  if(myString.indexOf("k") >= 0) {
    gear+=1;
    if (gear == 2) {
      Serial.println("2단");
      mspeed = 200;
      tspeed = 150;
    }
    else if (gear == 3) {
      Serial.println("3단");
      mspeed = 255;
      tspeed = 200;
    }
    else if (gear > 3) {
      Serial.println("최대기어 입니다.");
      gear = 3;
    }
  }
  if(myString.indexOf("K") >= 0) {
    gear-=1;
    if (gear == 1) {
      Serial.println("1단");
      mspeed = 160;
      tspeed = 150;
    }
    else if (gear == 2) {
      Serial.println("2단");
      mspeed = 200;
      tspeed = 150;
    }
    else if (gear < 1) {
      Serial.println("더 이상 내릴 수 없습니다.");
      gear = 1;
    }
  }
  //

  // 전조등
  if (myString.indexOf("L") >= 0) {
    Light_On();
  }
  if (myString.indexOf("l") >= 0) {
    Light_Off()
  }
  //

  // 경적
  if (myString.indexOf("m") >= 0) {
    Clarkson();
  }
  //

  // 비상등
  if (myString.indexOf("E") >= 0) {
    Light_On();
  }
  if (myString.indexOf("z") >= 0) {
    Light_Off();
  }
  //
  
  if (myString.indexOf("b") >= 0) {
    Serial.println("Go");
    Go();
  }
  else if (myString.indexOf("g") >= 0) {
    Serial.println("Back");
    Back();
  }
  else if (myString.indexOf("d") >= 0) {
    Serial.println("Left");
    Left();
  }
  else if (myString.indexOf("e") >= 0) {
    Serial.println("Right");
    Right();
  }
  else if (myString.indexOf("i") >= 0) {
    Serial.println("Clockwise");
    TurnR();
  }
  else if (myString.indexOf("j") >= 0) {
    Serial.println("R Clockwise");
    TurnL();
  }
  else if (myString.indexOf("a") >= 0) {
    Serial.println("Go Left");
    Goleft();
  }
  else if (myString.indexOf("c") >= 0) {
    Serial.println("Go Right");
    Goright();    
  }
  else if (myString.indexOf("f") >= 0) {
    Serial.println("Back Left");
    Backleft();
  }
  else if (myString.indexOf("h") >= 0) {
    Serial.println("Back Right");
    Backright();
  }
  else if (myString.indexOf("S") >= 0) {
    Serial.println("RC stop");
    RCstop();
  }
  delay(10);
}

void Go() {
  analogWrite(speedPin_A, mspeed);
  analogWrite(speedPin_B, mspeed);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
}
void Goleft() {
  analogWrite(speedPin_A, tspeed);
  analogWrite(speedPin_B, mspeed);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
}
void Goright() {
  analogWrite(speedPin_A, mspeed);
  analogWrite(speedPin_B, tspeed);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
}
void Back() {
  analogWrite(speedPin_A, mspeed);
  analogWrite(speedPin_B, mspeed);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
}
void Backleft() {
  analogWrite(speedPin_A, tspeed);
  analogWrite(speedPin_B, mspeed);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
}
void Backright() {
  analogWrite(speedPin_A, mspeed);
  analogWrite(speedPin_B, tspeed);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
}
void Left() {
  analogWrite(speedPin_B, mspeed);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
}
void Right() {
  analogWrite(speedPin_A, mspeed);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
}
void TurnR() {
  analogWrite(speedPin_A, mspeed);
  analogWrite(speedPin_B, mspeed);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
}
void TurnL() {
  analogWrite(speedPin_A, mspeed);
  analogWrite(speedPin_B, mspeed);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
}
void RCstop() {
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
}

void Light_On() {
  digitalWrite(LED_Pin,HIGH);
}
void Light_Off() {
  digitalWrite(LED_Pin,LOW);
}

void Clarkson() {
  int S_num = 0;
  S_num += 1;
  if (S_num == 1) {
    tone(soundPin, 1023);
    delay(500);
    noTone(soundPin);
    S_num -= 1;
    }
  else noTone(soundPin); 
}

void BackSensor() {
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = ((float)(340*duration) / 10000) / 2;
  Serial. print("Duration :"); Serial. print(duration);
  Serial. print("\nDistance :"); Serial. print(distance);
  Serial. println("cm\n");
  if (distance <= 50) {
    tone(soundPin, 1023);
    delay(500);
    noTone(soundPin);
    delay(500);
  }
  else if (distance <= 20) {
    RCstop();
    noTone(soundPin);
  }
}
