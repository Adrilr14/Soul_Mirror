//#pragma once
//
//#include <vec3.hpp>
//#include <vector>
//#include <list>
//#include <stdlib.h>
//#include <algorithm>
//#include <iostream>
//
//
//struct Node {
//
//    Node(int px,int py,int pTipo,Node* pObjetivo) : posx(px),posy(py){
//        posx = px;
//        posy = py;
//
//        tipo = pTipo;
//        
//
//        if(pObjetivo != nullptr){
//            Heuristica = abs(this->posx - pObjetivo->posx) + abs(this->posy - pObjetivo->posy);
//        }
//    }
//
//    const int getPuntaje() const { return puntaje; };
//    const int getX() const { return posx; };
//    const int getY() const { return posy; };
//    const int getTipo() const { return tipo; };
//    int setAnterior(Node* pAnterior) { anterior = pAnterior;};
//
//    void CalculaCosto(){
//        if(anterior == nullptr){
//            distancia = 0;
//        }else{
//            distancia =  anterior->distancia + 1;
//            puntaje = distancia + Heuristica;
//        }
//    }
//
//private:
//    int distancia {0};
//    int Heuristica {0};
//    int puntaje {0};
//    int posx {0};
//    int posy {0};       
//    Node* anterior {nullptr};
//    
//    int tipo;
//};
//
//struct Mapa{
//    
//    Mapa(){
//        int destinoX = 10;
//        int destinoY = 10;
//        
//
//        objetivo = new Node(destinoX,destinoY,0,nullptr);
//        for (int i = 0; i < columna; i++){
//            for (int j = 0; j < fila; j++){
//
//                *mapaNodos[j,i] = new Node(j,i,mapa[j][i],objetivo);
//            }
//        } 
//
//        mapaNodos[destinoX][destinoY] = objetivo;
//      
//        AStar();
//    }
//
//    void AStar(){
//        
//        Node* actual = nullptr;
//        int inicioX = 2;
//        int inicioY = 1;
//        abierta.push_back(mapaNodos[inicioX][inicioY]);
//     
//        while(abierta.size() != 0){
//            Node* lessP = lessPuntaje();
//            if(lessP != nullptr){ 
//                if(lessP->getX() == objetivo->getX() && lessP->getY() == objetivo->getY()){
//                    //Ya hemos llegado
//                    break;
//                }else{
//                    abierta.remove(lessP);
//                    cerrada.push_back(lessP);
//
//                    //verificamos los nodos adyacentes  
//                    for(int i = lessP->getX()-1; i <= lessP->getX()+1;i++){
//                        for(int j = lessP->getY()-1; j <= lessP->getY()+1;j++){
//                            Node* current = mapaNodos[tFila(fila)][tColumna(columna)];
//                            auto ab =std::find(abierta.begin(),abierta.end(),current);
//                            auto ce =std::find(cerrada.begin(),cerrada.end(),current);
//                            if(ab != abierta.end() && ce != cerrada.end() && current->getTipo() != 1){
//                                mapaNodos[tFila(fila)][tColumna(columna)]->setAnterior(lessP);
//                                mapaNodos[tFila(fila)][tColumna(columna)]->CalculaCosto();
//
//                                abierta.push_back(mapaNodos[tFila(fila)][tColumna(columna)]);
//                            }
//                        
//                        }
//                    }
//                }
//            
//           }
//        }
//    }
//
//    int tColumna(int pColumna){
//        if(pColumna < 0 ){
//            return 0;
//        }
//        if(pColumna >= 0){
//            return columna-1;
//        }
//
//        return pColumna;
//    }
//
//    int tFila(int pFila){
//        if(pFila < 0 ){
//            return 0;
//        }
//        if(pFila >= 0){
//            return fila-1;
//        }
//
//        return pFila;
//    }
//
//    Node* lessPuntaje(){
//        Node* p = nullptr;
//        int puntaje = 99999;
//        for ( auto& node : abierta){
//            if(puntaje < node->getPuntaje()){
//                puntaje = node->getPuntaje();
//                p = node;
//            } 
//        }
//        return p;
//    }
//
//private:
//    int mapa [11][11]  = {
//        {1,1,0,0,0,0,0,0,1,0},
//        {1,1,0,0,0,0,0,0,1,0},
//        {0,0,0,0,0,0,0,0,0,0},
//        {1,0,0,1,1,1,1,1,1,0},
//        {0,0,0,0,0,1,0,1,0,0},
//        {0,0,0,0,0,0,0,0,1,0},
//        {0,0,1,0,0,0,0,1,0,0},
//        {0,1,1,0,0,0,0,0,0,0},
//        {0,0,1,0,0,0,0,1,1,1},
//        {0,0,0,0,0,0,0,0,0,0}
//    };
//
//    Node* mapaNodos[11][11];
//    int fila {11};
//    int columna {11};
//    Node* objetivo {nullptr};
//    std::list<Node*> abierta;
//    std::list<Node*> cerrada;
//    
//};
//