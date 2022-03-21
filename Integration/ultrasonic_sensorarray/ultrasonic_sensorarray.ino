#define MAX_SENSORS (6)

#define SPEED_OF_SOUND 0.034
#define LEFT_THRESHOLD (30.0)

#define MIDDLE_THRESHOLD (30.0)
#define RIGHT_THRESHOLD (30.0)
//front
int trigPin_1 = 12;
int echoPin_1 = 11;

//front left
int trigPin_2 = 9;
int echoPin_2 = 8;

//front right
int trigPin_3 = 2;
int echoPin_3 = 3;


//Object to close PIN
int objectDetectPin = 7;

//Measurements
const int numMeas = 11;
int samples[MAX_SENSORS][numMeas];
int trigPins[] = {trigPin_1, trigPin_2, trigPin_3};
int echoPins[] = {echoPin_1, echoPin_2, echoPin_3};

int j, i, swap_var, firstReading;
int currIndex;
int duration[MAX_SENSORS];
float distance[MAX_SENSORS];
int numSensors;

void setup() {
  // put your setup code here, to run once:
  numSensors = 3;
  currIndex = 0;
  firstReading = 1;
  for(int i = 0; i < numSensors; i++){
    pinMode(trigPins[i],OUTPUT);
    pinMode(echoPins[i], INPUT);
  }
  //Serial.begin(9600);
  pinMode(objectDetectPin, OUTPUT);
  
  for(int currSensor = 0; currSensor < numSensors; currSensor++){
      for(j = 0; j < numMeas; j++) {
        generateTrigger(trigPins[currSensor]);
        samples[currSensor][j] = pulseIn(echoPins[currSensor], HIGH);
      } 
      duration[currSensor] = medianFiltering(samples[currSensor]);
      distance[currSensor] = duration[currSensor] * SPEED_OF_SOUND / 2;
    }
    outputResults();
}

int medianFiltering(int samples[]) {
  sort(samples);
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

void outputResults(){
  if(distance[0] > 0 && distance[0] < MIDDLE_THRESHOLD || distance[1] > 0 && distance[1] < LEFT_THRESHOLD || distance[2] > 0 && distance[2] < RIGHT_THRESHOLD) {
        digitalWrite(objectDetectPin, HIGH); 
        //Serial.print("H ");
    } else {
        digitalWrite(objectDetectPin, LOW);
        //Serial.print("L ");
    }
}

void loop() {
// put your main code here, to run repeatedly:
  for(int currSensor = 0; currSensor < numSensors; currSensor++){
      generateTrigger(trigPins[currSensor]);
      samples[currSensor][currIndex] = pulseIn(echoPins[currSensor], HIGH);
      currIndex = (currIndex + 1) % numMeas;
      duration[currSensor] = medianFiltering(samples[currSensor]);
      distance[currSensor] = duration[currSensor] * SPEED_OF_SOUND / 2;
    } 
    outputResults();   
}
