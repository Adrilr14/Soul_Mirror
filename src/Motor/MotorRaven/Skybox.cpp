#include "Skybox.hpp"
#include "SOIL.h"
#include "vector"

#include <iostream>

Skybox::Skybox(){
    
}

Skybox::Skybox(RMalla *skybox_, const char* right, const char* left, const char* top, const char* bottom, const char* front, const char* back) : skybox(skybox_){
    if(skybox)
    {
        vertex = skybox->getVertexSkybox();
        ind = skybox->getIndicesSkybox();

        std::vector<const char*> textures_faces{
            right,
            left,
            top,
            bottom,
            front,
            back
        };

        glGenTextures(1, &skyboxID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxID);

        int width, height, nrComponents;
        unsigned char *data;  
        
        // Flip the image on the Y axis
        //int x,j;
        //for( j = 0; j*2 < height; ++j )
        //{
        //    int index1 = j * width * nrComponents;
        //    int index2 = (height - 1 - j) * width * nrComponents;
        //    for( x = width * nrComponents; x > 0; --x )
        //    {
        //        GLubyte temp = data[index1];
        //        data[index1] = data[index2];
        //        data[index2] = temp;
        //        ++index1;
        //        ++index2;
        //    }
        //}
        
        for(GLuint i = 0; i < textures_faces.size(); i++)
        {
            data = SOIL_load_image(textures_faces[i], &width, &height, &nrComponents, SOIL_LOAD_AUTO);
            
            if(data)
            {
                GLenum format = GL_RGBA;
                if (nrComponents == 1)
                    format = GL_RED;
                else if (nrComponents == 3)
                    format = GL_RGB;
                else if (nrComponents == 4)
                    format = GL_RGBA;

                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE); 
                glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);	
                glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
                glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);

                SOIL_free_image_data(data);

                //std::cout << "Cubemap texture readed" << std::endl;
            }
            else
            {
                //std::cout << "Cubemap texture failed to load at path: " << textures_faces[i] << std::endl;

                SOIL_free_image_data(data);
            }
        }
        

        // skybox VAO
        /*glGenVertexArrays(1, &skyboxVAO);
        glGenBuffers(1, &skyboxVBO);
        glBindVertexArray(skyboxVAO);
        glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);*/

        glGenVertexArrays(1, &skyboxVAO);
        glGenBuffers(1, &skyboxVBO);
        glGenBuffers(1, &skyboxEBO);

        // Seleccion del Vertex Array porque vamos a trabajar con el VBO (el VBO esta en el VAO).
        glBindVertexArray(skyboxVAO);
        glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);

        //Como en el struct Vertex esta todo seguido podemos pasarselo entero al glBufferData
        // Leemos la informacion de los triangulos.
        glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(Vertex), &vertex[0], GL_STATIC_DRAW);

        // Leemos la informacion de los indices.
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind.size() * sizeof(unsigned int), &ind[0], GL_STATIC_DRAW);

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
        glDrawElements(GL_TRIANGLES, sizeof(ind), GL_UNSIGNED_SHORT, (void*)0);
    }
    
}



void Skybox::dibujar(glm::mat4x4 mat, unsigned int shader) {

    int model = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(mat));

    glBindVertexArray(skyboxVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxID);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthMask(GL_TRUE);
        //std::cout << "entra en el dibujar de skybox" << std::endl;
    // ... draw rest of the scene

}

void Skybox::DrawDepthMap(unsigned int shaderID){

}