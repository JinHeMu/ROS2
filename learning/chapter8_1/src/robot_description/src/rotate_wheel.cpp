#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "std_msgs/msg/string.hpp"

class RotateWheelNode : public rclcpp::Node
{
public:
    RotateWheelNode(std::string name) : Node(name), joint_speeds_({0.0, 0.0})
    {
        RCLCPP_INFO(this->get_logger(), "%s节点已经启动.", name.c_str());

        pub_joint_states_ = this->create_publisher<sensor_msgs::msg::JointState>("joint_states", 10);

        timer_ = this->create_wall_timer(std::chrono::milliseconds(200), std::bind(&RotateWheelNode::timer_callback, this));

        joint_states_init();

    }

    void update_speed(const std::vector<double> &speeds)
    {
        joint_speeds_ = speeds;
    }



private:


    void joint_states_init()
    {
        joint_states_.header.stamp = this->get_clock()->now();
        joint_states_.name = {"left_wheel_joint", "right_wheel_joint"};
        joint_states_.position = {0.0, 0.0};
        joint_states_.velocity = joint_speeds_;
        joint_states_.effort = {0.0, 0.0};
    }


    void timer_callback()
    {

        // 更新位置
        joint_states_.position[0] += 0.2 * joint_states_.velocity[0];
        joint_states_.position[1] += 0.2 * joint_states_.velocity[1];
        // 更新速度
        joint_states_.velocity = joint_speeds_;
        // 更新 header
        joint_states_.header.stamp = this->get_clock()->now();

        // 发布关节数据
        pub_joint_states_->publish(joint_states_);
        
    }

    rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr pub_joint_states_;

    rclcpp::TimerBase::SharedPtr timer_;

    sensor_msgs::msg::JointState joint_states_;

    std::vector<double> joint_speeds_;

};







int main(int argc, char **argv)
{
    /* 初始化rclcpp  */
    rclcpp::init(argc, argv);
    /*产生一个节点*/
    auto node = std::make_shared<RotateWheelNode>("rotate_robot_wheel");

    node->update_speed({1.0, -1.0});

    /* 运行节点，并检测退出信号 Ctrl+C*/
    rclcpp::spin(node);
    /* 停止运行 */
    rclcpp::shutdown();
    return 0;
}