#include "OSC.h"
#include <vector>
#include <lo/lo.h>
#include <iostream>
#include <thread>
#include <string>
#include <sstream>
#include <chrono>
#include <unordered_map>

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

std::tuple<std::unordered_map<char, int>, std::vector<float>> OSC::parseMacro(std::string string)
{
    // instantiate map with default values
    std::unordered_map<char, int> macros_map{
        {'A', 0},
        {'B', 0},
        {'C', 0},
        {'D', 0},
        {'E', 0},
        {'F', 0},
        {'G', 0},
        {'H', 0}};

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
    std::string macros_str = string.substr(slashIndicies[0] + 1, slashIndicies[1] - slashIndicies[0] - 1);
    std::string glideTimes_str = string.substr(slashIndicies[1] + 1, slashIndicies[2] - slashIndicies[1] - 1);
    std::stringstream macros_ss(macros_str);
    std::stringstream glideTimes_ss(glideTimes_str);
    std::string temp;

    macros_str.erase(std::remove(macros_str.begin(), macros_str.end(), ';'), macros_str.end());
    macros_str.erase(std::remove(macros_str.begin(), macros_str.end(), ','), macros_str.end());

    while (std::getline(macros_ss, temp, ' '))
    {
        char letter = temp[0];
        int value;
        try
        {
            value = std::stoi(temp.substr(2));
            // use the value here
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Invalid argument: " << e.what() << ", the invalid argument was: " << temp.substr(1) << '\n';
        }
        catch (const std::out_of_range &e)
        {
            std::cerr << "Out of range: " << e.what() << '\n';
        }
        macros_map[letter] = value;
    }

    while (std::getline(glideTimes_ss, temp, ','))
    {
        glideTimes.push_back(std::stof(temp));
    }
    return std::make_tuple(macros_map, glideTimes);
}

void OSC::sendMacro(std::unordered_map<char, int> values, std::vector<float> glideTimes)
{
    lo_message msg = lo_message_new();
    lo_message_add_int32(msg, values['A']);
    lo_message_add_int32(msg, values['B']);
    lo_message_add_int32(msg, values['C']);
    lo_message_add_int32(msg, values['D']);
    lo_message_add_int32(msg, values['E']);
    lo_message_add_int32(msg, values['F']);
    lo_message_add_int32(msg, values['G']);
    lo_message_add_int32(msg, values['H']);
    lo_message_add_float(msg, glideTimes[0]);
    lo_message_add_float(msg, glideTimes[1]);
    lo_message_add_float(msg, glideTimes[2]);
    lo_message_add_float(msg, glideTimes[3]);
    lo_message_add_float(msg, glideTimes[4]);
    lo_message_add_float(msg, glideTimes[5]);
    lo_message_add_float(msg, glideTimes[6]);
    lo_message_add_float(msg, glideTimes[7]);
    lo_send_message(target, "/macro", msg);
    lo_message_free(msg);
    this->wait(35);
}