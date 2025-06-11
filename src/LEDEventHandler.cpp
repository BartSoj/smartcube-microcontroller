#include "LEDEventHandler.h"
#include "config/LEDColorConfig.h"

// Constructor with color mappings from configuration
LEDEventHandler::LEDEventHandler()
{
    // Color mappings from configuration file
    colorMappings[0] = {"Top", LED_COLOR_TOP};
    colorMappings[1] = {"Bottom", LED_COLOR_BOTTOM};
    colorMappings[2] = {"Right", LED_COLOR_RIGHT};
    colorMappings[3] = {"Left", LED_COLOR_LEFT};
    colorMappings[4] = {"Front", LED_COLOR_FRONT};
    colorMappings[5] = {"Back", LED_COLOR_BACK};
}

// Configure custom color mappings
void LEDEventHandler::configureColorMappings(const FaceColorMapping* mappings)
{
    for (int i = 0; i < 6; i++)
    {
        colorMappings[i] = mappings[i];
    }
}

// Set color for a specific face
void LEDEventHandler::setFaceColor(const char* faceName, CRGB color)
{
    for (int i = 0; i < 6; i++)
    {
        if (strcmp(colorMappings[i].faceName, faceName) == 0)
        {
            colorMappings[i].color = color;
            return;
        }
    }
}

// Configure all face colors at once
void LEDEventHandler::configureFaceColors(
    CRGB topColor,
    CRGB bottomColor,
    CRGB rightColor,
    CRGB leftColor,
    CRGB frontColor,
    CRGB backColor
)
{
    colorMappings[0].color = topColor;
    colorMappings[1].color = bottomColor;
    colorMappings[2].color = rightColor;
    colorMappings[3].color = leftColor;
    colorMappings[4].color = frontColor;
    colorMappings[5].color = backColor;
}

// Find the color for a specific face
CRGB LEDEventHandler::getColorForFace(const char* faceName)
{
    for (int i = 0; i < 6; i++)
    {
        if (strcmp(colorMappings[i].faceName, faceName) == 0)
        {
            return colorMappings[i].color;
        }
    }

    return CRGB::Black;
}

// Handle face change events
void LEDEventHandler::onFaceChange(const char* previousFace, const char* currentFace)
{
    // Get the color for the current face
    CRGB faceColor = getColorForFace(currentFace);

    // Set the background color
    Serial.print("Setting background color for '");
    Serial.print(currentFace);
    Serial.print("' face to RGB(");
    Serial.print(faceColor.r);
    Serial.print(",");
    Serial.print(faceColor.g);
    Serial.print(",");
    Serial.print(faceColor.b);
    Serial.println(")");

    // Update the LED manager with the new color
    ledManager.setBackgroundColor(faceColor);
}

// Initialize with default configuration and register the handler
bool initLEDEventHandler()
{
    // Create a static instance of the LED event handler
    static LEDEventHandler ledHandler;

    // Register the LED handler with the event system
    registerEventHandler(&ledHandler);

    Serial.println("LED Event Handler initialized");
    return true;
}
