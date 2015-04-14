# Calculon

Calculon is an over-dramatic robot that lives in the Data News office.  Calculon is a Spark Core in the DataNews office that does some fun stuff.  Check out [NotoriousBOT Calculon integration](https://github.com/datanews/NotoriousBOT/blob/master/scripts/calculon.js) to see how the world (and Hubot) talks to Calculon.

## Software

1. Be the owner of the Spark Core.  Only one account can own a Spark Core and though it asks for a transfer for ownership, this does not work.  This means you have to be the current owner to update the code.
1. Open up the [Spark Core build dashboard](https://build.spark.io/build).
1. Select the relevant Spark Core in the **Core** section.
1. If this project has already been made, select the **Calculon** code project in the **Code** section.
1. Add libraries (this may already be done).  Adding libraries is done through the interface.
    * NeoPixels
1. Copy the code from `calculon.ino` into the **Code** editor.
1. Flash the Spark with the **Flash** icon.

## Hardware

### Chartbeat meter

This uses a string of NeoPixels to represent the Chartbeat API.

*IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input and minimize distance between Arduino and first pixel.*

Example update:

    curl https://api.spark.io/v1/devices/<CORE_ID>/chartbeat \
      -d access_token=<ACCESS_TOKEN> \
      -d params=<NUMBER_OF_USERS_FROM_CHARTBEAT>

### Ice cream party

This uses a servo to spin an ice cream cone around when its ice cream time.

Example update:

    curl https://api.spark.io/v1/devices/<CORE_ID>/icecream \
      -d access_token=<ACCESS_TOKEN>

### Camera rotator

This takes in a number of degrees to move a servo.

    curl https://api.spark.io/v1/devices/<CORE_ID>/camera \
      -d access_token=<ACCESS_TOKEN> \
      -d params=<DEGREES_TO_MOVE>
