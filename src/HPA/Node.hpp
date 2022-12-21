#pragma once

#include "../game/util/Vector3D.hpp"
#include <ostream>

struct GraphNode {

public:
    
    //(invalid node_index) menor que 0 : Valor negativo
    GraphNode() : m_iIndex(Graph_data::invalid_index){}
    GraphNode(int idx) : m_iIndex(idx){}
    //GraphNode(GraphNode&) = delete; //borramos el constructor de copia, evitamos copias
    //CREO QUE SE HACEN COPIAS MIRAR BIEN Y EVITARLO PARA MEJORAR EL RENDIMIENTO

    virtual ~GraphNode(){}

    //Getters & Setter
    constexpr int getIndex() const { return m_iIndex; };
    constexpr void setIndex(int newIndex) { m_iIndex = newIndex; };
    
    //Output Sobrecargamos el operador salida <<
    friend std::ostream& operator<<(std::ostream& os,const GraphNode& n){
        os << "Indice: " << n.getIndex() << "\n";
        return os;
    }

private:

    //Every node has an index. A valid index is >= 0
    int m_iIndex;

};
