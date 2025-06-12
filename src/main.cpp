#include <Arduino.h>
#include "MPUManager.h"
#include "LEDManager.h"
#include "FaceManager.h"
#include "EventManager.h"
#include "HttpRequestEventHandler.h"
#include "LEDEventHandler.h"

void setup()
{
    Serial.begin(115200);

    // Initialize MPU6050
    if (!mpuManager.init())
    {
        Serial.println("Failed to initialize MPU6050. Check connections.");
    }
    else
    {
        Serial.println("MPU6050 initialized successfully.");
    }
    delay(2000);

    // Initialize LED panel
    if (!ledManager.init())
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

    // Initialize HTTP Request Event Handler
    if (initHttpRequestEventHandler())
    {
        Serial.println("HTTP Request Event Handler initialized successfully.");
    }

    // Initialize LED Event Handler
    if (initLEDEventHandler())
    {
        Serial.println("LED Event Handler initialized successfully.");
    }
}

void loop()
{
    // Update event manager to detect face changes
    eventManager.update();

    delay(8);
}
