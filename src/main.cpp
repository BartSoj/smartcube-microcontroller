#include <Arduino.h>
#include <FastLED.h>

// How many LEDs are in the strip?
#define NUM_LEDS 60 // Change this to your number of LEDs

// For ESP32, any GPiO pin can be used.
#define DATA_PIN 4  // The GPIO pin connected to the DI of the LED strip (e.g., D4)

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() {
    Serial.begin(115200); // For debugging
    delay(1000); // Power-up safety delay

    // FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); // For WS2812B, NEOPIXEL is often an alias
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS); // Explicitly WS2812B, GRB color order
    // Some strips might be RGB, if colors are swapped, try RGB:
    // FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);

    FastLED.setBrightness(50); // Set overall brightness (0-255). Start low!
    Serial.println("FastLED Setup Done.");
}

void loop() {
    // Simple animation: a cycling rainbow
    fill_rainbow(leds, NUM_LEDS, millis() / 20, 7); // hue, delta hue
    FastLED.show();
    delay(16); // ~60 FPS

    // Example: Set first LED to red
    // leds[0] = CRGB::Red;
    // FastLED.show();
    // delay(1000);

    // leds[0] = CRGB::Black; // Turn it off
    // FastLED.show();
    // delay(1000);
}