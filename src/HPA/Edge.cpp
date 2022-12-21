#include "Edge.hpp"
#include <cmath>


/*Funcion que calcula el coste en el aire para asi tener un ahorro de memoria
para asi ahorrarnos el paso de parametros en el constructor*/
void GraphEdge::CostOnthefly(){
    //m_dCost = Distance();
}

double GraphEdge::Distance(Vector3D fnode,Vector3D snode){
    //Calculamos la disntancia entre los dos Nodos
    double valueX = pow(2,(snode.m_x - fnode.m_x));
    double valueY = pow(2,(snode.m_y - fnode.m_y));
    double valueZ = pow(2,(snode.m_z - fnode.m_z));

    return sqrt((valueX+valueY+valueZ));
}

