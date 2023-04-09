#include <lo/lo.h>
#include "OSC.h"
#include <chrono>
#include <thread>

int main()
{
  OSC oscserver("127.0.0.1", "7400");
  std::thread t1(&OSC::sendMonoNote, &oscserver, 60, 1.0, 1000);
  oscserver.wait(500);
  std::thread t2(&OSC::sendMonoNote, &oscserver, 64, 1.0, 1000);
  oscserver.wait(500);
  std::thread t3(&OSC::sendMonoNote, &oscserver, 67, 1.0, 1000);
  t1.join();
  t2.join();
  t3.join();
  std::thread t4(&OSC::sendPoly, &oscserver, std::vector<int>{60, 64, 67, 69, 72}, std::vector<float>{1.0, 1.0, 1.0, 1.0, 1.0}, 1000);
  t4.join();
  return 0;
}
