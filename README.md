# ESP32ObjectDetector
This is an object detection hardware project which measures the distance to objects using an ultrasonic sensor and measures gyroscopic axis using the MPU-9250 sensor. I have included the C++/Arduino code in this repo.

# Construction
* I Calculated the distance by measuring the time taken between sending and receiving a pulse from the ultrasonic sensor
* I was inspired by the MiniRadar project from InterestingEngineering
* I have applied this in my SmartUAV project as a rangefinder up to 3m on the drone, to detect solid objects such as walls, feedback the distance to the flight controller and adjust course.
* The gyroscopic and accelerometer measurements from the MPU-9250 can assist in correct flight by making sure the drone moves away from the object in the correct direction and orientation respective to the ground

# Learning outcomes
* Used an algorithm to detect and monitor the distance to objects using an ultrasonic sensor
* Feed this information back to raspberry Pi in SmartUAV project: www.github.com/harryhancock/SmartUAV

# Components
* HC-SR04 utrasonic sensor, detects solid objects up to 3m
* Heltec ESP32 v2 to run the c++ code

# Updates

## Acknowledgments

* MPU9250_asukiaaa
* Arduino
* Platform.io
