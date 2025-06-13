#include "LEDManager.h"

// --- Special Placeholder for Background Pixels ---
const CRGB BG_PLACEHOLDER = CRGB(1, 2, 3);

// --- Icon Definitions ---
// Heart Icon (8x8)
const CRGB heartIcon[PANEL_SIZE][PANEL_SIZE] = {
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

// Smiley Icon (8x8)
const CRGB smileyIcon[PANEL_SIZE][PANEL_SIZE] = {
    {
        BG_PLACEHOLDER, BG_PLACEHOLDER, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, BG_PLACEHOLDER,
        BG_PLACEHOLDER
    },
    {
        BG_PLACEHOLDER, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow,
        BG_PLACEHOLDER
    },
    {CRGB::Yellow, CRGB::Yellow, CRGB::Black, CRGB::Yellow, CRGB::Yellow, CRGB::Black, CRGB::Yellow, CRGB::Yellow},
    {CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow},
    {CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow},
    {CRGB::Yellow, CRGB::Black, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Black, CRGB::Yellow},
    {BG_PLACEHOLDER, CRGB::Yellow, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Yellow, BG_PLACEHOLDER},
    {
        BG_PLACEHOLDER, BG_PLACEHOLDER, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, BG_PLACEHOLDER,
        BG_PLACEHOLDER
    }
};

// Arrow Icon (8x8)
const CRGB arrowIcon[PANEL_SIZE][PANEL_SIZE] = {
    {
        BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, CRGB::White, CRGB::White, BG_PLACEHOLDER, BG_PLACEHOLDER,
        BG_PLACEHOLDER
    },
    {
        BG_PLACEHOLDER, BG_PLACEHOLDER, CRGB::White, CRGB::White, CRGB::White, CRGB::White, BG_PLACEHOLDER,
        BG_PLACEHOLDER
    },
    {BG_PLACEHOLDER, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, BG_PLACEHOLDER},
    {CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White},
    {
        BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, CRGB::White, CRGB::White, BG_PLACEHOLDER, BG_PLACEHOLDER,
        BG_PLACEHOLDER
    },
    {
        BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, CRGB::White, CRGB::White, BG_PLACEHOLDER, BG_PLACEHOLDER,
        BG_PLACEHOLDER
    },
    {
        BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, CRGB::White, CRGB::White, BG_PLACEHOLDER, BG_PLACEHOLDER,
        BG_PLACEHOLDER
    },
    {
        BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, CRGB::White, CRGB::White, BG_PLACEHOLDER, BG_PLACEHOLDER,
        BG_PLACEHOLDER
    }
};

// Exclamation Icon (8x8)
const CRGB exclamationIcon[PANEL_SIZE][PANEL_SIZE] = {
    {
        BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, CRGB::Red, CRGB::Red, BG_PLACEHOLDER, BG_PLACEHOLDER,
        BG_PLACEHOLDER
    },
    {BG_PLACEHOLDER, BG_PLACEHOLDER, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, BG_PLACEHOLDER, BG_PLACEHOLDER},
    {BG_PLACEHOLDER, BG_PLACEHOLDER, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, BG_PLACEHOLDER, BG_PLACEHOLDER},
    {BG_PLACEHOLDER, BG_PLACEHOLDER, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, BG_PLACEHOLDER, BG_PLACEHOLDER},
    {BG_PLACEHOLDER, BG_PLACEHOLDER, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, BG_PLACEHOLDER, BG_PLACEHOLDER},
    {
        BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER,
        BG_PLACEHOLDER
    },
    {BG_PLACEHOLDER, BG_PLACEHOLDER, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, BG_PLACEHOLDER, BG_PLACEHOLDER},
    {BG_PLACEHOLDER, BG_PLACEHOLDER, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, BG_PLACEHOLDER, BG_PLACEHOLDER}
};

// Question Mark Icon (8x8)
const CRGB questionIcon[PANEL_SIZE][PANEL_SIZE] = {
    {BG_PLACEHOLDER, BG_PLACEHOLDER, CRGB::Blue, CRGB::Blue, CRGB::Blue, CRGB::Blue, BG_PLACEHOLDER, BG_PLACEHOLDER},
    {BG_PLACEHOLDER, CRGB::Blue, CRGB::Blue, BG_PLACEHOLDER, BG_PLACEHOLDER, CRGB::Blue, CRGB::Blue, BG_PLACEHOLDER},
    {
        BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, CRGB::Blue, CRGB::Blue,
        BG_PLACEHOLDER
    },
    {
        BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, CRGB::Blue, CRGB::Blue, CRGB::Blue, BG_PLACEHOLDER,
        BG_PLACEHOLDER
    },
    {
        BG_PLACEHOLDER, BG_PLACEHOLDER, CRGB::Blue, CRGB::Blue, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER,
        BG_PLACEHOLDER
    },
    {
        BG_PLACEHOLDER, BG_PLACEHOLDER, CRGB::Blue, CRGB::Blue, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER,
        BG_PLACEHOLDER
    },
    {
        BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER,
        BG_PLACEHOLDER
    },
    {
        BG_PLACEHOLDER, BG_PLACEHOLDER, CRGB::Blue, CRGB::Blue, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER,
        BG_PLACEHOLDER
    }
};

// Empty icon (just background)
const CRGB emptyIcon[PANEL_SIZE][PANEL_SIZE] = {
    {
        BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER,
        BG_PLACEHOLDER
    },
    {
        BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER,
        BG_PLACEHOLDER
    },
    {
        BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER,
        BG_PLACEHOLDER
    },
    {
        BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER,
        BG_PLACEHOLDER
    },
    {
        BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER,
        BG_PLACEHOLDER
    },
    {
        BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER,
        BG_PLACEHOLDER
    },
    {
        BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER,
        BG_PLACEHOLDER
    },
    {
        BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER, BG_PLACEHOLDER,
        BG_PLACEHOLDER
    }
};

// Global LEDManager instance
LEDManager ledManager;

// --- LEDManager Implementation ---

LEDManager::LEDManager() :
    leds{},
    currentBackgroundColor(CRGB::Blue),
    currentBrightness(10),
    ledsEnabled(true)
{
    // Initialize all panels to empty icons
    for (auto& currentIcon : currentIcons)
    {
        currentIcon = ICON_NONE;
    }
}

bool LEDManager::init()
{
    Serial.println("Initializing LED Manager for 6-panel cube");
    Serial.print("Total LEDs: ");
    Serial.println(NUM_LEDS);

    CFastLED::addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS)
        .setCorrection(TypicalLEDStrip);
    setBrightness(currentBrightness);
    FastLED.clear();
    FastLED.show();

    // Set default state
    setBackgroundColor(currentBackgroundColor);
    setAllIcons(ICON_NONE);

    return true;
}

