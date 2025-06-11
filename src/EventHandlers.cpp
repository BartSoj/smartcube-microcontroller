#include "EventHandlers.h"
#include "EventManager.h"

// Global pointer to the current event handler
EventHandlerInterface* currentEventHandler = nullptr;

// Callback function that bridges between EventManager and EventHandlers
void faceChangeCallbackBridge(const char* previousFace, const char* currentFace) {
    if (currentEventHandler != nullptr) {
        currentEventHandler->onFaceChange(previousFace, currentFace);
    }
}

// Default implementation of face change handler
void DefaultEventHandler::onFaceChange(const char* previousFace, const char* currentFace) {
    Serial.print("Face changed from ");
    Serial.print(previousFace);
    Serial.print(" to ");
    Serial.println(currentFace);
}

// Register an event handler with the event manager
void registerEventHandler(EventHandlerInterface* handler) {
    // Store the handler in the global pointer
    currentEventHandler = handler;

    // Register the bridge callback with the event manager
    eventManager.setFaceChangeCallback(faceChangeCallbackBridge);
}

// Initialize the default event handler
bool initEventHandlers() {
    // Create and register the default event handler
    static DefaultEventHandler defaultHandler;
    registerEventHandler(&defaultHandler);

    return true;
}
