#include <gtest/gtest.h>
#include "../headers/MPointer.h"
#include "../headers/MPointerGC.h"


class MPointerTest : public ::testing::Test {
protected:
    void SetUp() override {
        MPointerGC<int>::getInstance(); // Asegura que el GC esté inicializado
    }
};

// Prueba básica de asignación
TEST_F(MPointerTest, BasicAssertions) {
    MPointer<int> ptr1 = MPointer<int>::New();
    *ptr1 = 10;

    // Imprimir el valor del puntero
    std::cout << "El valor de ptr1 es: " << *ptr1 << std::endl;

    EXPECT_EQ(*ptr1, 10);
}

// Prueba de asignación de punteros
TEST_F(MPointerTest, PointerAssignment) {
    MPointer<int> ptr1 = MPointer<int>::New();
    *ptr1 = 100;

    MPointer<int> ptr2 = MPointer<int>::New();
    ptr2 = ptr1;

    // Imprimir los valores de los punteros
    std::cout << "El valor de ptr1 es: " << *ptr1 << std::endl;
    std::cout << "El valor de ptr2 es: " << *ptr2 << std::endl;

    EXPECT_EQ(*ptr1, 100);
    EXPECT_EQ(*ptr2, 100);
}

// Prueba de asignación a nullptr
TEST_F(MPointerTest, NullPointerAssignment) {
    MPointer<int> ptr1 = MPointer<int>::New();
    ptr1 = nullptr;

    // Imprimir el valor de ptr1 tras asignarlo a nullptr
    std::cout << "ptr1 es nullptr" << std::endl;

    EXPECT_EQ(ptr1, nullptr);
}

// Prueba de fugas de memoria y recolección de basura
TEST_F(MPointerTest, MemoryLeakTest) {
    {
        MPointer<int> ptr1 = MPointer<int>::New();
        *ptr1 = 1000;

        // Imprimir el valor del puntero
        std::cout << "El valor de ptr1 antes de salir del scope es: " << *ptr1 << std::endl;
    }

    // Mostrar el estado del GC después de que el puntero haya salido de alcance
    MPointerGC<int>::getInstance()->debug();
}
