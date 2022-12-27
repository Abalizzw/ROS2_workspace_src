#include "rclcpp/rclcpp.hpp"
#include "ros_study_types/msg/human.hpp"
 
#include <iostream>
#include <chrono>
using namespace std::chrono_literals;
 
int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
 
  auto n = rclcpp::Node::make_shared("bmi_talker");
 
  auto chatter_pub = n->create_publisher<ros_study_types::msg::Human>("chatter", 1000);
 
  rclcpp::WallRate loop_rate(100ms);
 
  auto count = 0;
  while (rclcpp::ok())
  {
    ros_study_types::msg::Human msg;
/*
    std::cout << "Enter Name [str]: " << std::endl;
    std::cin >> msg.name;
    std::cout << "Enter Height [int/cm]: " << std::endl;
    std::cin >> msg.height;
    std::cout << "Enter Weight [float/kg]: " << std::endl;
    std::cin >> msg.weight;
*/
    msg.name="Taro";
    msg.height=100+count;
    msg.weight=100.0;
 
    if(msg.height >= 200){
      msg.height=msg.height-100;
      msg.weight=msg.weight+0.1;
    }
 
    RCLCPP_INFO(n->get_logger(), "[%02d] name: %s height: %d weight: %.2f",
      count, msg.name.c_str(), msg.height, msg.weight);
 
    chatter_pub->publish(msg);
 
    rclcpp::spin_some(n);
 
    loop_rate.sleep();
 
    ++count;
  }
 
  rclcpp::shutdown();
  return 0;
}
