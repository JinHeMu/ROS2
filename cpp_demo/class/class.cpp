#include <iostream>
#include <functional>




class parent {
public:
    void print() {
        std::cout << "parent" << std::endl;
    }


    int create(int x, int y) {
        return x + y;
    }


};




class child : public parent {
public:

    int c;

    void printc() {
        c =
        c = this->create(1, 2);
        std::cout << c << std::endl;
    }


};

int main() {
    child c;
    c.print();
    c.printc();



    return 0;
}
