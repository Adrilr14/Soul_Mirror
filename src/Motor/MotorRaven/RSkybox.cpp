/*#include "RSkybox.hpp"

// OBJ-Loader library
#include "OBJ_Loader.h"

RSkybox::RSkybox (std::string path) : Recurso(path){}


RSkybox::~RSkybox() {}

void RSkybox::cargarFichero (const char* fichero) {

    objl::Loader loader;
    bool loaded = loader.LoadFile(fichero);

    if(!loaded || loader.LoadedMeshes.size() == 0){
        std::cout << "ERROR:OBJ-Loader::Error al cargar el fichero" << std::endl;
        return;
    }

    std::vector<objl::Mesh> node = loader.LoadedMeshes;
    glm::vec3 vert;
    Vertex vertices;

    for(unsigned int i = 0; i < node.size(); i++){
        objl::Mesh mesh = node[i];

        for(unsigned int i = 0; i < mesh.Vertices.size(); i++)
        {
            vert.x = mesh.Vertices[i].Position.X;
            vert.y = mesh.Vertices[i].Position.Y;
            vert.z = mesh.Vertices[i].Position.Z;
            vertices.position = vert;

            vertex.push_back(vertices);

        }

        for(unsigned int i = 0; i < mesh.Indices.size(); i++){
            ind.push_back(mesh.Indices[i]);
        }
    }
}

void RSkybox::dibujar (unsigned int shader) {}*/
