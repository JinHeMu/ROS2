#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class TopicPublisher01 : public rclcpp::Node
{
public:
    TopicPublisher01(std::string name) : Node(name)
    {
        RCLCPP_INFO(this->get_logger(), "%s节点已经启动.", name.c_str());
        // 创建发布者
        command_publisher = this->create_publisher<std_msgs::msg::String>("command", 10);
        // 创建定时器 500ms为周期
        /*
        
        std::bind(&TopicPublisher01::timer_callback, this) 将 TopicPublisher01 类的成员函数 timer_callback 与当前对象的 this 指针绑定在一起。
        返回的结果是一个可调用对象，这个对象在被调用时会执行 this 对象的 timer_callback 成员函数。
        
        */
        timer = this->create_wall_timer(std::chrono::milliseconds(500), std::bind(&TopicPublisher01::timer_callback, this));
        
    }
private:

    void timer_callback()
    {
        // 创建消息
        std_msgs::msg::String message;
        message.data = "forward";
        // 日志打印
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        command_publisher->publish(message);
    }


    rclcpp::TimerBase::SharedPtr timer;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr command_publisher;



};


int main(int argc, char const *argv[])
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<TopicPublisher01>("topic_publisher_01");
    

    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}
