#include "RFuente.hpp"
#include "SOIL.h"

// GLEW library
#define GLEW_STATIC
#include <glew.h>

RFuente::RFuente(std::string fichero) : Recurso(fichero) {}

RFuente::~RFuente() {
    glDeleteTextures(1, &id);
}

unsigned int RFuente::getId (){
    return id;
}

void RFuente::cargarFichero (const char* path) {

    unsigned int textureID;

    glGenTextures(1, &textureID);

    int nrComponents, width, height;

    unsigned char *data = SOIL_load_image(path, &width, &height, &nrComponents, SOIL_LOAD_AUTO);

    widthImg = width;
    heightImg = height;

    if (data)
    {
        GLenum format = GL_RGBA;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        //SOIL_create_OGL_texture(data, width, height, nrComponents, 0, SOIL_FLAG_MULTIPLY_ALPHA);

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        SOIL_free_image_data(data);
    }
    else
    {
        //std::cout << "Texture failed to load at path: " << path << std::endl;
        SOIL_free_image_data(data);
    }

    id = textureID;
    
}
