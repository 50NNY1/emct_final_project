#ifndef OSC_H
#define OSC_H

#include <lo/lo.h>
#include <chrono>
#include <string>
#include <array>
#include <thread>

class OSC
{
public:
    OSC(std::string address, std::string port);
    void sendMonoNote(int note, float velocity, float duration);
    void sendPoly(int *notes, float *velocities, float duration, int size);
    void wait(int duration);

private:
    lo_address target;
};

#endif
