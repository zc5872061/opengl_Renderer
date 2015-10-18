#version 400 core

uniform mat4 WorldViewProjection;
uniform vec3 overrideColor;

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Color;
layout (location = 2) in vec2 TextureCoordinate;

out VS_OUTPUT
{
	vec4 Color;
    vec2 Texcoord;
} OUT;

void main()
{	
	gl_Position = WorldViewProjection * vec4(Position,1.0);
	OUT.Color = vec4(Color*overrideColor,1.0);
    OUT.Texcoord = TextureCoordinate;
}