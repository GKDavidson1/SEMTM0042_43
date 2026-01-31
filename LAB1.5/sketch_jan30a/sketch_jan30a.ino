#include "encoders.h"
#include "Motors.h"

Motors_c motors;
unsigned long speed_est_ts; // timestamp for speed estimation
#define SPEED_EST_MS 10     // estimate speed every 10ms




// This will store the previous count of pulses from encoder 0
// To estimate speed, we will need to know the difference in
// encoder counts over time.
long last_e0;

// Let's store wheel speed as a global float
float speed_e0;

void setup() {
  setupEncoder0();
  setupEncoder1();

  // This takes the initial count from encoder 0
  // and saves it as the "last" (previous) count
  last_e0 = count_e0;

  // Assuming we start with motors off.
  speed_e0 = 0.0;

  // Capture the time the robot has started, so
  // that we can then know when 20ms has elapsed.
  speed_est_ts = millis();
}

void loop() {
  motors.setPWM(35, 35);
  // Create an if() block here that uses the above
  // speed_est_ts and SPEED_EST_MS variables to
  // only conduct a speed estimate every 10ms
  unsigned long elapsed_time = millis() - speed_est_ts;
  if ( elapsed_time >= SPEED_EST_MS) {
    Serial.println(elapsed_time);
    // Work out the difference in encoder counts
    long count_difference = last_e0 - count_e0;

    // Save the current count as the last count
    // for the next time we do this (10ms in the
    // future).
    last_e0 = count_e0;

    // Take into account time in your measurement.
    // This operation may not happen at exactly
    // 20ms.
    // Remember to typecast into float if you are
    // dividing.  A division on a long will lose
    // any numbers after the decimal place.
    // ...
    speed_e0 = float(count_difference / elapsed_time);

    // Report the result, so that it can be viewed
    // on the Serial Plotter.
        Serial.println( speed_e0 * 10.0, 4 );

    speed_est_ts = millis();
  }

}