// Maps x,y coordinates to LED index within a specific panel
uint16_t LEDManager::XY(uint8_t x, uint8_t y, PanelSide panel)
{
    // Basic validation
    if (x >= PANEL_SIZE || y >= PANEL_SIZE || panel >= NUM_PANELS)
    {
        return 0; // Return first LED on error
    }

    uint16_t panelOffset = panel * NUM_LEDS_PER_PANEL;
    uint16_t indexInPanel;

    if (y % 2 == 0)
    {
        // Even rows (0, 2, 4...) - data flows left to right
        indexInPanel = (y * PANEL_SIZE) + x;
    }
    else
    {
        // Odd rows (1, 3, 5...) - data flows right to left (serpentine layout)
        indexInPanel = (y * PANEL_SIZE) + (PANEL_SIZE - 1 - x);
    }

    return panelOffset + indexInPanel;
}

// Apply an icon to a specific panel
void LEDManager::applyIconToPanel(IconType icon, PanelSide panel)
{
    if (!ledsEnabled) return;

    const CRGB (*iconData)[PANEL_SIZE];

    // Select the appropriate icon data
    switch (icon)
    {
    case ICON_HEART:
        iconData = heartIcon;
        break;
    case ICON_SMILEY:
        iconData = smileyIcon;
        break;
    case ICON_ARROW:
        iconData = arrowIcon;
        break;
    case ICON_EXCLAMATION:
        iconData = exclamationIcon;
        break;
    case ICON_QUESTION:
        iconData = questionIcon;
        break;
    case ICON_NONE:
    default:
        iconData = emptyIcon;
        break;
    }

    // Apply the icon to the panel with background color
    for (int y = 0; y < PANEL_SIZE; y++)
    {
        for (int x = 0; x < PANEL_SIZE; x++)
        {
            CRGB pixelColor = iconData[y][x];
            if (pixelColor == BG_PLACEHOLDER)
            {
                leds[XY(x, y, panel)] = currentBackgroundColor;
            }
            else
            {
                leds[XY(x, y, panel)] = pixelColor;
            }
        }
    }

    // Remember the current icon for this panel
    currentIcons[panel] = icon;
}

void LEDManager::updateLEDs() const
{
    if (ledsEnabled)
    {
        FastLED.show();
    }
}

void LEDManager::setIcon(IconType icon, PanelSide panel)
{
    if (panel >= NUM_PANELS) return;

    applyIconToPanel(icon, panel);
    updateLEDs();
}

void LEDManager::setAllIcons(IconType icon)
{
    for (int panel = 0; panel < NUM_PANELS; panel++)
    {
        applyIconToPanel(icon, static_cast<PanelSide>(panel));
    }
    updateLEDs();
}

void LEDManager::setBackgroundColor(CRGB color)
{
    currentBackgroundColor = color;

    // Refresh all panels to apply the new background color
    for (int panel = 0; panel < NUM_PANELS; panel++)
    {
        applyIconToPanel(currentIcons[panel], static_cast<PanelSide>(panel));
    }
    updateLEDs();
}

void LEDManager::setBrightness(uint8_t brightness)
{
    currentBrightness = brightness;
    FastLED.setBrightness(brightness);
    updateLEDs();
}

void LEDManager::enableLEDs(bool enable)
{
    ledsEnabled = enable;

    if (!enable)
    {
        // Turn off all LEDs
        FastLED.clear();
        FastLED.show();
    }
    else
    {
        // Refresh all panels
        for (int panel = 0; panel < NUM_PANELS; panel++)
        {
            applyIconToPanel(currentIcons[panel], static_cast<PanelSide>(panel));
        }
        updateLEDs();
    }
}

CRGB LEDManager::getBackgroundColor() const
{
    return currentBackgroundColor;
}

uint8_t LEDManager::getBrightness() const
{
    return currentBrightness;
}

bool LEDManager::isEnabled() const
{
    return ledsEnabled;
}

IconType LEDManager::getCurrentIcon(PanelSide panel) const
{
    if (panel >= NUM_PANELS)
    {
        return ICON_NONE;
    }
    return currentIcons[panel];
}
