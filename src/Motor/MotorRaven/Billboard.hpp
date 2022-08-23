#pragma once

#include "Entidad.hpp"

class RImagen;

/*struct Vertex {
    // position
    glm::vec2 position;
    // texCoords
    glm::vec2 texCoords;
};*/


class Billboard : public Entidad {
    public:
        Billboard(RImagen* image_, int x, int y, int width_, int height_);
        ~Billboard();

        void dibujar(glm::mat4x4 mat, unsigned int shader) override;

        RImagen* getTexture(){ return imagen;};
        
        void setTexture(RImagen* t) { imagen = t;};

        void setPosX(int x) { posX = x;};
        int  getposX()      { return posX;};
        void setPosY(int y) { posY = y;};
        int  getposY()      { return posY;};

    private:
        RImagen* imagen = nullptr;

        unsigned int VBO {0}, VAO {0}, EBO {0};
        
        int width, height;
        int posX, posY;

        //Placeholder para mandar algo por el VAO si no no dibuja
        /*float position[6] = {
            1.0, 1.0, 1.0,
            1.0, 1.0, 1.0
        };*/
        //unsigned int vertexBuffer, UVBuffer, VAO;
        
                
};
