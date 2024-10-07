
#include "pion.h"
using namespace mavsdk;
using namespace std::chrono_literals;

Pion::Pion(const std::string &drone_address, int mavlink_port) {
  connection_result = mavsdk.add_any_connection("udp://" + drone_address + ":" +
                                                std::to_string(mavlink_port));
  if (connection_result != ConnectionResult::Success) {
    throw std::runtime_error("Failed to connect to drone.");
  }

  system = mavsdk.systems().at(0); // Assuming one drone connected
  action = std::make_shared<Action>(system);
  telemetry = std::make_shared<Telemetry>(system);
  offboard = std::make_shared<Offboard>(system);

  telemetry_thread = std::thread(&Pion::handle_telemetry, this);
}

Pion::~Pion() { telemetry_thread.join(); }

void Pion::arm() { action->arm(); }

void Pion::disarm() { action->disarm(); }

void Pion::takeoff() { action->takeoff(); }

void Pion::land() { action->land(); }

void Pion::goto_position(float x, float y, float z, float yaw) {
  action->goto_location(x, y, z, yaw);
}

void Pion::send_velocity(float vx, float vy, float vz, float yaw_rate) {
  Offboard::VelocityBodyYawspeed velocity{};
  velocity.forward_m_s = vx;
  velocity.right_m_s = vy;
  velocity.down_m_s = vz;
  velocity.yawspeed_deg_s = yaw_rate;

  offboard->set_velocity_body(velocity);

  if (!offboard->is_active()) {
    offboard->start();
  }
}

void Pion::reboot_drone() { action->reboot(); }

void Pion::handle_telemetry() {
  telemetry->subscribe_position([](Telemetry::Position position) {
    std::cout << "Position: (" << position.latitude_deg << ", "
              << position.longitude_deg << ", " << position.relative_altitude_m
              << ")\n";
  });

  telemetry->subscribe_battery([](Telemetry::Battery battery) {
    std::cout << "Battery: " << battery.remaining_percent * 100 << "%\n";
  });
}
