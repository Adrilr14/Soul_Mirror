/*#pragma once

#include <vector>
#include <cstdint>
#include <list>

struct Graph {
    
    Graph();

    const std::vector<Connection>& getConections(Node fromNode){
        return fromNode.getConnections();
    }
 
private:
    
    std::vector<Node> nodes; //Vector de nodos

};

struct Connection{
    
    Connection();

    const float getCost() const { return cost; };
    const Node& getFromNode() const { return initial; };
    const Node& getToNode() const { return destiny; };

private:
    float cost;     //Coste de la conexión  
    Node initial;   //Nodo inicial significa el nodo desde donde nace la conexion
    Node destiny;   //Nodo destino que significa el nodo donde la conexión llega a su fin
};

struct Node {

    Node();
    const uint32_t getID() const { return ID; };
    const std::vector<Connection>& getConnections() const { return conexiones; };

private:
    uint32_t ID { ++nextID };
    inline static uint32_t nextID { 0 };
    std::vector<Connection> conexiones; //vector de conexiones que puede tener un nodo
};

struct PathFindingAStar {

    PathFindingAStar(Graph g,Node start,Node end,Heuristic h);
    ~PathFindingAStar();

    std::vector<NodeRecord> update();
    NodeRecord& smallestElement();

private:
    NodeRecord startRecord;
    Node goal;
    Graph graph;
    std::list<NodeRecord> open;
    std::list<NodeRecord> closed;
};

struct NodeRecord{
    Node n;
    Connection cnx; //esto hay q inicializarlo a nullptr pq tiene none conexiones
    float costSoFar { 0.0 };
    float totalCost { 0.0};   
    NodeRecord(); 
};

struct Heuristic {
    
    Heuristic(Node goal) : goalNode(goal){};
    //Generates an estimated cost to the reach the goal
    //from the given node
    const float estimate(Node n) const;

private:
    //stores the goal node that this heuristic is
    //estimating for 
    Node goalNode;

};
*/
