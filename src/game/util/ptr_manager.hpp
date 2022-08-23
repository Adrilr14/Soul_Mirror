#pragma once

#include <vector>
#include <memory>

//Creamos una clase que gestione los unique_ptr
//La hacemos template para asi poder 
template <typename T>
struct ptr_Manager{
    
    using NodeStorage = std::vector<std::unique_ptr<T>>;
    using MemoryStorage = std::unique_ptr<std::byte[]>;

    explicit ptr_Manager(std::size_t bytes = 50) 
    : mem_size { bytes } {}

    ~ptr_Manager() {
        for(unsigned int i = 0; i < nodes.size(); i++){ //TESTO QUITAR SI NO VA
            ~nodes[i];
        }
        nodes.clear();
    }

    void AddNode(std::unique_ptr<T> node){
        nodes.push_back(std::move(node)); 
        //Hacemos un move porque si no se crearía una copia
        // y daría una error
    }

    template <typename... pTs> //Paso de parametros los que sean (1,2,3...)
    auto& createNode(pTs&&... args){
        auto* ptr_node = ptr_mem - sizeof(T);
        T* node = new (ptr_node) T(std::forward<pTs>(args)...);
        nodes.emplace_back(node);
        ptr_mem = ptr_node;
        return *node;
    }

    //Variables de clase
private:
    NodeStorage nodes;
    std::size_t mem_size { 100 };
    MemoryStorage mem { std::make_unique<std::byte[]>(mem_size) };
    std::byte* ptr_mem { mem.get() + mem_size };
};