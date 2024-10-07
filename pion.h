
#include <Eigen/Dense>
#include <chrono>
#include <iostream>
#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/action/action.h>
#include <mavsdk/plugins/offboard/offboard.h>
#include <mavsdk/plugins/telemetry/telemetry.h>
#include <string>
#include <thread>
// #ifdef _WIN32
//     #define DLL_EXPORT __declspec(dllexport)
// #else
//     #define DLL_EXPORT
// #endif
class Pion {
public:
  Pion(const std::string &drone_address, int mavlink_port);
  ~Pion();

  void arm();
  void disarm();
  void takeoff();
  void land();
  void goto_position(float x, float y, float z, float yaw);
  void send_velocity(float vx, float vy, float vz, float yaw_rate);
  void reboot_drone();
  void handle_telemetry();

private:
  mavsdk::Mavsdk mavsdk;
  std::shared_ptr<mavsdk::System> system;
  std::shared_ptr<mavsdk::Action> action;
  std::shared_ptr<mavsdk::Telemetry> telemetry;
  std::shared_ptr<mavsdk::Offboard> offboard;

  mavsdk::ConnectionResult connection_result;

  std::thread telemetry_thread;
};
