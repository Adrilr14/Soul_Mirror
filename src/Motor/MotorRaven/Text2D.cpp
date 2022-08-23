#include "Text2D.hpp"
#include "RFuente.hpp"

#include <iostream>
#include <vector>
#include <cstring>

Text2D::Text2D(const char * t, RFuente* font, glm::vec4 color_, int x, int y, int s, int width_, int height_) : text(t), fuente(font), color(color_), posX(x), posY(y), size(s), width(width_), height(height_){
    // Initialize VBO
	glGenBuffers(1, &Text2DVertexBufferID);
	glGenBuffers(1, &Text2DUVBufferID);
	//glGenVertexArrays(1, &VAO);
    //glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);
}

Text2D::~Text2D() {
    // Delete buffers
	glDeleteBuffers(1, &Text2DVertexBufferID);
	glDeleteBuffers(1, &Text2DUVBufferID);
	//glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &VAO);
    //glDeleteBuffers(1, &EBO);
}

void Text2D::dibujar(glm::mat4x4 mat, unsigned int shader) {
    unsigned int length = strlen(text);

	// Fill buffers
	std::vector<glm::vec2> vertices;
	std::vector<glm::vec2> UVs;

    int aux = 0; // Variable auxiliar para multiplicar por el size
    int y = posY; // Variable para guardar la posición y sin modificar la variable de clase

	for ( unsigned int i=0 ; i<length ; i++ ){
		
        char character = text[i];
        int c = character/1;
        //std::cout << character << " / " << c << std::endl;

        // Si el caracter es 10 (salto de línea) reiniciamos la variable auxiliar y aumentamos la posY
        if(c == 10)
        {
           aux = 0;
           y -= (size*2 - size/2); 
        } 

        // Si no metemos el caracter en los vectores
        else
        {
            glm::vec2 vertex_up_left    = glm::vec2( posX+aux*size     , y+size );
            glm::vec2 vertex_up_right   = glm::vec2( posX+aux*size+size, y+size );
            glm::vec2 vertex_down_right = glm::vec2( posX+aux*size+size, y      );
            glm::vec2 vertex_down_left  = glm::vec2( posX+aux*size     , y      );

            vertex_down_left    -= glm::vec2(960, 540);
            vertex_up_left      -= glm::vec2(960, 540);
            vertex_up_right     -= glm::vec2(960, 540);
            vertex_down_right   -= glm::vec2(960, 540);

            vertex_down_left    /= glm::vec2(960, 540);
            vertex_up_left      /= glm::vec2(960, 540);
            vertex_up_right     /= glm::vec2(960, 540);
            vertex_down_right   /= glm::vec2(960, 540);

            vertices.push_back(vertex_up_left   );
            vertices.push_back(vertex_down_left );
            vertices.push_back(vertex_up_right  );

            vertices.push_back(vertex_down_right);
            vertices.push_back(vertex_up_right);
            vertices.push_back(vertex_down_left);

            //float uv_x = ((character - 32)%16)/16.0f;
            //float uv_y = ((character - 32)/16)/16.0f;
            float uv_x = ((character)%16)/16.0f;
            float uv_y = ((character)/16)/16.0f;

            glm::vec2 uv_up_left    = glm::vec2( uv_x           , uv_y );
            glm::vec2 uv_up_right   = glm::vec2( uv_x+1.0f/16.0f, uv_y );
            glm::vec2 uv_down_right = glm::vec2( uv_x+1.0f/16.0f, (uv_y + 1.0f/16.0f) );
            glm::vec2 uv_down_left  = glm::vec2( uv_x           , (uv_y + 1.0f/16.0f) );

            /*std::cout << "uv_x = " << uv_x << "; uv_y = " << uv_y << std::endl;
            std::cout << "uv_down_left x = " << uv_down_left.x << "; uv_up_left x = " << uv_up_left.x << "; uv_up_right x = " << uv_up_right.x << "; uv_down_right x = " << uv_down_right.x << std::endl;
            std::cout << "uv_down_left y = " << uv_down_left.y << "; uv_up_left y = " << uv_up_left.y << "; uv_up_right y = " << uv_up_right.y << "; uv_down_right y = " << uv_down_right.y << std::endl;
            std::cout << std::endl;*/
            
            UVs.push_back(uv_up_left   );
            UVs.push_back(uv_down_left );
            UVs.push_back(uv_up_right  );

            UVs.push_back(uv_down_right);
            UVs.push_back(uv_up_right);
            UVs.push_back(uv_down_left);

            // Aumentamos la variable auxiliar
            aux++;
        }

	}
    
	glBindBuffer(GL_ARRAY_BUFFER, Text2DVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, Text2DUVBufferID);
	glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs[0], GL_STATIC_DRAW);

	// Bind shader
	//glUseProgram(Text2DShaderID);

	glActiveTexture(GL_TEXTURE0);
    // Set our "myTextureSampler" sampler to use Texture Unit 0
    glUniform1i(glGetUniformLocation(shader, "myTextureSampler"), 0);
    // Bind texture
    glBindTexture(GL_TEXTURE_2D, fuente->getId());

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, Text2DVertexBufferID);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, Text2DUVBufferID);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

    // Pasamos el color
    glUniform4f(glGetUniformLocation(shader, "color"), color.x, color.y, color.z, color.w);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Draw call
	glDrawArrays(GL_TRIANGLES, 0, vertices.size() );

	glDisable(GL_BLEND);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

}
