# Mini Project: Serial Communication between KL25Z board

## Purpose

In order for the PAT Unit to operate successfully, the various subsystems responsible for driving and obstacle avoidance will need to communicate effectively. This is where serial communication between boards comes in. Communication between boards allows for a more modular design of the PAT Unit, and ensures that environmental stimuli gets responded to in a timely fashion.

## System Overview

![Alt text](Documentation/out/puml/system-uart/system-uart.png?raw=true "System Overview")

This mini project will consist of 2 KL25Z Microcontrollers (Board A, and board B) communicating through UART. Board A will be responsible for reading data from the onboard accelerometer using I2C, and sending the data to Board B. Board B will then receive the data, and display it on the LCD.

### Board A

![Alt text](Documentation/out/puml/BoardA/BoardA.png?raw=true "Board A Sequence Diagram")

Board A is responsible for reading new data from the onboard accelerometer. This will involve reading from the accelerometer through its I2C interface. After which the data will need to be sent to Board B via the UART connection.

### Board B

![Alt text](Documentation/out/puml/BoardB/BoardB.png?raw=true "Board B Sequence Diagram")

Board B will receive data from the UART connection to Board A. Upon receiving data from Board A, Board B will need to update the LCD display to output the new data.

## Communication of Data

It should be noted that in order to transmit all the data from Board A to Board B there may have to be multiple packets sent. This will require design of a communication pattern to ensure all data is recieved before updating the LCD

## Repository Structure

This repo consists of Documentation, and a Keil workspace containing 2 Keil projects. In order to open this workspace, please open the workspace file "MiniProject.uvmpw". This will open both projects in keil.

Each project exists in their own subdirectories "IR_Sender" for BoardA's project, and "LCD_Receiver" for BoardB's project. Each subdirectory has the source and include files for the corresponding project.

See the diagram below for an overview of the repo's structure.

![Alt text](Documentation/out/puml/Structure/Structure.png?raw=true "Repo Structure")

## Contributing

When adding source (_.c) or header files (_.h) place them in the Source or Include folders that correspond to the project they belong to.
