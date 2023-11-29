#ifndef SPEED_CONTROLLER
#define SPEED_CONTROLLER

#include <Romi32U4.h>
#include "apriltag_finder.h"

class SpeedController{
    private:
        const float Kp = 0.5; //Adapt the parameters until your robot moves at the speed you command it to drive
        const float Ki = 0.1; 
        float E_left = 0; 
        float E_right = 0;
        float e_distance = 0;
        int counts = 1440; //assignment
        MyCamera* camera;

    public:
        void Init(MyCamera*);
        float RunTo(int, int); // target distance, tag size cm
        void Run(float, float); //speed left, speed right
        boolean Turn(int,int); //degrees, direction of rotation: 0->left, 1->right
        boolean Straight(int, int); //speed, duration
        boolean Curved(int,int,int); //speed left, speed right, duration
        void Stop(void);
};

#endif