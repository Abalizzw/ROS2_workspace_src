# First of all

ROS2 basic tutorial which following the Kyoto Univ.'s lecture.

http://lab3.kuis.kyoto-u.ac.jp/~takase/ros/4dashing.pdf

#### Debug record
[Debug](debug.md)

#### Environment setting

```
source /opt/ros/version-name/setup.bash
```
#### Workspace structure

<details>
<summary>click to view the directories' structure</summary>

````
ros2_ws/
    build/
       ...
    log/
       ...
    install/
       ...
    src/
        README.md
        build/
        install/
        log/
        package_1/
        package_2/
           ...
````
</details>

<details>
<summary>pull down exp.</summary>
<pre><code>System.out.println("Hello to see U!");
</code></pre>
</details>

#### ROS2 setup
```
cd ~/ros2_ws
colcon build
source install/local_setup.bash
```

# Contents
[Topic](#topic)  / [Message](#message) / [Service](#service) / [Action](#action) / [Component](#component) / [Parameters](#parameters) / [Launch](#launch)
---

<span id='topic'/>  

## Topic  
Genarate a package:
```
cd ~/ros2_ws/src
ros2 pkg create pubsub_topic --dependencies std_msgs rclcpp
```
Build package `pubsub_topic`:
```
cd ~/ros2_ws
colcon build --packages-select pubsub_topic
```
Execute `talker` in terminal 1:
```
. ~/ros2_ws/install/local_setup.bash
ros2 run pubsub_topic talker
```
Execute `listener` in terminal 2:
```
. ~/ros2_ws/install/local_setup.bash
ros2 run pubsub_topic listener
```
**[Back to contents](#contents)**

## Message
Workspace configration:
```
cd ~/ros2_ws
source install/local_setup.bash
```
Generate a pacakage:
```
cd src/
ros2 pkg create ros_study_types --dependencies rosidl_default_generators
```
Delete useless directories:
```
rm -rf ros_study_types/src ros_study_types/include
```
Add the following statement to the file `src/ros_study_types/msg/Human.msg`:
```
string name
uint16 height
float32 weight
```
Bulid package `ros_study_types`:
```
cd ~/ros2_ws
colcon build --packages-select ros_study_types
```
Create a new package using Unique defined type:
```
cd src
ros2 pkg create pubsub_custom --dependencies rclcpp ros_study_types
```
Bulid package `pubsub_custom`:
```
cd ~/ros2_ws
colcon build --packages-select pubsub_custom
```
Execute `talker` in terminal 1:
```
. ~/ros2_ws/install/local_setup.bash
ros2 run pubsub_custom bmi_talker
```
Execute `listener` in terminal 2:
```
. ~/ros2_ws/install/local_setup.bash
ros2 run pubsub_custom bmi_listener
```
[Back to contents](#contents)

## Service
Add the following statement to the file `src/ros_study_types/srv/Human.srv`:
```
stirng name
uint16 height
float32 weight
---
float32 bmi
```
Bulid package `ros_study_types`:
```
cd ~/ros2_ws
colcon build --packages-select ros_study_types
```
Generate a new package `service_custom`:
```
cd ~/ros2_ws
source install/local_setup.bash
cd src/
ros2 pkg create service_custom --dependencies rclcpp ros_study_types
```
Bulid package `service_custom`:
```
cd ~/ros2_ws
colcon build --packages-select service_custom
```
Execute `bmi_server` in terminal 1:
```
. ~/ros2_ws/install/local_setup.bash
ros2 run service_custom bmi_server
```
Execute `client` in termianl 2:
```
. ~/ros2_ws/install/local_setup.bash
ros2 run service_custom bmi_client ¥
bob 183 64.4
```

[Back to contents](#contents)

## Action
Create an action file in ` cd ros_study_types/action` and paste belowing contents and save as `Fibonacci.action`:
```
int32 order
---
int32[] sequence
---
int32[] sequence
```

Build the package `ros_study_types`:
```
cd ~/ros2_ws
colcon build --packages-select ros_study_types
```

Create the action package `action_costum`:
```
cd ~/ros2_ws
source install/local_setup.bash
cd src/
ros2 pkg create action_custom --dependencies rclcpp rclcpp_action ros_study_types
```

Build the package `action_costum`:
```
cd ~/ros2_ws
colcon build --packages-select action_custom
```

Execute `server` in terminal 1:
```
. ~/ros2_ws/install/local_setup.bash
ros2 run action_custom servier
```

Execute `client` in terminal 2:
```
. ~/ros2_ws/install/local_setup.bash
ros2 run action_custom client
```

[Back to contents](#contents)

## Component
Generate a new package `pubsub_component` under `ros2_ws/src`:
```
ros2 pkg create pubsub_component --dependencies rclcpp std_msgs class_loader
```
(Use existing files in this library)

Build the package `pubsub_component`:
```
cd ~/ros2_ws
colcon build --packages-select pubsub_component
```

Execute `pubsub_component-->talker` in terminal 1:
```
. ~/ros2_ws/install/local_setup.bash
ros2 run pubsub_component talker
```

Execute `pubsub_topic-->listener` in terminal 2:
```
. ~/ros2_ws/install/local_setup.bash
ros2 run pubsub_topic listener
```

You also can try execute the `listener` by using component: [Reference to this github](https://github.com/takasehideki/ros_study/commit/dd922acdb6ae273b5376f0473cfe10f546fe14e3)

[Back to contents](#contents)

## Parameters

Parameters is following the ROS2 official tutorial: [Using parameters in a class (C++, Humble)](https://docs.ros.org/en/humble/Tutorials/Beginner-Client-Libraries/Using-Parameters-In-A-Class-CPP.html)

Generate a new package `cpp_parameters` in `ros2_ws/src`:
```
ros2 pkg create --build-type ament_cmake cpp_parameters --dependencies rclcpp
```

Update `package.xml`:
```
<description>C++ parameter tutorial</description>
<maintainer email="you@email.com">Your Name</maintainer>
<license>Apache License 2.0</license>
```

Update `Cmakelist.txt` as the file provided in this library.　　

Build and run the package `cpp_parameters` in `ros2_ws`:
```
colcon build --packages-select cpp_parameters
```

Source the setup file in a new terminal under `ros2_ws` & run the node `cpp_parameters`:
```
. install/setup.bash
ros2 run cpp_parameters minimal_param_node
```

[Back to contents](#contents)

## Launch
Coming soon...  
[Back to contents](#contents)


---

