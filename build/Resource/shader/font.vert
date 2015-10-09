#version 410 core

layout (location = 0) in vec4 Position;
layout (location = 1) in vec4 Color;

out VS_OUTPUT
{
	vec2 TexCoords;
} OUT;

void main()
{	
	gl_Position = WorldViewProjection * Position;
	OUT.TexCoords = Color;
}