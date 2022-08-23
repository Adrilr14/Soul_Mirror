#version 430 core
out vec4 FragColor;

in vec4 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D myTextureSampler;

void main()
{
	vec4 texColor = ourColor * texture(myTextureSampler, TexCoord);
	if(texColor.a < 0.1)
        discard;
    FragColor = texColor;
	//FragColor = texture(myTextureSampler, TexCoord);
}
