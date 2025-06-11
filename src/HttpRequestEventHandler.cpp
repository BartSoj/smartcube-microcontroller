#include "HttpRequestEventHandler.h"
#include "config/HttpRequestConfig.h"

HttpRequestEventHandler::HttpRequestEventHandler()
{
    // Initialize all URLs to empty strings
    for (int i = 0; i < 6; i++)
    {
        faceUrls[i] = "";
    }
}

// Helper method to get the index of a face name
int HttpRequestEventHandler::getFaceIndex(const char* faceName)
{
    if (strcmp(faceName, "Top") == 0) return 0;
    if (strcmp(faceName, "Bottom") == 0) return 1;
    if (strcmp(faceName, "Right") == 0) return 2;
    if (strcmp(faceName, "Left") == 0) return 3;
    if (strcmp(faceName, "Front") == 0) return 4;
    if (strcmp(faceName, "Back") == 0) return 5;
    return -1; // Face not found
}

// Configure URL for a specific face
void HttpRequestEventHandler::setFaceUrl(const char* faceName, const String& url)
{
    int index = getFaceIndex(faceName);
    if (index >= 0 && index < 6)
    {
        faceUrls[index] = url;
    }
}

// Configure all face URLs at once
void HttpRequestEventHandler::configureFaceUrls(
    const String& topUrl,
    const String& bottomUrl,
    const String& rightUrl,
    const String& leftUrl,
    const String& frontUrl,
    const String& backUrl
)
{
    faceUrls[0] = topUrl;
    faceUrls[1] = bottomUrl;
    faceUrls[2] = rightUrl;
    faceUrls[3] = leftUrl;
    faceUrls[4] = frontUrl;
    faceUrls[5] = backUrl;
}

// Send HTTP request for a specific face
void HttpRequestEventHandler::sendRequestForFace(const char* faceName)
{
    int index = getFaceIndex(faceName);
    if (index < 0 || index >= 6)
    {
        Serial.print("Unknown face: ");
        Serial.println(faceName);
        return;
    }

    // Get the URL for this face
    String url = faceUrls[index];
    if (url.length() == 0)
    {
        Serial.print("No URL configured for face: ");
        Serial.println(faceName);
        return;
    }

    // Send the HTTP request
    Serial.print("Sending request for face '");
    Serial.print(faceName);
    Serial.print("' to: ");
    Serial.println(url);

    // Send the GET request
    DynamicJsonDocument response = HttpRequestManager::sendRequest(url, "GET");

    // Process the response
    if (response.containsKey("error"))
    {
        Serial.print("HTTP request failed: ");
        Serial.println(response["error"].as<String>());
    }
    else
    {
        Serial.print("HTTP response status: ");
        Serial.println(response["status"].as<int>());

        // Print response data if available
        if (response.containsKey("data"))
        {
            Serial.print("Response: ");
            Serial.println(response["data"].as<String>());
        }
        else
        {
            // Print the JSON response
            Serial.println("Response JSON:");
            serializeJsonPretty(response, Serial);
            Serial.println();
        }
    }
}

// Handle face change events
void HttpRequestEventHandler::onFaceChange(const char* previousFace, const char* currentFace)
{
    // Send HTTP request for the new face
    sendRequestForFace(currentFace);
}

// Initialize with default configuration and register the handler
bool initHttpRequestEventHandler()
{
    // Create a static instance of the HTTP request handler
    static HttpRequestEventHandler httpHandler;

    // Configure URLs for each face from the configuration file
    httpHandler.configureFaceUrls(
        HTTP_URL_TOP, // Top face
        HTTP_URL_BOTTOM, // Bottom face
        HTTP_URL_RIGHT, // Right face
        HTTP_URL_LEFT, // Left face
        HTTP_URL_FRONT, // Front face
        HTTP_URL_BACK // Back face
    );

    // Register the HTTP handler with the event system
    registerEventHandler(&httpHandler);

    Serial.println("HTTP Request Event Handler initialized");
    return true;
}
