#include "RF24.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// Initialize MPU6050 sensor
Adafruit_MPU6050 mpu;

sensors_event_t a, g, temp;

int data[3];

RF24 radio(9,10);

//Create a pipe addresses for the communicate                                    
const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup(void) {
  Wire.begin();
  radio.begin();
  radio.openWritingPipe(pipe);

  // set accelerometer range to +-8G
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  // set gyro range to +- 500 deg/s
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  // set filter bandwidth to 21 Hz
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  
  delay(100);
}

void loop() {
  /* Get new sensor events with the readings */
//  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  data[0] = (a.acceleration.x + 0.2)*1000;
  data[1] = (a.acceleration.y)*1000;
  data[2] = (g.gyro.z)*1000;

  radio.write(data, sizeof(data));
  delay(100);
}
