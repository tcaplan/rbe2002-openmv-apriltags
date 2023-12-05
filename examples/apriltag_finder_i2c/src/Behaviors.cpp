#include "Behaviors.h"
#include "Speed_controller.h"
#include "turn_controller.h"
#include "Position_estimation.h"
#include "mycamera.h"

//sensors
Romi32U4ButtonA buttonA;

//motor-speed controller
SpeedController PIController;
TurnController PDController;

int speed_distance = 0;
int speed_turn = 0;
AprilTagDatum tag;
int count = 0;
int max = 200;

MyCamera camera; 

void Behaviors::Init(void)
{
    tag.id = 10000;
    camera.Init();
    PIController.Init(&camera);
    PDController.Init(&camera);
}

void Behaviors::Stop(void)
{
    PIController.Stop();
}

void Behaviors::Run(void)
{
    int speed1 = 100;
    int speed2 = 90;
    PIController.Curved(speed1, speed2, 35);
    PIController.Curved(speed2, speed1, 35);
}