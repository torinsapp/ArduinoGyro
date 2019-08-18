#include <Wire.h>
#include <MPU6050.h>
MPU6050 mpu;
#include <SoftwareSerial.h>
SoftwareSerial ArduinoUno(3,2); 
int xAvg = 0, yAvg = 0, count = 0, realX = 0, realY = 0;
int cutoff = 10;
String strX, strY;

void setup() 
{
  Serial.begin(9600);
  ArduinoUno.begin(9600);
  Serial.println("Initialize MPU6050");

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  do
  {
    Vector rawAccel = mpu.readRawAccel();
    Vector normAccel = mpu.readNormalizeAccel();
    xAvg = xAvg + normAccel.XAxis;
    yAvg = yAvg + normAccel.YAxis;
    count++;
  }while(count<100);
  xAvg = xAvg/100;
  yAvg = yAvg/100;
}
void checkmpu()
{
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
}
void loop()
{
  if(realX > 9)
  {
    realX = 9;
  }
  if(realY > 9)
  {
    realY = 9;
  }
  if(realX < -9)
  {
    realX = -9;
  }
  if(realY < -9)
  {
    realY = -9;
  }
  checkmpu();
  Vector rawAccel = mpu.readRawAccel();
  Vector normAccel = mpu.readNormalizeAccel();
  realX = (xAvg - normAccel.XAxis) * -1;
  realY = yAvg - normAccel.YAxis;
  strX = String(realX);
  strY = String(realY);
  if
  Serial.println("X"+strX + "Y" + strY);
  delay(10);
}
