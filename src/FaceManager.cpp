#include "FaceManager.h"
#include "MPUManager.h"
#include "config/FaceDirectionConfig.h"

// Global instance of FaceManager
FaceManager faceManager;

// Default constructor - initialize with standard cube orientation
FaceManager::FaceManager()
{
    // Standard orientation mapping
    // Each entry defines which direction in sensor space corresponds to each face
    faceMappings[0] = {"Top", FACE_DIR_TOP_X, FACE_DIR_TOP_Y, FACE_DIR_TOP_Z}; // Top face
    faceMappings[1] = {"Bottom", FACE_DIR_BOTTOM_X, FACE_DIR_BOTTOM_Y, FACE_DIR_BOTTOM_Z}; // Bottom face
    faceMappings[2] = {"Right", FACE_DIR_RIGHT_X, FACE_DIR_RIGHT_Y, FACE_DIR_RIGHT_Z}; // Right face
    faceMappings[3] = {"Left", FACE_DIR_LEFT_X, FACE_DIR_LEFT_Y, FACE_DIR_LEFT_Z}; // Left face
    faceMappings[4] = {"Front", FACE_DIR_FRONT_X, FACE_DIR_FRONT_Y, FACE_DIR_FRONT_Z}; // Front face
    faceMappings[5] = {"Back", FACE_DIR_BACK_X, FACE_DIR_BACK_Y, FACE_DIR_BACK_Z}; // Back face
}

// Configure custom face mappings
void FaceManager::configureFaceMappings(const FaceDirection* mappings)
{
    for (int i = 0; i < 6; i++)
    {
        faceMappings[i] = mappings[i];
    }
}

// Helper function to calculate dot product
float FaceManager::dotProduct(float x1, float y1, float z1, float x2, float y2, float z2)
{
    return x1 * x2 + y1 * y2 + z1 * z2;
}

// Get the current face pointing up
const char* FaceManager::getCurrentFace()
{
    float gravity[3];
    mpuManager.getGravityVector(gravity);

    // Find the face with direction most closely aligned with local up
    float bestMatch = -1.0f; // Start with minimum possible dot product
    int bestFaceIndex = 0;

    for (int i = 0; i < 6; i++)
    {
        // Calculate alignment score (dot product)
        float score = dotProduct(gravity[0], gravity[1], gravity[2],
                                 faceMappings[i].x, faceMappings[i].y, faceMappings[i].z);

        // If this face is better aligned than our previous best match
        if (score > bestMatch)
        {
            bestMatch = score;
            bestFaceIndex = i;
        }
    }

    // Return the name of the best matching face
    return faceMappings[bestFaceIndex].name;
}

// Debug function to print current face mappings
void FaceManager::printFaceMappings()
{
    Serial.println("Current Face Mappings:");
    for (auto& faceMapping : faceMappings)
    {
        Serial.print(faceMapping.name);
        Serial.print(": (");
        Serial.print(faceMapping.x);
        Serial.print(", ");
        Serial.print(faceMapping.y);
        Serial.print(", ");
        Serial.print(faceMapping.z);
        Serial.println(")");
    }
}

// Initialize the FaceManager
bool initFaceManager()
{
    // Currently just uses default configuration
    // You could load custom mappings from storage here if needed
    return true;
}
