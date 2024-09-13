#include <gtest/gtest.h>
#include "../headers/MPointer.h"
#include "../headers/MPointerGC.h"

// Prueba de gestión de instancias
TEST(MPointerGCTest, InstanceManagement) {
    MPointer<int> ptr1 = MPointer<int>::New();
    MPointer<int> ptr2 = MPointer<int>::New();

    *ptr1 = 200;

    // Imprimir los IDs de los punteros
    std::cout << "ID de ptr1: " << ptr1.getId() << std::endl;
    std::cout << "ID de ptr2: " << ptr2.getId() << std::endl;

    // Verificar que los IDs sean diferentes
    EXPECT_NE(ptr1.getId(), ptr2.getId());

    // Mostrar el estado del GC
    MPointerGC<int>::getInstance()->debug();
}

// Prueba de conteo de referencias
TEST(MPointerGCTest, ReferenceCounting) {
    MPointer<int> ptr1 = MPointer<int>::New();
    *ptr1 = 200;
    MPointer<int> ptr2 = ptr1;

    // Imprimir los valores de los punteros
    std::cout << "El valor de ptr1 es: " << *ptr1 << std::endl;
    std::cout << "El valor de ptr2 es: " << *ptr2 << std::endl;

    EXPECT_EQ(*ptr1, 200);
    EXPECT_EQ(*ptr2, 200);

    // Asignar nullptr a ptr2
    ptr2 = nullptr;

    // Mostrar el estado del GC tras la eliminación de ptr2
    MPointerGC<int>::getInstance()->debug();
}


// Prueba para reasignación entre punteros de diferentes tipos
TEST(MPointerGCTest, DifferentTypesAssignmentTest) {
    MPointer<double> ptrDouble = MPointer<double>::New();
    *ptrDouble = 3.14159;

    MPointer<std::string> ptrString = MPointer<std::string>::New();
    *ptrString = "Hola mundo";

    // Imprimir valores de los punteros de diferentes tipos
    std::cout << "El valor de ptrDouble es: " << *ptrDouble << std::endl;
    std::cout << "El valor de ptrString es: " << *ptrString << std::endl;

    EXPECT_EQ(*ptrDouble, 3.14159);
    EXPECT_EQ(*ptrString, "Hola mundo");
}

// Prueba para verificar que el destructor de MPointer se llame correctamente
TEST(MPointerGCTest, DestructorTest) {
    {
        MPointer<int> ptr1 = MPointer<int>::New();
        *ptr1 = 500;
        std::cout << "Valor de ptr1: " << *ptr1 << std::endl;
    }
    // Aquí, el recolector de basura debería haber limpiado la memoria
    MPointerGC<int>::getInstance()->debug();
}