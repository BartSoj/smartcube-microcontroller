#ifndef FACE_MANAGER_H
#define FACE_MANAGER_H

#include <Arduino.h>

// Face directions defined as vectors (normalized)
typedef struct
{
    const char* name; // Face name (Top, Bottom, Front, Back, Left, Right)
    float x; // X component of the face direction vector
    float y; // Y component of the face direction vector
    float z; // Z component of the face direction vector
} FaceDirection;

class CubeOrientation
{
private:
    // Array of face directions mapping sensor axes to face names
    FaceDirection faceMappings[6]{};

    // Calculate dot product between two 3D vectors
    static float dotProduct(float x1, float y1, float z1, float x2, float y2, float z2);

public:
    // Constructor with default face mappings
    CubeOrientation();

    // Initialize with custom face mappings
    void configureFaceMappings(const FaceDirection* mappings);

    // Get the current face pointing up using gravity vector
    const char* getCurrentFace();

    // Print current face mappings to Serial for debugging
    void printFaceMappings();
};

// Create a global instance of FaceManager
extern CubeOrientation cubeOrientation;

// Initialize the FaceManager with default settings
bool initCubeOrientation();

#endif // FACE_MANAGER_H
