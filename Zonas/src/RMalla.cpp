
#include "RMalla.hpp"
#include "RTextura.hpp"
#include "Malla.hpp"

RMalla::RMalla (std::string path, RTextura *c, RTextura *h, RTextura *m, RTextura *n, RTextura *r) 
               : Recurso(path), diffuse(c), height(h), metalness(m), normal(n), roughness(r) {}


RMalla::~RMalla() {}

void RMalla::cargarFichero (const char* fichero) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(fichero, aiProcess_Triangulate | aiProcess_FlipUVs);
    
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        std::cout << "ERROR:ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }
    procesarNodo(scene->mRootNode, scene);
}

void RMalla::procesarNodo(aiNode *node, const  aiScene *scene){
    for(unsigned int i = 0; i<node->mNumMeshes; i++){
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        mallas.push_back(procesarMalla(mesh,scene));
    }
    
    for(unsigned int i = 0; i< node->mNumChildren; i++){
        procesarNodo(node->mChildren[i], scene);
    }
}


Malla RMalla::procesarMalla(aiMesh *mesh, const aiScene *scene){
    std::vector<float> vert;
    std::vector<float> norm;
    std::vector<float> coordt;
    std::vector<unsigned int> ind;
    std::vector<RTextura> text;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++){
        vert.push_back(mesh->mVertices[i].x);
        vert.push_back(mesh->mVertices[i].x);
        vert.push_back(mesh->mVertices[i].x);

        if(mesh->HasNormals()){
            norm.push_back(mesh->mNormals[i].x);
            norm.push_back(mesh->mNormals[i].y);
            norm.push_back(mesh->mNormals[i].z);
        }
        if(mesh->mTextureCoords[0]){
            coordt.push_back(mesh->mTextureCoords[0][i].x);
            coordt.push_back(mesh->mTextureCoords[0][i].y);
            coordt.push_back(mesh->mTextureCoords[0][i].z);
        }else{
            coordt.push_back(0.0f);
            coordt.push_back(0.0f);
        }
    }

    for(unsigned int i = 0; i < mesh ->mNumFaces; i++){
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++){
            ind.push_back(face.mIndices[j]);
        }
    }
    return Malla(vert, norm, coordt, ind, diffuse, height, metalness, normal, roughness);
}


void RMalla::dibujar (unsigned int shader) {
    for(unsigned int i = 0; i < mallas.size(); i++){
        mallas[i].dibujar(shader);
    }
}

