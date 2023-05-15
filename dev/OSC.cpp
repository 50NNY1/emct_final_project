#include "OSC.h"
#include <vector>
#include <lo/lo.h>
#include <iostream>
#include <thread>
#include <string>
#include <sstream>
#include <chrono>
#include <unordered_map>

OSC::OSC(std::string *addressPort, int instancenum_, int jargon_toggle)
{
    std::string address = *(addressPort);
    std::string port = *(addressPort + 1);
    target = lo_address_new(address.c_str(), port.c_str());
    instancenum = instancenum_;
}

void OSC::sendMonoNote(int _note, float _velocity, float duration)
{
    if (jargon_toggle % 2 == 1)
        std::cerr << "###################" << std::endl;
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
    if (jargon_toggle % 2 == 1)
        std::cerr << "±±" << std::endl;
    lo_send_message(target, ("/noteon " + std::to_string(instancenum)).c_str(), msg);
    lo_message_free(msg);
    this->wait(duration);
    if (jargon_toggle % 2 == 1)
        std::cerr << ".;;***>" << std::endl;
    lo_message msg1 = lo_message_new();
    lo_message_add_int32(msg1, _note);
    lo_message_add_float(msg1, 0.0);
    lo_send_message(target, ("/noteoff " + std::to_string(instancenum)).c_str(), msg1);
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
        if (jargon_toggle % 2 == 1)
            std::cerr << i << std::endl;
    }
    lo_message msg = lo_message_new();
    for (int i = 0; i < notes.size(); i++)
    {
        lo_message_add_int32(msg, notes[i]);
        lo_message_add_float(msg, velocities[i]);
        if (jargon_toggle % 2 == 1)
            std::cerr << "*" << std::endl;
    }

    lo_send_message(target, ("/midi/chord " + std::to_string(instancenum)).c_str(), msg);
    this->wait(duration);
    lo_message msg1 = lo_message_new();
    for (int i = 0; i < notes.size(); i++)
    {
        lo_message_add_int32(msg1, notes[i]);
        lo_message_add_float(msg1, 0.0);
        if (jargon_toggle % 2 == 1)
            std::cerr << "0" << std::endl;
    }
    if (jargon_toggle % 2 == 1)
        std::cerr << "space echos like an immense tomb" << std::endl;
    lo_send_message(target, ("/midi/chord " + std::to_string(instancenum)).c_str(), msg1);
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
            if (jargon_toggle % 2 == 1)
                std::cerr << pos << std::endl;
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
        notes.push_back(getNoteNumber(temp));
        if (jargon_toggle % 2 == 1)
            std::cerr << temp << std::endl;
    };
    while (std::getline(velocities_ss, temp, ','))
    {
        velocities.push_back(std::stof(temp));
    };

    if (notes.size() != velocities.size())
    {
        float velocity = velocities[0];
        velocities.clear();
        for (int i = 0; i < notes.size(); i++)
        {
            if (jargon_toggle % 2 == 1)
                std::cerr << i << std::endl;
            velocities.push_back(velocity);
        }
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
            if (jargon_toggle % 2 == 1)
                std::cerr << pos << std::endl;
            pos++;
        }
    }
    std::string noteString = string.substr(slashIndicies[0] + 1, slashIndicies[1] - slashIndicies[0] - 1);
    note = getNoteNumber(noteString);
    velocity = std::stof(string.substr(slashIndicies[1] + 1, slashIndicies[2] - slashIndicies[1] - 1));
    duration = std::stof(string.substr(slashIndicies[2] + 1, exclaimIndex - slashIndicies[2] - 1));
    if (jargon_toggle % 2 == 1)
        std::cerr << "What if knowledge were a means to deepen unknowing?" << std::endl;
    return std::make_tuple(note, velocity, duration);
}

