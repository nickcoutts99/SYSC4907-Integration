#include <LiquidCrystal.h>
//front
int trigPin_1 = 12;
int echoPin_1 = 11;

//front left
int trigPin_2 = 9;
int echoPin_2 = 10;

//front right
int trigPin_3 = 2;
int echoPin_3 = 3;

//back
int trigPin_4 = 7;
int echoPin_4 = 5;

//back left
int trigPin_5 = 6;
int echoPin_5 = 8;

//back right
int trigPin_6 = 9;
int echoPin_6 = 12;

//LCD stuff
int RS = 2;
int RW = 3;
int E = 4;
int DB4 = 5;
int DB5 = 6;
int DB6 = 7;
int DB7 = 8;
LiquidCrystal lcd(RS, RW, E, DB4, DB5, DB6, DB7);

//Measurements
const int numMeas = 10;
int samples[numMeas];

float avMeas, avMeas2;
int j;
float sum1, sum2;
int duration[2];
float distance[2];

#define SPEED_OF_SOUND 0.034

int medianFiltering() {
    
}
void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin_1, OUTPUT);
  pinMode(echoPin_1, INPUT);
  pinMode(trigPin_2, OUTPUT);
  pinMode(echoPin_2, INPUT);
  sum1 = 0;
  avMeas = 0;
  sum2 = 0;
  avMeas2 = 0;
  lcd.begin(16,2);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  delay(5000);

//  for(j=1; j < numMeas; j = j+1) {
//    digitalWrite(trigPin_1, LOW);
//    delayMicroseconds(10);
//    digitalWrite(trigPin_1, HIGH);
//    delayMicroseconds(10);
//    digitalWrite(trigPin_1, LOW);
//    duration[0] = pulseIn(echoPin_1, HIGH);
//    distance[0] = duration[0] * SPEED_OF_SOUND / 2;
//    Serial.print(distance[0]);
//    sum1 = sum1 + distance[0];
//  }
//
//  avMeas = sum1 / numMeas;
//
//  for(j=1; j < numMeas; j = j+1) {
//    digitalWrite(trigPin_2, LOW);
//    delayMicroseconds(10);
//    digitalWrite(trigPin_2, HIGH);
//    delayMicroseconds(10);
//    digitalWrite(trigPin_2, LOW);
//    duration[1] = pulseIn(echoPin_2, HIGH);
//    distance[1] = duration[1] * SPEED_OF_SOUND / 2;
//    Serial.print(distance[1]);
//    sum2 = sum2 + distance[1];
//  }

//  avMeas2 = sum2 / numMeas;

//  //Front Ultrasonic
  digitalWrite(trigPin_1, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin_1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_1, LOW);
  duration[0] = pulseIn(echoPin_1, HIGH);
  distance[0] = duration[0] * SPEED_OF_SOUND / 2;
  delay(25);

  //Front Left Ultrasonic
//  digitalWrite(trigPin_2, LOW);
//  delayMicroseconds(10);
//  digitalWrite(trigPin_2, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin_2, LOW);
//  duration[1] = pulseIn(echoPin_2, HIGH);
//  distance[1] = duration[1] * SPEED_OF_SOUND / 2;
//  delay(25);

  //Printing Ultrasonics
  lcd.setCursor(0,0);
  lcd.print("S1: ");
  lcd.print(distance[0]);
  lcd.print(" cm");
//  lcd.setCursor(0,1);
//  lcd.print("S2: ");
//  lcd.print(distance[1]);
//  lcd.print(" cm");
  avMeas = 0;
  avMeas2 = 0;
  sum1 = 0;
  sum2 = 0;
  delay(1000);
}
