#ifndef DIRECTIONAL_LIGHT_COUNT
    #define DIRECTIONAL_LIGHT_COUNT 1
#endif
#ifndef POINT_LIGHT_COUNT
    #define POINT_LIGHT_COUNT 1
#endif
#ifndef SPOT_LIGHT_COUNT
    #define SPOT_LIGHT_COUNT 1
#endif

#ifndef TEXTURING_MODE_ADDITION
    #define TEXTURING_MODE_ADDITION 0
#endif
#ifndef TEXTURING_MODE_SUBTRACTION
    #define TEXTURING_MODE_SUBTRACTION 1
#endif
#ifndef TEXTURING_MODE_REVERSE_SUBTRACTION
    #define TEXTURING_MODE_REVERSE_SUBTRACTION 2
#endif
#ifndef TEXTURING_MODE_MODULATION
    #define TEXTURING_MODE_MODULATION 3
#endif
#ifndef TEXTURING_MODE_DECALING
    #define TEXTURING_MODE_DECALING 4
#endif

uniform vec3 ambient_light_color;

uniform vec3 material_ambient_color;
uniform vec4 material_diffuse_color;
uniform vec4 material_emission_color;
uniform vec3 material_specular_color;
uniform float material_specular_exponent;

#if DIRECTIONAL_LIGHT_COUNT > 0
    uniform bool directional_light_enabled[DIRECTIONAL_LIGHT_COUNT];
    uniform bool directional_light_two_sided[DIRECTIONAL_LIGHT_COUNT];
    uniform vec3 directional_light_view_direction[DIRECTIONAL_LIGHT_COUNT];
    uniform vec3 directional_light_ambient_color[DIRECTIONAL_LIGHT_COUNT];
    uniform vec3 directional_light_diffuse_color[DIRECTIONAL_LIGHT_COUNT];
    uniform vec3 directional_light_specular_color[DIRECTIONAL_LIGHT_COUNT];
    uniform float directional_light_intensity[DIRECTIONAL_LIGHT_COUNT];
#endif

#if POINT_LIGHT_COUNT > 0
    uniform bool point_light_enabled[POINT_LIGHT_COUNT];
    uniform bool point_light_two_sided[POINT_LIGHT_COUNT];
    uniform vec3 point_light_view_position[POINT_LIGHT_COUNT];
    uniform vec3 point_light_ambient_color[POINT_LIGHT_COUNT];
    uniform vec3 point_light_diffuse_color[POINT_LIGHT_COUNT];
    uniform vec3 point_light_specular_color[POINT_LIGHT_COUNT];
    uniform float point_light_intensity[POINT_LIGHT_COUNT];
    uniform float point_light_constant_attenuation[POINT_LIGHT_COUNT];
    uniform float point_light_linear_attenuation[POINT_LIGHT_COUNT];
    uniform float point_light_quadratic_attenuation[POINT_LIGHT_COUNT];
#endif

#if SPOT_LIGHT_COUNT > 0
    uniform bool spot_light_enabled[SPOT_LIGHT_COUNT];
    uniform bool spot_light_two_sided[SPOT_LIGHT_COUNT];
    uniform vec3 spot_light_view_position[SPOT_LIGHT_COUNT];
    uniform vec3 spot_light_view_direction[SPOT_LIGHT_COUNT];
    uniform vec3 spot_light_ambient_color[SPOT_LIGHT_COUNT];
    uniform vec3 spot_light_diffuse_color[SPOT_LIGHT_COUNT];
    uniform vec3 spot_light_specular_color[SPOT_LIGHT_COUNT];
    uniform float spot_light_exponent[SPOT_LIGHT_COUNT];
    uniform float spot_light_cutoff_angle_cosine[SPOT_LIGHT_COUNT];
    uniform float spot_light_intensity[SPOT_LIGHT_COUNT];
    uniform float spot_light_constant_attenuation[SPOT_LIGHT_COUNT];
    uniform float spot_light_linear_attenuation[SPOT_LIGHT_COUNT];
    uniform float spot_light_quadratic_attenuation[SPOT_LIGHT_COUNT];
#endif

uniform sampler2D texture1_sampler;
uniform bool texture1_enabled;
uniform int texturing_mode1;

uniform sampler2D texture2_sampler;
uniform bool texture2_enabled;
uniform int texturing_mode2;

varying vec3 fragment_view_direction;
varying vec3 fragment_view_normal;
varying vec4 fragment_color;
varying vec2 fragment_texture1_coordinates;
varying vec2 fragment_texture2_coordinates;

