#include <memory>
#include <iostream>

struct feedback
{
    int progress;
};


int main(int argc, char const *argv[])
{
    std::shared_ptr<const feedback> feedback_ptr = std::make_shared<const feedback>(feedback{42});
    std::cout << "Progress: " << feedback_ptr->progress << std::endl;
    return 0;
}



