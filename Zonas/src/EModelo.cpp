
#include "EModelo.hpp"
#include "RMalla.hpp"
//#include "RShader.hpp" 

EModelo::EModelo (RMalla *m): malla(m) {}

EModelo::~EModelo () {}

void EModelo::cargarModelo (const char* f) {
    malla->cargarFichero(f);
}

void EModelo::dibujar (glm::mat4x4 mat, unsigned int shader) {
    //std::cout << "Entro en el dibujar de entidad modelo" << std::endl;
    malla->dibujar(shader);
}
