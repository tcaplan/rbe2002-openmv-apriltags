#ifndef TURN_CONTROLLER
#define TURN_CONTROLLER

#include <Romi32U4.h>
#include "apriltag_finder.h"

class TurnController{
    private:
        const float Kp = 2; //Adapt parameters Kp and Kd until your robot consistently drives along a wall
        const float Kd = 1;
        float error = 0;
        float prev_error = 0;
        MyCamera* camera;

    public:
        void Init(MyCamera*);
        float Process();
};

#endif