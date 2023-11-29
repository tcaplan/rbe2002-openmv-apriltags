#include "Behaviors.h"
#include "Speed_controller.h"
#include "turn_controller.h"
#include "Position_estimation.h"
#include "apriltag_finder.h"

//sensors
Romi32U4ButtonA buttonA;

//motor-speed controller
SpeedController PIController;
TurnController PDController;

MyCamera camera; 

void Behaviors::Init(void)
{
    camera.setup();
    PIController.Init(&camera);
    PDController.Init(&camera);
}

void Behaviors::Stop(void)
{
    PIController.Stop();
}

void Behaviors::Run(void)
{
    switch (robot_state)
    {
    case IDLE:
        if(buttonA.getSingleDebouncedRelease()){ 
            robot_state = FIND_TAG; 
            PIController.Stop();             
            PIController.Init(&camera);             
        } 
        else { 
            robot_state = IDLE;
            PIController.Stop(); 
        }   
        break;
    
    case FIND_TAG:
        if(buttonA.getSingleDebouncedRelease()){ 
            robot_state = IDLE;
            PIController.Stop();             
        } else if (camera.FindAprilTags() > 0 && camera.getID() == 4) {
            robot_state = FOLLOW_TAG;
        } else {
            PIController.Turn(10, 1);
            PIController.Stop();
        }
        break;
    case FOLLOW_TAG:
        if(buttonA.getSingleDebouncedRelease()){ 
            robot_state = IDLE;
            PIController.Stop();             
        } else if (camera.FindAprilTags() > 0 && camera.getID() == 4) {
            // FOLLOW AT 20 cm, 4cm tag
            int speed_distance = PIController.RunTo(20, 4);
            
            int speed_turn = PDController.Process();

            PIController.Run(speed_distance + speed_turn, speed_distance - speed_turn); //speed in [[mm/s]]

        } else {
            robot_state = FIND_TAG;
            PIController.Stop();
        }
        break;
    }
}