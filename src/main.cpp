#include <Arduino.h>
#include "MPUManager.h"
#include "LEDManager.h"

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
}

void loop()
{
    // Update MPU data - call frequently to prevent FIFO overflow
    updateMPU();

    // Update LEDs (handle background color cycling)
    updateLEDs();

    // Print rotation angles every 500ms
    static unsigned long lastMpuPrintTime = 0;
    unsigned long currentTime = millis();
    if (currentTime - lastMpuPrintTime >= 500)
    {
        lastMpuPrintTime = currentTime;

        Serial.print("Rotation (degrees) - X: ");
        Serial.print(getXRotation());
        Serial.print(", Y: ");
        Serial.print(getYRotation());
        Serial.print(", Z: ");
        Serial.println(getZRotation());
    }

    delay(10);
}
