/*#version 430 core

// Interpolated values from the vertex shaders
in vec2 UV;

// Ouput data
layout (location = 0) out vec4 FragColor;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;

void main(){

	FragColor = texture(myTextureSampler, UV);
	
	
}*/

#version 430 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D myTextureSampler;

void main()
{
	vec4 texColor = vec4(ourColor, 1.0) * texture(myTextureSampler, TexCoord);

	// Descatamos este tipo de fragmentos para asegurar la transparencia 
	if(texColor.a < 0.1) discard;

    FragColor = texColor;
	//FragColor = texture(myTextureSampler, TexCoord);
}
