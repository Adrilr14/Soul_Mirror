#pragma once

#include "Entidad.hpp"

class RFuente;

/*struct Vertex {
    // position
    glm::vec2 position;
    // texCoords
    glm::vec2 texCoords;
};*/


class Text2D : public Entidad {
    public:
        Text2D(const char * t, RFuente* font, glm::vec4 color_, int x, int y, int s, int width_, int height_);
        ~Text2D();

        void dibujar(glm::mat4x4 mat, unsigned int shader) override;

        RFuente* getTexture(){ return fuente;};
        void setTexture(RFuente* t) { fuente = t;};

        void setText(const char *t) { text = t;};
        const char* getText()       { return text;};

        void setPosX(int x) { posX = x;};
        int  getposX()      { return posX;};
        void setPosY(int y) { posY = y;};
        int  getposY()      { return posY;};

        void setsize(int s) { size = s;};
        int  getsize()      { return size;};

    private:
        RFuente* fuente { nullptr };
        glm::vec4 color {0.f};

        unsigned int Text2DVertexBufferID {0};
        unsigned int Text2DUVBufferID {0};

        //unsigned int VBO {0}, VAO {0}, EBO {0};
        
        const char * text {""};

        int width, height;
        int posX, posY;

        int size;
                
};
