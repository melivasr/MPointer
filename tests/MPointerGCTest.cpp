#include <gtest/gtest.h>
#include "../library/headers/MPointer.h"
#include "../library/headers/MPointerGC.h"

TEST(MPointerGCTest, InstanceManagement) {
    MPointer<int> ptr1 = MPointer<int>::New();
    MPointer<int> ptr2 = MPointer<int>::New();

    *ptr1 = 200;

    EXPECT_NE(ptr1.getId(), ptr2.getId());

    MPointerGC<int>::getInstance()->debug();
}

TEST(MPointerGCTest, ReferenceCounting) {
    MPointer<int> ptr1 = MPointer<int>::New();
    *ptr1 = 200;
    MPointer<int> ptr2 = ptr1;

    EXPECT_EQ(*ptr1, 200);
    EXPECT_EQ(*ptr2, 200);

    ptr2 = nullptr; // Decrement reference count
    MPointerGC<int>::getInstance()->debug();
}
