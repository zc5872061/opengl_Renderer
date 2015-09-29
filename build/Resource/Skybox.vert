#version 400 core

uniform mat4 WorldViewProjection;

in vec4 Position;

out VS_OUTPUT
{
	vec3 TextureCoordinate;
} OUT;

void main()
{	
	gl_Position = WorldViewProjection * Position;
	OUT.TextureCoordinate = Position.xyz;
}