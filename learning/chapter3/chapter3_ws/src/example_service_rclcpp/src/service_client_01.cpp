#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

class ServiceClient01 : public rclcpp::Node
{
public:
    ServiceClient01(std::string name) : Node(name)
    {
        RCLCPP_INFO(this->get_logger(), "%s节点已经启动.", name.c_str());


        client = this->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints_srv");

    }


    void send_request(int a, int b)
    {
        RCLCPP_INFO(this->get_logger(), "计算数据%d+%d", a, b);

        // 1.等待服务端上线
        while (!client->wait_for_service(std::chrono::seconds(1)))
        {
            if (!rclcpp::ok())
            {
                RCLCPP_ERROR(this->get_logger(), "等待服务的过程中被打断...");
                return;
            }
            RCLCPP_INFO(this->get_logger(), "服务未就绪，等待一会");
        }
   
        // 2.创建请求
        auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
        request->a = a;
        request->b = b;
        // 3.发送异步请求,等待返回,返回时调用回调函数
        client->async_send_request(
            request, std::bind(&ServiceClient01::result_callback, this, 
                               std::placeholders::_1));
    }
private:

    rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr client;
    void result_callback(
        rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedFuture
        result_future) {
        auto response = result_future.get();
        RCLCPP_INFO(this->get_logger(), "计算结果：%ld", response->sum);
    }

};


int main(int argc, char const *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ServiceClient01>("service_client_01");


    node->send_request(10, 20);

    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}

