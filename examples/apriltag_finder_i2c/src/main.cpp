#include <Arduino.h>
#include "Behaviors.h"

Behaviors aprilTagFollower;

void setup() {
  aprilTagFollower.Init();
}

void loop() {
  aprilTagFollower.Run();
}