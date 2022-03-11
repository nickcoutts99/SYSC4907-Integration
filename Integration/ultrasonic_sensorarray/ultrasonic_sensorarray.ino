#include <LiquidCrystal.h>
#define MAX_SENSORS (6)
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
int samples[MAX_SENSORS][numMeas];
int trigPins[] = {trigPin_1, trigPin_2, trigPin_3, trigPin_4, trigPin_5, trigPin_6};
int echoPins[] = {echoPin_1, echoPin_2, echoPin_3, echoPin_4, echoPin_5, echoPin_6};

int j, i, swap_var, firstReading;
int currIndex;
int duration[MAX_SENSORS];
float distance[MAX_SENSORS];
int numSensors;

#define SPEED_OF_SOUND 0.034

void setup() {
  // put your setup code here, to run once:
  numSensors = 2;
  currIndex = 0;
  firstReading = 1;
 // trigPins = {trigPin_1, trigPin_2, trigPin_3, trigPin_4, trigPin_5, trigPin_6};
  //echoPins = ;
  for(int i = 0; i < numSensors; i++){
    pinMode(trigPins[i],OUTPUT);
    pinMode(echoPins[i], INPUT);
  }
  lcd.begin(16,2);
  Serial.begin(9600);
}

int medianFiltering(int samples[]) {
  sort(samples);
  Serial.print("| ");
  for(int i = 0; i < numMeas; i++){
    Serial.print(samples[i]);
    Serial.print(" ");
  }
  return samples[numMeas/2];
}

void sort(int samples[]) {
  for (i = 0 ; i < numMeas - 1; i++){
    for (j = 0 ; j < numMeas - i - 1; j++) {
      if (samples[j] > samples[j+1]){
        swap_var = samples[j];
        samples[j] = samples[j+1];
        samples[j+1] = swap_var;
      }
    }
  }
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
  //delay(5000);

  if(firstReading) {
    for(int currSensor = 0; currSensor < numSensors; currSensor++){
      for(j = 0; j < numMeas; j++) {
        generateTrigger(trigPins[currSensor]);
        samples[currSensor][j] = pulseIn(echoPins[currSensor], HIGH);
      } 
      duration[currSensor] = medianFiltering(samples[currSensor]);
      distance[currSensor] = duration[currSensor] * SPEED_OF_SOUND / 2;
    }
    firstReading = 0;

  }
  else{
    for(int currSensor = 0; currSensor < numSensors; currSensor++){
        generateTrigger(trigPins[currSensor]);
        samples[currSensor][currIndex] = pulseIn(echoPins[currSensor], HIGH);
        currIndex = (currIndex + 1) % numMeas;
        duration[currSensor] = medianFiltering(samples[currSensor]);
        distance[currSensor] = duration[currSensor] * SPEED_OF_SOUND / 2;
      } 
    }
  //lcd.print(duration[0]);
//  Serial.print(" * ");
//  Serial.print(duration[0]);
//  Serial.print(" * |");
//  //Front Ultrasonic
//  generateTrigger(trigPin_1);
  //duration[0] = pulseIn(echoPin_1, HIGH);
  
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
  for(int currSensor = 0; currSensor < numSensors; currSensor++){
  lcd.print(distance[currSensor]);
  lcd.print("  ");
  }
 
//  lcd.setCursor(0,1);
//  lcd.print("S2: ");
//  lcd.print(distance[1]);
//  lcd.print(" cm");
  delay(10);
}
