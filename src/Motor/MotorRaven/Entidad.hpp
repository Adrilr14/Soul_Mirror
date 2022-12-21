#pragma once

// GLM library
#include "vec3.hpp" // glm::vec3
#include "vec4.hpp" // glm::vec4
#include "mat4x4.hpp" // glm::mat4
#include <ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include "gtc/type_ptr.hpp"

// GLEW library
#define GLEW_STATIC
#include <glew.h>

//class RShader;

class Entidad
{
public:
    Entidad(); 
    ~Entidad();

    virtual void dibujar(glm::mat4x4 mat, unsigned int shader);
     
private:
    
};