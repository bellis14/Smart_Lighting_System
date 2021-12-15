# Smart Lighting System

## Objectives

1) Utilize interrupts, I/O, and timers on the MSP432
2) Implement a power efficient lighting system that turns on street lights when vehicles are in the area
________________________________________________________________________

## Overview

This application has a real-world implication. It simulates a motion detecting lighting system to reduce power consumption by only turning on street lights when cars are in the area. When no cars are in the area a timer will begin and once the timer as reached a specified time interval the street lights will be turned when no cars are in the area.

## Description

MSP432 microcontroller application in C that functions with the interrupt, I/O, and timer technologies built in to the MSP432. Using these technologies, a 
power efficient lighting system can be created using a PIR sensor as the input and an LED as the output. When the PIR sensor detects motion, it sends 
a digital 1 signal to the MSP432 which triggers an interrupt to turn on the LED. When the sensor no longer detects motion a timer begins and counts for 
approximately 5 seconds. If the sensor detects motion during those five seconds the timer is reset and begins counting again from the start with the LED 
remaining on. If the timer reaches the 5 second time frame an interrupt is triggered and a check to see if the sensor is on will be evaluated and if 
the sensor is providing a digital 0 then the LED will be turned off. This system design reduces power consumption by turning on street lights only when 
cars are in the area. Additional details can be found in the full report in the Smart_lighting_system.docx file in this repository upon download.
________________________________________________________________________

## Equipment

This application requires the following parts:

1 MSP432 LaunchPad with USB cable
3 Female to Female Jumper Wires
1 PIR motion sensor

## Schematic/Peripheral Connections 



The output port of the PIR sensor labeled OUT connects the pin P1.5 on the MSP432 while the port GND of the sensor connects to a GND pin on the board and 5V on the board connects to the port labeled VCC on the sensor. The LED at pin P1.0 is built-in on the board so there is no need to include any additional wiring.
