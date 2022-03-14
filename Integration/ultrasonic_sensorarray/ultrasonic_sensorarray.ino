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


//Object to close PIN
int objectDetectPin = 7;

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
char transmittedMessage[5];

#define SPEED_OF_SOUND 0.034

void setup() {
  // put your setup code here, to run once:
  numSensors = 3;
  currIndex = 0;
  firstReading = 1;
  for(int i = 0; i < numSensors; i++){
    pinMode(trigPins[i],OUTPUT);
    pinMode(echoPins[i], INPUT);
  }
  pinMode(objectDetectPin, OUTPUT);
  Serial.begin(9600);
}

int medianFiltering(int samples[]) {
  sort(samples);
  //Serial.print("| ");
  for(int i = 0; i < numMeas; i++){
//    Serial.print(samples[i]);
//    Serial.print(" ");
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

    if(distance[0] < 30.0 || distance[1] < 30.0 || distance[2] < 30.0) {
        digitalWrite(objectDetectPin, HIGH);
    } else {
      digitalWrite(objectDetectPin, LOW);
    }
  
}
