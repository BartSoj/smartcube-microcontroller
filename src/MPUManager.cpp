#include "MPUManager.h"
#include "Wire.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "I2Cdev.h"

// MPU control/status vars
MPU6050 mpu;
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// Orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container

// MPU6050 initialization with DMP
bool initMPU() {
    // Initialize I2C communication
    Wire.begin(19, 18); // SDA on pin 19, SCL on pin 18
    Wire.setClock(400000); // 400kHz I2C clock

    // Initialize MPU6050
    Serial.println("Initializing MPU6050...");
    mpu.initialize();
    
    // Check if connected
    if (!mpu.testConnection()) {
        Serial.println("MPU6050 connection failed!");
        return false;
    }
    
    Serial.println("MPU6050 connection successful");
    
    // Initialize DMP
    Serial.println("Initializing DMP...");
    devStatus = mpu.dmpInitialize();
    
    // Make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        // Supply your own gyro offsets here, scaled for min sensitivity
        // These should be calibrated for your specific device
        mpu.setXGyroOffset(220);
        mpu.setYGyroOffset(76);
        mpu.setZGyroOffset(-85);
        mpu.setZAccelOffset(1788);

        // Generate offsets and calibrate our MPU6050
        mpu.CalibrateAccel(6);
        mpu.CalibrateGyro(6);
        mpu.PrintActiveOffsets();

        // Configure DMP rate - set to a slower rate to prevent FIFO overflow
        // The DMP sample rate affects how quickly the FIFO fills up
        mpu.setRate(4); // 0 = 8kHz, 1 = 4kHz, 2 = 2kHz, 4 = 1kHz, etc.
        Serial.println("DMP sample rate set to 1kHz");

        // Configure FIFO
        mpu.setDMPEnabled(false); // Temporarily disable while configuring

        // Configure which sensor data goes to FIFO to minimize data size
        // These calls set which motion processing data is pushed to the FIFO
        mpu.setFIFOEnabled(true);

        // Only enable the data we need (quaternions) in the FIFO
        mpu.setXGyroFIFOEnabled(false);
        mpu.setYGyroFIFOEnabled(false);
        mpu.setZGyroFIFOEnabled(false);
        mpu.setAccelFIFOEnabled(false);

        // Turn on the DMP
        Serial.println("Enabling DMP...");
        mpu.setDMPEnabled(true);

        // Set our DMP Ready flag so the main loop() function knows it's okay to use it
        dmpReady = true;

        // Get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();

        return true;
    } else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        Serial.print("DMP Initialization failed (code ");
        Serial.print(devStatus);
        Serial.println(")");
        return false;
    }
}

// Update MPU data using DMP
void updateMPU() {
    // If DMP not ready, exit
    if (!dmpReady) return;

    // Get current FIFO count
    fifoCount = mpu.getFIFOCount();

    // Check for overflow
    if (fifoCount >= 1024) {
        // Reset so we can continue cleanly
        mpu.resetFIFO();
        Serial.println("FIFO overflow! Resetting...");
        return;
    }

    // Process all available packets (don't wait for new data if we have enough)
    // This helps prevent FIFO overflow by ensuring we're always emptying the buffer
    if (fifoCount >= packetSize) {
        // Read as many complete packets as possible
        while (fifoCount >= packetSize) {
            mpu.getFIFOBytes(fifoBuffer, packetSize);
            fifoCount -= packetSize;
        }

        // Process the latest packet (the most recent data)
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
    }
}

// Get X rotation in degrees (pitch)
float getXRotation() {
    return ypr[1] * 180/M_PI;
}

// Get Y rotation in degrees (roll)
float getYRotation() {
    return ypr[2] * 180/M_PI;
}

// Get Z rotation in degrees (yaw)
float getZRotation() {
    return ypr[0] * 180/M_PI;
}
