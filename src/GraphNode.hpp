#pragma once 

#include <vec3.hpp>

enum {
    invalid_node_index = -1
};

//Base Class
struct GraphNode{

protected:
    //Every Node has an index. A valid index >= 0
    int m_Index;

public:

    GraphNode(int idx) : m_Index(idx){}

    const int getIndex() const { return m_Index;};
    void setIndex(int NewIndex) { m_Index = NewIndex; };   
};


template <class extra_info = void*>
struct NavGraphNode : public GraphNode{
    
protected:
//the node's position 
glm::vec3 m_vPosition;

extra_info m_ExtraInfo;

public:
    NavGraphNode() : m_ExtraInfo(extra_info()){}

    NavGraphNode(int idx, glm::vec3 pos) : GraphNode(idx),m_vPosition(pos),m_ExtraInfo(extra_info()){}

    virtual ~NavGraphNode(){}

    const glm::vec3 getPosition() const { return m_vPosition;};
    void setPosition(glm::vec3 newPos) { m_vPosition = newPos; };

    const extra_info getExtraInfo() const { return m_ExtraInfo; };

    void setExtraInfo(extra_info info ) { m_ExtraInfo = info; };
};

struct GraphEdge {

protected: 
    //An edge connects two nodes;
    int m_iFrom;
    int m_iTo;

    //the cost of transversing the edge
    double m_dCost;

public:
    GraphEdge(int from,int to,double cost) : m_dCost(cost),m_iFrom(from),m_iTo(to){}

    GraphEdge(int from,int to) : m_dCost(1.0),m_iFrom(from),m_iTo(to) {}

    GraphEdge():m_dCost(1.0),m_iFrom(invalid_node_index),m_iTo(invalid_node_index){}

    virtual ~GraphEdge(){}

    const int getFrom()const { return m_iFrom; };
    void SetFrom(int NewIndex) { m_iFrom = NewIndex; };

    const int getTo()const { return m_iTo; };
    void SetTo(int NewIndex) { m_iTo = NewIndex; };
    
    const double getCost()const { return  m_dCost; };
    void SetCost(double NewCost) { m_dCost = NewCost; };       
};  