ROS2 basic tutorial which following the Tokyo Univ.'s lecture.

http://lab3.kuis.kyoto-u.ac.jp/~takase/ros/4dashing.pdf

#### Environment setting

```
source /opt/ros/version-name/setup.bash
```
#### Workspace structure

<details>
<summary>click to view the files' structure</summary>

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

## Topic
Genarate a package:
```
cd ~/ros2_ws/src
ros2 pkg create pubsub_topic --dependencies std_msgs rclcpp
```
Build the package:
```
cd ~/ros2_ws
colcon build --packages-select pubsub_topic
```
Execute in terminal 1:
```
. ~/ros2_ws/install/local_setup.bash
ros2 run pubsub_topic talker
```
Execute in terminal 2:
```
. ~/ros2_ws/install/local_setup.bash
ros2 run pubsub_topic listener
```