void main()
{
    vec3 view_direction = normalize(fragment_view_direction);
    vec3 view_normal = normalize(fragment_view_normal);

    vec4 front_color = material_emission_color;
    front_color.rgb += material_ambient_color * ambient_light_color;
    front_color.a += material_diffuse_color.a;

    vec4 back_color = front_color;

#if DIRECTIONAL_LIGHT_COUNT > 0
    for (int i = 0; i < DIRECTIONAL_LIGHT_COUNT; i++) {
        if (directional_light_enabled[i]) {
            float n_dot_l = max(dot(view_normal, directional_light_view_direction[i]), 0.0);
            vec3 diffuse_color = material_diffuse_color.rgb * directional_light_diffuse_color[i];
            vec3 diffuse_term = n_dot_l * diffuse_color;

            vec3 reflection_vector = reflect(-directional_light_view_direction[i], view_normal);
            float n_dot_h = clamp(dot(view_direction, reflection_vector), 0.0, 1.0);
            vec3 specular_color = material_specular_color.rgb * directional_light_specular_color[i];
            vec3 specular_term = pow(n_dot_h, material_specular_exponent) * specular_color;

            front_color.rgb += directional_light_intensity[i] * (directional_light_ambient_color[i] + diffuse_term + specular_term);

            if (directional_light_two_sided[i]) {
                vec3 inverted_view_normal = -view_normal;

                n_dot_l = max(dot(inverted_view_normal, directional_light_view_direction[i]), 0.0);
                diffuse_term = n_dot_l * diffuse_color;

                reflection_vector = reflect(-directional_light_view_direction[i], inverted_view_normal);
                n_dot_h = clamp(dot(view_direction, reflection_vector), 0.0, 1.0);
                specular_term = pow(n_dot_h, material_specular_exponent) * specular_color;

                back_color.rgb += directional_light_intensity[i] * (directional_light_ambient_color[i] + diffuse_term + specular_term);
            }
        }
    }
#endif

#if POINT_LIGHT_COUNT > 0
    for (int i = 0; i < POINT_LIGHT_COUNT; i++) {
        if (point_light_enabled[i]) {
            vec3 point_light_vector = point_light_view_position[i] + fragment_view_direction;

            float point_light_vector_length = length(point_light_vector);
            point_light_vector /= point_light_vector_length;

            float point_light_vector_length_squared = point_light_vector_length * point_light_vector_length;
            float attenuation_factor =
                (1.0 / (point_light_constant_attenuation[i]                              +
                        point_light_linear_attenuation[i]    * point_light_vector_length +
                        point_light_quadratic_attenuation[i] * point_light_vector_length_squared));
            attenuation_factor *= point_light_intensity[i];

            float n_dot_l = max(dot(view_normal, point_light_vector), 0.0);
            vec3 diffuse_color = material_diffuse_color.rgb * point_light_diffuse_color[i];
            vec3 diffuse_term = n_dot_l * diffuse_color;

            vec3 reflection_vector = reflect(-point_light_vector, view_normal);
            float n_dot_h = clamp(dot(view_direction, reflection_vector), 0.0, 1.0);
            vec3 specular_color = material_specular_color.rgb * point_light_specular_color[i];
            vec3 specular_term = pow(n_dot_h, material_specular_exponent) * specular_color;

            front_color.rgb += attenuation_factor * (point_light_ambient_color[i] + diffuse_term + specular_term);

            if (point_light_two_sided[i]) {
                vec3 inverted_view_normal = -view_normal;

                n_dot_l = max(dot(-inverted_view_normal, point_light_vector), 0.0);
                diffuse_term = n_dot_l * diffuse_color;

                reflection_vector = reflect(-point_light_vector, inverted_view_normal);
                n_dot_h = clamp(dot(view_direction, reflection_vector), 0.0, 1.0);
                specular_term = pow(n_dot_h, material_specular_exponent) * specular_color;

                back_color.rgb += attenuation_factor * (point_light_ambient_color[i] + diffuse_term + specular_term);
            }
        }
    }
#endif

#if SPOT_LIGHT_COUNT > 0
    for (int i = 0; i < SPOT_LIGHT_COUNT; ++i) {
        if (spot_light_enabled[i]) {
            vec3 spot_light_vector = spot_light_view_position[i] - fragment_view_direction;

            float spot_light_vector_length = length(spot_light_vector);
            spot_light_vector /= spot_light_vector_length;

            float spot_light_vector_lengthSquared = spot_light_vector_length * spot_light_vector_length;
            float attenuation_factor =
                (1.0 / (spot_light_constant_attenuation[i]                          +
                        spot_light_linear_attenuation[i]    * spot_light_vector_length +
                        spot_light_quadratic_attenuation[i] * spot_light_vector_lengthSquared));
            attenuation_factor *= spot_light_intensity[i];

            float n_dot_l = max(dot(view_normal, spot_light_vector), 0.0);
            vec3 diffuse_color = material_diffuse_color.rgb * spot_light_diffuse_color[i];
            vec3 diffus_term = n_dot_l * diffuse_color;

            vec3 reflection_vector = reflect(-spot_light_vector, view_normal);
            float n_dot_h = clamp(dot(view_direction, reflection_vector), 0.0, 1.0);
            vec3 specular_color = material_specular_color.rgb * spot_light_specular_color[i];
            vec3 specular_term = pow(n_dot_h, material_specular_exponent) * specular_color;

            float spot_factor = 0.0;
            float vertex_direction_dot_spot_direction = max(dot(-spot_light_vector, spot_light_view_direction[i]), 0.0);
            if (spot_light_cutoff_angle_cosine[i] <= vertex_direction_dot_spot_direction) {
                spot_factor = pow(vertex_direction_dot_spot_direction, spot_light_exponent[i]);
            }
            attenuation_factor *= spot_factor;

            front_color.rgb += attenuation_factor * (spot_light_ambient_color[i] + diffus_term + specular_term);

            if (spot_light_two_sided[i]) {
                vec3 inverted_view_normal = -view_normal;

                n_dot_l = max(dot(-view_normal, spot_light_vector), 0.0);
                diffus_term = n_dot_l * diffuse_color;

                reflection_vector = reflect(-spot_light_vector, inverted_view_normal);
                n_dot_h = clamp(dot(view_direction, reflection_vector), 0.0, 1.0);
                specular_term = pow(n_dot_h, material_specular_exponent) * specular_color;

                back_color.rgb += attenuation_factor * (spot_light_ambient_color[i] + diffus_term + specular_term);
            }
        }
    }
#endif

    gl_FragColor = fragment_color;
    if (gl_FrontFacing) {
        gl_FragColor *= front_color;
    } else {
        gl_FragColor *= back_color;
    }

    if (texture1_enabled) {
        if (texturing_mode1 == TEXTURING_MODE_ADDITION) {
            gl_FragColor += texture2D(texture1_sampler, fragment_texture1_coordinates);
        } else if (texturing_mode1 == TEXTURING_MODE_MODULATION) {
            gl_FragColor *= texture2D(texture1_sampler, fragment_texture1_coordinates);
        } else if (texturing_mode1 == TEXTURING_MODE_DECALING) {
            vec4 texel_color = texture2D(texture1_sampler, fragment_texture1_coordinates);
            gl_FragColor.rgb = mix(gl_FragColor.rgb, texel_color.rgb, texel_color.a);
        } else if (texturing_mode1 == TEXTURING_MODE_SUBTRACTION) {
            gl_FragColor -= texture2D(texture1_sampler, fragment_texture1_coordinates);
        } else if (texturing_mode1 == TEXTURING_MODE_REVERSE_SUBTRACTION) {
            gl_FragColor = texture2D(texture1_sampler, fragment_texture1_coordinates) - gl_FragColor;
        }
    }

    if (texture2_enabled) {
        if (texturing_mode2 == TEXTURING_MODE_ADDITION) {
            gl_FragColor += texture2D(texture2_sampler, fragment_texture2_coordinates);
        } else if (texturing_mode2 == TEXTURING_MODE_MODULATION) {
            gl_FragColor *= texture2D(texture2_sampler, fragment_texture2_coordinates);
        } else if (texturing_mode2 == TEXTURING_MODE_DECALING) {
            vec4 texel_color = texture2D(texture2_sampler, fragment_texture2_coordinates);
            gl_FragColor.rgb = mix(gl_FragColor.rgb, texel_color.rgb, texel_color.a);
        } else if (texturing_mode2 == TEXTURING_MODE_SUBTRACTION) {
            gl_FragColor -= texture2D(texture2_sampler, fragment_texture2_coordinates);
        } else if (texturing_mode2 == TEXTURING_MODE_REVERSE_SUBTRACTION) {
            gl_FragColor = texture2D(texture2_sampler, fragment_texture2_coordinates) - gl_FragColor;
        }
    }
}
