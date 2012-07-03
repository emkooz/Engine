#version 150

out vec4 outColor;
in vec2 Texcoord;

uniform sampler2D texPyro;

void main()
{
	outColor = texture2D( texPyro, Texcoord );
}
