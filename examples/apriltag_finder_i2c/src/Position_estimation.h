#ifndef POSITION_ESTIMATION
#define POSITION_ESTIMATION

#include <Romi32U4.h>

class Position{
    private:
        float x, y, theta;
        float x_t, y_t, theta_t;
        unsigned long time_prev, time_now;
        const float L = 142.875; //assignment // mm
        
    public:
        struct pose_data {
            float X;
            float Y;
            float THETA;
        };
        void Init(void);
        void UpdatePose(float,float);
        pose_data ReadPose(void);
        void PrintPose(void);
        void Stop(void);
};

#endif