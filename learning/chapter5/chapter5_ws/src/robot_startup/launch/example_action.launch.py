from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():

    return LaunchDescription([
            Node(
                package="example_action_rclcpp",
                executable="action_robot_01",
            ),
            Node(
                package="example_action_rclcpp",
                executable="action_control_01",
            )
        ])