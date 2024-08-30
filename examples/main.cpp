#include "/home/mvasquezr/DatosII/MPointer/library/headers/MPointer.h"
#include "/home/mvasquezr/DatosII/MPointer/library/headers/MPointerGC.h"
#include <iostream>


MPointer<int> foo() {
    MPointer<int> temp = MPointer<int>::New();
    *temp = 666;
    MPointerGC<int>::getInstance()->debug();
    return temp;
}

int main() {
    MPointer<int> mp1 = MPointer<int>::New();
    MPointer<int> mp2 = MPointer<int>::New();
    *mp1 = 100;
    *mp2 = 200;

    foo();

    MPointerGC<int>::getInstance()->debug();

    mp2 = mp1;

    MPointerGC<int>::getInstance()->debug();

    return 0;
}


