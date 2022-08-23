
#include "RTextura.hpp"
#include "SOIL.h"

// GLEW library
#define GLEW_STATIC
#include <glew.h>

RTextura::RTextura(std::string fichero) : Recurso(fichero),path(fichero) {}

/*void RTextura::setPath (const char *path) {
    this->setNombre(path);
    cargarFichero(this->getNombre().c_str());
}*/

/*RTextura::~RTextura() {
    glDeleteTextures(1, &id);
}*/

RTextura::~RTextura() {
    glDeleteTextures(1, &idDiffuse);
    glDeleteTextures(1, &idHeight);
    glDeleteTextures(1, &idMetallic);
    glDeleteTextures(1, &idNormal);
    glDeleteTextures(1, &idRoughness);
}

/*unsigned int RTextura::getId (){
    return id;
}*/

unsigned int RTextura::getIdDiffuse() {
    return idDiffuse;
}

unsigned int RTextura::getIdHeight() {
    return idHeight;
}

unsigned int RTextura::getIdMetallic() {
    return idMetallic;
}

unsigned int RTextura::getIdNormal() {
    return idNormal;
}

unsigned int RTextura::getIdRoughness() {
    return idRoughness;
}

void RTextura::cargarFichero (const char* path) {

    unsigned int textureID;

    std::string ficheroDiffuse = path;
    ficheroDiffuse += "_BaseColor.png";

    std::string ficheroHeight = path;
    ficheroHeight += "_Height.png";

    std::string ficheroMetallic = path;
    ficheroMetallic += "_Metallic.png";

    std::string ficheroNormal = path;
    ficheroNormal += "_Normal.png";

    std::string ficheroRoughness = path;
    ficheroRoughness += "_Roughness.png";

    const char *ficheros[5];
    ficheros[0] = ficheroDiffuse.c_str();
    ficheros[1] = ficheroHeight.c_str();
    ficheros[2] = ficheroMetallic.c_str();
    ficheros[3] = ficheroNormal.c_str();
    ficheros[4] = ficheroRoughness.c_str();

    for (unsigned int x = 0; x < 5; x++)
    {
        glGenTextures(1, &textureID);

        int nrComponents, width, height;

        unsigned char *data = SOIL_load_image(ficheros[x], &width, &height, &nrComponents, SOIL_LOAD_AUTO);

        widthText = width;
        heightText = height;

        if (data)
        {
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
            
            GLenum format = GL_RGBA;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            SOIL_free_image_data(data);
        }
        else
        {
            //std::cout << "Texture failed to load at path: " << path << std::endl;
            SOIL_free_image_data(data);
        }

        if(x == 0) {idDiffuse = textureID;}
        if(x == 1) {idHeight = textureID;}
        if(x == 2) {idMetallic = textureID;}
        if(x == 3) {idNormal = textureID;}
        if(x == 4) {idRoughness = textureID;}
        //id = textureID;
    }
    
    
}
