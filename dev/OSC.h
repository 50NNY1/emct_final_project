#ifndef OSC_H
#define OSC_H

#include <lo/lo.h>
#include <chrono>
#include <string>
#include <vector>
class OSC
{
public:
    OSC(std::string *addressPort, int instancenum_);
    void sendMonoNote(int note, float velocity, float duration);
    void sendPoly(std::vector<int> notes, std::vector<float> velocities, float duration);
    void sendMacro(std::unordered_map<char, int> values, std::vector<float> velocities);
    std::tuple<int, float, float> parseMono(std::string string);
    std::tuple<std::vector<int>, std::vector<float>, float> parsePoly(std::string string);
    std::tuple<std::unordered_map<char, int>, std::vector<float>> parseMacro(std::string string);
    int getNoteNumber(std::string notename);
    void test(std::string string);
    void wait(int duration);

private:
    lo_address target;
    int instancenum;
};

#endif