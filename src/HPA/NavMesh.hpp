#pragma once 

#include <vector>
#include <string>
#include <list>
#include <map>
#include "../game/util/Vector3D.hpp"
//-----------------------Node


struct GraphNode {

public:

    //Un nodo contiene un GraphEdge con todas las aristas con las que se relaciona
    struct GraphEdge{
        public:

        explicit GraphEdge() = default;  
        
        void addNewArista(int ar){
            for(unsigned int i = 0; i < aristas.size(); i++){
                if(aristas[i] == ar){
                    return;
                }
            }
            aristas.push_back(ar);                     
        }
        //Variables de Clase
        std::vector<int> aristas;
    };
    
    GraphNode() : idx(invalid_index){}
    GraphNode(int i) : idx(i){}
    GraphNode(int i , Vector3D vec) : idx(i), vecPos(vec) {}
    ~GraphNode() {}

    //Funciones para un Nodo
    constexpr bool compareVec3D(float x,float y,float z);
    
    int idx; //Identificador
    Vector3D vecPos; //Vector Posicion X Y Z
    float fGlobalGoal { 99999 }; //Poner a Infinito con el limits
    float fLocalGoal  { 99999 };
    bool visited { false };
    GraphEdge edges;

};

struct NavMesh_t{
    
public:
    explicit NavMesh_t() = default;
    ~NavMesh_t();

    bool Load(std::string pathToOpen);
    bool CompareIDNode(float x,float y,float z,int id);
    void AddBeforeRepeats(int first, int second, int third);

    //Getters
    GraphNode getNodoFromID(int id);

    std::vector<GraphNode> m_graph;
    std::map<int,std::vector<int>> m_repeats;
};

struct AStar{
    
public:
    NavMesh_t& m_Graph;

    std::vector<int> m_resultado;


    int m_Source;
    int m_Target;
    

    //Constructor
    AStar(NavMesh_t& graph,int source,int target) : 
    m_Graph(graph),
    m_Source(source),
    m_Target(target){}

std::vector<int> getResultado() {
    return m_resultado;
}

std::vector<Vector3D> getPosicionRes(){
    std::vector<Vector3D> res;
    for(unsigned int i = 0; i < m_resultado.size();i++){
        res.push_back(m_Graph.getNodoFromID(m_resultado[i]).vecPos);
    }
    return res;
}

void SearchAStar(){
       
       auto distance = [](GraphNode a, GraphNode b){
           return sqrtf((a.vecPos.m_x - b.vecPos.m_x)*(a.vecPos.m_x - b.vecPos.m_x)
            + (a.vecPos.m_y - b.vecPos.m_y)*(a.vecPos.m_y - b.vecPos.m_y) 
            + (a.vecPos.m_z - b.vecPos.m_z)*(a.vecPos.m_z - b.vecPos.m_z));
       };

       auto heuristic = [distance](GraphNode a, GraphNode b){
           return distance(a,b);
       };

       GraphNode nodeCurrent = m_Graph.getNodoFromID(m_Source);
       GraphNode nodeEnd = m_Graph.getNodoFromID(m_Target);
       nodeCurrent.fLocalGoal = 0.0f;
       nodeCurrent.fGlobalGoal = heuristic(nodeCurrent,nodeEnd);
      
       std::list<GraphNode> listNotTestedNodes;
       listNotTestedNodes.push_back(nodeCurrent);

       while(!listNotTestedNodes.empty() && nodeCurrent.idx != nodeEnd.idx){
           //std::cout << "NodeCurrent : " << nodeCurrent.idx << "    NodeEnd : " << nodeEnd.idx << std::endl;  
            //std::cout << listNotTestedNodes.front().visited <<  std::endl;
           listNotTestedNodes.sort([](const GraphNode a, const GraphNode b){ return a.fGlobalGoal < b.fGlobalGoal; });

           while(!listNotTestedNodes.empty() && listNotTestedNodes.front().visited){
               listNotTestedNodes.pop_front();
           }
           //std::cout << "List " << listNotTestedNodes.front().idx << " " << listNotTestedNodes.back().idx << std::endl;
           if(listNotTestedNodes.empty()){ break; }

           nodeCurrent = listNotTestedNodes.front();
           nodeCurrent.visited = true;
           listNotTestedNodes.front().visited = true;
           m_resultado.push_back(nodeCurrent.idx);

            //std::cout << "NodeCurrent : " << nodeCurrent.idx << std::endl; 
           for(unsigned int i = 0; i < nodeCurrent.edges.aristas.size(); i++){
               auto nodeNeighbour = m_Graph.getNodoFromID(nodeCurrent.edges.aristas[i]);

               if(!nodeNeighbour.visited){
                   listNotTestedNodes.push_back(nodeNeighbour);
               }

                float possiblyLowerGoal = nodeCurrent.fLocalGoal + distance(nodeCurrent,nodeNeighbour);

                if(possiblyLowerGoal < nodeNeighbour.fLocalGoal){
                    //nodeNeighbour.parent = nodeCurrent;
                    nodeNeighbour.fLocalGoal = possiblyLowerGoal;

                    nodeNeighbour.fGlobalGoal = nodeNeighbour.fLocalGoal + heuristic(nodeNeighbour,nodeEnd);
                }    

           } 
       }
    }
};

