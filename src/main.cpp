#include <Arduino.h>
#include "MotionSensor.h"
#include "LedController.h"
#include "CubeOrientation.h"
#include "OrientationNotifier.h"
#include "WebObserver.h"
#include "LedObserver.h"

void setup()
{
    Serial.begin(115200);

    // Initialize MPU6050
    if (!motionSensor.init())
    {
        Serial.println("Failed to initialize MPU6050. Check connections.");
    }
    else
    {
        Serial.println("MPU6050 initialized successfully.");
    }
    delay(2000);

    // Initialize LED panel
    if (!ledController.init())
    {
        Serial.println("Failed to initialize LED panel.");
    }
    else
    {
        Serial.println("LED panel initialized successfully.");
    }

    // Initialize Face Manager
    if (initCubeOrientation())
    {
        Serial.println("Face Manager initialized successfully.");
        cubeOrientation.printFaceMappings();
    }

    // Initialize Event Manager
    if (initOrientationNotifier())
    {
        Serial.println("Event Manager initialized successfully.");
    }

    // Initialize LED Event Handler
    if (initLedObserver())
    {
        Serial.println("LED Event Handler initialized successfully.");
    }

    // Initialize HTTP Request Event Handler
    if (initWebObserver())
    {
        Serial.println("HTTP Request Event Handler initialized successfully.");
    }
}

void loop()
{
    // Update event manager to detect face changes
    orientationNotifier.checkAndNotify();
}
