#version 120

attribute vec4 position;
attribute vec4 color;
attribute vec4 texture_coordinates;

uniform mat4 model_view_projection_matrix;
uniform vec4 emission_color;
uniform float point_size;

varying vec4 fragment_color;
varying vec2 fragment_texture_coordinates;

void main()
{
    fragment_color = color * emission_color;
    fragment_texture_coordinates = vec2(texture_coordinates);

    gl_Position = model_view_projection_matrix * position;
    gl_PointSize = point_size;
}
