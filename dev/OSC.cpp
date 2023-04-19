#include "OSC.h"
#include <vector>
#include <lo/lo.h>
#include <thread>
#include <string>
#include <sstream>
#include <chrono>

OSC::OSC(std::string *addressPort)
{
    std::string address = *(addressPort);
    std::string port = *(addressPort + 1);
    target = lo_address_new(address.c_str(), port.c_str());
}

void OSC::sendMonoNote(int _note, float _velocity, float duration)
{
    lo_message msg = lo_message_new();
    lo_message_add_int32(msg, _note);
    float velocity;
    if (_velocity > 127)
        velocity = 127;
    else if (_velocity < 0)
        velocity = 0;
    else
        velocity = _velocity;
    lo_message_add_float(msg, velocity);
    lo_send_message(target, "/noteon", msg);
    lo_message_free(msg);
    this->wait(duration);
    // auto start_time = std::chrono::steady_clock::now();
    // while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_time).count() < _duration)
    //     ;
    lo_message msg1 = lo_message_new();
    lo_message_add_int32(msg1, _note);
    lo_message_add_float(msg1, 0.0);
    lo_send_message(target, "/noteoff", msg1);
    lo_message_free(msg1);
}

void OSC::sendPoly(std::vector<int> notes, std::vector<float> velocities, float duration)
{

    // bound test for velocity
    for (int i = 0; i < velocities.size(); i++)
    {
        if (velocities[i] > 127)
            velocities[i] = 127;
        else if (velocities[i] < 0)
            velocities[i] = 0;
        else
            velocities[i] = velocities[i];
    }
    lo_message msg = lo_message_new();
    for (int i = 0; i < notes.size(); i++)
    {
        lo_message_add_int32(msg, notes[i]);
        lo_message_add_float(msg, velocities[i]);
    }

    lo_send_message(target, "/midi/chord", msg);
    this->wait(duration);
    lo_message msg1 = lo_message_new();
    for (int i = 0; i < notes.size(); i++)
    {
        lo_message_add_int32(msg1, notes[i]);
        lo_message_add_float(msg1, 0.0);
    }
    lo_send_message(target, "/midi/chord", msg1);
    lo_message_free(msg);
    lo_message_free(msg1);
}

void OSC::wait(int duration)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(duration));
}

std::tuple<std::vector<int>, std::vector<float>, float> OSC::parsePoly(std::string string)
{
    std::vector<int> notes;
    std::vector<float> velocities;
    float duration;

    int exclaimIndex = string.find("!");
    std::vector<int> slashIndicies;
    std::size_t pos = 0;

    if (string[exclaimIndex - 1] == 'p')
    {
        while ((pos = string.find('/', pos)) != std::string::npos)
        {
            slashIndicies.push_back(pos);
            pos++;
        }
    }
    // now get strings of ints, and floats.
    std::string notes_str = string.substr(slashIndicies[0] + 1, slashIndicies[1] - slashIndicies[0] - 1);
    std::string velocities_str = string.substr(slashIndicies[1] + 1, slashIndicies[2] - slashIndicies[1] - 1);
    duration = std::stof(string.substr(slashIndicies[2] + 1, slashIndicies[3] - slashIndicies[2] - 1));
    std::stringstream notes_ss(notes_str);
    std::stringstream velocities_ss(velocities_str);
    std::string temp;
    while (std::getline(notes_ss, temp, ','))
    {
        notes.push_back(std::stoi(temp));
    }
    while (std::getline(velocities_ss, temp, ','))
    {
        velocities.push_back(std::stof(temp));
    }
    return std::make_tuple(notes, velocities, duration);
}
std::tuple<int, float, float> OSC::parseMono(std::string string)
{
    int note;
    float velocity;
    float duration;

    int exclaimIndex = string.find("!");
    std::vector<int> slashIndicies;
    std::size_t pos = 0;
    if (string[exclaimIndex - 1] == 'm')
    {
        while ((pos = string.find('/', pos)) != std::string::npos)
        {
            slashIndicies.push_back(pos);
            pos++;
        }
    }
    note = std::stoi(string.substr(slashIndicies[0] + 1, slashIndicies[1] - slashIndicies[0] - 1));
    velocity = std::stof(string.substr(slashIndicies[1] + 1, slashIndicies[2] - slashIndicies[1] - 1));
    duration = std::stof(string.substr(slashIndicies[2] + 1, exclaimIndex - slashIndicies[2] - 1));
    return std::make_tuple(note, velocity, duration);
}

void OSC::test(std::string string)
{
    lo_message msg = lo_message_new();
    lo_message_add_string(msg, string.c_str());
    lo_send_message(target, "/test", msg);
    lo_message_free(msg);
    this->wait(35);
}

std::tuple<std::vector<int>, std::vector<float>> OSC::parseMacro(std::string string)
{
    std::vector<int> values;
    std::vector<float> glideTimes;

    int exclaimIndex = string.find("!");
    std::vector<int> slashIndicies;
    std::size_t pos = 0;
    if (string[exclaimIndex - 1] == 'o')
    {
        while ((pos = string.find('/', pos)) != std::string::npos)
        {
            slashIndicies.push_back(pos);
            pos++;
        }
    }

    std::string values_str = string.substr(slashIndicies[0] + 1, slashIndicies[1] - slashIndicies[0] - 1);
    std::string glideTimes_str = string.substr(slashIndicies[1] + 1, slashIndicies[2] - slashIndicies[1] - 1);
    std::stringstream values_ss(values_str);
    std::stringstream glideTimes_ss(glideTimes_str);
    std::string temp;
    while (std::getline(values_ss, temp, ';'))
    {
        values.push_back(std::stoi(temp));
    }
    while (std::getline(glideTimes_ss, temp, ','))
    {
        glideTimes.push_back(std::stof(temp));
    }
    return std::make_tuple(values, glideTimes);
}

void OSC::sendMacro(std::vector<int> values, std::vector<float> glideTimes)
{
    lo_message msg = lo_message_new();
    lo_message_add_string(msg, "macro");
    lo_send_message(target, "/macro", msg);
    lo_message_free(msg);
}