#ifndef EVENT_HANDLERS_H
#define EVENT_HANDLERS_H

#include <Arduino.h>
#include <vector>

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

// Function to register an event handler with the event manager
void registerEventHandler(EventHandlerInterface* handler);

// Function to unregister an event handler
bool unregisterEventHandler(EventHandlerInterface* handler);

// Function to initialize the event handlers system
bool initEventHandlers();

// Global collection of event handlers
extern std::vector<EventHandlerInterface*> eventHandlers;

#endif // EVENT_HANDLERS_H
