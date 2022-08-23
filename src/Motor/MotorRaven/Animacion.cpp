
#include "Animacion.hpp"
#include "RMalla.hpp"
#include "RTextura.hpp"

// GLFW library
#include <glfw3.h>
#define GLFW_INCLUDE_NONE

Animacion::Animacion (std::vector<RMalla*> mallas_, int fps_, RTextura *t): mallas(mallas_), nMalla(0),  before(0.0), fps(fps_), end(false), textura(t){}

Animacion::~Animacion () {}

//void Animacion::cargarModelo (const char* f) {
//    malla->cargarFichero(f);
//}

void Animacion::dibujar (glm::mat4x4 mat, unsigned int shader) {
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

    mallas[nMalla]->dibujar(shader);

    // Comprobamos si estamos en la última malla para poner a true el final de la animación
    if(nMalla == mallas.size()-1)
    {
        end = true;
    }

    // Comprobamos que haya pasado 1/8 de segundo para cambiar de malla
    double now = glfwGetTime();
    double time = 1.0/(double)fps;
    //std::cout << "Before = " << before << std::endl;
    //std::cout << "Now = " << now << std::endl;
    //std::cout << "Time = " << time << std::endl;
    //std::cout << std::endl;
    if (now - before >= time)
    {
        before = now;
        nMalla++;
    }

    // Si el número de malla es mayor o igual que el tamaño del vector lo reiniciamos a 0
    if(nMalla >= mallas.size())
    {
        nMalla = 0;
        end = false;
    }
    //std::cout << "Numero de malla = " << nMalla << std::endl;
}
