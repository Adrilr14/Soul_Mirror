#pragma once

#include <vector>

struct Snode{
    bool obstaculo = false;
    bool visitado = false;
    float fGlobalGoal;
    float flocalGoal;
    int x;
    int y;
    std::vector<Snode*> vecNeibour;
    Snode* parent;
};

struct Mapa{
    
    Mapa();
    void Solve_Astar();
    void drawPath();
private:
     int mapa [11][11]  = {
        {1,1,0,0,0,0,0,0,1,0,0},
        {1,1,0,0,0,0,0,0,1,0,0},
        {0,0,0,0,0,0,0,0,0,0,0},
        {1,0,0,1,1,1,1,1,1,0,0},
        {0,0,0,0,0,1,0,1,0,0,0},
        {0,0,0,0,0,0,0,0,1,0,0},
        {0,0,1,0,0,0,0,1,0,0,0},
        {0,1,1,0,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,1,1,1,0},
        {0,0,0,0,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,1,1,1,0},
    };
    Snode* nodes {nullptr};
    int fila {11};
    int columna {11};
    Snode* nodeStart {nullptr};
    Snode* nodeEnd {nullptr};
};

