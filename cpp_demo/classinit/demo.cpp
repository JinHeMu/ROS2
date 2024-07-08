#include <iostream>

class Test
{
public:
    Test(std::string name)
    {
        std::cout << "Test" <<  name << std::endl;
    }
};

class Date : public Test
{
public:
// 构造函数
	Date(std::string name)  : Test(name)    // 初始化列表
	{}
 
	int _month = 3;
	int _day = 31;

    
private:

};


int main(int argc, char const *argv[])
{
    /* code */
    Date d("2019");
    return 0;
}
