#include "OrientationNotifier.h"
#include "CubeOrientation.h"
#include <algorithm> // for std::find

OrientationNotifier orientationNotifier;

OrientationNotifier::OrientationNotifier() : lastFace(nullptr)
{
    removeAllObservers();
}

void OrientationNotifier::registerObserver(IFaceChangeObserver* handler)
{
    // Check if the handler is already registered
    if (std::find(observers.begin(), observers.end(), handler) == observers.end())
    {
        // Add the handler to the vector
        observers.push_back(handler);
    }
}

bool OrientationNotifier::unregisterObserver(IFaceChangeObserver* handler)
{
    auto it = std::find(observers.begin(), observers.end(), handler);
    if (it != observers.end())
    {
        observers.erase(it);
        return true;
    }
    return false;
}

void OrientationNotifier::notifyObservers(const char* previousFace, const char* currentFace)
{
    // Call all registered event handlers
    for (auto handler : observers)
    {
        handler->onFaceChange(previousFace, currentFace);
    }
}

void OrientationNotifier::checkAndNotify()
{
    // Get current face from FaceManager
    const char* currentFace = cubeOrientation.getCurrentFace();

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
        notifyObservers(lastFace, currentFace);

        // Update last face
        lastFace = currentFace;
    }
}

const char* OrientationNotifier::getLastFace() const
{
    return lastFace;
}

void OrientationNotifier::removeAllObservers()
{
    // Clear any existing handlers
    observers.clear();
}

bool initOrientationNotifier()
{
    // Initialize with default settings
    orientationNotifier.removeAllObservers();
    return true;
}
