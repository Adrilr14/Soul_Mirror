#include "Malla.hpp"
//#include "RShader.hpp"
#include "RTextura.hpp"
#include "glm/glm.hpp"
//#include "glad/glad.h"
#include <glew.h>


Malla::Malla(std::vector<float> verts, std::vector<float> norms, std::vector<float> coord, std::vector<unsigned int> ind, RTextura *c, RTextura *h, RTextura *m, RTextura *n, RTextura *r) :
vertices(verts), normales(norms), coordtex(coord), indices(ind), diffuse(c), height(h), metalness(m), normal(n), roughness(r) {
    setupMalla();   
}

Malla::~Malla() {}

void Malla::setupMalla() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBOV);
    glGenBuffers(2, &VBON);
    glGenBuffers(3, &VBOC);

    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
   

   

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);


    //POSICIÓN DE LOS VERTICES
    glBindBuffer(GL_ARRAY_BUFFER, VBOV);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * sizeof(indices), &vertices[0], GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(indices), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBON);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normales) * sizeof(indices), &normales[0], GL_STATIC_DRAW);
   
    glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE,sizeof(indices), (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, VBOC);
    glBufferData(GL_ARRAY_BUFFER, sizeof(coordtex) * sizeof(indices), &coordtex[0], GL_STATIC_DRAW);
    
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,sizeof(indices), (void*)0);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}


void Malla::dibujar (unsigned int shader) {
   // bind appropriate textures
    /*unsigned int diffuseNr = 1;
    unsigned int heightNr = 1;
    unsigned int metalnessNr = 1;
    unsigned int normalNr = 1;
    unsigned int roughnessNr = 1;
    std::string name;*/

    unsigned int i = 0;


    ///TEXTURA///
    if(diffuse != nullptr)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        //name = "texture_diffuse";

        // now set the sampler to the correct texture unit
        //glUniform1i(glGetUniformLocation(shader.ID, (name + std::to_string(diffuseNr)).c_str()), i);
        //glUniform1i(glGetUniformLocation(shader->ID, "texture_diffuse"), i);
        glUniform1i(glGetUniformLocation(shader, "texture_diffuse"), i);

        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, diffuse->getId());

        i++;
    }
    
    if(height != nullptr)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        //name = "texture_height";

        // now set the sampler to the correct texture unit
        //glUniform1i(glGetUniformLocation(shader.ID, (name + std::to_string(heightNr)).c_str()), i);
        //glUniform1i(glGetUniformLocation(shader->ID, "texture_height"), i);
        glUniform1i(glGetUniformLocation(shader, "texture_height"), i);

        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, height->getId());

        i++;
    }

    if(metalness != nullptr)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        //name = "texture_height";

        // now set the sampler to the correct texture unit
        //glUniform1i(glGetUniformLocation(shader.ID, (name + std::to_string(heightNr)).c_str()), i);
        //glUniform1i(glGetUniformLocation(shader->ID, "texture_metalness"), i);
        glUniform1i(glGetUniformLocation(shader, "texture_metalness"), i);

        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, metalness->getId());

        i++;
    }

    if(normal != nullptr)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        //name = "texture_height";

        // now set the sampler to the correct texture unit
        //glUniform1i(glGetUniformLocation(shader.ID, (name + std::to_string(heightNr)).c_str()), i);
        //glUniform1i(glGetUniformLocation(shader->ID, "texture_normal"), i);
        glUniform1i(glGetUniformLocation(shader, "texture_normal"), i);

        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, normal->getId());

        i++;
    }

    if(roughness != nullptr)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        //name = "texture_height";

        // now set the sampler to the correct texture unit
        //glUniform1i(glGetUniformLocation(shader.ID, (name + std::to_string(heightNr)).c_str()), i);
        //glUniform1i(glGetUniformLocation(shader->ID, "texture_roughness"), i);
        glUniform1i(glGetUniformLocation(shader, "texture_roughness"), i);

        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, roughness->getId());

        i++;
    }
    /////////////

    ///MALLA///
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);

}

