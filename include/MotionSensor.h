#ifndef MPU_MANAGER_H
#define MPU_MANAGER_H

#include <Arduino.h>

/**
 * MPUManager class for interfacing with MPU6050 sensor
 * 
 * This class provides an interface to access the gravity vector data
 * from the MPU6050 with DMP support. It handles all internal state
 * management to prevent overflow issues.
 */
class MotionSensor
{
public:
    /**
     * Constructor
     * 
     * @param sdaPin SDA pin for I2C connection
     * @param sclPin SCL pin for I2C connection
     */
    explicit MotionSensor(int sdaPin = 19, int sclPin = 18);

    /**
     * Initialize the MPU6050 sensor with Digital Motion Processor (DMP)
     * 
     * @return true if initialization successful, false otherwise
     */
    bool init();

    /**
     * Get the gravity vector
     *
     * @param vec Pointer to a float array of size 3 to store [x, y, z] components
     * @return true if gravity vector was successfully updated, false otherwise
     */
    bool getGravityVector(float* vec);

private:
    int _sdaPin;
    int _sclPin;
    bool _dmpReady;

    // Process FIFO data and update sensor readings
    bool updateSensorData() const;
};

extern MotionSensor motionSensor;

#endif // MPU_MANAGER_H
