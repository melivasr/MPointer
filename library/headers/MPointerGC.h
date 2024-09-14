#ifndef MPOINTERGC_H
#define MPOINTERGC_H

#include "LinkedList.h"
#include <thread>
#include <mutex>
#include <atomic>

// Forward declaration de MPointer y LinkedList
template <typename T>
class MPointer;

template <typename T>
class LinkedList; // Añadir la declaración anticipada de LinkedList


template <typename T>
class MPointerGC {
private:
    static MPointerGC* instance;  // Instancia singleton
    LinkedList<MPointer<T>> pointersList;  // Lista doblemente enlazada de punteros MPointer
    std::mutex mtx;
    std::thread gcThread;
    std::atomic<bool> running;
    int nextId;  // ID único autogenerado

    MPointerGC();

    static void runGC(MPointerGC* mp);  // Metodo que ejecuta el recolector de basura

public:
    static MPointerGC* getInstance();  // Obtener la instancia singleton

    int generateId();  // Generar un nuevo ID único
    void addPointer(MPointer<T>* mp);  // Agregar un nuevo MPointer
    void removePointer(int id);  // Eliminar un MPointer por ID
    void incrementRefCount(int id);  // Incrementar el conteo de referencias
    void decrementRefCount(int id);  // Decrementar el conteo de referencias

    void debug();  // Metodo para mostrar el estado de la memoria
    ~MPointerGC();  // Destructor
};

#endif // MPOINTERGC_H