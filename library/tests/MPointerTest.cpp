#include <gtest/gtest.h>
#include "../headers/MPointer.h"
#include "../headers/MPointerGC.h"

class MPointerTest : public ::testing::Test {
protected:
    void SetUp() override {
        MPointerGC<int>::getInstance(); // Asegura que el GC esté inicializado
    }
};

TEST_F(MPointerTest, BasicAssertions) {
    MPointer<int> ptr1 = MPointer<int>::New();
    *ptr1 = 10;
    EXPECT_EQ(*ptr1, 10);

}

TEST_F(MPointerTest, PointerAssignment) {
    MPointer<int> ptr1 = MPointer<int>::New();
    *ptr1 = 100;

    MPointer<int> ptr2 = MPointer<int>::New();
    ptr2 = ptr1;

    EXPECT_EQ(*ptr1, 100);
    EXPECT_EQ(*ptr2, 100);
}

TEST_F(MPointerTest, NullPointerAssignment) {
    MPointer<int> ptr1 = MPointer<int>::New();
    ptr1 = nullptr;
    EXPECT_EQ(ptr1, nullptr);
}

TEST_F(MPointerTest, MemoryLeakTest) {
    {
        MPointer<int> ptr1 = MPointer<int>::New();
        *ptr1 = 1000;
    } // `ptr1` goes out of scope, memory should be freed by GC
    MPointerGC<int>::getInstance()->debug();
}
