#pragma once

#include <vector>

class RTextura;
//class RShader;

class Malla
{
public:
    
    Malla(std::vector<float> verts, std::vector<float> norms, std::vector<float> coord, std::vector<unsigned int> ind, RTextura *c, RTextura *h, RTextura *m, RTextura *n, RTextura *r);
    ~Malla();

    /*std::string getNombre ();
    void setNombre (std::string c);*/

    void dibujar(unsigned int shader);

     
private:
    std::vector<float> vertices;
    std::vector<float> normales;
    std::vector<float> coordtex;
    std::vector<unsigned int> indices;

    RTextura *diffuse;
    RTextura *height;
    RTextura *metalness;
    RTextura *normal;
    RTextura *roughness;

    unsigned int VAO, VBOV, VBOC, VBON, EBO;
    void setupMalla();
};
