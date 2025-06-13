#include "HttpRequestManager.h"
#include "../include/config/secrets.h"

bool HttpRequestManager::_initialized = false;

bool HttpRequestManager::init()
{
    if (_initialized)
    {
        return true;
    }

    Serial.println("Connecting to WiFi...");
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    // Wait for connection with timeout
    int timeout = 20; // 10 seconds timeout
    while (WiFi.status() != WL_CONNECTED && timeout > 0)
    {
        delay(500);
        Serial.print(".");
        timeout--;
    }

    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("\nFailed to connect to WiFi");
        return false;
    }

    Serial.println("\nWiFi connected successfully");
    printWifiStatus();
    _initialized = true;
    return true;
}

bool HttpRequestManager::isConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

bool HttpRequestManager::reconnect()
{
    if (isConnected())
    {
        return true;
    }

    // Try to reconnect
    WiFi.disconnect();
    delay(1000);
    return init();
}

DynamicJsonDocument HttpRequestManager::sendRequest(const String& url, const String& method, const JsonDocument* body)
{
    DynamicJsonDocument responseDoc(2048); // Adjust size based on expected response size

    // Ensure WiFi is connected
    if (!isConnected() && !reconnect())
    {
        responseDoc["error"] = "WiFi not connected";
        return responseDoc;
    }

    HTTPClient http;
    http.begin(url);
    http.addHeader("Content-Type", "application/json");
    http.setTimeout(150);

    int httpResponseCode = 0;
    String payload;

    if (method == "GET")
    {
        httpResponseCode = http.GET();
    }
    else if (method == "POST" || method == "PUT" || method == "PATCH")
    {
        String jsonBody = "";
        if (body != nullptr)
        {
            // Serialize JSON document to string
            serializeJson(*body, jsonBody);
        }

        if (method == "POST")
        {
            httpResponseCode = http.POST(jsonBody);
        }
        else if (method == "PUT")
        {
            httpResponseCode = http.PUT(jsonBody);
        }
        else if (method == "PATCH")
        {
            httpResponseCode = http.PATCH(jsonBody);
        }
    }
    else if (method == "DELETE")
    {
        httpResponseCode = http.sendRequest("DELETE");
    }

    // Process response
    if (httpResponseCode > 0)
    {
        payload = http.getString();

        // Try to parse JSON response
        DeserializationError error = deserializeJson(responseDoc, payload);
        if (error)
        {
            // If not valid JSON, return raw response
            responseDoc.clear();
            responseDoc["data"] = payload;
        }
        responseDoc["status"] = httpResponseCode;
    }
    else
    {
        responseDoc["error"] = http.errorToString(httpResponseCode);
        responseDoc["status"] = httpResponseCode;
    }

    http.end();
    return responseDoc;
}

void HttpRequestManager::printWifiStatus()
{
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    Serial.print("Signal strength (RSSI): ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
}
