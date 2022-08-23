#include "NavMesh.hpp"
#include <fstream>
#include <sstream>  

std::vector<std::string> splitPattern3(const std::string_view s,const char* delimiter){
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

constexpr bool GraphNode::compareVec3D(float x,float y,float z){
    return vecPos.m_x == x && vecPos.m_y == y && vecPos.m_z == z; 
}

//--------------Funciones de NavMesh

NavMesh_t::~NavMesh_t() {
    m_graph.clear();
    m_repeats.clear();
}

bool NavMesh_t::Load(std::string pathToOpen){
    std::ifstream input(pathToOpen);
        if(input.is_open() == false){
            //Management errors
            return false;
        }

        NavMesh_t::~NavMesh_t();
        std::string line;
        int id {1};
        while(!input.eof()){ //Mientras sea disinto de end of file
            getline(input,line);
            if(line != ""){
                auto caracter = line[0]; //Solo necesitamos dos o el vertice o la cara
                if(caracter == 'v' || caracter == 'f'){
                    //Hacemos el split de los espacios " "
                    auto vector = splitPattern3(line," ");
                    if(caracter == 'v'){            
                        auto x = std::stof(vector[1]);auto y = std::stof(vector[2]); auto z = std::stof(vector[3]); 
                        bool proved = CompareIDNode(x,y,z,id);
                        if(proved == false){
                            //Significa que no esta aun asi que lo añadimos
                            m_graph.emplace_back(id,Vector3D{x,y,z});
                        }
                        id++;
                    }else if(caracter == 'f'){
                        //Ahora vamos a añadir los edges a cada arista
                        auto v1 = splitPattern3(vector[1],"/")[0];
                        auto v2 = splitPattern3(vector[2],"/")[0];
                        auto v3 = splitPattern3(vector[3],"/")[0];
                        AddBeforeRepeats(std::stoi(v1),std::stoi(v2),std::stoi(v3));
                    }
                }
            }
        }    
        return true;
}

void NavMesh_t::AddBeforeRepeats(int first, int second, int third){
    for (const auto& [key, value] : m_repeats) {
        for(int i = 0; i < value.size(); i++){
            if(first == value[i]){
                first = key;
            }else if(second == value[i]){
                second = key;
            }else if(third == value[i]){
                third = key;
            }
        }
    }

    for(unsigned int i = 0; i < m_graph.size(); i++){
        if(m_graph[i].idx == first){
            m_graph[i].edges.addNewArista(second);
        }else if(m_graph[i].idx == second){
            m_graph[i].edges.addNewArista(third);                
        }else if(m_graph[i].idx == third){
            m_graph[i].edges.addNewArista(first);
        }
    }
}

 bool NavMesh_t::CompareIDNode(float x,float y,float z, int idActual){
    for(unsigned int i = 0; i < m_graph.size(); i++){
        auto res = m_graph[i].compareVec3D(x,y,z);
        if(res){
            m_repeats[m_graph[i].idx].push_back(idActual);
            return true;
        }
    }
    return false;
}


GraphNode NavMesh_t::getNodoFromID(int id){
    for(unsigned int i = 0; i < m_graph.size(); i++){
        if(m_graph[i].idx == id){
            return m_graph[i];
        }
    }
    GraphNode automatico;
    return automatico;
}