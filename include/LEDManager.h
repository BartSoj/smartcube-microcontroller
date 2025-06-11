#ifndef LED_MANAGER_H
#define LED_MANAGER_H

#include <Arduino.h>
#include <FastLED.h>

// --- LED Panel Configuration ---
#define DATA_PIN 22     // GPIO pin connected to the DIN of the LED panel (e.g., D4)
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB // Most WS2812B panels are GRB. Try RGB if colors are swapped.

#define NUM_LEDS_X 8     // Number of LEDs in the X direction (width)
#define NUM_LEDS_Y 8     // Number of LEDs in the Y direction (height)
#define NUM_LEDS (NUM_LEDS_X * NUM_LEDS_Y) // Total number of LEDs (64 for an 8x8 panel)

// Brightness (0-255). Start low! Max for 64 LEDs can be ~3.8A.
#define BRIGHTNESS 5

/**
 * Initialize the LED panel
 * 
 * @return true if initialization successful, false otherwise
 */
bool initLEDs();

/**
 * Update the LED panel with cycling background colors
 * This function should be called periodically from the main loop
 */
void updateLEDs();

/**
 * Display an image with a specific background color
 * 
 * @param bgColorIndex Index of the background color to use
 */
void displayWithBackgroundColor(int bgColorIndex);

/**
 * Get the current background color index
 * 
 * @return Current background color index
 */
int getCurrentBgColorIndex();

#endif // LED_MANAGER_H
