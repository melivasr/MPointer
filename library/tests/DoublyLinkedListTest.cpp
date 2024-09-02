#include <gtest/gtest.h>

#include "../doublyLinkedList/DoublyLinkedList.h"
#include "../headers/MPointerGC.h"
TEST(DoublyLinkedListTest, AppendAndPrepend) {
    DoublyLinkedList<int> list;
    list.prepend(1);


    EXPECT_FALSE(list.isEmpty());

    list.display();
}

TEST(DoublyLinkedListTest, RemoveElement) {
    DoublyLinkedList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);

    list.remove(2);
    list.display();
}
