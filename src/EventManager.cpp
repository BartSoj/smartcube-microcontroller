#include "EventManager.h"
#include "FaceManager.h"
#include <algorithm> // for std::find

// Global instance of EventManager
EventManager eventManager;

EventManager::EventManager() : lastFace(nullptr)
{
    // Constructor implementation
    clearHandlers();
}

void EventManager::registerEventHandler(EventHandlerInterface* handler)
{
    // Check if the handler is already registered
    if (std::find(eventHandlers.begin(), eventHandlers.end(), handler) == eventHandlers.end())
    {
        // Add the handler to the vector
        eventHandlers.push_back(handler);
    }
}

bool EventManager::unregisterEventHandler(EventHandlerInterface* handler)
{
    auto it = std::find(eventHandlers.begin(), eventHandlers.end(), handler);
    if (it != eventHandlers.end())
    {
        eventHandlers.erase(it);
        return true;
    }
    return false;
}

void EventManager::notifyFaceChange(const char* previousFace, const char* currentFace)
{
    // Call all registered event handlers
    for (auto handler : eventHandlers)
    {
        handler->onFaceChange(previousFace, currentFace);
    }
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
        // Face has changed, notify all registered handlers
        notifyFaceChange(lastFace, currentFace);

        // Update last face
        lastFace = currentFace;
    }
}

const char* EventManager::getLastFace() const
{
    return lastFace;
}

void EventManager::clearHandlers()
{
    // Clear any existing handlers
    eventHandlers.clear();
}

bool initEventManager()
{
    // Initialize with default settings
    eventManager.clearHandlers();
    return true;
}
