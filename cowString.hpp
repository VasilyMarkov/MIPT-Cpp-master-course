#ifndef COW_STRING_H
#define COW_STRING_H
#include <iostream>


class CowString final {
public:
    CowString() {std::cout << "CowString()" << std::endl;}
    ~CowString() {std::cout << "~CowString()" << std::endl;}
private:

};

#endif //COW_STRING_H