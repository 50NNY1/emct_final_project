#include <lo/lo.h>
#include "OSC.h"
#include <chrono>
#include <thread>

int main()
{
  OSC oscserver("127.0.0.1", "7400");
  std::thread t1(&OSC::sendMonoNote, &oscserver, 60, 1.0, 1000);
  std::thread t2(&OSC::sendMonoNote, &oscserver, 64, 1.0, 1000);
  t1.join();
  t2.join();
  return 0;
}
