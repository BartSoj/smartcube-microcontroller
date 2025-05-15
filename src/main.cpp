#include <Arduino.h>
#include <FastLED.h>

// LED Panel Configuration
#define DATA_PIN 4     // GPIO pin connected to the DIN of the LED panel
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB // Most WS2812B panels are GRB. Try RGB if colors are swapped.

#define NUM_LEDS_X 8     // Number of LEDs in the X direction (width)
#define NUM_LEDS_Y 8     // Number of LEDs in the Y direction (height)
#define NUM_LEDS (NUM_LEDS_X * NUM_LEDS_Y) // Total number of LEDs (64 for a 8x8 panel)

CRGB leds[NUM_LEDS];

// Brightness (0-255). Start low, especially when testing!
// Max brightness for 64 LEDs can draw a lot of current (64 * 60mA = ~3.8A)
#define BRIGHTNESS 30

// This function handles serpentine layouts often found in matrices.
// Adjust if your panel has a different wiring pattern.
uint16_t XY(uint8_t x, uint8_t y)
{
    uint16_t i;
    if (y % 2 == 0)
    {
        i = (y * NUM_LEDS_X) + x;
    }
    else
    {
        i = (y * NUM_LEDS_X) + (NUM_LEDS_X - 1 - x);
    }
    return i;
}

void setup()
{
    Serial.begin(115200);
    delay(1000); // Power-up safety delay

    // Initialize FastLED
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS)
           .setCorrection(TypicalLEDStrip);

    FastLED.setBrightness(BRIGHTNESS);
    FastLED.clear(); // Clear all LEDs to off
    FastLED.show();

    Serial.println("ESP32 WS2812B Panel Initialized");
    Serial.print("Total LEDs: ");
    Serial.println(NUM_LEDS);
    Serial.print("Brightness: ");
    Serial.println(BRIGHTNESS);
}

void simpleRainbow()
{
    fill_rainbow(leds, NUM_LEDS, millis() / 20, 7);
}

void singlePixelChase()
{
    static uint8_t x = 0;
    static uint8_t y = 0;
    static uint32_t lastPixelTime = 0;

    if (millis() - lastPixelTime > 100)
    {
        // Move pixel every 100ms
        lastPixelTime = millis();

        FastLED.clearData(); // Clear previous pixel efficiently

        leds[XY(x, y)] = CRGB::Blue; // Set current pixel to blue

        x++;
        if (x >= NUM_LEDS_X)
        {
            x = 0;
            y++;
            if (y >= NUM_LEDS_Y)
            {
                y = 0; // Reset to top-left
            }
        }
    }
}

void loop()
{
    // simpleRainbow();
    singlePixelChase();

    // Example: Set a single pixel at (x=2, y=3) to red
    // FastLED.clearData(); // Clear previous frame
    // leds[XY(2, 3)] = CRGB::Red;

    // Example: Fill the panel with green
    fill_solid(leds, NUM_LEDS, CRGB::Red);

    FastLED.show(); // Update the LEDs
    delay(16); // Aim for roughly 60 FPS (1000ms / 60 = ~16ms)
}
