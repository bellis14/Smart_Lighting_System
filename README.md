# Smart Lighting System
MSP432 microcontroller application that functions with the interrupt, I/O, and timer technologies built in to the MSP432. Using these technologies, a 
power efficient lighting system can be created using a PIR sensor as the input and an LED as the output. When the PIR sensor detects motion, it sends 
a digital 1 signal to the MSP432 which triggers an interrupt to turn on the LED. When the sensor no longer detects motion a timer begins and counts for 
approximately 5 seconds. If the sensor detects motion during those five seconds the timer is reset and begins counting again from the start with the LED 
remaining on. If the timer reaches the 5 second time frame an interrupt is triggered and a check to see if the sensor is on will be evaluated and if 
the sensor is providing a digital 0 then the LED will be turned off. This system design reduces power consumption by turning on street lights only when 
cars are in the area. 
