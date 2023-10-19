#include <Wire.h>
const int sda = 21;
const int scl = 22;
int address = 0x68;
// define int for Accelerometer
byte ACCEL_XOUT_H = 0;
byte ACCEL_XOUT_L = 0;
byte ACCEL_YOUT_H = 0;
byte ACCEL_YOUT_L = 0;
byte ACCEL_ZOUT_H = 0;
byte ACCEL_ZOUT_L = 0;
int16_t ACCEL_X_RAW = 0;
int16_t ACCEL_Y_RAW = 0;
int16_t ACCEL_Z_RAW = 0;
float gX;
float gY;
float gZ;
//define int for Gyrometer
byte GYRO_XOUT_H = 0;
byte GYRO_XOUT_L = 0;
byte GYRO_YOUT_H = 0;
byte GYRO_YOUT_L = 0;
byte GYRO_ZOUT_H = 0;
byte GYRO_ZOUT_L = 0;
int16_t GYRO_X_RAW = 0;
int16_t GYRO_Y_RAW = 0;
int16_t GYRO_Z_RAW = 0;

void setup(){
    Wire.begin(sda,scl); //to call the SDA and SCL
    Serial.begin(9600);
}
void loop(){
  readAccelerometer();
  readGyrometer();
  delay(100);

}

void readAccelerometer(){
  // read accelerometer data from x axis from the sensor
    //send read request to read the left 8 bit of accel_x from register 3B
    Wire.beginTransmission(address);
    Wire.write(0x3B); // the register you are looking for. register refers to a memory location or data storage area within an I2C
    Wire.endTransmission(); // sends the data package to SOMETHINGSOMETHING

    //read answer to request from 3B
    Wire.requestFrom(address, 6); // prepares to read length bytes from "address"
    ACCEL_XOUT_H = Wire.read(); // reads the available byte
    ACCEL_XOUT_L = Wire.read(); // reads the next avilable byte
    ACCEL_YOUT_H = Wire.read();
    ACCEL_YOUT_L = Wire.read();
    ACCEL_ZOUT_H = Wire.read();
    ACCEL_ZOUT_L = Wire.read();

    ACCEL_X_RAW = ACCEL_XOUT_H << 8 | ACCEL_XOUT_L; // bit shift
    ACCEL_Y_RAW = ACCEL_YOUT_H << 8 | ACCEL_YOUT_L;
    ACCEL_Z_RAW = ACCEL_ZOUT_H << 8 | ACCEL_ZOUT_L;

    gX = ACCEL_X_RAW / 16384.0;
    gY = ACCEL_Y_RAW / 16384.0;
    gZ = ACCEL_Z_RAW / 16384.0;
    
    Serial.print("Accel X-axis:");
    Serial.print(gX);
    Serial.print(",");
    Serial.print ("Accel Y-axis:");
    Serial.print(gY);
    Serial.print(",");
    Serial.print("Accel Z-axis:");
    Serial.println(gZ);
}

void readGyrometer(){
  Wire.beginTransmission(address);
  Wire.write(0x43);
  Wire.endTransmission();
  // read answer to request from 43
  Wire.requestFrom(address, 6);
  GYRO_XOUT_H = Wire.read();
  GYRO_XOUT_L = Wire.read();
  GYRO_YOUT_H = Wire.read();
  GYRO_YOUT_L = Wire.read();
  GYRO_ZOUT_H = Wire.read();
  GYRO_ZOUT_L = Wire.read();

  GYRO_X_RAW = GYRO_XOUT_H << 8 | GYRO_XOUT_L;
  GYRO_Y_RAW = GYRO_YOUT_H << 8 | GYRO_YOUT_L;
  GYRO_Z_RAW = GYRO_ZOUT_H << 8 | GYRO_ZOUT_L;


  Serial.print("Gyro X-axis:");
  Serial.print(GYRO_X_RAW);
  Serial.print(",");
  Serial.print ("Gyro Y-axis:");
  Serial.print(GYRO_Y_RAW);
  Serial.print(",");
  Serial.print("Gyro Z-axis:");
  Serial.println(GYRO_Z_RAW);
}