#version 410 core

in vec2 TexCoord;
out vec4 Color;
uniform sampler2D text;

void main()
{
    
    //Color = texture(text,TexCoord);
    Color = vec4(1.0,1.0,1.0,1.0);
}