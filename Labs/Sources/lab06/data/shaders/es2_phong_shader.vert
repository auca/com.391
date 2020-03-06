attribute vec4 position;
attribute vec4 color;
attribute vec3 normal;
attribute vec4 texture_coordinates;

uniform mat4 model_view_matrix;
uniform mat4 projection_matrix;
uniform mat3 normal_matrix;
uniform float point_size;

varying vec3 fragment_view_direction;
varying vec3 fragment_view_normal;
varying vec4 fragment_color;
varying vec2 fragment_texture_coordinates;

void main()
{
    vec4 view_position = model_view_matrix * position;
    fragment_view_direction = -view_position.xyz;
    fragment_view_normal = normalize(normal_matrix * normal);
    fragment_color = color;
    fragment_texture_coordinates = vec2(texture_coordinates);

    gl_Position = projection_matrix * view_position;
    gl_PointSize = point_size;
}
