#include "rclcpp/rclcpp.hpp"
#include "pubsub_component/listener_component.hpp"

int main(int argc, char **argv)
{

  rclcpp::init(argc, argv);

  auto n = std::make_shared<pubsub_component::Listener>();

  rclcpp::spin(n);

  rclcpp::shutdown();
  return 0;
}
