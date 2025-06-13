#include "HttpRequestEventHandler.h"
#include "config/HttpRequestConfig.h"

HttpRequestEventHandler::HttpRequestEventHandler()
{
    // URL mappings from configuration file
    urlMappings[0] = {"Top", HTTP_URL_TOP};
    urlMappings[1] = {"Bottom", HTTP_URL_BOTTOM};
    urlMappings[2] = {"Right", HTTP_URL_RIGHT};
    urlMappings[3] = {"Left", HTTP_URL_LEFT};
    urlMappings[4] = {"Front", HTTP_URL_FRONT};
    urlMappings[5] = {"Back", HTTP_URL_BACK};
}

// Configure custom URL mappings
void HttpRequestEventHandler::configureUrlMappings(const FaceUrlMapping* mappings)
{
    for (int i = 0; i < 6; i++)
    {
        urlMappings[i] = mappings[i];
    }
}

// Set URL for a specific face
void HttpRequestEventHandler::setFaceUrl(const char* faceName, const String& url)
{
    for (int i = 0; i < 6; i++)
    {
        if (strcmp(urlMappings[i].faceName, faceName) == 0)
        {
            urlMappings[i].url = url;
            return;
        }
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
    urlMappings[0].url = topUrl;
    urlMappings[1].url = bottomUrl;
    urlMappings[2].url = rightUrl;
    urlMappings[3].url = leftUrl;
    urlMappings[4].url = frontUrl;
    urlMappings[5].url = backUrl;
}

// Helper method to get URL for a given face name
String HttpRequestEventHandler::getFaceUrl(const char* faceName)
{
    for (int i = 0; i < 6; i++)
    {
        if (strcmp(urlMappings[i].faceName, faceName) == 0)
        {
            return urlMappings[i].url;
        }
    }

    return ""; // Face not found
}

// Send HTTP request for a specific face
void HttpRequestEventHandler::sendRequestForFace(const char* faceName)
{
    // Get the URL for this face directly from config
    String url = getFaceUrl(faceName);
    if (url.length() == 0)
    {
        Serial.print("Unknown face or no URL configured for face: ");
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

// Initialize and register the handler
bool initHttpRequestEventHandler()
{
    // Create a static instance of the HTTP request handler
    static HttpRequestEventHandler httpHandler;

    // Register the HTTP handler with the event system
    eventManager.registerEventHandler(&httpHandler);

    Serial.println("HTTP Request Event Handler initialized");
    return true;
}
