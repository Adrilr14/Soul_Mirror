/*#include "Graph.hpp"

#include <algorithm>

PathFindingAStar::PathFindingAStar(Graph g,Node start,Node end,Heuristic h){
    //primero calculamos la Heuristica para el coste total estimado
    //startRecord.estimatedTotalCost = heuristic.estimate(start);
    //me pasan la heuristica por parametro asi q aprovechamos
    
    
}

PathFindingAStar::~PathFindingAStar(){
    
}

std::vector<NodeRecord> PathFindingAStar::update(){
    //Iterate  through processing each node

    while (open.size() > 0){
        //Find the smallest element in the open list
        //using the estimatedTotalCost
        auto& current = smallestElement();

        if(current.n.getID() == goal.getID()){ //Si coinciden los ID es que son el mismo
            break;
        }

        std::vector<Connection> connections = graph.getConections(current.n);

        for (auto& con : connections){
            //Get the estimate for the end node
            auto& e = con.getToNode();
            float thecost = current.costSoFar + con.getCost();
            
            //if the node is closed we may have to skip or remove it from the closet list
            if(std::find(closed.begin(),closed.end(),e) != closed.end()){
                for (auto& endNodeR : closed){
                    if(endNodeR.n.getID() == e.getID()){
                        if(endNodeR.costSoFar <= thecost){
                            continue;
                        }else{

                        }
                    }
                }
            }else if (std::find(open.begin(),open.end(),e) != open.end()){
                for (auto& endNodeR : open){
                    if(endNodeR.costSoFar <= thecost){
                        continue;
                    }
                }
            }else{
                //Creamos un NodeRecord
                
            }
        }
    }
    
}

NodeRecord& PathFindingAStar::smallestElement(){
    float sizeCost = 99999.0; //Como tenemos que encontrar el elemeno más pequeño establecemos uno grande estandar
    
    
   
}
*/