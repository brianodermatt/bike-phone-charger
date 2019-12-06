/**
 * Use SSD1306 driver to display on the OLED
 * Set the displayPowerIntegral variable and then call displayUpdate()
 */
#include "main.h"
#include "display.h"

#include <Adafruit_SSD1306.h>
#include <splash.h>

#define DISPLAY_ADDRESS 0x3C

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/*
 * Conversion rate J to CO2
 * https://www.eecabusiness.govt.nz/tools/wood-energy-calculators/co2-emission-calculator/
 * 0.1 t CO2 / 1 GJ
 * 100 kg CO2 / 1 GJ
 * 10^5 g CO2 / 1 GJ
 * 10^5 g CO2 / 10^9 J
 * 10^-4 g CO2 / J
 */
#define G_CO2_PER_J 1e-4f


/* variables to set before displayUpdate() */
float displayPowerIntegral;
bool  displayCharging;

/* initialize the display */
void displaySetup(void) {
  echoln("setup display");
  if (!display.begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADDRESS)) {
    echoln("Error during display setup");
    for(;;);  // don't proceed
  }
  display.setTextColor(WHITE);
}

/* update power text */
void displayUpdate(void) {  
  char str[10];
  sprintf(str, "%d.%02d J used so far", (int)displayPowerIntegral, (int)(displayPowerIntegral*100)%100);
  display.clearDisplay();

  // display equivalent Joule
  long mg_co2 = displayPowerIntegral * 1000 * G_CO2_PER_J;
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print(mg_co2 > 1000 ? mg_co2/1000 : mg_co2);
  display.print(mg_co2 > 1000 ? " g CO" : " mg CO");
  display.setTextSize(1);
  display.println("2");
  
  // display power integral value
  display.setCursor(0,22);
  display.setTextSize(1);
  display.print(displayPowerIntegral, 0);
  display.print(" J ");

  // display charging text
  display.println(displayCharging ? "(charging)" : "(pause)");
  
  display.display();
}
