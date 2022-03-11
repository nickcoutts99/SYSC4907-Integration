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
const int numMeas = 11;
int samples[numMeas];

int j, i, swap_var, firstReading;
int duration[2];
float distance[2];

#define SPEED_OF_SOUND 0.034

int medianFiltering(int samples[]) {
  sort(samples);
  return samples[numMeas/2];
}

void sort(int samples[]) {
  for (i = 0 ; i < numMeas - 1; i++){
    for (j = 0 ; j < numMeas - i - 1; j++)
    {
      if (samples[j] > samples[j+1]){
        swap_var = samples[j];
        samples[j] = samples[j+1];
        samples[j+1] = swap_var;
      }
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin_1, OUTPUT);
  pinMode(echoPin_1, INPUT);
  pinMode(trigPin_2, OUTPUT);
  pinMode(echoPin_2, INPUT);
  firstReading = 1;
  lcd.begin(16,2);
  Serial.begin(9600);
}

void generateTrigger(int trigPin){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  delay(5000);

  if(firstReading) {
    Serial.print("| ");
    for(j = 0; j < numMeas; j++) {
      generateTrigger(trigPin_1);
      samples[j] = pulseIn(echoPin_1, HIGH);
      Serial.print(samples[j]);
      Serial.print(" ");
    }
    firstReading = 0;
  }
  else{
    
  }
  duration[0] = medianFiltering(samples);
  Serial.print(" * ");
  Serial.print(duration[0]);
  Serial.print(" * |");
//  //Front Ultrasonic
//  generateTrigger(trigPin_1);
  //duration[0] = pulseIn(echoPin_1, HIGH);
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
  delay(1000);
}
