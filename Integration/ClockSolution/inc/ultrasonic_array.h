#ifndef ULTRASONIC_ARRAY_H
#define ULTRASONIC_ARRAY_H

#include "MKL25Z4.h"
#include "queue.h"

#define NUM_SENSORS (2)
#define NUM_FRONT_SENSORS (2)
#define NUM_SAMPLES (3)
#define PRESCALE_FACTOR (8)

//Structure for each type of trigger (one for front of car and one for rear of car)
typedef struct {
	uint32_t ultrasonicTrigSCGCMask;
	PORT_Type* trigPort;
	GPIO_Type* trigPortGPIO;
	uint32_t trigPin;
} TRIG_TYPE;

//Structure for each ultrasonic sensor
typedef struct 
{
	//Hold temporary values
	int index;
	int ticksElapsed;
	int measureFlag;
	volatile int isEchoFalling;
	
	//Running sum
	float measurementSum;
	
	//Trigger
	TRIG_TYPE trigger;
	
	//Echo
	uint32_t ultrasonicEchoSCGCMask;
	PORT_Type* echoPort;
	uint32_t echoPin;
	uint32_t echoTPMMux;
	
	//Keep track of the samples for each measurement
	Q_T samples;
} ULTRASONIC_SENSOR;


//Trigger ports for the front array of sensors and rear array of sensors
extern TRIG_TYPE curr_trig;

//Variables to read from the front sensors and/or the rear sensors
extern int measureFrontSensors;
extern int measureRearSensors;

//Ultrasonic sensors
extern ULTRASONIC_SENSOR ultrasonic_front;
extern ULTRASONIC_SENSOR ultrasonic_frontright;
extern ULTRASONIC_SENSOR ultrasonic_frontleft;
extern ULTRASONIC_SENSOR ultrasonic_back;
extern ULTRASONIC_SENSOR ultrasonic_backleft;
extern ULTRASONIC_SENSOR ultrasonic_backright;

//Application methods
void Ultrasonic_Init(ULTRASONIC_SENSOR* ultrasonic_cfg);
void Measure_Reading(ULTRASONIC_SENSOR* ultrasonic_cfg);
void Generate_Trigger(ULTRASONIC_SENSOR* ultrasonic_cfg);
void Start_PIT(void);

#endif
