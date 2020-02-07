#version 110

attribute vec4 position;
attribute vec4 color;

uniform mat4 model_view_projection_matrix;

varying vec4 fragment_color;

void main()
{
    fragment_color = color;

    gl_Position = model_view_projection_matrix * position;
}
