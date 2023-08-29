import rclpy
from rclpy.node import Node


def main(args=None):
    rclpy.init(args=args)
    li4_node = Node("li4")
    li4_node.get_logger().info("大家好我是李四")
    rclpy.spin(li4_node)
    rclpy.shutdown()
