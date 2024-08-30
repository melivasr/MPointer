#ifndef MPOINTERGC_H
#define MPOINTERGC_H

#include <unordered_map>
#include <thread>
#include <mutex>
#include <atomic>

template <typename T>
class MPointer;

template <typename T>
class MPointerGC {
private:
    static MPointerGC<T>* instance;  // Instancia singleton
    std::unordered_map<int, MPointer<T>*> pointers;  // Mapa de IDs a punteros
    std::unordered_map<int, int> refCounts;  // Mapa de IDs a conteos de referencias
    std::mutex mtx;
    std::thread gcThread;
    std::atomic<bool> running;
    int nextId;  // ID único autogenerado

    MPointerGC();

    void runGC();  // Metodo que ejecuta el recolector de basura

public:
    static MPointerGC<T>* getInstance();  // Obtener la instancia singleton

    int generateId();  // Generar un nuevo ID único
    void addPointer(MPointer<T>* mp);  // Agregar un nuevo MPointer
    void removePointer(int id);  // Eliminar un MPointer por ID
    void incrementRefCount(int id);  // Incrementar el conteo de referencias
    void decrementRefCount(int id);  // Decrementar el conteo de referencias

    void debug();  // Metodo para mostrar el estado de la memoria
    ~MPointerGC();  // Destructor
};

#endif // MPOINTERGC_H

