#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <Arduino.h>
#include <vector>
#include "FaceManager.h"

// Interface for event handlers
class EventHandlerInterface
{
public:
    // Virtual destructor for proper cleanup in derived classes
    virtual ~EventHandlerInterface()
    {
    }

    // Handler for face change events
    virtual void onFaceChange(const char* previousFace, const char* currentFace) = 0;
};

class EventManager
{
private:
    const char* lastFace; // Keep track of the last detected face
    std::vector<EventHandlerInterface*> eventHandlers; // Collection of event handlers

public:
    // Constructor
    EventManager();

    // Register an event handler
    void registerEventHandler(EventHandlerInterface* handler);

    // Unregister an event handler
    bool unregisterEventHandler(EventHandlerInterface* handler);

    // Check if face has changed and trigger event if it did
    void update();

    // Get the last detected face
    const char* getLastFace() const;

    // Notify all event handlers about face change
    void notifyFaceChange(const char* previousFace, const char* currentFace);

    // Clear all registered handlers
    void clearHandlers();
};

// Global instance of EventManager
extern EventManager eventManager;

// Initialize the EventManager and event handlers
bool initEventManager();

#endif // EVENT_MANAGER_H
