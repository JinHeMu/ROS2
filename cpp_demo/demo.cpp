#include <iostream>

class Entity
{
public:
    float a,b,c;
    Entity() : a(11), b(12), c(10)
    {

    }
 private:
};


int main(int argc, char const *argv[])
{
    Entity Entity;
    std::cout <<Entity.a <<Entity.b <<Entity.c << std::endl;
    return 0;
}
