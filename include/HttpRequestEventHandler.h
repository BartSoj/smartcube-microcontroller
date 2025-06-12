#ifndef HTTP_REQUEST_EVENT_HANDLER_H
#define HTTP_REQUEST_EVENT_HANDLER_H

#include "EventManager.h"
#include "HttpRequestManager.h"

// Event handler that sends HTTP requests based on cube face
class HttpRequestEventHandler : public EventHandlerInterface
{
private:
    // Array of URLs for each face (indexed in the same order as faces in FaceManager)
    String faceUrls[6]; // Top, Bottom, Right, Left, Front, Back

    // Helper method to find the index of a face name
    int getFaceIndex(const char* faceName);

    // Send the HTTP request for a specific face
    void sendRequestForFace(const char* faceName);

public:
    // Constructor with default empty URLs
    HttpRequestEventHandler();

    // Configure the URL for a specific face
    void setFaceUrl(const char* faceName, const String& url);

    // Handler for face change events
    void onFaceChange(const char* previousFace, const char* currentFace) override;

    // Set all face URLs at once
    void configureFaceUrls(
        const String& topUrl,
        const String& bottomUrl,
        const String& rightUrl,
        const String& leftUrl,
        const String& frontUrl,
        const String& backUrl
    );
};

// Function to initialize and register the HTTP request handler
bool initHttpRequestEventHandler();

#endif // HTTP_REQUEST_EVENT_HANDLER_H
