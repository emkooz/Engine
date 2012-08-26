#version 150

in vec3 position;
in vec2 texcoord;

out vec2 Texcoord;


uniform mat4 MVP;

void main()
{
	Texcoord = texcoord;
    gl_Position = MVP * vec4( position, 1.0 );
}
