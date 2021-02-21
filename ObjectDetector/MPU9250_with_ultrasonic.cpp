#include <MPU9250_asukiaaa.h>
#include <Arduino.h>

//MPU_9250
#define SDA_PIN 21
#define SCL_PIN 22
MPU9250_asukiaaa mySensor;
float gX, gY, gZ;
//aX, aY, aZ, aSqrt, 
//gX, gY, gZ, 
//mDirection, mX, mY, mZ;

//ultrasonic sensor
const int out=4;
const int in=17;
int last = 0;
long dur;
long cm;

long microsecondsToCentimeters(long microseconds) {
return microseconds / 29 / 2;
}

void setup() {

//ultrasonic sensor
Serial.begin(9600);
pinMode(in, INPUT);
pinMode(out, OUTPUT);
 
//MPU_9250 gyro sensor
Wire.begin(SDA_PIN, SCL_PIN); //sda, scl
mySensor.setWire(&Wire);
 
//mySensor.beginAccel();
  mySensor.beginGyro();
//mySensor.beginMag();
 
// you can set your own offset for mag values
//mySensor.magXOffset = -20;
//mySensor.magYOffset = -60;
//mySensor.magZOffset = -10;
}

void loop() {

//ultrasonic sensor code -----------------------------------------------------------------------------------------------------------------
digitalWrite(out,LOW);
delayMicroseconds(2);
digitalWrite(out,HIGH);
delayMicroseconds(10);
digitalWrite(out,LOW);
dur=pulseIn(in,HIGH);
cm=microsecondsToCentimeters(dur);

if ((cm == 2217) || (cm > 100 + last)) { //if tocm = 2217 or is > 100 from last number then signal lost error
    Serial.println("error or signal lost");
} else if (cm < 10) {
     Serial.println("too close"); //move drone away at speed of 2cm/s. Verify with motion sensor
} else {
    last = cm; //Just put in else statement: carry through last number until number deviation is <5 so (lastnumber -= 5) <= tocm <= (last number += 5), then set last number to current tocm value
    Serial.println("distance: " + String(cm) + "cm");
}
delay(100);

//MPU_9250 gyro code -----------------------------------------------------------------------------------------------------------------
uint8_t sensorId;
  if (mySensor.readId(&sensorId) == 0) {
    Serial.println("sensorId: " + String(sensorId));
  } else {
    Serial.println("Cannot read sensorId");
  }
  /*
   if (mySensor.accelUpdate() == 0) {
    aX = mySensor.accelX();
    aY = mySensor.accelY();
    aZ = mySensor.accelZ();
    aSqrt = mySensor.accelSqrt();
    Serial.println("accelX: " + String(aX));
    Serial.println("accelY: " + String(aY));
    Serial.println("accelZ: " + String(aZ));
    Serial.println("accelSqrt: " + String(aSqrt));
  } else {
    Serial.println("Cannod read accel values");
  }
  */

  
    if (mySensor.gyroUpdate() == 0) {
    gX = mySensor.gyroX();
    gY = mySensor.gyroY();
    gZ = mySensor.gyroZ();
    Serial.println("gyroX: " + String(gX));
    Serial.println("gyroY: " + String(gY));
    Serial.println("gyroZ: " + String(gZ));
    if (gX >100) {
       Serial.println("Moved in Pos X direction!");
    } else if (gX < -100) {
       Serial.println("Moved in Neg X direction!");
    } 

    if (gY > 100) {
       Serial.println("Moved in Pos Y direction!");
        buzz(buzzer, 1000, 1000);
    } else if (gY < -100) {
       Serial.println("Moved in Neg Y direction!");
    }

    if (gZ > 100) {
       Serial.println("Moved in Pos Z direction!");
    } else if (gZ < -100) {
       Serial.println("Moved in Neg Z direction!");
    }
  } else {
    Serial.println("Cannot read gyro values");
  }

/*
  if (mySensor.magUpdate() == 0) {
    mX = mySensor.magX();
    mY = mySensor.magY();
    mZ = mySensor.magZ();
    mDirection = mySensor.magHorizDirection();
    Serial.println("magX: " + String(mX));
    Serial.println("maxY: " + String(mY));
    Serial.println("magZ: " + String(mZ));
    Serial.println("horizontal direction: " + String(mDirection));
  } else {
    Serial.println("Cannot read mag values");
  }
  */
  

  Serial.println("at " + String(millis()) + "ms");
  Serial.println(""); // Add an empty line
  delay(200);

}