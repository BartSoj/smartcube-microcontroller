#include "EventManager.h"
#include "FaceManager.h"

// Global instance of EventManager
EventManager eventManager;

EventManager::EventManager() : lastFace(nullptr), faceChangeCallback(nullptr)
{
    // Constructor implementation
}

void EventManager::setFaceChangeCallback(FaceChangeCallback callback)
{
    faceChangeCallback = callback;
}

void EventManager::update()
{
    // Get current face from FaceManager
    const char* currentFace = faceManager.getCurrentFace();

    // Check if this is the first update or if the face has changed
    if (lastFace == nullptr)
    {
        lastFace = currentFace;
        return; // First update, just store the face
    }

    // Check if face has changed
    if (strcmp(lastFace, currentFace) != 0)
    {
        // Face has changed, trigger callback if registered
        if (faceChangeCallback != nullptr)
        {
            faceChangeCallback(lastFace, currentFace);
        }

        // Update last face
        lastFace = currentFace;
    }
}

const char* EventManager::getLastFace() const
{
    return lastFace;
}

bool initEventManager()
{
    // Initialize with default settings
    return true;
}
