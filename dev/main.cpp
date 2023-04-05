#include <lo/lo.h>
#include "OSC.h"
#include <chrono>
#include <thread>

int main()
{
  OSC oscserver("127.0.0.1", "7400");

  std::thread t0(&OSC::sendMonoNote, &oscserver, 60, 1.0, 1000);
  std::thread t1([&]()
                 { oscserver.sendMonoNote(69, 1.0, 1000); });
  t0.join();
  t1.join();
  return 0;
}
