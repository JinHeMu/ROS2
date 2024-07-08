#include <iostream>
#include <functional>

class TopicSubscribe01 {
public:
    void sub_callback(int x, int y) {

        std::cout << "Callback called with value: " << x << "," << y << std::endl;
    }
};

int main() {
    TopicSubscribe01 obj;
    // 使用 std::bind 绑定成员函数和对象指针/
    auto bound_func = std::bind(&TopicSubscribe01::sub_callback, &obj, std::placeholders::_1, std::placeholders::_2);

    // 调用绑定的函数
    bound_func(1,2);  // 输出: Callback called with value: 42

    return 0;
}
