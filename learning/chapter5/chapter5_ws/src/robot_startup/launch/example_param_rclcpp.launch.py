from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():

    return LaunchDescription([
            Node(
                package="example_parpameters_rclcpp",
                namespace="rclcpp",
                executable="parameters_basic",
                parameters=[{'rcl_log_level': 10}]
            )
        ])