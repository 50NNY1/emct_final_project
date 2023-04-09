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
    void sendPoly(std::vector<int> notes, std::vector<float> velocities, float duration);
    void wait(int duration);

private:
    lo_address target;
};

#endif
