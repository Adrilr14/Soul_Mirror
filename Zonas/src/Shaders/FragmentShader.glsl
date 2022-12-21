#version 330 core
out vec4 FragColor;

in vec3 ourColor;

void main()
{
    FragColor = vec4(ourColor, 1.0f);
}

/*
//precision mediump float;	// Precisi�n media

varying vec4 v_Color;		// in: color del vertex shader


// PARA LAS TEXTURAS.
varying vec2 v_TextureCoord; // in: coordenada del vertex shader
varying vec4 v_Luz; // in: luz calculada del vertex.
uniform sampler2D u_Sampler; // la variable textura activada desde el programa.
uniform int activada; // para indicar si tiene que coger textura o color.


void main(){
        if(activada == 0){
    		gl_FragColor = v_Color; // este color lleva la luz.
        }
        else{
            gl_FragColor = texture2D(u_Sampler, v_TextureCoord)*v_Luz;
        }
}
*/
