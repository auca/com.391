#version 120

attribute vec4 position;
attribute vec4 color;

uniform mat4 model_view_projection_matrix;
uniform vec4 emission_color;
uniform float point_size;

varying vec4 fragment_color;

void main()
{
    fragment_color = color * emission_color;

    gl_Position = model_view_projection_matrix * position;
    gl_PointSize = point_size;
}
