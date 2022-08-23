#include "Malla.hpp"
//#include "RShader.hpp"
#include "RTextura.hpp"
//#include "glad/glad.h"
#include <glew.h>


Malla::Malla(std::vector<Vertex> vertices, std::vector<unsigned int> ind, RTextura *t) : vertex(vertices), indices(ind), textura(t)
{
    setupMalla();
}

Malla::~Malla() {}

void Malla::setupMalla() {

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Seleccion del Vertex Array porque vamos a trabajar con el VBO (el VBO esta en el VAO).
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //Como en el struct Vertex esta todo seguido podemos pasarselo entero al glBufferData
    // Leemos la informacion de los triangulos.
    glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), &vertex[0], GL_STATIC_DRAW);

    // Leemos la informacion de los indices.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texCoords));

    glBindVertexArray(0);
    glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_SHORT, (void*)0);
}


void Malla::dibujar (unsigned int shader) {

    /*unsigned int i = 0;

    ///TEXTURA///
    if(textura != nullptr)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding

        // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shader, "Material.Diffuse"), i);

        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, textura->getIdDiffuse());

        i++;
    
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding

        // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shader, "Material.Height"), i);

        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, textura->getIdHeight());

        i++;


        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding

        // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shader, "Material.Specular"), i);

        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, textura->getIdMetallic());

        i++;


        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding

        // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shader, "Material.Normal"), i);

        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, textura->getIdNormal());

        i++;


        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding

        // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shader, "Material.Roughness"), i);

        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, textura->getIdRoughness());

        i++;
    }

    // Put Shininess
    glUniform1f(glGetUniformLocation(shader, "Material.Shininess"), 8.f);

    /////////////*/

    ///MALLA///
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);

}

