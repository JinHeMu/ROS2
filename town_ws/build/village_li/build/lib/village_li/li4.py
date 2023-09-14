import rclpy
from rclpy.node import Node
from std_msgs.msg import String,UInt32
# 导入服务接口
from village_interfaces.srv import BorrowMoney

# 导入服务接口
# 创建服务端回调函数
# 声明并创建服务端
# 编写回调函数逻辑处理请求


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

        self.borrow_server = self.create_service(BorrowMoney, "borrow_money", self.borrow_money_callback)
    #创建服务端的回调函数
    def borrow_money_callback(self,request,response):

        # request:来自客户端的请求数据
        # response:服务端的相应数据
        # 编写回调函数逻辑处理请求

        self.get_logger().info(f"收到来自:{request.name}的借钱请求,账户目前有:{self.account}")

        if request.money <= self.account * 0.1:
            response.success = True
            response.money = request.money
            self.account = self.account - request.money
            self.get_logger().info("借钱成功，借出%f,目前还有%d" % (response.money, self.account))

        else:
            response.success = False
            response.money = 0
            self.get_logger().info("对不起，没钱了，不能借你钱了！！！")
        return response


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
