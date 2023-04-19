#ifndef OSC_H
#define OSC_H

#include <lo/lo.h>
#include <chrono>
#include <string>
#include <vector>
class OSC
{
public:
    OSC(std::string *addressPort);
    void sendMonoNote(int note, float velocity, float duration);
    void sendPoly(std::vector<int> notes, std::vector<float> velocities, float duration);
    void sendMacro(std::vector<int> notes, std::vector<float> velocities);
    std::tuple<int, float, float> parseMono(std::string string);
    std::tuple<std::vector<int>, std::vector<float>, float> parsePoly(std::string string);
    std::tuple<std::vector<int>, std::vector<float>> parseMacro(std::string string);
    void test(std::string string);
    void wait(int duration);

private:
    lo_address target;
};

#endif