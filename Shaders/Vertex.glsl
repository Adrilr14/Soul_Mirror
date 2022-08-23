#version 430 core
layout (location = 0) in vec3 aPos;        // VERTICES EN COORDENADAS LOCALES
layout (location = 1) in vec3 aNormal;     // NORMALES EN COORDENADAS LOCALES
layout (location = 2) in vec2 aTexCoords;  // COORDENADAS DE TEXTURA

//out vec3 GPosition;  // VERTICES EN COORDENADAS DE VISTA
//out vec3 GNormal;    // NORMALES EN COORDENADAS DE VISTA
//out vec2 GTexCoords; // COORDENADAS DE TEXTURA

out vec3 Position;  // VERTICES EN COORDENADAS DE VISTA
out vec3 Normal;    // NORMALES EN COORDENADAS DE VISTA
out vec2 TexCoords; // COORDENADAS DE TEXTURA

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
//uniform mat4 NormalMatrix; // NormalMatrix = transpose(inverse(ModelViewMatrix))
//uniform mat4 MVP;

void main()
{
    mat4 ModelViewMatrix = view * model;
    mat3 NormalMatrix = mat3(transpose(inverse(ModelViewMatrix)));

    // TRANSFORMAR VERTICE Y NORMAL A COORDENADAS DE VISTA
    Position = vec3(ModelViewMatrix * vec4(aPos, 1.0));
    Normal = normalize(NormalMatrix * aNormal);

    // LAS COORDENADAS DE LA TEXTURA NO SUFREN TRANSFORMACION
    TexCoords = aTexCoords;    

    // TRANSFORMAR Y PROYECTAR EL VERTICE (POSICION DEL FRAGMENTO)
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}

