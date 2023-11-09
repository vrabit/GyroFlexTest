#ifndef BNO055_H
#define BNO055_H

#include "mbed.h"

// I2C SETUP
#define IMU_ADDRESS (0X28 << 1) // to 8 bit address
#define MAX_FREQ 400000

// GYRO <15:8> <7:0>
#define GYR_DATA_Z_MSB 0X19
#define GYR_DATA_Z_LSB 0X18
#define GYR_DATA_Y_MSB 0X17
#define GYR_DATA_Y_LSB 0X16
#define GYR_DATA_X_MSB 0X15
#define GYR_DATA_X_LSB 0X14

// TEMPERATURE 
#define TEMP_ADDRESS 0X34


class Gyro{
public:
    Gyro(PinName scl, PinName sda) : IMU(I2C_SDA, I2C_SDA), temp(0){
        tx[0]= '\0';
        tx[1]= '\0';
    }

    void read_temp(){
        tx[0] = TEMP_ADDRESS;
        IMU.write(IMU_ADDRESS, &tx[0], 1, true);
        wait_us(2);
        IMU.read(IMU_ADDRESS, &temp, 1, false);
        wait_us(2);
    }

    char temp;

private:
    I2C IMU;
    char tx[2];


};

#endif