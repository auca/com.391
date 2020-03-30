#version 120

attribute vec4 position;
attribute vec4 color;
attribute vec4 texture1_coordinates;
attribute vec4 texture2_coordinates;

uniform mat4 model_view_projection_matrix;
uniform vec4 emission_color;
uniform float point_size;

uniform bool texture1_enabled;
uniform bool texture1_transformation_enabled;
uniform mat4 texture1_transformation_matrix;

uniform bool texture2_enabled;
uniform bool texture2_transformation_enabled;
uniform mat4 texture2_transformation_matrix;

varying vec4 fragment_color;
varying vec2 fragment_texture1_coordinates;
varying vec2 fragment_texture2_coordinates;

void main()
{
    fragment_color = color * emission_color;

    if (texture1_enabled) {
        if (texture1_transformation_enabled) {
            vec4 transformed_texture1_coordinates = texture1_transformation_matrix * vec4(texture1_coordinates.st, 0.0, 1.0);
            fragment_texture1_coordinates = vec2(transformed_texture1_coordinates);
        } else {
            fragment_texture1_coordinates = vec2(texture1_coordinates);
        }
    }
    if (texture2_enabled) {
        if (texture2_transformation_enabled) {
            vec4 transformed_texture2_coordinates = texture2_transformation_matrix * vec4(texture2_coordinates.st, 0.0, 1.0);
            fragment_texture2_coordinates = vec2(transformed_texture2_coordinates);
        } else {
            fragment_texture2_coordinates = vec2(texture2_coordinates);
        }
    }

    gl_Position = model_view_projection_matrix * position;
    gl_PointSize = point_size;
}
