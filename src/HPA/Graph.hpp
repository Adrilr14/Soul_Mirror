#pragma once

#include <list>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cassert>

#include "../game/util/Vector3D.hpp"

//SparseGRaph Class
//Esta clase esta pensada para agrupar tanto nodos como aristas del grafo
//Problemas al borrar en un nodo mirarlo!!

template <class node_type, class edge_type>
struct SparseGraph{

    //Enable easy client access to the edge and node types used in the graph
    typedef edge_type EdgeType;
    typedef node_type NodeType;

    //a few more useful typedefs 
    typedef std::vector<node_type>  NodeVector;
    typedef std::list<edge_type>    EdgeList;
    typedef std::vector<EdgeList>   EdgeListVector;

private:

    //the nodes that comprise this graph
    NodeVector m_Nodes;

    //a vector of adjacency edge list. (each node index keys into the)
    //list of edges associated with that node 
    EdgeListVector m_Edges;

    //Is this a directed graph?
    bool    m_bDigraph;

    //the index of the next node to be added
    int     m_iNextNodeIndex;

public:

    //Constructor
    SparseGraph(bool digraph) : m_iNextNodeIndex(0), m_bDigraph(digraph){}

    //return the node at the given index
    const NodeType& getNode(int idx) const{
        assert( (idx < (int)m_Nodes.size()) &&
            (idx >=0)             &&
          "<SparseGraph::GetNode>: invalid index");
    
        return m_Nodes[idx];
    }

    //non-const version
    NodeType& getNode(int idx){
        assert( (idx < (int)m_Nodes.size()) &&
            (idx >=0)             &&
          "<SparseGraph::GetNode>: invalid index");
    
        return m_Nodes[idx];
    }

    const NodeVector& getNodes() const{
        return m_Nodes;
    }

    //const method for obtaning a reference to and edge
    EdgeType& getEdge(int from, int to);

    const EdgeListVector& getEdges() const {
        return m_Edges;
    }

    int getNextFreeNodeIndex() const{
        return m_iNextNodeIndex;
    }

    //adds a node to the graph and returns its index 
    void AddNode(Vector3D& vc){

        if(m_Nodes.size() > 0){
            bool addTo { false };
            for(unsigned int i = 0; i < m_Nodes.size();i++){
                auto nodo = m_Nodes[i];
                addTo = Compare(nodo.getPos(),vc);
                if(addTo == true){
                    break;
                }
            }
            if(addTo == false){
                m_Nodes.emplace_back(m_iNextNodeIndex,vc);
                m_iNextNodeIndex++;        
            }
        }else{
            m_Nodes.emplace_back(m_iNextNodeIndex,vc);
            m_iNextNodeIndex++;
        }
    }

    //removes a node by setting its index to invalid_index
    void RemoveNode(int node);

    //methods to add and remove edges
    void AddEdge(EdgeType edge);
    void RemoveEdge(int from, int to);

    //return the number of active + inactive nodes present in the graph
    int NumNodes() const{
        return m_Nodes.size();
    }

    //returns the number of active nodes present in the graph
    int NumActiveNodes() const{
        int activeNodes = 0;

        for(unsigned int i = 0; i < m_Nodes.size();i++){
            if(m_Nodes[i].getIndex() != Graph_data::invalid_index){
                activeNodes++;
            }
        }
        return activeNodes;
    }

    //returns the number of edges present in the graph
    int NumEdges() const{
        //Pendiente por hacer
    }

    //return true if the graph constains no nodes
    bool isEmpty() const {
        return m_Nodes.empty();
    };

    //returns true if a node with the given index is present in the graph
    bool isPresent(int nd) const{
        //Primero miramos si m_Nodes es mayor que 0
        if(m_Nodes.size() > 0){
            if(m_Nodes[nd].getIndex() != Graph_data::invalid_index){
                return true;
            }
        }
        return false;
    }

    //methods for loading and saving graph from an open file stream or from a file
    bool Save(const char* FileName) const;
    bool Save(std::ofstream& stream) const;

    std::vector<std::string> splitPattern(const std::string_view s,const char* delimiter){
        int posInit = 0;
        int posFound = 0;
        std::string splitted;
        std::vector<std::string> resultados;

        while(posFound >= 0){
            posFound = s.find(delimiter, posInit);
            splitted = s.substr(posInit, posFound - posInit);
            posInit = posFound + 1;
            resultados.push_back(splitted);
        }

        return resultados;
    }

    bool Load(const char* FileName) {
        std::ifstream input(FileName);
        if(input.is_open() == false){
            //Management errors
            return false;
        }

        //Cuando cargamos un nuevo grafo
        //Borramos el q habia previamente
       
        SparseGraph::Clear();
        std::string line;
        
        while(!input.eof()){ //Mientras sea disinto de end of file
            getline(input,line);
            if(line != ""){
                auto caracter = line[0]; //Solo necesitamos dos o el vertice o la cara
                if(caracter == 'v' || caracter == 'f'){
                    //Hacemos el split de los espacios " "
                    auto vector = splitPattern(line," ");
                    if(caracter == 'v'){            
                        Vector3D vc{std::stof(vector[1]) , std::stof(vector[2]) , std::stof(vector[3])};
                        AddNode(vc);
                    }else{
                        auto v1 = splitPattern(vector[1],"/");
                        auto v2 = splitPattern(vector[2],"/");
                        auto v3 = splitPattern(vector[3],"/");
                        auto fp = std::stof(v1[0]);
                        auto sp = std::stof(v2[0]);
                        auto tp = std::stof(v3[0]);
                
                        EdgeType e1(fp,sp);
                        EdgeType e2(sp,tp);
                        EdgeType e3(tp,fp);
                        EdgeList lista { e1,e2,e3 };
                        m_Edges.push_back(lista);
                    }
                }
            }
        }    
        return true;
    }

    //Compare between 2 positions
    bool Compare(Vector3D nodo1,Vector3D nodo2){
        if(nodo1.m_x == nodo2.m_x &&
           nodo1.m_y == nodo2.m_y && 
           nodo1.m_z == nodo2.m_z){
               return true;
           }
        return false;
    }

    //Clear the graph ready for new insertions
    void Clear(){
        m_Nodes.clear();
        m_Edges.clear();
        m_iNextNodeIndex = 0;
    }

    //iterators clients may use to access
    //Version const del iterador
    struct ConstEdgeIterator{
        private:                                                                

        typename EdgeList::const_iterator        curEdge;

        const SparseGraph<node_type, edge_type>& G;

        const int                                NodeIndex;

      public:

        ConstEdgeIterator(const SparseGraph<node_type, edge_type>& graph,
                          int                           node): G(graph),
                                                               NodeIndex(node)
        {
          /* we don't need to check for an invalid node index since if the node is
             invalid there will be no associated edges
         */

          curEdge = G.m_Edges[NodeIndex].begin();
        }

        const EdgeType*  begin()
        {        
          curEdge = G.m_Edges[NodeIndex].begin();
    
          return &(*curEdge);
        }

        const EdgeType*  next()
        {
          ++curEdge;
    
          return &(*curEdge);

        }

        //return true if we are at the end of the edge list
        bool end()
        {
          return (curEdge == G.m_Edges[NodeIndex].end());
        }
    };
    struct EdgeIterator;
    struct NodeIterator;
    struct ConstNodeIterator;
    
};


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