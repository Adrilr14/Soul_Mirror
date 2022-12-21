#pragma once

#include "../game/util/Vector3D.hpp"

#include <ostream>
//Esta clase es una encapsulación básica de la información
//de la conexión entre dos nodos de un grafo
struct GraphEdge{
    
public:
    GraphEdge(int from,int to,double cost) : m_dCost(cost),
                                             m_iFrom(from),
                                             m_iTo(to)
    {}

    GraphEdge(int from, int to) : m_dCost(1.0), m_iFrom(from),
                                  m_iTo(to)
    {}

    GraphEdge() :  m_dCost(1.0),m_iFrom(-1),m_iTo(-1)
    {}

    virtual ~GraphEdge(){}

    //Saving memory can calculate the cost apart cost "on-the-fly"
    //Si el coste de la arista es igual a la distancia entre 2 nodos
    //La funcion sería la distancia eucladiana
    void CostOnthefly(); //Mirar la página 206 final TODO : implementarlo
    double Distance(Vector3D fnode,Vector3D snode);

    //Getters y Setters

    constexpr int getFrom() const { return m_iFrom; };
    constexpr void setFrom(int newFrom) { m_iFrom = newFrom;  };

    constexpr int getTo() const { return m_iTo; };
    constexpr void setTo(int newTo) { m_iTo = newTo; } ;
    
    constexpr int getCost() const { return m_dCost; };
    constexpr void setCost(int newCost) { m_dCost = newCost; } ;

    //Sobrecarga del operador salida <<
     friend std::ostream& operator<<(std::ostream& os,const GraphEdge& n){
        os << "De: "  << n.getFrom() << " A: " << n.getTo() << std::endl;
        return os;
    }

protected:

    //Una arista que conecta dos nodos. Los nodos validos son siempre positivos
    int m_iFrom;
    int m_iTo;

    //El coste de ir de una arista a otra
    double m_dCost;    

};
