#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <Arduino.h>
#include <vector>

// Interface for event handlers
class IFaceChangeObserver
{
public:
    // Virtual destructor for proper cleanup in derived classes
    virtual ~IFaceChangeObserver()
    = default;

    // Handler for face change events
    virtual void onFaceChange(const char* previousFace, const char* currentFace) = 0;
};

class OrientationNotifier
{
private:
    const char* lastFace; // Keep track of the last detected face
    std::vector<IFaceChangeObserver*> observers; // Collection of event handlers

public:
    // Constructor
    OrientationNotifier();

    // Register an event handler
    void registerObserver(IFaceChangeObserver* handler);

    // Unregister an event handler
    bool unregisterObserver(IFaceChangeObserver* handler);

    // Check if face has changed and trigger event if it did
    void checkAndNotify();

    // Get the last detected face
    const char* getLastFace() const;

    // Notify all event handlers about face change
    void notifyObservers(const char* previousFace, const char* currentFace);

    // Clear all registered handlers
    void removeAllObservers();
};

// Global instance of EventManager
extern OrientationNotifier orientationNotifier;

// Initialize the EventManager and event handlers
bool initOrientationNotifier();

#endif // EVENT_MANAGER_H
