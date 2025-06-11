#include <Arduino.h>
#include "MPUManager.h"
#include "LEDManager.h"
#include "FaceManager.h"
#include "EventManager.h"
#include "EventHandlers.h"

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

    // Initialize Event Manager
    if (initEventManager())
    {
        Serial.println("Event Manager initialized successfully.");
    }

    // Initialize Event Handlers
    if (initEventHandlers())
    {
        Serial.println("Event Handlers initialized successfully.");
    }
}

void loop()
{
    // Update MPU data - call frequently to prevent FIFO overflow
    updateMPU();

    // Update LEDs (handle background color cycling)
    updateLEDs();

    // Update event manager to detect face changes
    eventManager.update();

    delay(10);
}
