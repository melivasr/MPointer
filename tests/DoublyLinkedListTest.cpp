#include <gtest/gtest.h>

#include "../library/doublyLinkedList/DoublyLinkedList.h"

TEST(DoublyLinkedListTest, AppendAndPrepend) {
    DoublyLinkedList<int> list;
    list.append(1);
    list.append(2);
    list.prepend(0);

    EXPECT_FALSE(list.isEmpty());

    list.display(); // You might want to capture output and compare
}

TEST(DoublyLinkedListTest, RemoveElement) {
    DoublyLinkedList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);

    list.remove(2);
    list.display();
}
