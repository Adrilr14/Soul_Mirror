#include "Billboard.hpp"
#include "RImagen.hpp"

#include <iostream>
#include <vector>

Billboard::Billboard(RImagen* imagen_, int x, int y, int width_, int height_) : imagen(imagen_), posX(x), posY(y), width(width_), height(height_) {
    //glGenVertexArrays(1, &VAO);
    //glGenBuffers(1, &vertexBuffer);
    //glGenBuffers(1, &vertexBuffer);
	//glGenBuffers(1, &UVBuffer);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
}

Billboard::~Billboard() {
    // Delete buffers
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VAO);
    glDeleteBuffers(1, &EBO);
}

void Billboard::dibujar(glm::mat4x4 mat, unsigned int shaderID){
    if(imagen != nullptr){
        //std::cout << "Width = " << width << "; Height = " << height << std::endl;
        // Fill buffers

        glm::vec2 vertex_down_left  = glm::vec2((float)posX, (float)posY);
        glm::vec2 vertex_up_left    = glm::vec2((float)posX + (float)width, (float)posY);
        glm::vec2 vertex_up_right   = glm::vec2((float)posX + (float)width, (float)posY + (float)height);
        glm::vec2 vertex_down_right = glm::vec2((float)posX, (float)posY + (float)height);

        /*std::cout << "vertex_down_left.x = " << vertex_down_left.x << "; vertex_down_left.y = " << vertex_down_left.y << std::endl;
        std::cout << "vertex_up_left.x = " << vertex_up_left.x << "; vertex_up_left.y = " << vertex_up_left.y << std::endl;
        std::cout << "vertex_up_right.x = " << vertex_up_right.x << "; vertex_up_right.y = " << vertex_up_right.y << std::endl;
        std::cout << "vertex_down_right.x = " << vertex_down_right.x << "; vertex_down_right.y = " << vertex_down_right.y << std::endl;
        std::cout << std::endl;*/

        vertex_down_left    -= glm::vec2(960, 540);
        vertex_up_left      -= glm::vec2(960, 540);
        vertex_up_right     -= glm::vec2(960, 540);
        vertex_down_right   -= glm::vec2(960, 540);

        /*std::cout << "vertex_down_left.x = " << vertex_down_left.x << "; vertex_down_left.y = " << vertex_down_left.y << std::endl;
        std::cout << "vertex_up_left.x = " << vertex_up_left.x << "; vertex_up_left.y = " << vertex_up_left.y << std::endl;
        std::cout << "vertex_up_right.x = " << vertex_up_right.x << "; vertex_up_right.y = " << vertex_up_right.y << std::endl;
        std::cout << "vertex_down_right.x = " << vertex_down_right.x << "; vertex_down_right.y = " << vertex_down_right.y << std::endl;
        std::cout << std::endl;*/

        vertex_down_left    /= glm::vec2(960, 540);
        vertex_up_left      /= glm::vec2(960, 540);
        vertex_up_right     /= glm::vec2(960, 540);
        vertex_down_right   /= glm::vec2(960, 540);

        /*std::cout << "vertex_down_left.x = " << vertex_down_left.x << "; vertex_down_left.y = " << vertex_down_left.y << std::endl;
        std::cout << "vertex_up_left.x = " << vertex_up_left.x << "; vertex_up_left.y = " << vertex_up_left.y << std::endl;
        std::cout << "vertex_up_right.x = " << vertex_up_right.x << "; vertex_up_right.y = " << vertex_up_right.y << std::endl;
        std::cout << "vertex_down_right.x = " << vertex_down_right.x << "; vertex_down_right.y = " << vertex_down_right.y << std::endl;
        std::cout << std::endl;*/

        GLfloat TexCoord[] = {
                0, 0,
                1, 0,
                1, 1,
                0, 1,
            };
        /*GLubyte indices[] = {0,1,2, // first triangle (bottom left - top left - top right)
                            0,2,3}; // second triangle (bottom left - top right - bottom right)
        */
        /*float vertices[] = {
            // positions          // colors           // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // top left 
        };
        unsigned int indices[] = {  
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };*/

        float vertices[] = {
            // positions                                        // colors           // texture coords
            vertex_down_left.x,  vertex_down_left.y, 0.0f,      1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // bottom left
            vertex_up_left.x, vertex_up_left.y, 0.0f,           1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // top left
            vertex_up_right.x, vertex_up_right.y, 0.0f,         1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // top right
            vertex_down_right.x,  vertex_down_right.y, 0.0f,    1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // bottom right
        };

        unsigned int indices[] = {  
            0,1,2, // first triangle (bottom left - top left - top right)
            0,2,3  // second triangle (bottom left - top right - bottom right)
        };

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // texture coord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // Bind shader
        //glUseProgram(shaderID);

        glActiveTexture(GL_TEXTURE0);
        // Set our "myTextureSampler" sampler to use Texture Unit 0
        glUniform1i(glGetUniformLocation(shaderID, "myTextureSampler"), 0);
        // Bind texture
        glBindTexture(GL_TEXTURE_2D, imagen->getId());

        // Active Alpha component 
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // optional: de-allocate all resources once they've outlived their purpose:
        // ------------------------------------------------------------------------
        //glDeleteVertexArrays(1, &VAO);
        //glDeleteBuffers(1, &VBO);
        //glDeleteBuffers(1, &EBO);

        glDisable(GL_BLEND);

	    glDisableVertexAttribArray(0);
	    glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);

    }
}