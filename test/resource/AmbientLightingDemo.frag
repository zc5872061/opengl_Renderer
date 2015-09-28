#version 400 core

uniform sampler2D ColorTextureSampler;
uniform vec4 AmbientColor;

in VS_OUTPUT
{
	vec2 TextureCoordinate;
} IN;

out vec4 Color;

void main()
{
	vec4 sampledColor = texture(ColorTextureSampler, IN.TextureCoordinate);
    sampledColor.a  = 0.0;
    vec4 mAmbientColor = AmbientColor;
    Color.rgb = sampledColor.rgb * AmbientColor.rgb;

}