#pragma once

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"
#include "shaders.h"
//#include "texturebuffer.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;
class Model {

    std::vector<Texture> textures_loaded;

    public:
        Model(const char *path) {
            std::cerr << "Loading model...\n";
            loadModel(path);
        }
        void Draw(Shader &shader) {
            for(unsigned int i = 0; i < meshes.size(); i++)
            meshes[i].Draw(shader);
        }  
    private:
        // model data
        std::vector<Mesh> meshes;
        std::string directory;

        void loadModel(std::string path) {
            Assimp::Importer import;
            cerr << "Importing scene...\n";
            const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);	
	
            if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
            {
                std::cout << "ASSIMP ERROR:" << import.GetErrorString() << std::endl;
                return;
            }
            directory = path.substr(0, path.find_last_of('/'));
            cerr << "Scene imported. Processing nodes and data...\n";
            processNode(scene->mRootNode, scene);
            cerr << "Data and nodes processed.\n";
        }

        void processNode(aiNode *node, const aiScene *scene) {
            cerr << "Processing meshes in scene...\n";
            for (unsigned int i = 0; i < node->mNumMeshes; i++) {
                aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
                meshes.push_back(processMesh(mesh, scene));
                //cerr << "Mesh returned successfully.\n";
            }
            cerr << "Meshes processed. Processing the nodes...\n";
            
            for (unsigned int i = 0; i < node->mNumChildren; i++) {
                processNode(node->mChildren[i], scene);
            }
        }  

        Mesh processMesh(aiMesh *mesh, const aiScene *scene) {
            std::vector<Vertex> vertices;
            std::vector<unsigned int> indices;
            std::vector<Texture> textures;

            //cerr << "VBO creation\n";
            for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
                Vertex vertex;
                //cerr << "Vertex copying\n";
                glm::vec3 vector; 
                vector.x = mesh->mVertices[i].x;
                vector.y = mesh->mVertices[i].y;
                vector.z = mesh->mVertices[i].z; 
                vertex.Position = vector;

                //cerr << "Normal copying\n";
                if (mesh->HasNormals()) {
                    vector.x = mesh->mNormals[i].x;
                    vector.y = mesh->mNormals[i].y;
                    vector.z = mesh->mNormals[i].z; 
                    vertex.Normal = vector;
                }
                //cerr << "Texture coordinates copying\n";
                if (mesh->mTextureCoords[0]) { // does the mesh contain texture coordinates?
                    glm::vec2 vec;
                    vec.x = mesh->mTextureCoords[0][i].x; 
                    vec.y = mesh->mTextureCoords[0][i].y;
                    vertex.TexCoords = vec;
                } else {
                    vertex.TexCoords = glm::vec2(0.0f);
                } 
                //cerr << "Pushing into vertices vector...\n";
                vertices.push_back(vertex);
            }

            //cerr << "EBO creation\n";
            // indices
            for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
                    aiFace face = mesh->mFaces[i];
                    for (unsigned int j = 0; j < face.mNumIndices; j++)
                        indices.push_back(face.mIndices[j]);
            }  
            cerr << "Texture creation\n";
            //// process material
            //cerr << "Material processing...\n";
            if(mesh->mMaterialIndex >= 0) {
                //cerr << "Mesh has material index.\n";
                aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
                std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
                //cerr << "Inserting diffuse textures...\n";
                textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
                //cerr << "Diffuse textures loaded.";
                std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
                //cerr << "Inserting specular textures...\n";
                textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
                //cerr << "Specular textures loaded.\n";
            }
            //cerr << "Returning mesh...";
            return Mesh(vertices, indices, textures);
        }  

        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName) {
            //cerr << "Loading textures...\n";
            std::vector<Texture> textures;
            //cerr << "Material count: " << mat->GetTextureCount(type) << "\n";
            for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
                //cerr << "Material #" << i << "\n";
                aiString str;
                mat->GetTexture(type, i, &str);
                bool skip = false;
                for (unsigned int j = 0; j < textures_loaded.size(); j++) {
                    if(std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0) { //are the textures the same?
                        textures.push_back(textures_loaded[j]); //add the texture then
                        skip = true; 
                        //cerr << "Texture added\n";
                        break;
                    }
                } if(!skip) {   // if texture hasn't been loaded already, load it
                    //cerr << "New texture found\n";
                    Texture texture;
                    texture.ID = TextureFromFile(str.C_Str(), directory);
                    texture.type = typeName;
                    texture.path = str.C_Str();
                    textures.push_back(texture);
                    textures_loaded.push_back(texture); // add to loaded textures
                    //cerr << "New texture loaded\n";
                }
            }
            cerr << "Textures all loaded. Returning...\n";
            return textures;
        } 

        unsigned int TextureFromFile(const char *path, const std::string &directory) {
            std::string filename = std::string(path);
            filename = directory + '/' + filename;

            unsigned int textureID;
            glGenTextures(1, &textureID);

            int width, height, nrComponents;
            unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
            if (data) {
                GLenum format;
                if (nrComponents == 1)
                    format = GL_RED;
                else if (nrComponents == 3)
                    format = GL_RGB;
                else if (nrComponents == 4)
                    format = GL_RGBA;

                glBindTexture(GL_TEXTURE_2D, textureID);
                glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                stbi_image_free(data);
            }
            else {
                std::cout << "Texture failed to load at path: " << path << std::endl;
                stbi_image_free(data);
            }

    return textureID;
}
};