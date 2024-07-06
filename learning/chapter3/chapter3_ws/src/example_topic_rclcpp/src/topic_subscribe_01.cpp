#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"




class TopicSubscribe01 : public rclcpp::Node
{

public:

    TopicSubscribe01(std::string name) : Node(name)
    {
        RCLCPP_INFO(this->get_logger(), "%s节点已经启动.", name.c_str());

        sub = this->create_subscription<std_msgs::msg::String>("command", 10, std::bind(&TopicSubscribe01::sub_callback, this, std::placeholders::_1));
    }


private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub;
    void sub_callback(const std_msgs::msg::String::SharedPtr msg)
    {
        double speed = 0.0f;
        if (msg->data == "forward")
        {
            speed = 0.2f;
        }

         RCLCPP_INFO(this->get_logger(), "收到[%s]指令，发送速度 %f", msg->data.c_str(),speed);

    }

};


int main(int argc, char const *argv[])
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<TopicSubscribe01>("topic_subscribe_01");
    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}
