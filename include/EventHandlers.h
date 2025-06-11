#ifndef EVENT_HANDLERS_H
#define EVENT_HANDLERS_H

#include <Arduino.h>

// Interface for event handlers
class EventHandlerInterface {
public:
    // Virtual destructor for proper cleanup in derived classes
    virtual ~EventHandlerInterface() {}

    // Handler for face change events
    virtual void onFaceChange(const char* previousFace, const char* currentFace) = 0;
};

// Default implementation of event handlers
class DefaultEventHandler : public EventHandlerInterface {
public:
    void onFaceChange(const char* previousFace, const char* currentFace) override;
};

// Function to register an event handler with the event manager
void registerEventHandler(EventHandlerInterface* handler);

// Function to set up the default event handler
bool initEventHandlers();

// Global event handler instance
extern EventHandlerInterface* currentEventHandler;

#endif // EVENT_HANDLERS_H
