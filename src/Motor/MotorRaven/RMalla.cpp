
#include "RMalla.hpp"
#include "RTextura.hpp"
#include "Malla.hpp"

// OBJ-Loader library
#include "OBJ_Loader.h"

RMalla::RMalla (std::string path, RTextura *t) 
               : Recurso(path), textura(t) {}


RMalla::~RMalla() {}

void RMalla::cargarFichero (const char* fichero) {

    objl::Loader loader;
    bool loaded = loader.LoadFile(fichero);

    if(!loaded || loader.LoadedMeshes.size() == 0){
        std::cout << "ERROR:OBJ-Loader::Error al cargar el fichero" << std::endl;
        return;
    }

    std::vector<objl::Mesh> node = loader.LoadedMeshes;
    glm::vec3 vert;
    glm::vec3 norm;
    glm::vec2 coordt;
    std::vector<Vertex> vertex;
    std::vector<unsigned int> ind;
    std::vector<RTextura> text;
    Vertex vertices;

    for(unsigned int i = 0; i < node.size(); i++){
        objl::Mesh mesh = node[i];

        for(unsigned int i = 0; i < mesh.Vertices.size(); i++)
        {
            vert.x = mesh.Vertices[i].Position.X;
            vert.y = mesh.Vertices[i].Position.Y;
            vert.z = mesh.Vertices[i].Position.Z;
            vertices.position = vert;

            norm.x = mesh.Vertices[i].Normal.X;
            norm.y = mesh.Vertices[i].Normal.Y;
            norm.z = mesh.Vertices[i].Normal.Z;
            vertices.normal = norm;

            coordt.x = mesh.Vertices[i].TextureCoordinate.X;
            coordt.y = mesh.Vertices[i].TextureCoordinate.Y;
            vertices.texCoords = coordt;

            vertex.push_back(vertices);

        }

        for(unsigned int i = 0; i < mesh.Indices.size(); i++){
            ind.push_back(mesh.Indices[i]);
        }

        mallas.push_back(Malla(vertex, ind, textura));
    }
}

void RMalla::dibujar (unsigned int shader) {
    for(unsigned int i = 0; i < mallas.size(); i++){
        mallas[i].dibujar(shader);
    }
}

/*void RMalla::cargarFichero (const char* fichero) {

    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(fichero, aiProcess_Triangulate | aiProcess_FlipUVs);
    
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        std::cout << "ERROR:ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    aiNode *node = scene->mRootNode;
    glm::vec3 vert;
    glm::vec3 norm;
    glm::vec2 coordt;
    std::vector<Vertex> vertex;
    std::vector<unsigned int> ind;
    std::vector<RTextura> text;
    Vertex vertices;

    std::cout << "Número de mallas = " << node->mNumMeshes << std::endl;
    for(unsigned int i = 0; i < node->mNumMeshes; i++){
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];

        for(unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            vert.x = mesh->mVertices[i].x;
            vert.y = mesh->mVertices[i].y;
            vert.z = mesh->mVertices[i].z;
            vertices.position = vert;

            norm.x = mesh->mNormals[i].x;
            norm.y = mesh->mNormals[i].y;
            norm.z = mesh->mNormals[i].z;
            vertices.normal = norm;

            coordt.x = mesh->mTextureCoords[0][i].x;
            coordt.y = mesh->mTextureCoords[0][i].y;
            vertices.texCoords = coordt;

            vertex.push_back(vertices);

        }

        for(unsigned int i = 0; i < mesh ->mNumFaces; i++){
            aiFace face = mesh->mFaces[i];
            for(unsigned int j = 0; j < face.mNumIndices; j++){
                ind.push_back(face.mIndices[j]);
            }
        }

        mallas.push_back(Malla(vertex, ind, textura));
    }
}*/
