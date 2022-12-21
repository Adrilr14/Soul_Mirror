#pragma once

#include "Node.hpp"
#include "../game/util/Vector3D.hpp"

template <class extra_info = void*>
struct NavGraphNode : public GraphNode{
    
public:

    //Constructrors
    NavGraphNode() : m_ExtraInfo(extra_info()){}

    NavGraphNode(int idx, Vector3D pos) : GraphNode(idx),m_vPosition(pos),m_ExtraInfo(extra_info()){}

    virtual ~NavGraphNode(){}

    //Getters y setters
    constexpr Vector3D getPos() const { return m_vPosition;};
    constexpr void setPos(Vector3D newPosition) { m_vPosition = newPosition; };

    extra_info getExtraInfo() const { return m_ExtraInfo; };
    void setExtraInfo(extra_info info) { m_ExtraInfo = info; } ;

    //Output operador salida << 
    friend std::ostream& operator<<(std::ostream& os,const NavGraphNode& n){
        os << "Indice: " << n.getIndex() << " Posiciones X,Y,Z: " 
                                         << n.getPos().m_x << " " 
                                         << n.getPos().m_y << " "
                                         << n.getPos().m_z
        << " \n";
        return os; 

    }

private:

    //the node's position
    Vector3D m_vPosition;

    extra_info m_ExtraInfo;

};