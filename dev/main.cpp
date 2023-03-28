#include <lo/lo.h>

int main()
{
  lo_address target = lo_address_new("127.0.0.1", "9000");
  // Create an OSC message to send a sequence of notes
  lo_message msg = lo_message_new();
  // Add the note data to the OSC message
  lo_message_add_int32(msg, 60);           // MIDI note number for middle C
  lo_message_add_float(msg, 0.5);          // note on velocity (0.0 - 1.0)
  lo_send_message(target, "/noteon", msg); // send the OSC message with the "/noteon" address

  // Add another note to the OSC message
  lo_message_add_int32(msg, 64);           // MIDI note number for E
  lo_message_add_float(msg, 0.8);          // note on velocity (0.0 - 1.0)
  lo_send_message(target, "/noteon", msg); // send the OSC message with the "/noteon" address

  // Free the OSC message and OSC address
  lo_message_free(msg);
  lo_address_free(target);
  return 0;
}
