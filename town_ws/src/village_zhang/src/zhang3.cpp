#include "rclcpp/rclcpp.hpp"
#include "village_interfaces/srv/sell_novel.hpp"

// 提前声明的占位符，留着创建客户端的时候用
using std::placeholders::_1;

/*
    创建一个类节点，名字叫做PoorManNode,继承自Node.
    写麻了，到时候还要给新生做培训，狠狠装逼，看看有没有妹妹能看上我
*/
class PoorManNode : public rclcpp::Node
{

public:
    /* 构造函数 */
    PoorManNode(std::string name) : Node(name)
    {
        // 打印一句自我介绍
        RCLCPP_INFO(this->get_logger(), "大家好，我是得了穷病的张三.");

        // 声明和创建
        novel_client = this->create_client<village_interfaces::srv::SellNovel>("sell_novel");
    }

    // 5.编写发送请求逻辑
    void buy_novels()
    {
        RCLCPP_INFO(this->get_logger(),"准备买小说了捏");
        // 1.等待客户端上线
        while (!novel_client->wait_for_service(std::chrono::seconds(1)))
        {
            RCLCPP_INFO(this->get_logger(),"等待服务端上线");
        }
        
        // 2.构造请求数据
        auto request = std::make_shared<village_interfaces::srv::SellNovel_Request>();
        request-> money = 5;
        novel_client->async_send_request(request, std::bind(&PoorManNode::novels_callback,this,_1));


        // 3.发送异步请求
    }


private:
    rclcpp::Client<village_interfaces::srv::SellNovel>::SharedPtr novel_client;

    // 接受小说的回调函数
    void novels_callback(rclcpp::Client<village_interfaces::srv::SellNovel>::SharedFuture response)
    {
        auto result = response.get();
        RCLCPP_INFO(this->get_logger(),"收到了%d的小说,现在开始按照章节读", (int)(result->novels.size()));

        for(std::string novel:result->novels)
        {
            RCLCPP_INFO(this->get_logger(), "收到的小说: %s", novel.c_str());
        }
        
        RCLCPP_INFO(this->get_logger(), "小说读完了，好刺激，价格优惠");
    }


};

/*主函数*/
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    /*产生一个Zhang3的节点*/
    auto node = std::make_shared<PoorManNode>("zhang3");

    node->buy_novels();

    /* 运行节点，并检测rclcpp状态*/
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
