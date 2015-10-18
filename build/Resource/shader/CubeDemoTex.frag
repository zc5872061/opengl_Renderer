#version 400 core

uniform sampler2D ColorTextureSampler;

in VS_OUTPUT
{
	vec4 Color;
    vec2 Texcoord;
} IN;

out vec4 Color;

void main()
{
    Color = IN.Color*texture(ColorTextureSampler, IN.Texcoord);
}