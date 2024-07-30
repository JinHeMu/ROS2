import rclpy
from rclpy.node import Node
from sensor_msgs.msg import JointState
import threading
import time

class RotateArmNode(Node):
    def __init__(self, name):
        super().__init__(name)
        self.get_logger().info(f"node {name} init ...")

        self.pub_joint_states = self.create_publisher(JointState, "joint_states", 10)
        self.pub_rate = self.create_rate(30)

        self._init_joint_state()

        self.stop_thread = False
        self.thread_ = threading.Thread(target=self._thread_pub)
        self.thread_.start()

    def _thread_pub(self):
        last_update_time = time.time()
        while rclpy.ok() and not self.stop_thread:
            delta_time = time.time() - last_update_time
            last_update_time = time.time()
            
            # 更新位置
            self.joint_states.position[0] = 1
            self.joint_states.position[1] = 2
            
            # 更新速度
            self.joint_states.velocity = self.joint_speeds
            
            # 更新 header
            self.joint_states.header.stamp = self.get_clock().now().to_msg()
            
            # 发布关节数据
            self.pub_joint_states.publish(self.joint_states)
            self.pub_rate.sleep()

    def _init_joint_state(self):
        self.joint_speeds = [0.0, 0.0]
        self.joint_states = JointState()
        self.joint_states.header.stamp = self.get_clock().now().to_msg()
        self.joint_states.header.frame_id = ""
        self.joint_states.name = ['joint1', 'joint2']
        self.joint_states.position = [0.0, 0.0]
        self.joint_states.velocity = self.joint_speeds
        self.joint_states.effort = []

    def update_speed(self, speeds):
        self.joint_speeds = speeds

    def stop(self):
        self.stop_thread = True
        self.thread_.join()

def main(args=None):
    rclpy.init(args=args)
    node = RotateArmNode("rotate_arm")

    node.update_speed([1.0, 1.0])

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.stop()
        rclpy.shutdown()
