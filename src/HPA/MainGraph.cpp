#include "MainGraph.hpp"

#include <algorithm>
#include <limits>
#include <math.h>
#include <list>
#include <iostream>

Mapa::Mapa(){

    nodes = new Snode[fila*columna];


    for(int i = 0; i < columna; i++){
        for(int j = 0; j < fila; j++){
            nodes[j*columna+i].x = i;
            nodes[j*columna+i].y = j;
            if(mapa[i][j] == 1){
               nodes[j*columna+i].obstaculo = true; 
            }else{
                nodes[j*columna+i].obstaculo = false; 
            }
            nodes[j*columna+i].parent = nullptr;
            nodes[j*columna+i].visitado = false;  
        }
    }

    for(int i = 0; i < columna; i++){
        for(int j = 0; j < fila; j++){
            if(j > 0){
                nodes[j*columna + i].vecNeibour.push_back(&nodes[(j - 1) * columna + (i + 0)]);
            }
            if(i<fila-1)
                nodes[j*columna + i].vecNeibour.push_back(&nodes[(j + 1) * columna + (i + 0)]);
            if (i>0)
                nodes[j*columna + i].vecNeibour.push_back(&nodes[(j + 0) * columna + (i - 1)]);
            if(i<columna-1)
                nodes[j*columna + i].vecNeibour.push_back(&nodes[(j + 0) * columna + (i + 1)]);
        }
    }

    nodeStart = &nodes[4];
    std::cout << "Posicion nodeStart X y Y : " <<  nodeStart->x << " " << nodeStart->y << std::endl;
    nodeEnd = &nodes[10];
    std::cout << "Posicion nodeEnd X y Y : " <<  nodeEnd->x << " " << nodeEnd->y << std::endl;
}

void Mapa::Solve_Astar(){
    for (int x = 0; x < columna; x++)
			for (int y = 0; y < fila; y++)
			{
				nodes[y*columna + x].visitado = false;
				nodes[y*columna + x].fGlobalGoal = std::numeric_limits<int>::max();
				nodes[y*columna + x].flocalGoal = std::numeric_limits<int>::max();
				nodes[y*columna + x].parent = nullptr;	// No parents
			}

        auto distance = [](Snode* a, Snode* b) // For convenience
		{
			return sqrtf((a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y));
		};

		auto heuristic = [distance](Snode* a, Snode* b) // So we can experiment with heuristic
		{
			return distance(a, b);
		};

        Snode *nodeCurrent = nodeStart;
		nodeStart->flocalGoal = 0.0f;
		nodeStart->fGlobalGoal = heuristic(nodeStart, nodeEnd);

        std::list<Snode*> listNotTestedNodes;
		listNotTestedNodes.push_back(nodeStart);

        while (!listNotTestedNodes.empty() && nodeCurrent != nodeEnd)// Find absolutely shortest path // && nodeCurrent != nodeEnd)
		{
			// Sort Untested nodes by global goal, so lowest is first
			listNotTestedNodes.sort([](const Snode* lhs, const Snode* rhs){ return lhs->fGlobalGoal < rhs->fGlobalGoal; } );
			
			// Front of listNotTestedNodes is potentially the lowest distance node. Our
			// list may also contain nodes that have been visited, so ditch these...
			while(!listNotTestedNodes.empty() && listNotTestedNodes.front()->visitado)
				listNotTestedNodes.pop_front();

			// ...or abort because there are no valid nodes left to test
			if (listNotTestedNodes.empty())
				break;

			nodeCurrent = listNotTestedNodes.front();
			nodeCurrent->visitado = true; // We only explore a node once
			
					
			// Check each of this node's neighbours...
			for (auto nodeNeighbour : nodeCurrent->vecNeibour)
			{
				// ... and only if the neighbour is not visited and is 
				// not an obstacle, add it to NotTested List
				if (!nodeNeighbour->visitado && nodeNeighbour->obstaculo == false){
                    std::cout << "Posicion X y Y: " << nodeNeighbour->x << " " << nodeNeighbour->y << std::endl;
                    std::cout << "obstaculo" << nodeNeighbour->obstaculo << std::endl;
                    listNotTestedNodes.push_back(nodeNeighbour);
                }
					

				// Calculate the neighbours potential lowest parent distance
				float fPossiblyLowerGoal = nodeCurrent->flocalGoal + distance(nodeCurrent, nodeNeighbour);

				// If choosing to path through this node is a lower distance than what 
				// the neighbour currently has set, update the neighbour to use this node
				// as the path source, and set its distance scores as necessary
				if (fPossiblyLowerGoal < nodeNeighbour->flocalGoal)
				{
					nodeNeighbour->parent = nodeCurrent;
					nodeNeighbour->flocalGoal = fPossiblyLowerGoal;

					// The best path length to the neighbour being tested has changed, so
					// update the neighbour's score. The heuristic is used to globally bias
					// the path algorithm, so it knows if its getting better or worse. At some
					// point the algo will realise this path is worse and abandon it, and then go
					// and search along the next best path.
					nodeNeighbour->fGlobalGoal = nodeNeighbour->flocalGoal + heuristic(nodeNeighbour, nodeEnd);
				}
			}	
		}
}

void Mapa::drawPath(){
     for (int x = 0; x < columna; x++){
        for (int y = 0; y < fila; y++){
            std::cout << nodes[y*columna + x].obstaculo ;
        }
        std::cout << std::endl;
    }

    std::cout << "aaaaaaaaaaaaaaaaaaaaaaa" << std::endl;

     for (int x = 0; x < columna; x++)
        for (int y = 0; y < fila; y++){
            if(nodes[y*columna + x].visitado == true){
                std::cout << "Posicion X y Y: " << nodes[y*columna + x].x << " " << nodes[y*columna + x].y << " " << std::endl;
            }
        }
        
}