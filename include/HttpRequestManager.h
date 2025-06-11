#ifndef HTTP_REQUEST_MANAGER_H
#define HTTP_REQUEST_MANAGER_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

class HttpRequestManager
{
public:
    // Initialize the WiFi connection
    static bool init();

    // Check if WiFi is connected
    static bool isConnected();

    // Reconnect to WiFi if disconnected
    static bool reconnect();

    // Send HTTP request with optional JSON body
    static DynamicJsonDocument sendRequest(const String& url, const String& method, const JsonDocument* body = nullptr);

    // Print WiFi status information
    static void printWifiStatus();

private:
    static bool _initialized;
};

#endif // HTTP_REQUEST_MANAGER_H
