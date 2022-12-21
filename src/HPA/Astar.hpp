#pragma once

#include "IndexedPriorityQLow.hpp"
#include <vector>
#include <list>
#include <iostream>

//Implementando el Algoritmo A*
template <class graph_type,class heuristic>
struct Graph_SearchStar{

    //create a typedef for the edge type used by the graph
    typedef typename graph_type::EdgeType Edge;
    typedef typename graph_type::ConstEdgeIterator constEdgeItr;

private:

    const graph_type&   m_Graph;

    // indexed into by node. Constains the "real" acumulative cost to that node
    std::vector<double> m_GCosts;

    // indexed into by node.Constains the cost from adding m_GCosts[n] to
    // the heuristic cost from n to the target node. This is the vector the
    // iPQ indexes into.
    std::vector<double> m_FCosts;

    std::vector<const Edge*> m_ShortesPath;
    std::vector<const Edge*> m_SearchFrontier;

    int     m_Source;
    int     m_Target;

public:

    //constructor 
    Graph_SearchStar(graph_type& graph,int source,int target) :
    m_Graph(graph),
    m_ShortesPath(graph.NumNodes()),
    m_SearchFrontier(graph.NumNodes()),
    m_GCosts(graph.NumNodes(),0.0),
    m_FCosts(graph.NumNodes(),0.0),
    m_Source(source),
    m_Target(target)
    {}


     //the A* search algorithm
    void SearchAStar(){
        //create an indexed priority queue of nodes. The queue will give 
        //priority to nodes with low F cost. (F = G+H);
        IndexedPriorityQLow pq(m_FCosts,m_Graph.NumNodes());
    
        //insertamos el source node a la lista
        pq.insert(m_Source);
        std::cout << "m_Source " << m_Source << std::endl; 

        while(!pq.empty()){
            //get lowest cost node from the queue
            int nextCloseNode = pq.Pop();
            std::cout << "nextCloseNode " << nextCloseNode << std::endl; 

            //move this node from the frontier to the spanning tree 
            m_ShortesPath[nextCloseNode] = m_SearchFrontier[nextCloseNode];

            //if the target has been found exit
            if(nextCloseNode == m_Target){
                return;
            }
            //now to test all the edges attached to this node
            constEdgeItr ConstEdgeItr(m_Graph,nextCloseNode);

            for(const Edge* pE = ConstEdgeItr.begin(); !ConstEdgeItr.end();pE = ConstEdgeItr.next()){
                //Calculate the Heuristic Cost from this node to the target (H)
                double HCost = heuristic::Calculate(m_Graph,m_Target,pE->getTo());
                std::cout << "getFrom() " << pE->getFrom() << "getTo() " << pE->getTo() << std::endl;
                std::cout << "HCost " << HCost << std::endl; 
                //Calculate the "real" cost to this node from the source (G)
                
                double GCost = m_GCosts[nextCloseNode] + pE->getCost();
                std::cout << "GCost " << GCost << std::endl; 

                //if the node has not been to the frontier, add it and update the G and F costs
                if(m_SearchFrontier[pE->getTo()] == nullptr){
                    m_FCosts[pE->getTo()] = GCost + HCost;
                    m_GCosts[pE->getTo()] = GCost;

                    pq.insert(pE->getTo());

                    m_SearchFrontier[pE->getTo()] = pE;    
                }else if((GCost < m_GCosts[pE->getTo()]) && m_ShortesPath[pE->getTo()] == nullptr ){
                    //if this node is already on the frontier but the cost to get here this way
                    //is cheaper than has benn found previously, update the node costs and frontier
                    m_FCosts[pE->getTo()] = GCost + HCost;
                    m_GCosts[pE->getTo()] = GCost;

                    pq.ChangePriority(pE->getTo()); //CREAR ESTA FUNCION

                    m_SearchFrontier[pE->getTo()] = pE;
                }
            }
        }
    }

    //Getters
    std::vector<const Edge*> getSPT() const;
    
    std::list<int> getPathToTarget() const {
        std::list<int> path;

        //just return an empty path if no target or no path found
        if (m_Target < 0)  return path;    

        int nd = m_Target;

        path.push_front(nd);
            
        while ((nd != m_Source) && (m_ShortesPath[nd] != 0))
        {
            nd = m_ShortesPath[nd]->getFrom();

            path.push_front(nd);
        }

        return path;
    }

    double getCostToTarget();

};

struct Heuristic_Euclidian{

public: 

    explicit Heuristic_Euclidian() = default;

    template <class graph_type>
    static double Calculate(const graph_type& graph,int node1,int node2){
        return vec3DDistance(graph.getNode(node1).getPos(),graph.getNode(node2).getPos());
    }
};