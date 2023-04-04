#include <lo/lo.h>
#include "OSC.h"
#include <chrono>

int main()
{
  OSC oscserver("127.0.0.1", "7400");
  oscserver.sendMonoNote(69, 1.0, 1000);
  oscserver.sendMonoNote(72, 1.0, 1000);
  std::vector<int> notes;
  notes.push_back(69);
  notes.push_back(72);

  std::vector<float> velocities;
  velocities.push_back(1.0);
  velocities.push_back(1.0);

  oscserver.sendPolyNote(notes, velocities, 1000);

  return 0;
}
