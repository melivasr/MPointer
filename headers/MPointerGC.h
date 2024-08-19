#ifndef MPOINTERGC_H
#define MPOINTERGC_H

#include <list>
#include <thread>
#include <mutex>

template <typename T>
class MPointer;

template <typename T>
class MPointerGC {
private:
    static MPointerGC<T>* instance;  // Instancia recolector de basura
    std::list<MPointer<T>*> pointers;
    std::mutex mtx;

    MPointerGC();

public:
    static MPointerGC<T>* getInstance();

    // Agregar un nuevo MPointer
    void addPointer(MPointer<T>* mp);

    // Eliminar un MPointer
    void removePointer(MPointer<T>* mp);

    // Ejecutar el recolector de basura para liberar memoria
    void runGC();
};

#endif
