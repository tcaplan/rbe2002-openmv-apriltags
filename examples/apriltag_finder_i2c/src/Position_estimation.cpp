#include  "Position_estimation.h"
#include "Encoders.h"

Encoder RomiEncoders;
float x = 0;
float y = 0;
float theta = 0;
unsigned long time_prev = millis();
unsigned long time_now = 0;

void Position::Init(void)
{
    time_prev = millis();
    x = 0;
    y = 0;
    theta = 0;
    x_t = 0;
    y_t = 0;
    theta_t = 0;
}

void Position::Stop(void)
{
    time_prev = millis();
    // x = 0; 
    // y = 0;
    // theta = 0;
    // x_t = 0;
    // y_t = 0;
    // theta_t = 0;
}

Position::pose_data Position::ReadPose(void)
{
    return {x,y,theta};
}

void Position::PrintPose(void)
{
    Serial.print(x);
    Serial.print('\t');
    Serial.print(y);
    Serial.print('\t');
    Serial.println(theta);
}

void Position::UpdatePose(float target_speed_left, float target_speed_right)
{
    time_now = millis();
    if(time_now - time_prev >= 50) //update every 50ms for practical reasons
    {
        //assignment
        float v_left = RomiEncoders.ReadVelocityLeft();
        float v_right = RomiEncoders.ReadVelocityRight();
        float R = -1;
        float w = -1;
        float angle = 0;
        float x_calculated = 0;
        float y_calculated = 0;

        float R_theoretical = -1;
        float w_theoretical = -1;
        float angle_theoretical = 0;
        float x_theoretical = 0;
        float y_theoretical = 0;
        
        float t = (time_now - time_prev) / 1000.0;

        // Calculated
        if(v_left == v_right) {  // drive straight
            x_calculated = x + v_left * cos(theta) * t; 
            y_calculated = y + v_left * sin(theta) * t;   
            angle = theta;
        } else if (v_left == (v_right * -1)){ // point turn
            w = (v_right - v_left) / L;
            x_calculated = x;
            y_calculated = y;
            angle = theta + w * t;
        } else { // curve
            R = L / 2 * (v_right + v_left) / (v_right - v_left);
            w = (v_right - v_left) / L;
            angle = theta + w * t;
            x_calculated = x - R * sin(theta) + R * sin(angle);
            y_calculated = y + R * cos(theta) - R * cos(angle);
        }

        // Theoretical
        if(target_speed_left == target_speed_right) {
            x_theoretical = x_t + target_speed_left * cos(theta_t) * t;
            y_theoretical = y_t + target_speed_right * sin(theta_t) * t;   
            angle_theoretical = theta_t;     
        } else if(target_speed_left == (-1 * target_speed_right)) {
            x_theoretical = x_t;
            y_calculated = y_t;
            y_theoretical = (target_speed_right - target_speed_left) / L;
            angle_theoretical = theta_t + w_theoretical * t;
        } else {
            R_theoretical = L / 2 * (target_speed_right + target_speed_left) / (target_speed_right - target_speed_left);
            w_theoretical = (target_speed_right - target_speed_left) / L;
            angle_theoretical = theta_t + w_theoretical * t;
            x_theoretical = x_t - R_theoretical * sin(theta_t) + R_theoretical * sin(angle_theoretical);
            y_theoretical = y_t + R_theoretical * cos(theta_t) - R_theoretical * cos(angle_theoretical);
        }

        x = x_calculated;
        y = y_calculated;
        theta = angle;

        x_t = x_theoretical;
        y_t = y_theoretical;
        theta_t = angle_theoretical;

        Serial.print(t);
        Serial.print("\t");
        Serial.print(time_now);
        Serial.print("\t");
        Serial.print(time_prev);
        Serial.print("\t|\t");

        Serial.print(target_speed_left);
        Serial.print("\t");
        Serial.print(target_speed_right);
        Serial.print("\t");
        Serial.print(R_theoretical);
        Serial.print("\t");
        Serial.print(angle_theoretical * 180 / PI);
        Serial.print("\t");
        Serial.print(x_theoretical);
        Serial.print("\t");
        Serial.print(y_theoretical);
        Serial.print("\t|\t");

        Serial.print(v_left);
        Serial.print("\t");
        Serial.print(v_right);
        Serial.print("\t");
        Serial.print(R);
        Serial.print("\t");
        Serial.print(angle * 180 / PI);
        Serial.print("\t");
        Serial.print(x_calculated);
        Serial.print("\t");
        Serial.println(y_calculated);

        time_prev = time_now;
    }
}

