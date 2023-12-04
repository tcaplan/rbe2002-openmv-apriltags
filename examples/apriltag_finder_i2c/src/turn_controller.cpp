#include <Romi32U4.h>
#include "Encoders.h"
#include "turn_controller.h"

#define SIZE 19
#define ANGLE 45

float speeds[SIZE];
int index = 0;
bool filled = false;

void sort(float* arr, int i);

void TurnController::Init(MyCamera* c)
{
    filled = false;
    camera = c;
}

float TurnController::Process(AprilTagDatum tag)
{
  if(tag.id != 10000) {
    
    error =  tag.cx - (camera->x_max / 2);
    int e_d = error - prev_error;

    float speed = Kp * error + Kd * e_d;

    prev_error = speed;

    Serial.print(tag.cx);
    Serial.print("\t");
    Serial.print(camera->x_max / 2);
    Serial.print("\t");
    Serial.println(speed);

    return speed;
  }

   return 0;
}
