#include <Arduino.h>
#include "MPUManager.h"
#include "LEDManager.h"
#include "FaceManager.h"

void setup()
{
    Serial.begin(115200);

    // Initialize MPU6050
    if (!initMPU())
    {
        Serial.println("Failed to initialize MPU6050. Check connections.");
    }
    else
    {
        Serial.println("MPU6050 initialized successfully.");
    }
    delay(2000);

    // Initialize LED panel
    if (!initLEDs())
    {
        Serial.println("Failed to initialize LED panel.");
    }
    else
    {
        Serial.println("LED panel initialized successfully.");
    }

    // Initialize Face Manager
    if (initFaceManager())
    {
        Serial.println("Face Manager initialized successfully.");
        faceManager.printFaceMappings();
    }
}

void loop()
{
    // Update MPU data - call frequently to prevent FIFO overflow
    updateMPU();

    // Update LEDs (handle background color cycling)
    updateLEDs();

    // Print rotation angles and current face every 500ms
    static unsigned long lastMpuPrintTime = 0;
    unsigned long currentTime = millis();
    if (currentTime - lastMpuPrintTime >= 500)
    {
        lastMpuPrintTime = currentTime;

        // Print rotation data
        Serial.print("Rotation (degrees) - X: ");
        Serial.print(getXRotation());
        Serial.print(", Y: ");
        Serial.print(getYRotation());
        Serial.print(", Z: ");
        Serial.println(getZRotation());

        // Print gravity vector
        float gravity[3];
        getGravityVector(gravity);
        Serial.print("Gravity vector: (");
        Serial.print(gravity[0]);
        Serial.print(", ");
        Serial.print(gravity[1]);
        Serial.print(", ");
        Serial.print(gravity[2]);
        Serial.println(")");

        // Print current face pointing up
        Serial.print("Current face pointing up: ");
        Serial.println(faceManager.getCurrentFace());
        Serial.println();
    }

    delay(10);
}
