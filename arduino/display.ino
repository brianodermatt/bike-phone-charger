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
  // display power integral value
  display.setCursor(0,0);
  display.setTextSize(2);
  display.print(displayPowerIntegral);
  display.println(" J");

  // display charging text
  display.setTextSize(1);
  display.setCursor(0,20);
  display.println(displayCharging ? "(charging)" : "(pause)");
  
  display.display();
}
