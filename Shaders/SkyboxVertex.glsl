#version 430 core
layout (location = 0) in vec3 aPos;        // VERTICES EN COORDENADAS LOCALES
layout (location = 1) in vec3 aNormal;     // NORMALES EN COORDENADAS LOCALES
layout (location = 2) in vec2 aTexCoords;  // COORDENADAS DE TEXTURA

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    TexCoords.x = aTexCoords.x;
    TexCoords.y = aTexCoords.y;
    TexCoords.z = 1.0;
    vec3 Position = vec3(model * vec4(aPos, 1.0));
    vec4 pos = projection * view * vec4(Position, 1.0);
    gl_Position = pos.xyww;
}  