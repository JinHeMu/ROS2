import rclpy
from rclpy.node import Node


class WriterNode(Node):
    def __init__(self, name):
        super().__init__(name)
        self.get_logger().info("大家好，我是作家：%s." % name)


def main(args=None):
    rclpy.init(args=args)

    li4_node = WriterNode("li5")
    rclpy.spin(li4_node)
    rclpy.shutdown()
