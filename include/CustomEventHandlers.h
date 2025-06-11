#ifndef CUSTOM_EVENT_HANDLERS_H
#define CUSTOM_EVENT_HANDLERS_H

#include "EventHandlers.h"

// Example of a custom event handler implementation
class CustomEventHandler : public EventHandlerInterface {
public:
    void onFaceChange(const char* previousFace, const char* currentFace) override;
};

// Function to initialize and register the custom handler
bool initCustomEventHandlers();

#endif // CUSTOM_EVENT_HANDLERS_H
