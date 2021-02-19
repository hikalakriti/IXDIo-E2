// Adafruit IO Digital Input Example
// Tutorial Link: https://learn.adafruit.com/adafruit-io-basics-digital-input
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
// Sensor code referenced from https://www.makerguides.com/hc-sr04-arduino-tutorial/ Written by  Benne de Bakker 
#include "config.h"
#include <NewPing.h>


#define TRIGGER_PIN  14  // Feather pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     12  // Feather pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

int duration;
int distance;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


AdafruitIO_Feed *sensor = io.feed("sensor");

void setup(){

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
      
    Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // set up a message handler for the 'digital' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.

  //change to your feed name you created in Adafruit IO
  //sensor->onMessage(handleMessage); //New!

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

  //change to your feed name you created in Adafruit IO
  sensor->get(); //New!

}


void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  int getData = sonar.ping_cm ();

  delay(500);
   // Serial.print("Ping: ");
  //Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  //Serial.println("cm");
  int distance = sonar.ping_cm();// store the distance value in "distance" variable
  if(distance <=30 && distance >0){             // if distance is less than 12, do somethings. For example here just print "very close"
    
int showVal =  distance;

Serial.println(showVal);
  sensor->save(showVal);
  }
  
  

}
