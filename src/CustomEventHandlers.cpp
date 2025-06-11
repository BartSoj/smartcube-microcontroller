#include "CustomEventHandlers.h"
#include "LEDManager.h"

void CustomEventHandler::onFaceChange(const char* previousFace, const char* currentFace) {
    Serial.print("[CUSTOM HANDLER] Face changed from ");
    Serial.print(previousFace);
    Serial.print(" to ");
    Serial.println(currentFace);

    // Example of custom actions based on specific faces
    if (strcmp(currentFace, "Top") == 0) {
        // Example: Set LEDs to green when top face is up
        // setLEDColor(0, 255, 0); // Assuming a function like this exists
        Serial.println("Top face detected - special action triggered!");
    } 
    else if (strcmp(currentFace, "Bottom") == 0) {
        // Example: Set LEDs to red when bottom face is up
        // setLEDColor(255, 0, 0);
        Serial.println("Bottom face detected - special action triggered!");
    }

    // Add more custom actions for other faces as needed
}

bool initCustomEventHandlers() {
    // Create a static instance of the custom handler
    static CustomEventHandler customHandler;

    // Register the custom handler with the event system
    registerEventHandler(&customHandler);

    return true;
}
