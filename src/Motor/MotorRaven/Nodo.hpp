#pragma once

#include "Entidad.hpp"
#include "vector"

// GLM library
#include "vec3.hpp" // glm::vec3
#include "vec4.hpp" // glm::vec4
#include "mat4x4.hpp" // glm::mat4
#include <ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale

class Nodo
{
public:
    Nodo (std::size_t n, Entidad *ent, Nodo *p); 
    ~Nodo ();

    void añadirHijo (Nodo *h);
    void borrarHijo (Nodo *h);
    void clear ();

    std::size_t getID ();
    Nodo *getNodoFromID (std::size_t n);

    void setMatrizTransf (glm::mat4x4 mat);
    glm::mat4x4 getMatrizTransf ();

    void setEntidad (Entidad *ent);
    Entidad *getEntidad ();

    std::vector<Nodo*> getHijos ();
    Nodo *getHijo (Nodo *h);

    void setPadre (Nodo *p);
    Nodo *getPadre ();

    void setTraslacion (glm::vec3 tras);
    glm::vec3 getTraslacion ();

    void setRotacion (glm::vec3 rot);
    glm::vec3 getRotacion ();

    void setEscalado (glm::vec3 esc);
    glm::vec3 getEscalado ();

    glm::vec3 getTraslacionGlobal() const;
    glm::vec3 getRotacionGlobal() const;
    glm::vec3 getEscaladoGlobal() const;

    void trasladar (glm::vec3 tras);
    void rotar (glm::vec3 rot);
    void escalar (glm::vec3 esc);

    void recorrer (glm::mat4x4 matAcum, unsigned int shader, bool actualizar); 

    void setActualizarMatriz (bool act);

private:
    std::size_t id;
    glm::mat4x4 matrizTransf;
    Entidad *entidad;
    std::vector <Nodo*> hijos;
    Nodo *padre;
    glm::vec3 traslacion;
    glm::vec3 rotacion;
    glm::vec3 escalado;
    bool actualizarMatriz;
};
