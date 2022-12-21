#include "Skybox.hpp"
#include "SOIL.h"
#include "vector"

#include <iostream>

Skybox::Skybox(){
    
}

Skybox::Skybox(const char* right, const char* left, const char* top, const char* bottom, const char* front, const char* back){
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
    int i,j;
    for( j = 0; j*2 < height; ++j )
    {
        int index1 = j * width * nrComponents;
        int index2 = (height - 1 - j) * width * nrComponents;
        for( i = width * nrComponents; i > 0; --i )
        {
            GLubyte temp = data[index1];
            data[index1] = data[index2];
            data[index2] = temp;
            ++index1;
            ++index2;
        }
    }
    
    for(GLuint i = 0; i < textures_faces.size(); i++)
    {
        data = SOIL_load_image(textures_faces[i], &width, &height, &nrComponents, SOIL_LOAD_AUTO);
        
        if(data){
            glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            SOIL_free_image_data(data);
        }else{
            std::cout << "Cubemap texture failed to load at path: " << textures_faces[i] << std::endl;

            SOIL_free_image_data(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE); 

    // skybox VAO
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}



void Skybox::dibujar(glm::mat4x4 mat, unsigned int shader) {
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