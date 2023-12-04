#include <Arduino.h>
#include "Behaviors.h"

Behaviors aprilTagFollower;

void setup() {
  aprilTagFollower.Init();
}

void loop() {
  // delay(1);
  aprilTagFollower.Run();
}