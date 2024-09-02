#include <gtest/gtest.h>

#include "../sortingAlgorithms/sortingAlgorithms.h"

TEST(SortingAlgorithmsTest, BubbleSort) {
    DoublyLinkedList<int> list;
    list.append(3);
    list.append(1);
    list.append(2);

    BubbleSort<int> sorter;
    sorter.sort(list);

    list.display(); // Ensure list is sorted: 1, 2, 3
}

TEST(SortingAlgorithmsTest, InsertionSort) {
    DoublyLinkedList<int> list;
    list.append(5);
    list.append(4);
    list.append(3);
    list.append(2);
    list.append(1);

    InsertionSort<int> sorter;
    sorter.sort(list);

    list.display(); // Ensure list is sorted: 1, 2, 3, 4, 5
}
