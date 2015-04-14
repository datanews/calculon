// Main code for Calculon.  Mostly this just responds to
// web hooks.

// Includes
#include "application.h"
#include "neopixel/neopixel.h"
//#include "spark_disable_wlan.h" (for faster local debugging only)


// Top-level config
#define PIXEL_COUNT 60
#define PIXEL_PIN D2
#define PIXEL_TYPE WS2812B
#define ICE_PIN A0
#define CAMERA_PIN A1


// Create strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

// Servo setup (Servo library is built in to spark)
int pos = 0;
Servo myservo;


// Main setup task
void setup()
{
   // Register our Spark functions here to respond to web hooks
   Spark.function("chartbeat", chartbeatUpdate);
   Spark.function("icecream", icecreamTime);

   // attaches the servo on the A0 pin to the servo object
   myservo.attach(ICE_PIN);

   // Initialize all strip pixels to 'off'
  strip.begin();
  strip.show();
}


// Main loop task
void loop()
{
  // nothing to do here
  // all commands are triggered with a web hook
}


// Web hook handler for ice cream
int icecreamTime(String command) {
  spinCone();
  return 1;
}

// This function spins an ice cream cone on a servo
void spinCone() {
  for (int i = 1; i <= 5; i++) {
    // goes from 0 degrees to 180 degrees
    // tell servo to go to position in variable 'pos'
    // waits 15ms for the servo to reach the position
    for (pos = 0; pos < 180; pos += 10) {
      myservo.write(pos);
      delay(15);
    }

    // goes from 180 degrees to 0 degrees
    // tell servo to go to position in variable 'pos'
    // waits 15ms for the servo to reach the position
    for (pos = 180; pos>=1; pos-=10) {
      myservo.write(pos);
      delay(15);
    }
  }
}


// Web hook to
int chartbeatUpdate(String command) {
  // turn the string into an integer
  int pixels = command.toInt();

  // clear the strip
  stripColor(0, 0, 0);

  // Set strip
  showPixels(pixels);
  return pixels;
}

// Show a specific number of pixels on the led strip
void showPixels(int pixels_to_light) {
  // Check to make sure strip're not trying to light more pixels than we have
  if (pixels_to_light > strip.numPixels()) {
    pixels_to_light = strip.numPixels();
  }

  // hard code the colors to use (for now)
  uint32_t c;
  uint32_t color1 = strip.Color(255, 34, 9 );  // deep orange
  uint32_t color2 = strip.Color(192, 76, 0);   // pretty yellow
  uint32_t color3 = strip.Color(0, 170, 0);    // excellent green

  // set them up
  for (uint16_t i=0; i < pixels_to_light; i++) {
    if (i < 30) {
      c = color1;
    }
    else if (i < 50) {
      c = color2;
    }
    else if (i < 60) {
      c = color3;
    }

    strip.setPixelColor(i, c);
  }

  // Light them up
  strip.show();
}

// Set whole strip a single color
void stripColor(int red, int green, int blue) {
  uint32_t c = strip.Color(red, green, blue);

  for (uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
}
