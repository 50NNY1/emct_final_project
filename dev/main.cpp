#include <lo/lo.h>
#include "OSC.h"
#include <chrono>

int main()
{
  OSC oscserver("127.0.0.1", "7400");
  oscserver.sendMonoNote(69, 1.0, 1000);
  oscserver.sendMonoNote(72, 1.0, 1000);
  int notes[2] = {69, 72};
  float velocities[2] = {1.0, 1.0};

  oscserver.sendPolyNote(notes, velocities, 1000, (sizeof(notes) / sizeof(notes[0])));

  return 0;
}
