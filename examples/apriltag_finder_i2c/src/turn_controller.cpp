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

void TurnController::Stop() {
  error_acc = 0;
  prev_error = 0;
}

float TurnController::Process(AprilTagDatum tag)
{
  if(tag.id != 10000) {
    
    error =  tag.cx - (camera->x_max / 2);
    
    error_acc += error;

    float error_d = prev_error - error;

    float error_i = min(Ki * error_acc, 10);

    float speed = Kp * error + error_i + Kd * error_d;

    prev_error = speed;

    return speed;
  }

   return 0;
}
