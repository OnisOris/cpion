#include "pion.h"
#include <iostream>

int main() {
  try {
    Pion pion("10.1.100.114", 8001);

    pion.arm();
    pion.takeoff();
    pion.goto_position(10, 0, 10, 0);
    std::this_thread::sleep_for(std::chrono::seconds(10));
    pion.land();
    pion.disarm();
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return 0;
}
