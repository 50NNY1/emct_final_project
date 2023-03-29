#include <lo/lo.h>
#include <chrono>

int main()
{
  lo_address target = lo_address_new("127.0.0.1", "7400");
  // Create an OSC message to send a sequence of notes
  lo_message msg = lo_message_new();
  lo_message msg2 = lo_message_new();
  lo_message msg3 = lo_message_new();
  // Add the note data to the OSC message
  auto start_time = std::chrono::steady_clock::now();
  lo_message_add_int32(msg, 60);  // MIDI note number for middle C
  lo_message_add_float(msg, 0.5); // note on velocity (0.0 - 1.0)

  lo_send_message(target, "/noteon", msg); // send the OSC message with the "/noteon" address
  bool run_at_1_sec = false;
  while (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start_time).count() < 2)
  {
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_time).count();
    // Check if we have elapsed 1.5 seconds
    if (!run_at_1_sec && elapsed_time >= 1000)
    {
      // Execute code to run at 1.5 seconds
      // ...
      lo_message_add_int32(msg2, 67);
      lo_message_add_float(msg2, 0.5);
      lo_send_message(target, "/noteon", msg2);
      run_at_1_sec = true;
    }
  }
  lo_message msg1 = lo_message_new();
  lo_message_add_int32(msg1, 60);
  lo_message_add_float(msg1, 0.0);
  lo_send_message(target, "/noteoff", msg1);

  lo_message_add_int32(msg3, 67);
  lo_message_add_float(msg3, 0.0);
  lo_send_message(target, "/noteoff", msg3);
  // Free the OSC message and OSC address
  lo_message_free(msg);
  lo_message_free(msg1);
  lo_message_free(msg2);
  lo_message_free(msg3);
  lo_address_free(target);
  return 0;
}
