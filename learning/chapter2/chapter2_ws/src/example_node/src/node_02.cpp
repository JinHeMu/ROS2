#include "rclcpp/rclcpp.hpp"



class Node_02 : public rclcpp::Node
{
public:
    Node_02(std::string name):Node(name)
    {
        RCLCPP_INFO(this->get_logger(), "大家好我是%s.",name.c_str());
    }

private:

};






int main(int argc, char const *argv[])
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<Node_02>("node_02");

    rclcpp::spin(node);
    rclcpp::shutdown();

    /* code */
    return 0;
}
