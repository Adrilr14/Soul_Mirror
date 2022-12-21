#pragma once

#include "Entidad.hpp"

class RImagen;

class Billboard : public Entidad {
    public:
        Billboard(RImagen* image_, float width_, float height_);
        ~Billboard() {};

        void dibujar(glm::mat4x4 mat, unsigned int shader) override;
        void DrawDepthMap(unsigned int shaderID) {};

        RImagen* getTexture(){ return imagen;};
        
        void setTexture(RImagen* t) { imagen = t;};

    private:
        RImagen* imagen = nullptr;
        //Placeholder para mandar algo por el VAO si no no dibuja
        float position[6] = {
            1.0, 1.0, 1.0,
            1.0, 1.0, 1.0
        };
        GLuint vertexBuffer {0}, VAO {0};
        float width {0}, height {0};
                
};
