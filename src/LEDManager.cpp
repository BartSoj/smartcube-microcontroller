#include "LEDManager.h"

// --- LED Panel Variables ---
CRGB leds[NUM_LEDS];

// --- Special Placeholder for Background Pixels ---
const CRGB BG_PLACEHOLDER = CRGB(1, 2, 3); // A unique, unlikely color for placeholder

// --- Icon Data (8x8 "Heart" with placeholder background) ---
// Icon color: Red (CRGB::Red)
// Background pixels: BG_PLACEHOLDER
const CRGB heartIcon[NUM_LEDS_Y][NUM_LEDS_X] = {
    {BG_PLACEHOLDER, CRGB::Red, CRGB::Red, BG_PLACEHOLDER, BG_PLACEHOLDER, CRGB::Red, CRGB::Red, BG_PLACEHOLDER},
    {CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red},
    {CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red},
    {CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red},
    {BG_PLACEHOLDER, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, BG_PLACEHOLDER},
    {BG_PLACEHOLDER, BG_PLACEHOLDER, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, BG_PLACEHOLDER, BG_PLACEHOLDER},
    {
        BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, CRGB::Red, CRGB::Red, BG_PLACEHOLDER, BG_PLACEHOLDER,
        BG_PLACEHOLDER
    },
    {
        BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER,
        BG_PLACEHOLDER
    }
};

// --- Hardcoded Background Colors ---
const int NUM_BG_COLORS = 6;
const CRGB backgroundColors[NUM_BG_COLORS] = {
    CRGB::Blue,
    CRGB::Green,
    CRGB::Purple,
    CRGB::Orange,
    CRGB::Teal,
    CRGB::DarkGoldenrod // A less common one for variety
};
int currentBgColorIndex = 0;
CRGB currentBackgroundColor = backgroundColors[0]; // Initial background color

// Variables for background color cycling
unsigned long lastBgChangeTime = 0;
const unsigned long bgChangeInterval = 1000; // Change background every 1000ms (1 second)

// --- Helper function for mapping X,Y coordinates to a single LED index ---
// This version assumes SERPENTINE_LAYOUT = true and FIRST_ROW_FROM_RIGHT = false
uint16_t XY(uint8_t x, uint8_t y)
{
    uint16_t i;
    if (y % 2 == 0)
    {
        // Even rows (0, 2, 4...) - data flows left to right
        i = (y * NUM_LEDS_X) + x;
    }
    else
    {
        // Odd rows (1, 3, 5...) - data flows right to left
        i = (y * NUM_LEDS_X) + (NUM_LEDS_X - 1 - x);
    }
    return i;
}

// --- Function to display an image with a dynamic background ---
void displayImageWithDynamicBackground(const CRGB image[NUM_LEDS_Y][NUM_LEDS_X], const CRGB& bgColor)
{
    for (int y = 0; y < NUM_LEDS_Y; y++)
    {
        for (int x = 0; x < NUM_LEDS_X; x++)
        {
            CRGB pixelColor = image[y][x];
            if (pixelColor == BG_PLACEHOLDER)
            {
                leds[XY(x, y)] = bgColor; // Use the dynamic background color
            }
            else
            {
                leds[XY(x, y)] = pixelColor; // Use the icon's color
            }
        }
    }
    FastLED.show(); // Update the physical LEDs
}

bool initLEDs()
{
    Serial.println("ESP32 WS2812B Panel - Icon with Cycling Background Colors");
    Serial.print("Initializing FastLED for ");
    Serial.print(NUM_LEDS);
    Serial.println(" LEDs...");

    CFastLED::addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS)
        .setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.clear();
    FastLED.show();

    Serial.print("Brightness set to: ");
    Serial.println(BRIGHTNESS);
    Serial.println("Initial background color displayed.");

    // Display the icon with the initial background color
    displayImageWithDynamicBackground(heartIcon, currentBackgroundColor);

    return true;
}

void updateLEDs()
{
    unsigned long currentTime = millis();

    // Change background color every second
    if (currentTime - lastBgChangeTime >= bgChangeInterval)
    {
        lastBgChangeTime = currentTime;

        // Cycle to the next background color
        currentBgColorIndex++;
        if (currentBgColorIndex >= NUM_BG_COLORS)
        {
            currentBgColorIndex = 0; // Wrap around
        }
        currentBackgroundColor = backgroundColors[currentBgColorIndex];

        // Update the display with the new background color
        displayImageWithDynamicBackground(heartIcon, currentBackgroundColor);
    }
}

void displayWithBackgroundColor(int bgColorIndex)
{
    if (bgColorIndex >= 0 && bgColorIndex < NUM_BG_COLORS)
    {
        currentBgColorIndex = bgColorIndex;
        currentBackgroundColor = backgroundColors[currentBgColorIndex];
        displayImageWithDynamicBackground(heartIcon, currentBackgroundColor);
    }
}

int getCurrentBgColorIndex()
{
    return currentBgColorIndex;
}
