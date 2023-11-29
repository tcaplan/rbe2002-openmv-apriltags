#ifndef MY_CAMERA
#define MY_CAMERA

#include <Arduino.h>
#include <Wire.h>
#include <openmv.h>

class MyCamera {
    private:
        OpenMV camera2;

    public:
        void setup(void);
        uint8_t FindAprilTags(void);
        uint16_t getCenterX(void);
        uint16_t getCenterY(void);
        uint16_t getWidth(void);
        uint16_t getHeight(void);
        uint16_t getID(void);
        float getDistance(float);

        double x_max = 160; // pixels
        double y_max = 120; // pixels


};

#endif