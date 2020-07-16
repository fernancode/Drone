//open serial plotter in arduino application to see plots
#include <Arduino.h>
#include <wire.h>
#include <math.h>

const int MPU=0x68; //I2C address of the MPU-6050
float GyX,GyY,GyZ;
float xCal,yCal,zCal;
const int step = 10;
const int cal_steps = 1000;
const int to_degrees = 182;
void calibrate();

void setup()
{
    Wire.begin(); //initiate wire library and I2C
    Wire.beginTransmission(MPU); //begin transmission to I2C slave device
    Wire.write(0x6B); // PWR_MGMT_1 register
    Wire.write(0); // set to zero (wakes up the MPU-6050)  
    Wire.endTransmission(true); //ends transmission to I2C slave device
    Serial.begin(9600); //serial communication at 9600 bauds
    calibrate();
}

void loop()
{
    Wire.beginTransmission(MPU); //begin transmission to I2C slave device
    Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false); //restarts transmission to I2C slave device
    Wire.requestFrom(MPU,14,true); //request 14 registers in total  

    //read accelerometer data
    //AcX=Wire.read()<<8|Wire.read(); // 0x3B (ACCEL_XOUT_H) 0x3C (ACCEL_XOUT_L)  
    //AcY=Wire.read()<<8|Wire.read(); // 0x3D (ACCEL_YOUT_H) 0x3E (ACCEL_YOUT_L) 
    //AcZ=Wire.read()<<8|Wire.read(); // 0x3F (ACCEL_ZOUT_H) 0x40 (ACCEL_ZOUT_L)
  
    //read temperature data 
    //Tmp=Wire.read()<<8|Wire.read(); // 0x41 (TEMP_OUT_H) 0x42 (TEMP_OUT_L) 
  
    //read gyroscope data
    GyX=Wire.read()<<8|Wire.read();// 0x43 (GYRO_XOUT_H) 0x44 (GYRO_XOUT_L)
    GyY=Wire.read()<<8|Wire.read();// 0x45 (GYRO_YOUT_H) 0x46 (GYRO_YOUT_L)
    GyZ=Wire.read()<<8|Wire.read();// 0x47 (GYRO_ZOUT_H) 0x48 (GYRO_ZOUT_L) 

    GyX = (GyX + xCal)/to_degrees;
    GyY = (GyY + yCal)/to_degrees;
    GyZ = (GyZ + zCal)/to_degrees;

//#TODO: plot accelerometer data and then modify numbers based on gyroscopic position so accelerometer is always plotting in my in my reference frame



    Serial.print("Gyroscope: ");
    Serial.print(GyX);
    Serial.print(",");
    Serial.print(GyY);
    Serial.print(",");
    Serial.println(GyZ);
    delay(step);
}

void calibrate()
    {
    xCal = 0;
    yCal = 0;
    zCal = 0;

    for (int i = 1; i <= cal_steps; i++) 
    { 
        Wire.beginTransmission(MPU); //begin transmission to I2C slave device
        Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
        Wire.endTransmission(false); //restarts transmission to I2C slave device
        Wire.requestFrom(MPU,14,true); //request 14 registers in total  
        GyX=Wire.read()<<8|Wire.read();
        GyY=Wire.read()<<8|Wire.read();
        GyZ=Wire.read()<<8|Wire.read();
        xCal -= GyX;
        yCal -= GyY;
        zCal -= GyZ;
        delay(step); 
    }

    xCal = xCal/cal_steps;
    yCal = yCal/cal_steps;
    zCal = zCal/cal_steps;
    //Serial.println(xCal);
    //Serial.println(yCal);
    //Serial.println(zCal);
    }