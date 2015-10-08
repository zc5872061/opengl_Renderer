#version 400 core

uniform samplerCube SkyboxTextureSampler;

in VS_OUTPUT
{
	vec3 TextureCoordinate;
} IN;

out vec4 Color;

void main()
{
	Color = texture(SkyboxTextureSampler, IN.TextureCoordinate);
}