#include <iostream>

template <typename T>
class MPointer {
private:
    T* pointer;  // Atributo que almacena el puntero
    int id;      // Identificador único de cada MPointer
    static int instance_count; // Conteo de instancias para ejemplo

public:
    // Constructor por defecto
    MPointer() : pointer(nullptr), id(-1) {}

    // Constructor de copia
    MPointer(const MPointer<T>& other) {
        this->pointer = other.pointer;
        this->id = other.id;
        instance_count++;  // Incrementar el contador
    }

    // Destructor
    ~MPointer() {
        if (pointer) {
            instance_count--;
            if (instance_count == 0) {
                delete pointer; // Liberar la memoria
            }
        }
    }

    // Método estático para crear un nuevo MPointer
    static MPointer<T> New() {
        MPointer<T> mp;
        mp.pointer = new T(); // Reservar memoria para el tipo T
        instance_count = 1;
        // Aquí se asignaría un id desde MPointerGC (por implementar)
        return mp;
    }

    // Sobrecarga del operador * para acceder al valor almacenado
    T& operator*() {
        return *pointer;
    }

    // Sobrecarga del operador & para obtener la dirección de memoria
    T* operator&() {
        return pointer;
    }

    // Sobrecarga del operador
    MPointer<T>& operator=(const MPointer<T>& other) {
        if (this != &other) {
            if (pointer) {
                instance_count--;
                if (instance_count == 0) {
                    delete pointer; // Liberar la memoria
                }
            }
            this->pointer = other.pointer;
            this->id = other.id;
            instance_count++;
            //MPointerGC para actualizar el conteo de referencias (por implementar)
        }
        return *this;
    }

    // Sobrecarga del operador
    MPointer<T>& operator=(const T& value) {
        if (!pointer) {
            pointer = new T();
        }
        *pointer = value;
        return *this;
    }
};

// Inicialización del contador de instancias
template<typename T>
int MPointer<T>::instance_count = 0;

// Ejemplo
int main() {
    MPointer<int> myPtr = MPointer<int>::New();
    *myPtr = 5;

    int valor = *myPtr; // Debería devolver 5
    std::cout << "Valor almacenado: " << valor << std::endl;

    MPointer<int> myPtr2 = MPointer<int>::New();
    myPtr2 = myPtr; // Asigna el mismo puntero e id

    *myPtr2 = 10;
    std::cout << "Nuevo valor almacenado en myPtr2: " << *myPtr2 << std::endl;
    std::cout << "Valor en myPtr (debería ser 10): " << *myPtr << std::endl;

    return 0;
}
