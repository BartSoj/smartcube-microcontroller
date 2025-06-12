#include "FaceManager.h"
#include "MPUManager.h"

// Global instance of FaceManager
FaceManager faceManager;

// Default constructor - initialize with standard cube orientation
FaceManager::FaceManager()
{
    // Standard orientation mapping
    // Each entry defines which direction in sensor space corresponds to each face
    faceMappings[0] = {"Top", 0.0f, 1.0f, 0.0f}; // Top face = +Y axis
    faceMappings[1] = {"Bottom", 0.0f, -1.0f, 0.0f}; // Bottom face = -Y axis
    faceMappings[2] = {"Right", 1.0f, 0.0f, 0.0f}; // Right face = +X axis
    faceMappings[3] = {"Left", -1.0f, 0.0f, 0.0f}; // Left face = -X axis
    faceMappings[4] = {"Front", 0.0f, 0.0f, 1.0f}; // Front face = +Z axis
    faceMappings[5] = {"Back", 0.0f, 0.0f, -1.0f}; // Back face = -Z axis
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

    // Calculate the local up vector (opposite of gravity)
    float localUp[3] = {-gravity[0], -gravity[1], -gravity[2]};

    // Find the face with direction most closely aligned with local up
    float bestMatch = -1.0f; // Start with minimum possible dot product
    int bestFaceIndex = 0;

    for (int i = 0; i < 6; i++)
    {
        // Calculate alignment score (dot product)
        float score = dotProduct(localUp[0], localUp[1], localUp[2],
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
    for (int i = 0; i < 6; i++)
    {
        Serial.print(faceMappings[i].name);
        Serial.print(": (");
        Serial.print(faceMappings[i].x);
        Serial.print(", ");
        Serial.print(faceMappings[i].y);
        Serial.print(", ");
        Serial.print(faceMappings[i].z);
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
