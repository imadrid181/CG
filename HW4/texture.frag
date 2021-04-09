
#version 330 core
out vec4 color;

in vec2 UV;
uniform sampler2D myTextureSampler;

void main()
{
    // TODO: pub with your code...
    
    // Apply the color that is returned from using the textureSampler with the 
    // UV data. In the UV data, the y must be inversed.
    color = texture(myTextureSampler, vec2(UV.x, 1.0 - UV.y));
}
