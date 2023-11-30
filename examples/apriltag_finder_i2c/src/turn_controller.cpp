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
    
    error = (camera->x_max / 2) - tag.cx;
    int e_d = error - prev_error;

    float speed = Kp * error + Kd * e_d;

    prev_error = speed;

    if(!filled) {
      index = 0;
      for(int i = 0; i < SIZE; i++) {
        speeds[i] = speed;
      }
    } else {
      index++;
      if(index >= SIZE) index = 0;
    }

    speeds[index] = speed;
    
    sort(speeds, index);

    index++;
    if(index >= SIZE) index = 0;
    


    // Serial.print(" [");
    // for(int i = 0; i < SIZE; i++) {
    //   Serial.print(speeds[i]);
    //   if(i != SIZE - 1) {
    //     Serial.print(", ");
    //   }
    // }
    // Serial.print(" ]\t");
    //   Serial.print("\tDE ");
    // Serial.print(speeds[SIZE/2]);
    return speeds[SIZE/2];
  }
   return 0;
}


void sort(float* arr, int i) {

  bool shiftedDown = false;
  int j = i;
  while(j > 0 && arr[j-1] > arr[j]) {
    float temp = arr[j-1];
    arr[j-1] = arr[j];
    arr[j] = temp;
    j--;
    shiftedDown = true;
  }
  if(!shiftedDown) {
    j = i;
    while(j < 5 && arr[j+1] < arr[j]) {
      float temp = arr[j+1];
      arr[j+1] = arr[j];
      arr[j] = temp;
    }
  }
}