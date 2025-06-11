#ifndef MPU_MANAGER_H
#define MPU_MANAGER_H

#include <Arduino.h>

/**
 * Initialize the MPU6050 sensor with Digital Motion Processor (DMP)
 * 
 * @return true if initialization successful, false otherwise
 */
bool initMPU();

/**
 * Update MPU data using DMP - call this in each loop iteration
 */
void updateMPU();

/**
 * Get X rotation (pitch) in degrees
 * 
 * @return rotation around X-axis in degrees
 */
float getXRotation();

/**
 * Get Y rotation (roll) in degrees
 * 
 * @return rotation around Y-axis in degrees
 */
float getYRotation();

/**
 * Get Z rotation (yaw) in degrees
 * 
 * @return rotation around Z-axis in degrees
 */
float getZRotation();

/**
 * Get the gravity vector
 *
 * @param vec Pointer to a float array of size 3 to store [x, y, z] components
 */
void getGravityVector(float* vec);

/**
 * Get the quaternion
 *
 * @param quat Pointer to a float array of size 4 to store [w, x, y, z] components
 */
void getQuaternion(float* quat);

#endif // MPU_MANAGER_H
