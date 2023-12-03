#include <Romi32U4.h>
#include "Encoders.h"
#include  "Speed_controller.h"
#include "Position_estimation.h"
#include "mycamera.h"

Romi32U4Motors motors;
Encoder MagneticEncoder; 
Position odometry;

void SpeedController::Init(MyCamera* c)
{
    MagneticEncoder.Init();
    odometry.Init();
    camera = c;
}

float SpeedController::RunTo(int target_distance, int tagSize, AprilTagDatum tag)
{
    if(tag.id != 10000) {
        // float e = camera->getDistance(tagSize) - target_distance;
        float e = (30.0 * 30.0) - (tag.w * tag.h);

        e_distance += e;

        float u = Kp_d*e ;//+ Ki_d*e_distance;

        return u;
    }
    return 0;
}

void SpeedController::Run(float target_velocity_left, float target_velocity_right)
{
    if(MagneticEncoder.UpdateEncoderCounts()){
        float e_left = target_velocity_left - MagneticEncoder.ReadVelocityLeft();
        float e_right = target_velocity_right - MagneticEncoder.ReadVelocityRight();

        E_left += e_left;
        E_right += e_right;

        float u_left = Kp*e_left + Ki*E_left;
        float u_right = Kp*e_right + Ki*E_right;

        motors.setEfforts(u_left,u_right);
        odometry.UpdatePose(target_velocity_left,target_velocity_right); //this is where your newly programmed function is/will be called
    }
}

boolean SpeedController::Turn(int degree, int direction)
{
    motors.setEfforts(0, 0);
    float w_b = 142.875; // mm
    float w_d = 70; // mm
    int turns = degree / 360.0 * w_b / w_d * counts; //assignment 1: convert degree into counts
    int count_turn = MagneticEncoder.ReadEncoderCountLeft();

    while(abs(abs(count_turn) - abs(MagneticEncoder.ReadEncoderCountLeft())) <= turns)
    {
        if(!direction) Run(50,-50);
        else Run(-50,50);
    }
    motors.setEfforts(0, 0);
    return 1;
}

boolean SpeedController::Straight(int target_velocity, int time) //in mm/s and s
{
    motors.setEfforts(0, 0);
    unsigned long now = millis();

    while ((unsigned long)(millis() - now) <= time*1000){
        Run(target_velocity,target_velocity);
    }
    motors.setEfforts(0, 0);
    return 1;
}

boolean SpeedController::Curved(int target_velocity_left, int target_velocity_right, int time) //in mm/s and s
{
    motors.setEfforts(0, 0);
    
    unsigned long now = millis();

    while ((unsigned long)(millis() - now) <= time*1000){
        Run(target_velocity_left,target_velocity_right);
    }
    motors.setEfforts(0, 0);
    return 1;
}

void SpeedController::Stop()
{
    motors.setEfforts(0,0);
    odometry.Stop();
    e_distance = 0;
}