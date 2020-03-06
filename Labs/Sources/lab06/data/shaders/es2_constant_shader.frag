#version 120

uniform sampler2D texture_sampler;

varying vec4 fragment_color;
varying vec2 fragment_texture_coordinates;

void main()
{
    gl_FragColor = fragment_color + texture2D(texture_sampler, fragment_texture_coordinates);
}
