import launch
import launch_ros.actions
 
 
def generate_launch_description():
    return launch.LaunchDescription([
 
        launch_ros.actions.Node(
            package='pubsub_custom',
            executable='bmi_talker',
            name='talker',
            output='screen'
        ),
 
        launch_ros.actions.Node(
            package='pubsub_custom',
            executable='bmi_listener',
            name='listener',
            output='screen'
        ),
 
  ])
