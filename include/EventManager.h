#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <Arduino.h>
#include "FaceManager.h"

// Function pointer type for event callbacks
typedef void (*FaceChangeCallback)(const char* previousFace, const char* currentFace);

class EventManager {
private:
    const char* lastFace; // Keep track of the last detected face
    FaceChangeCallback faceChangeCallback; // Function to call when face changes

public:
    // Constructor
    EventManager();

    // Set the callback function for face change events
    void setFaceChangeCallback(FaceChangeCallback callback);

    // Check if face has changed and trigger event if it did
    void update();

    // Get the last detected face
    const char* getLastFace() const;
};

// Global instance of EventManager
extern EventManager eventManager;

// Initialize the EventManager
bool initEventManager();

#endif // EVENT_MANAGER_H
