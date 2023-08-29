import rclpy
from rclpy.node import Node
from std_msgs.msg import String,UInt32


class WriterNode(Node):
    def __init__(self, name):
        super().__init__(name)
        self.get_logger().info("大家好，我是作家：%s." % name)
        self.pub_novel = self.create_publisher(String, "sexy_girl", 10)

        self.count = 0
        self.timer_period = 5
        self.timer = self.create_timer(self.timer_period, self.timer_callback)


        self.account = 80
        self.sub_money = self.create_subscription(UInt32, "sexy_girl_money", self.recv_money_callback, 10)

    def timer_callback(self):
        msg = String()
        msg.data  = "第%d回 第%d节" % (self.count, self.count)
        self.pub_novel.publish(msg)
        self.get_logger().info("发布了一个章节的小说，内容是：%s" % msg.data)
        self.count += 1

    def recv_money_callback(self,money):
        self.account += money.data
        self.get_logger().info("收到了：%d的稿费，现在账户里有%d" % (money.data, self.account))

def main(args=None):
    rclpy.init(args=args)

    li4_node = WriterNode("li5")
    rclpy.spin(li4_node)
    rclpy.shutdown()
