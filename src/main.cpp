#include <Arduino.h>
#include <I2Cdev.h>
#include <MPU6050_6Axis_MotionApps20.h>
#include <Wire.h>
int Key;
float x,y,z; //coordinates
MPU6050 mpu; 
bool dmpReady = false; //verify if the dmp thing is working or not
uint8_t mpuIntStatus;
uint8_t devStatus;
uint16_t packetSize;
uint16_t fifoCount;
uint8_t fifoBuffer[64];

Quaternion q;
VectorFloat gravity;

void Contact(){ //send A to the port and creat contact
  while(Serial.available() <= 0){
    Serial.print('A');
    delay(300);
  }
}


void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu.initialize();     //start the gyro
  devStatus = mpu.dmpInitialize();
  
  
  mpu.setXGyroOffset(220);
  mpu.setYGyroOffset(76);
  mpu.setZGyroOffset(-85);
  mpu.setZAccelOffset(1788);

  if (devStatus == 0) {
    mpu.setDMPEnabled(true);
    dmpReady = true;
    packetSize = mpu.dmpGetFIFOPacketSize();
  }
  
  
}

void loop() {
  if (!dmpReady) return;
  
  mpuIntStatus = mpu.getIntStatus();
  fifoCount = mpu.getFIFOCount();
  
  if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
    mpu.resetFIFO();
  } 
  else if (mpuIntStatus & 0x02) {
    while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
    
    mpu.getFIFOBytes(fifoBuffer, packetSize);
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    
    
    Serial.print("A");
    Serial.print(q.w); Serial.print(",");
    Serial.print(q.x); Serial.print(",");
    Serial.print(q.y); Serial.print(",");
    Serial.println(q.z);
    
    fifoCount -= packetSize;
  }
}
  
  
  


