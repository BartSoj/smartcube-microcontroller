#include "MotionSensor.h"
#include "Wire.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "I2Cdev.h"
#include "config/MPU6050Config.h"

// Forward declarations of private implementation variables
namespace
{
    MPU6050* mpuDevice = nullptr;
    uint8_t fifoBuffer[64]; // FIFO storage buffer
    uint16_t packetSize; // expected DMP packet size
    Quaternion q; // [w, x, y, z] quaternion container
    VectorFloat gravity; // [x, y, z] gravity vector
}

// Global MPUManager instance
MotionSensor motionSensor;

MotionSensor::MotionSensor(int sdaPin, int sclPin) : _sdaPin(sdaPin), _sclPin(sclPin), _dmpReady(false)
{
    // Constructor initializes member variables only
}

bool MotionSensor::init()
{
    // Initialize I2C communication
    Wire.begin(_sdaPin, _sclPin);
    Wire.setClock(400000); // 400kHz I2C clock

    // Create MPU device if it doesn't exist
    if (mpuDevice == nullptr)
    {
        mpuDevice = new MPU6050();
    }

    // Initialize MPU6050
    Serial.println("Initializing MPU6050...");
    mpuDevice->initialize();

    // Check if connected
    if (!mpuDevice->testConnection())
    {
        Serial.println("MPU6050 connection failed!");
        return false;
    }

    Serial.println("MPU6050 connection successful");

    // Initialize DMP
    Serial.println("Initializing DMP...");
    mpuDevice->setDLPFMode(MPU6050_DLPF_BW_98);
    uint8_t devStatus = mpuDevice->dmpInitialize();

    // Make sure it worked (returns 0 if so)
    if (devStatus == 0)
    {
        // Load the calibrated offsets from config file
        mpuDevice->setXAccelOffset(MPU6050Config::X_ACCEL_OFFSET);
        mpuDevice->setYAccelOffset(MPU6050Config::Y_ACCEL_OFFSET);
        mpuDevice->setZAccelOffset(MPU6050Config::Z_ACCEL_OFFSET);
        mpuDevice->setXGyroOffset(MPU6050Config::X_GYRO_OFFSET);
        mpuDevice->setYGyroOffset(MPU6050Config::Y_GYRO_OFFSET);
        mpuDevice->setZGyroOffset(MPU6050Config::Z_GYRO_OFFSET);

        // Configure DMP rate - set to a slower rate to prevent FIFO overflow
        mpuDevice->setRate(MPU6050Config::DMP_RATE); // 0 = 8kHz, 1 = 4kHz, 2 = 2kHz, 4 = 1kHz, etc.

        // Configure FIFO
        mpuDevice->setDMPEnabled(false); // Temporarily disable while configuring

        // Configure which sensor data goes to FIFO to minimize data size
        mpuDevice->setFIFOEnabled(true);

        // Only enable the data we need (quaternions) in the FIFO
        mpuDevice->setXGyroFIFOEnabled(false);
        mpuDevice->setYGyroFIFOEnabled(false);
        mpuDevice->setZGyroFIFOEnabled(false);
        mpuDevice->setAccelFIFOEnabled(false);

        // Turn on the DMP
        Serial.println("Enabling DMP...");
        mpuDevice->setDMPEnabled(true);

        // Set our DMP Ready flag
        _dmpReady = true;

        // Get expected DMP packet size for later comparison
        packetSize = mpuDevice->dmpGetFIFOPacketSize();

        // Reset FIFO to start clean
        mpuDevice->resetFIFO();

        return true;
    }
    else
    {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        Serial.print("DMP Initialization failed (code ");
        Serial.print(devStatus);
        Serial.println(")");
        return false;
    }
}

bool MotionSensor::updateSensorData() const
{
    // If DMP not ready, exit
    if (!_dmpReady || mpuDevice == nullptr)
    {
        return false;
    }

    // Get current FIFO count
    uint16_t fifoCount = mpuDevice->getFIFOCount();

    // Check for overflow
    if (fifoCount >= 1024)
    {
        // Reset so we can continue cleanly
        mpuDevice->resetFIFO();
        Serial.println("FIFO overflow! Resetting...");
        return false;
    }

    // If we don't have enough data, return false
    if (fifoCount < packetSize)
    {
        return false;
    }

    // Process all available packets to prevent FIFO overflow
    while (fifoCount >= packetSize)
    {
        mpuDevice->getFIFOBytes(fifoBuffer, packetSize);
        fifoCount -= packetSize;
    }

    // Process the latest packet (most recent data)
    mpuDevice->dmpGetQuaternion(&q, fifoBuffer);
    mpuDevice->dmpGetGravity(&gravity, &q);

    return true;
}

bool MotionSensor::getGravityVector(float* vec)
{
    // Update sensor data first
    bool success = updateSensorData();

    vec[0] = gravity.x;
    vec[1] = gravity.y;
    vec[2] = gravity.z;

    return success;
}
