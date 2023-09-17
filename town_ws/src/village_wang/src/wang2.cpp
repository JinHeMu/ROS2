#include "rclcpp/rclcpp.hpp"
//导入消息类型
#include "std_msgs/msg/string.hpp"
//导入发布者的消息接口
#include "std_msgs/msg/u_int32.hpp"

#include "village_interfaces/srv/sell_novel.hpp"
#include <queue>


using std::placeholders::_1;
using std::placeholders::_2;

class SingleDogNode : public rclcpp::Node
{
private:
    // 3，声明订阅者
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_novel;
    // m申明话题发布者
    rclcpp::Publisher<std_msgs::msg::UInt32>::SharedPtr pub_money;

    std::queue<std::string> novels_queue;

    // 声明回调组
    rclcpp::CallbackGroup::SharedPtr sell_novels_callback_group;

    // 声明服务端
    rclcpp::Service<village_interfaces::srv::SellNovel>::SharedPtr sell_server;


    // 声明参数， 书的单价

    int64_t novel_price = 1;

    /* data */
    void novel_callback(const std_msgs::msg::String::SharedPtr novels)
    {
        std_msgs::msg::UInt32 money;
        money.data = 10;
        pub_money->publish(money);


        novels_queue.push(novels->data);


        RCLCPP_INFO(this->get_logger(),"朕已阅%s.", novels->data.c_str());
    }

    void sell_novel_callback(const village_interfaces::srv::SellNovel::Request::SharedPtr request,
                            const village_interfaces::srv::SellNovel::Response::SharedPtr response)
    {
        // 判断当前书章节够不够，不够就要攒书后返回
        // 等待novel_queue 里头的书数量达到我们要买的

        
        RCLCPP_INFO(this->get_logger(),"收到买书的请求，给了%d元", request->money);

        this->get_parameter("novel_price", novel_price);


        // 计算应该返回客户端的小说数量

        unsigned int num = (int)request->money/novel_price;
        if (num > novels_queue.size())
        {
            // n等待，凑齐书
            
            RCLCPP_INFO(this->get_logger(),"书不够,书库%d, 要卖出%d", (int)novels_queue.size(), num);
        
            rclcpp::Rate rate(1);

            while (novels_queue.size() < num)
            {
                RCLCPP_INFO(this->get_logger(),"等待中，目前还差%d的小说", (int)num-(int)novels_queue.size());
            
                rate.sleep();
            
            }
            
        
        
        }

        RCLCPP_INFO(this->get_logger(),"当前书库里的书有%d,大于卖出的书的数量%d", (int)novels_queue.size(), num);

        for (int i = 0; i < (int)num; i++)
        {
            response->novels.push_back(novels_queue.front());
            novels_queue.pop();


        }
        

    
    
    }


public:
    SingleDogNode(std::string name):Node(name)
    {
        RCLCPP_INFO(this->get_logger(),"大家好我是单身狗%s.", name.c_str());

        sub_novel = this->create_subscription<std_msgs::msg::String>("sexy_girl",10,std::bind(&SingleDogNode::novel_callback,this,_1));
        //创建话题的发布者
        pub_money = this->create_publisher<std_msgs::msg::UInt32>("sexy_girl_money", 10);

        sell_novels_callback_group = this->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);

        sell_server = this->create_service<village_interfaces::srv::SellNovel>("sell_novel", 
        std::bind(&SingleDogNode::sell_novel_callback,this,_1,_2),
        rmw_qos_profile_system_default,
        sell_novels_callback_group);

        this->declare_parameter<std::int32_t>("novel_price", novel_price);


    }
};



int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    /*产生一个Wang2的节点*/
    auto node = std::make_shared<SingleDogNode>("wang2");
    /* 运行节点，并检测退出信号*/
    rclcpp::executors::MultiThreadedExecutor exector;
    exector.add_node(node);
    exector.spin();
    rclcpp::shutdown();
    return 0;
}
