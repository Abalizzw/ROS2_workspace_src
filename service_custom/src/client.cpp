/*
 * Copyright (C) 2008, Morgan Quigley and Willow Garage, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the names of Stanford University or Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

// %Tag(FULLTEXT)%
#include "rclcpp/rclcpp.hpp"
#include "ros_study_types/srv/human.hpp"
#include <chrono>
using namespace std::chrono_literals;

int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.
   * For programmatic remappings you can use a different version of init() which takes
   * remappings directly, but for most command-line programs, passing argc and argv is
   * the easiest way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  rclcpp::init(argc, argv);

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  auto n = rclcpp::Node::make_shared("bmi_client");

  if (argc != 4)
  {
    RCLCPP_INFO(n->get_logger(), "usage: bmi_clinent [Name(str)] [Height(uint/cm)] [Weight(float/kg)]");
    return 1;
  }

  /**
   * The ServiceClient() call
   */
// %Tag(SERVICECLIENT)%
  auto client = n->create_client<ros_study_types::srv::Human>("human_info");
// %EndTag(SERVICECLIENT)%

  while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(n->get_logger(), "client interrupted while waiting for service to appear.");
      return 1;
    }
    RCLCPP_INFO(n->get_logger(), "waiting for service to appear...");
  }

  auto request = std::make_shared<ros_study_types::srv::Human::Request>();
  request->name = argv[1];
  request->height = atoi(argv[2]);
  request->weight = atof(argv[3]);

  auto response_future = client->async_send_request(request);
  if (rclcpp::spin_until_future_complete(n, response_future) ==
    rclcpp::FutureReturnCode::SUCCESS)
  {
    auto response = response_future.get();
    RCLCPP_INFO(n->get_logger(), "%s's BMI is %.2f", request->name.c_str(), response->bmi);
  }
  else
  {
    RCLCPP_ERROR(n->get_logger(), "Failed to call service human_info.");
    return 1;
  }

  rclcpp::shutdown();
  return 0;
}
// %EndTag(FULLTEXT)%
