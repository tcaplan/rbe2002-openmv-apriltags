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
int max = 60;

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

    AprilTagDatum temp = camera.getTag();
    if(temp.id < 10000 || count > max) {
        tag = temp;
        count = 0;
    } else {
        count++;
    }
    // Serial.print(id);
    // Serial.print("\t"); 
    // Serial.println(temp);

    // camera.printTagData();

    switch (robot_state)
    {
    case IDLE:
        if(buttonA.getSingleDebouncedRelease()){ 
            robot_state = FIND_TAG; 
            PIController.Stop();  
            PDController.Stop();           
            PIController.Init(&camera);    
            Serial.println("Entering FIND_TAG");         
        } 
        else { 
            robot_state = IDLE;
            PIController.Stop(); 
            PDController.Stop();
        }   
        break;
    
    case FIND_TAG:
        if(buttonA.getSingleDebouncedRelease()){ 
            robot_state = IDLE;
            PIController.Stop();  
            PDController.Stop();
            Serial.println("Entering IDLE");         
           
        } else if (tag.id == 4) {
            robot_state = FOLLOW_TAG;
            Serial.println("Entering FOLLOW_TAG");         
        } else {
            // Serial.println( "Looking");
            // PIController.Turn(5, 1);
            // // delay(500);
            // temp = camera.getTag();
            // if(temp.id < 10000 || count > max) {
            //     tag = temp;
            //     count = 0;
            // } else {
            //     count++;
            // }
            // delay(500);
            PIController.Stop();
            PDController.Stop();
        }
        break;
    case FOLLOW_TAG:
        if(buttonA.getSingleDebouncedRelease()){ 
            robot_state = IDLE;
            PIController.Stop();
            PDController.Stop();
            Serial.println("Entering IDLE");                      
        } else if (tag.id == 4) {
            // FOLLOW AT 20 cm, 4cm tag
            speed_distance = PIController.RunTo(20, 4, tag);
            
            PIController.Run(speed_distance, speed_distance); //speed in [[mm/s]]
            
            speed_turn = min(PDController.Process(tag), 20);
            speed_turn = max(speed_turn, -20);

            PIController.Run(speed_distance + speed_turn, speed_distance - speed_turn); //speed in [[mm/s]]

            // Serial.print(speed_distance);
            // Serial.print("\t");
            // Serial.print(speed_turn);
            // Serial.print("\t");
            // Serial.print(speed_distance+speed_turn);
            // Serial.print("\t");
            // Serial.println(speed_distance-speed_turn);
            // Serial.println("Following");
        } else {
            robot_state = FIND_TAG;
            PIController.Stop();
            PDController.Stop();
            Serial.println("Entering FIND_TAG");         
        }
        break;
    }
}