#include "OSC.h"
#include <vector>
#include <lo/lo.h>
#include <chrono>

OSC::OSC(std::string address, std::string port)
{
    target = lo_address_new(address.c_str(), port.c_str());
}

void OSC::sendMonoNote(int note, float velocity, float duration)
{
    lo_message msg = lo_message_new();
    lo_message_add_int32(msg, note);
    lo_message_add_float(msg, velocity);
    lo_send_message(target, "/noteon", msg);
    lo_message_free(msg);
    auto start_time = std::chrono::steady_clock::now();
    while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_time).count() < duration)
        ;
    lo_message msg1 = lo_message_new();
    lo_message_add_int32(msg1, note);
    lo_message_add_float(msg1, 0.0);
    lo_send_message(target, "/noteoff", msg1);
    lo_message_free(msg1);
}

void OSC::sendPoly(std::vector<int> notes, std::vector<float> velocities, float duration)
{
    lo_message msg = lo_message_new();
    for (int i = 0; i < notes.size(); i++)
    {
        lo_message_add_int32(msg, notes[i]);
        lo_message_add_float(msg, velocities[i]);
    }

    lo_send_message(target, "/midi/chord", msg);
    auto start_time = std::chrono::steady_clock::now();
    while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_time).count() < duration)
        ;
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
    auto start_time = std::chrono::steady_clock::now();
    while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_time).count() < duration)
        ;
}