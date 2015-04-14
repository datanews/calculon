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
Servo ice_servo;
int ice_pos = 0;
// Servo we are using is 0 to 160 degrees
Servo camera_servo;
int camera_pos = 80;
int camera_pos_min = 0;
int camera_pos_max = 150;


// Main setup task
void setup()
{
   // Register our Spark functions here to respond to web hooks
   Spark.function("chartbeat", chartbeatUpdate);
   Spark.function("icecream", icecreamTime);
   Spark.function("camera", cameraPivot);

   // Attache servos to pins
   ice_servo.attach(ICE_PIN);
   ice_servo.write(ice_pos);
   camera_servo.attach(CAMERA_PIN);
   camera_servo.write(camera_pos);

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
  // Spin the cone
  for (int i = 1; i <= 5; i++) {
    // goes from 0 degrees to 180 degrees
    // tell servo to go to position in variable 'pos'
    // waits 15ms for the servo to reach the position
    for (ice_pos = 0; ice_pos < 180; ice_pos += 10) {
      ice_servo.write(ice_pos);
      delay(15);
    }

    // goes from 180 degrees to 0 degrees
    // tell servo to go to position in variable 'pos'
    // waits 15ms for the servo to reach the position
    for (ice_pos = 180; ice_pos >= 1; ice_pos -= 10) {
      ice_servo.write(ice_pos);
      delay(15);
    }
  }
  return 1;
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


// Move camera
int cameraPivot(String command) {
  // turn the string into an integer
  int p;
  int move = command.toInt();
  int orig_pos = camera_pos;
  camera_pos = camera_pos + move;

  // Limits
  if (camera_pos < camera_pos_min) {
    camera_pos = camera_pos_min;
  }
  if (camera_pos > camera_pos_max) {
    camera_pos = camera_pos_max;
  }

  // Move slowly
  if (camera_pos > orig_pos) {
    for (p = orig_pos; p <= camera_pos; p += 1) {
      camera_servo.write(p);
      delay(10);
    }
  }
  if (camera_pos < orig_pos) {
    for (p = orig_pos; p >= camera_pos; p -= 1) {
      camera_servo.write(p);
      delay(10);
    }
  }

  return camera_pos;
}
