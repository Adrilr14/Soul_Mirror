
#include "RTextura.hpp"
#include "SOIL.h"

// GLEW library
#define GLEW_STATIC
#include <glew.h>

RTextura::RTextura(std::string fichero) : Recurso(fichero) {}

void RTextura::setPath (const char *fichero) {
    this->setNombre(fichero);
    cargarFichero(this->getNombre().c_str());
}

RTextura::~RTextura() {
    glDeleteTextures(1, &id);
}

unsigned int RTextura::getId (){
    return id;
}

void RTextura::cargarFichero (const char* fichero) {

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int nrComponents, width, height;

    unsigned char *data = SOIL_load_image(fichero, &width, &height, &nrComponents, SOIL_LOAD_AUTO);
    widthText = width;
    heightText = height;

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

    if (data)
    {
        GLenum format;
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
        std::cout << "Texture failed to load at path: " << fichero << std::endl;
        SOIL_free_image_data(data);
    }

    id = textureID;
}
