#ifndef OSC_H
#define OSC_H

#include <lo/lo.h>
#include <chrono>
#include <string>
#include <vector>
class OSC
{
public:
    OSC(std::string address, std::string port);
    void sendMonoNote(int note, float velocity, float duration);
    void sendPoly(std::vector<int> notes, std::vector<float> velocities, float duration);
    std::tuple<int, float, float> parseMono(std::string string);
    void test();
    void wait(int duration);

private:
    lo_address target;
};

#endif