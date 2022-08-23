
#include "EModelo.hpp"
#include "RMalla.hpp"
#include "RTextura.hpp"
//#include "RShader.hpp" 

EModelo::EModelo (RMalla *m, RTextura *t): malla(m), textura(t) {}

EModelo::~EModelo () {}

void EModelo::cargarModelo (const char* f) {
    malla->cargarFichero(f);
}

void EModelo::dibujar (glm::mat4x4 mat, unsigned int shader) {
    //std::cout << "Entro en el dibujar de entidad modelo" << std::endl;
    int model = glGetUniformLocation(shader, "model");
    //std::cout << "Int matriz model = " << model << std::endl;
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(mat));

    unsigned int i = 0;

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

    /////////////

    malla->dibujar(shader);
}