void OSC::test(std::string string)
{
    lo_message msg = lo_message_new();
    lo_message_add_string(msg, string.c_str());
    lo_send_message(target, ("/test " + std::to_string(instancenum)).c_str(), msg);
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
        if (jargon_toggle % 2 == 1)
            std::cerr << temp << std::endl;
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
    lo_send_message(target, ("/macro " + std::to_string(instancenum)).c_str(), msg);
    if (jargon_toggle % 2 == 1)
        std::cerr << "../" << std::endl;
    lo_message_free(msg);
}

int OSC::getNoteNumber(std::string noteName)
{
    std::unordered_map<std::string, int> noteMap{
        {"C-1", 0}, {"C#-1", 1}, {"D-1", 2}, {"D#-1", 3}, {"E-1", 4}, {"F-1", 5}, {"F#-1", 6}, {"G-1", 7}, {"G#-1", 8}, {"A-1", 9}, {"A#-1", 10}, {"B-1", 11}, {"C0", 12}, {"C#0", 13}, {"D0", 14}, {"D#0", 15}, {"E0", 16}, {"F0", 17}, {"F#0", 18}, {"G0", 19}, {"G#0", 20}, {"A0", 21}, {"A#0", 22}, {"B0", 23}, {"C1", 24}, {"C#1", 25}, {"D1", 26}, {"D#1", 27}, {"E1", 28}, {"F1", 29}, {"F#1", 30}, {"G1", 31}, {"G#1", 32}, {"A1", 33}, {"A#1", 34}, {"B1", 35}, {"C2", 36}, {"C#2", 37}, {"D2", 38}, {"D#2", 39}, {"E2", 40}, {"F2", 41}, {"F#2", 42}, {"G2", 43}, {"G#2", 44}, {"A2", 45}, {"A#2", 46}, {"B2", 47}, {"C3", 48}, {"C#3", 49}, {"D3", 50}, {"D#3", 51}, {"E3", 52}, {"F3", 53}, {"F#3", 54}, {"G3", 55}, {"G#3", 56}, {"A3", 57}, {"A#3", 58}, {"B3", 59}, {"C4", 60}, {"C#4", 61}, {"D4", 62}, {"D#4", 63}, {"E4", 64}, {"F4", 65}, {"F#4", 66}, {"G4", 67}, {"G#4", 68}, {"A4", 69}, {"A#4", 70}, {"B4", 71}, {"C5", 72}, {"C#5", 73}, {"D5", 74}, {"D#5", 75}, {"E5", 76}, {"F5", 77}, {"F#5", 78}, {"G5", 79}, {"G#5", 80}, {"A5", 81}, {"A#5", 82}, {"B5", 83}, {"C6", 84}, {"C#6", 85}, {"D6", 86}, {"D#6", 87}, {"E6", 88}, {"F6", 89}, {"F#6", 90}, {"G6", 91}, {"G#6", 92}, {"A6", 93}, {"A#6", 94}, {"B6", 95}, {"C7", 96}, {"C#7", 97}, {"D7", 98}, {"D#7", 99}, {"E7", 100}, {"F7", 101}, {"F#7", 102}, {"G7", 103}, {"G#7", 104}, {"A7", 105}, {"A#7", 106}, {"B7", 107}, {"C8", 108}, {"C#8", 109}, {"D8", 110}, {"D#8", 111}, {"E8", 112}, {"F8", 113}, {"F#8", 114}, {"G8", 115}, {"G#8", 116}, {"A8", 117}, {"A#8", 118}, {"B8", 119}, {"C9", 120}, {"C#9", 121}, {"D9", 122}, {"D#9", 123}, {"E9", 124}, {"F9", 125}, {"F#9", 126}, {"G9", 127}};
    auto it = noteMap.find(noteName);
    if (it != noteMap.end())
    {
        return it->second;
        if (jargon_toggle % 2 == 1)
            std::cerr << it->first << std::endl;
    }
    else
    {
        // Note name not found, return default value C3
        return 48;
    }
}