#include <math.h>
#include "vectors.h"
#include "helpers.h"
// Define Input Connections
#define CH1 3
#define CH2 5
#define CH3 6
#define CH4 9
#define CH5 10
#define CH6 11

// Integers to represent values from sticks and pots
int ch1Value;
int ch2Value;
int ch3Value;
int ch4Value;

// Boolean to represent switch value
bool ch5Value;
bool ch6Value;

bool vectorApplied;
int direction = 0;


enum hexState {
  Stand,
  Walk,
  Idle,
  Leaning
};
enum Gait {
  Tripod,
  Crab
};
Vector3 currentPoints[6];
Vector2 centerPoint;
int legs[6][3]{
  { 23, 22, 21 },  //Leg1; Coxa, Fermur, Tibia
  { 27, 26, 25 },  //Leg2
  { 31, 30, 29 },  //Leg3

  { 15, 14, 13 },  //leg4
  { 11, 10, 9 },   //leg5
  { 7, 6, 5 },     //leg6
};
/* Leg conf
6 1
5-2
4 3
*/
int FL = 80;
int TL = 120;
float idleTime;
double timeSinceLastInput;
hexState currentState = Stand;
Gait currentGait = Tripod;
void setup() {
  Serial.begin(115200);
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT);
  pinMode(CH5, INPUT);
  pinMode(CH6, INPUT);
  /*  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 4; j++) {
      
      Serial.print("#");
      Serial.print(legs[i][j]);
      Serial.print(" P");
      Serial.print(1500);
      Serial.print(" T");
      Serial.println(200);
    }
  }*/
  moveLeg(0, Vector3(0, 100, -90));
  moveLeg(1, Vector3(0, 100, -90));
  moveLeg(2, Vector3(0, 100, -90));
  moveLeg(3, Vector3(0, 100, -90));
  moveLeg(4, Vector3(0, 100, -90));
  moveLeg(5, Vector3(0, 100, -90));
}



void loop() {
  ch1Value = readChannel(CH1, -50, 50, 0);
  ch2Value = readChannel(CH2, -50, 50, 0);
  ch3Value = readChannel(CH3, -40, 40, 0);  //x
  ch4Value = readChannel(CH4, -40, 40, 0);  //y
  switch (currentState) {
    case Stand:
      moveLeg(0, Vector3(0, 100, -90));
      moveLeg(1, Vector3(0, 100, -90));
      moveLeg(2, Vector3(0, 100, -90));
      moveLeg(3, Vector3(0, 100, -90));
      moveLeg(4, Vector3(0, 100, -90));
      moveLeg(5, Vector3(0, 100, -90));
      break;
    case Idle:
      moveLeg(0, Vector3(0, 10, 0));
      moveLeg(1, Vector3(0, 10, 0));
      moveLeg(2, Vector3(0, 10, 0));
      moveLeg(3, Vector3(0, 10, 0));
      moveLeg(4, Vector3(0, 10, 0));
      moveLeg(5, Vector3(0, 10, 0));
      break;
    case Leaning:
      bodyMovement(Vector2(ch3Value - centerPoint.x, ch4Value - centerPoint.y));
      centerPoint = Vector2(ch3Value, ch4Value);
      break;
    case Walk:
      walk(Vector3(50, 0, -90));
      break;
  }
  if (abs(ch1Value) >= 10 || abs(ch2Value) >= 10) {
    currentState = Walk;
    timeSinceLastInput = millis();
  }
  if (abs(ch3Value) >= 10 || abs(ch4Value) >= 10) {
    currentState = Leaning;
    timeSinceLastInput = millis();
    return;
  }

  if (abs(timeSinceLastInput - millis()) > 5) {
    currentState = Stand;
    return;
  }
}
void moveLeg(int legNumber, Vector3 pos) {
  int time = 150;  //POG time
  currentPoints[legNumber] = pos;
  float xPos = pos.x;
  float yPos = pos.y;
  float zPos = pos.z;

  float H = sqrt(pow(yPos, 2) + pow(xPos, 2));
  float L = sqrt(pow(zPos, 2) + pow(H, 2));
  //*********************************************************
  //                         J1
  double J1 = atan2(xPos, yPos);

  J1 = J1 + (3.14 / 2);
  J1 = (J1 * 180) / 3.14;
  //*********************************************************
  //                         J2
  double A1 = atan2(zPos, H);
  double A2 = acos((pow(L, 2) + pow(FL, 2) - pow(TL, 2)) / (2 * L * FL));
  double J2 = A2 + ((3.1415 / 2) + A1);
  J2 = (J2 * 180) / 3.14;
  //*********************************************************
  //                         J3
  double J3 = acos((pow(FL, 2) + pow(TL, 2) - pow(L, 2)) / (2 * FL * TL));
  J3 = (J3 * 180) / 3.14;
  //*********************************************************
  //                  Changing units :o
  J1 = int(J1);
  J2 = int(J2);
  J3 = int(J3);
  if (legNumber > 2) {
    J1 = map(J1, 0, 180, 2500, 500);
    J2 = map(J2, 0, 180, 500, 2500);
    J3 = map(J3, 0, 180, 2500, 500);
  } else {
    J1 = map(J1, 0, 180, 2500, 500);
    J2 = map(J2, 0, 180, 2500, 500);
    J3 = map(J3, 0, 180, 500, 2500);
  }
  //*********************************************************
  //                    moving servos
  Serial.print("#");
  Serial.print(legs[legNumber][0]);
  Serial.print(" P");
  Serial.print(J1);
  Serial.print(" T");
  Serial.print(time);

  Serial.print(" #");
  Serial.print(legs[legNumber][1]);
  Serial.print(" P");
  Serial.print(J2);
  Serial.print(" T");
  Serial.print(time);

  Serial.print(" #");
  Serial.print(legs[legNumber][2]);
  Serial.print(" P");
  Serial.print(J3);
  Serial.print(" T");
  Serial.print(time);
  Serial.println("");

  /* Serial.print(" #");
  Serial.print(24);
  Serial.print(" P");
  Serial.print(2423);
  Serial.print(" T");
  Serial.print(time);
  Serial.println("");*/
}
