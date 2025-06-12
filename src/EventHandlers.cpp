#include "EventHandlers.h"
#include "EventManager.h"
#include <algorithm> // for std::find

// Global collection of event handlers
std::vector<EventHandlerInterface*> eventHandlers;

// Callback function that bridges between EventManager and EventHandlers
void faceChangeCallbackBridge(const char* previousFace, const char* currentFace)
{
    // Call all registered event handlers
    for (auto handler : eventHandlers)
    {
        handler->onFaceChange(previousFace, currentFace);
    }
}

// Register an event handler with the event manager
void registerEventHandler(EventHandlerInterface* handler)
{
    // Check if the handler is already registered
    if (std::find(eventHandlers.begin(), eventHandlers.end(), handler) == eventHandlers.end())
    {
        // Add the handler to the vector
        eventHandlers.push_back(handler);
    }
}

// Unregister an event handler
bool unregisterEventHandler(EventHandlerInterface* handler)
{
    auto it = std::find(eventHandlers.begin(), eventHandlers.end(), handler);
    if (it != eventHandlers.end())
    {
        eventHandlers.erase(it);
        return true;
    }
    return false;
}

// Initialize the event handlers
bool initEventHandlers()
{
    // Clear any existing handlers
    eventHandlers.clear();

    // Register the callback with the event manager
    eventManager.setFaceChangeCallback(faceChangeCallbackBridge);

    return true;
}
