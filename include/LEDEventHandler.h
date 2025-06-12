#ifndef LED_EVENT_HANDLER_H
#define LED_EVENT_HANDLER_H

#include "EventManager.h"
#include "LEDManager.h"

// Structure to map face names to colors
typedef struct
{
    const char* faceName; // Face name (Top, Bottom, Front, Back, Left, Right)
    CRGB color; // Color to display when this face is up
} FaceColorMapping;

// Event handler that changes LED background color based on cube face
class LEDEventHandler : public EventHandlerInterface
{
private:
    // Array of face-to-color mappings
    FaceColorMapping colorMappings[6];

    // Helper method to find the color for a specific face
    CRGB getColorForFace(const char* faceName);

public:
    // Constructor with default color mappings
    LEDEventHandler();

    // Configure custom color mappings
    void configureColorMappings(const FaceColorMapping* mappings);

    // Handler for face change events
    void onFaceChange(const char* previousFace, const char* currentFace) override;

    // Set color for a specific face
    void setFaceColor(const char* faceName, CRGB color);

    // Configure all face colors at once
    void configureFaceColors(
        CRGB topColor,
        CRGB bottomColor,
        CRGB rightColor,
        CRGB leftColor,
        CRGB frontColor,
        CRGB backColor
    );
};

// Function to initialize and register the LED event handler
bool initLEDEventHandler();

#endif // LED_EVENT_HANDLER_H
