/*----------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/
#include <MKL25Z4.H>
#include <stdio.h>
#include "gpio_defs.h"
#include "LCD_4bit.h"
#include "LEDs.h"
#include "timers.h"
#include "delay.h"
#include "ultrasonic_array.h"

//0 for disable sensors and 1 for enable
int measureFrontSensors = 1;
int measureRearSensors = 0;

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) {
	
	Init_PIT(240); //gives us a period of 10 microseconds
	ULTRASONIC_SENSOR* sensor_array[NUM_SENSORS];
	sensor_array[0] = &ultrasonic_front;
	sensor_array[1] = &ultrasonic_frontleft;
//	sensor_array[2] = &ultrasonic_frontright;
//	sensor_array[3] = &ultrasonic_back;
//	sensor_array[4] = &ultrasonic_backleft;
//	sensor_array[5] = &ultrasonic_backright;
	
	//Initialize the TPM and Ultrasonic Sensor
	for(int i = 0; i < NUM_SENSORS; i++) {
		Q_Init(&(sensor_array[i]->samples));
		Ultrasonic_Init(sensor_array[i]);
		Init_TPM(sensor_array[i]);
	}
	Init_TPM_IRQ();
	
	float measuredDistance[NUM_SENSORS];
	int numSensorsMeasurements = 0;
	
	while(1) {
		
		if(measureFrontSensors){
			
			numSensorsMeasurements = 0;
			
			while(numSensorsMeasurements <= NUM_FRONT_SENSORS * NUM_SAMPLES){
				
				for(int i = 0; i < NUM_FRONT_SENSORS; i++) {
					if(Q_Full(&(sensor_array[i]->samples))) {
						measuredDistance[i] = sensor_array[i]->measurementSum / NUM_SAMPLES;
						float temp = Q_Dequeue(&(sensor_array[i]->samples));
						sensor_array[i]->measurementSum = sensor_array[i]->measurementSum - temp;
					}
					Generate_Trigger(sensor_array[i]); 
					Measure_Reading(sensor_array[i]);
					numSensorsMeasurements++;
				}
			}
		}
				
		if(measureRearSensors) {
			
			numSensorsMeasurements = 0;
			
			while(numSensorsMeasurements <= NUM_FRONT_SENSORS * NUM_SAMPLES){
				for(int i = NUM_FRONT_SENSORS; i < NUM_SENSORS; i++) {
					if(Q_Full(&(sensor_array[i]->samples))) {
						measuredDistance[i] = sensor_array[i]->measurementSum / NUM_SAMPLES;
						float temp = Q_Dequeue(&(sensor_array[i]->samples));
						sensor_array[i]->measurementSum -= temp;
					}
					Generate_Trigger(sensor_array[i]); 
					Measure_Reading(sensor_array[i]);
					numSensorsMeasurements++;
				}
			}
		}
	}
}

// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
