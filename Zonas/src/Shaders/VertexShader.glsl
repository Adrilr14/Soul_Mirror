#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
}

/*
// PARA LAS TEXTURAS.

attribute vec2 a_TextureCoord;       // in: Coordenada de textura de cada vertice.
varying vec2 v_TextureCoord;         // out: Para el Fragment coordenadas de texturas
varying vec4 v_Luz;                 // out: para el fragment la intensidad de la luz.


attribute vec4 a_Position;	        // in: Posici�n de cada v�rtice
attribute vec3 a_Normal;	        // in: Normal de cada v�rtice

uniform mat4 u_ProjectionMatrix; 	// in: Matriz Projection
uniform mat4 u_MVMatrix;	        // in: Matriz ModelView
uniform mat4 u_VMatrix;             // in: Matriz View (c�mara)
uniform vec4 u_Color;		        // in: Color del objeto

uniform int  u_Luz0;                // in: Indica si la luz 0 est� encedida
uniform int  u_Luz1;                // in: Indica si la luz 1 est� encedida
uniform int  u_Luz2;                // in: Indica si la luz 2 est� encedida

// posicion de la luz 0
uniform vec4 u_Position_Luz0;       // vector que lleva la posicion de la luz.
// posicion de la luz 1
uniform vec4 u_Position_Luz1;       // vector que lleva la posicion de la luz.
// posicion de la luz 2
uniform vec4 u_Position_Luz2;       // vector que lleva la posicion de la luz.

// intensidad de la luz0
uniform float u_Intensidad0;

// Seleccion habilitada.
uniform int u_selection_enabled;    // in: para saber si estamos en modo de seleccion.

varying vec4 v_Color;		        // out: Color al fragment shader

void main(){
    if(u_selection_enabled == 0){ // seleccion esta deshabilitada
        vec3 P = vec3(u_MVMatrix * a_Position);	            // Posici�n del v�rtice
        vec3 N = vec3(u_MVMatrix * vec4(a_Normal, 0.0));    // Normal del v�rtice

        vec3 viewVec = normalize(vec3(-P)); // para la especular.

        float ambient = 0.15;                               // (15% de int. ambiente)



        /////////// LUZ 0 ////////////////
        // vec4 LightPos = u_VMatrix*vec4( -100, 100, 50, 1);		// Posici�n de la luz [fija]
        vec4  LightPos0 = u_VMatrix * u_Position_Luz0; // es la misma para todos los modelos) recoge la transformacion de la escena unicamente.
        // rotacion traslacion y escalado del modelo. u_MVMatrix (cambia por modelo), es la matriz de vista por la del modelo.
        // todo se rota se trslada y se escala con la matriz de vista, pero cada modelo tiene ademas sus rotaciones transformaciones y escalados.
        float d0 = length(LightPos0.xyz - P);			        // distancia de la luz
        vec3  L0 = normalize(LightPos0.xyz - P);			    // Vector Luz
        float diffuse0 = 0.0;
        float specular0 = 0.0;
        if (u_Luz0 > 0) {                                     // Si la luz 0 est� encendida se calcula la intesidad difusa de L
            diffuse0 = max(dot(N, L0), 0.0);		            // C�lculo de la int. difusa
            // C�lculo de la atenuaci�n
            float attenuation0 = 80.0/(0.25+(0.01*d0)+(0.003*d0*d0));
            diffuse0 = diffuse0*attenuation0*u_Intensidad0;

            // calculo de la especular.
            vec3 lightVec0 = L0;
            vec3 reflectVec0 = reflect(-lightVec0, N);
            specular0 = clamp(dot(reflectVec0, viewVec),0.0, 1.0);
            specular0 = pow(specular0, 2.0);
            specular0 = specular0*u_Intensidad0;
        }

        ////////// LUZ 1 /////////////////
        vec4  LightPos1 = u_VMatrix * u_Position_Luz1; // es la misma para todos los modelos) recoge la transformacion de la escena unicamente.
        // rotacion traslacion y escalado del modelo. u_MVMatrix (cambia por modelo), es la matriz de vista por la del modelo.
        // todo se rota se trslada y se escala con la matriz de vista, pero cada modelo tiene ademas sus rotaciones transformaciones y escalados.
        float d1 = length(LightPos1.xyz - P);			        // distancia de la luz
        vec3  L1 = normalize(LightPos1.xyz - P);			    // Vector Luz
        float diffuse1 = 0.0;
        if (u_Luz1 > 0) {                                     // Si la luz 0 est� encendida se calcula la intesidad difusa de L
            diffuse1 = max(dot(N, L1), 0.0);		            // C�lculo de la int. difusa
            // C�lculo de la atenuaci�n
            float attenuation1 = 80.0/(0.25+(0.01*d1)+(0.003*d1*d1));
            diffuse1 = diffuse1*attenuation1;
        }

        ////////// LUZ 2 /////////////////
        vec4  LightPos2 = u_VMatrix * u_Position_Luz2; // es la misma para todos los modelos) recoge la transformacion de la escena unicamente.
        // rotacion traslacion y escalado del modelo. u_MVMatrix (cambia por modelo), es la matriz de vista por la del modelo.
        // todo se rota se trslada y se escala con la matriz de vista, pero cada modelo tiene ademas sus rotaciones transformaciones y escalados.
        float d2 = length(LightPos2.xyz - P);			        // distancia de la luz
        vec3  L2 = normalize(LightPos2.xyz - P);			    // Vector Luz
        float diffuse2 = 0.0;
        if (u_Luz2 > 0) {                                     // Si la luz 0 est� encendida se calcula la intesidad difusa de L
            diffuse2 = max(dot(N, L2), 0.0);		            // C�lculo de la int. difusa
            // C�lculo de la atenuaci�n
            float attenuation2 = 80.0/(0.25+(0.01*d2)+(0.003*d2*d2));
            diffuse2 = diffuse2*attenuation2;
        }

        // PARA LAS TEXTURAS.
        v_Luz = vec4(ambient + diffuse0 + diffuse1 + diffuse2 + specular0); // se la pasamos al fragment shader


        v_Color = u_Color * v_Luz;
        v_TextureCoord = a_TextureCoord;
        gl_Position = u_ProjectionMatrix * vec4(P, 1.0);
    }
    else{ // si la seleccion esta habilitada, calculamos el color sin luces.
        vec3 P = vec3(u_MVMatrix * a_Position);	            // Posici�n del v�rtice
        v_Color = vec4(u_Color.x, u_Color.x, u_Color.x, 0);
        v_TextureCoord = a_TextureCoord;
        gl_Position = u_ProjectionMatrix * vec4(P, 1.0);
    }
}
*/
