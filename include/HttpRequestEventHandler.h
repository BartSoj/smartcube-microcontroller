#ifndef HTTP_REQUEST_EVENT_HANDLER_H
#define HTTP_REQUEST_EVENT_HANDLER_H

#include "EventManager.h"
#include "HttpRequestManager.h"

// Structure to map face names to URLs
typedef struct
{
    const char* faceName; // Face name (Top, Bottom, Front, Back, Left, Right)
    String url; // URL to request when this face is up
} FaceUrlMapping;

// Event handler that sends HTTP requests based on cube face
class HttpRequestEventHandler : public EventHandlerInterface
{
private:
    // Array of face-to-URL mappings
    FaceUrlMapping urlMappings[6];

    // Helper method to get URL for a given face name
    String getFaceUrl(const char* faceName);

    // Send the HTTP request for a specific face
    void sendRequestForFace(const char* faceName);

public:
    // Constructor with default URL mappings
    HttpRequestEventHandler();

    // Configure custom URL mappings
    void configureUrlMappings(const FaceUrlMapping* mappings);

    // Set URL for a specific face
    void setFaceUrl(const char* faceName, const String& url);

    // Configure all face URLs at once
    void configureFaceUrls(
        const String& topUrl,
        const String& bottomUrl,
        const String& rightUrl,
        const String& leftUrl,
        const String& frontUrl,
        const String& backUrl
    );

    // Handler for face change events
    void onFaceChange(const char* previousFace, const char* currentFace) override;
};

// Function to initialize and register the HTTP request handler
bool initHttpRequestEventHandler();

#endif // HTTP_REQUEST_EVENT_HANDLER_H
