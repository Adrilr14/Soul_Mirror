#include "Billboard.hpp"
#include "RImagen.hpp"
#include "Entidad.hpp"

#include <iostream>

Billboard::Billboard(RImagen* imagen_, float width_, float height_) : imagen(imagen_), width(width_), height(height_) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &vertexBuffer);
}

void Billboard::dibujar(glm::mat4x4 mat, unsigned int shaderID){
    if(imagen != nullptr){
        std::cout << "Dibujo billboard" << std::endl;
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glUniform1f(glGetUniformLocation(shaderID, "width"), width);
        glUniform1f(glGetUniformLocation(shaderID, "height"), height);
        
        // active proper texture unit before binding
        glActiveTexture(GL_TEXTURE0); 
        // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shaderID, "ourTexture"), 0);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, imagen->getId());

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(position), &position[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 0, (void*)0);    
        glEnableVertexAttribArray(0);
        glDrawArrays(GL_POINTS, 0, 1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        //glDisableVertexAttribArray(0);

    }
}