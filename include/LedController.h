#ifndef LED_MANAGER_H
#define LED_MANAGER_H

#include <FastLED.h>
#include "config/PanelConfig.h"

// LED Panel Configuration
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define DATA_PIN 22

// Panel layout configuration
#define PANEL_SIZE 8  // 8x8 panels
#define NUM_PANELS 6  // 6 panels: top, bottom, left, right, front, back
#define NUM_LEDS_PER_PANEL (PANEL_SIZE * PANEL_SIZE)
#define NUM_LEDS (NUM_LEDS_PER_PANEL * NUM_PANELS)

// Panel identifiers
enum PanelSide
{
    TOP = PANEL_IDX_TOP,
    BOTTOM = PANEL_IDX_BOTTOM,
    LEFT = PANEL_IDX_LEFT,
    RIGHT = PANEL_IDX_RIGHT,
    FRONT = PANEL_IDX_FRONT,
    BACK = PANEL_IDX_BACK
};

// Icon identifiers
enum IconType
{
    ICON_NONE = 0,
    ICON_HEART,
    ICON_SMILEY,
    ICON_ARROW,
    ICON_EXCLAMATION,
    ICON_QUESTION
};

// Special value for background pixels in icon definitions
extern const CRGB BG_PLACEHOLDER;

class LedController
{
private:
    CRGB leds[NUM_LEDS];
    CRGB currentBackgroundColor;
    uint8_t currentBrightness;
    bool ledsEnabled;
    IconType currentIcons[NUM_PANELS]{};

    // Helper function to map x,y coordinates to LED index within a panel
    static uint16_t XY(uint8_t x, uint8_t y, PanelSide panel);

    // Helper to apply an icon to a panel with the current background
    void applyIconToPanel(IconType icon, PanelSide panel);

    // Updates the physical LEDs
    void updateLEDs() const;

public:
    LedController();

    // Initialization
    bool init();

    // Panel control functions
    void setIcon(IconType icon, PanelSide panel);
    void setAllIcons(IconType icon);
    void setBackgroundColor(CRGB color);
    void setBrightness(uint8_t brightness);
    void enableLEDs(bool enable);

    // Status getters
    CRGB getBackgroundColor() const;
    uint8_t getBrightness() const;
    bool isEnabled() const;
    IconType getCurrentIcon(PanelSide panel) const;
};

extern LedController ledController;

#endif // LED_MANAGER_H
