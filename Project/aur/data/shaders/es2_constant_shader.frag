#version 120

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

#ifndef FOG_TYPE_LINEAR
    #define FOG_TYPE_LINEAR 0
#endif
#ifndef FOG_TYPE_EXP
    #define FOG_TYPE_EXP 1
#endif
#ifndef FOG_TYPE_EXP2
    #define FOG_TYPE_EXP2 2
#endif

#ifndef FOG_DEPTH_PLANAR
    #define FOG_DEPTH_PLANAR 0
#endif
#ifndef FOG_DEPTH_PLANAR_ABSOLUTE
    #define FOG_DEPTH_PLANAR_ABSOLUTE 1
#endif
#ifndef FOG_DEPTH_RADIAL
    #define FOG_DEPTH_RADIAL 2
#endif

uniform sampler2D texture1_sampler;
uniform bool texture1_enabled;
uniform int texturing_mode1;

uniform sampler2D texture2_sampler;
uniform bool texture2_enabled;
uniform int texturing_mode2;

uniform bool fog_enabled;
uniform int fog_type;
uniform int fog_depth;
uniform vec3 fog_color;
uniform float fog_far_minus_near_plane;
uniform float fog_far_plane;
uniform float fog_density;

varying vec4 fragment_view_position;
varying vec4 fragment_color;
varying vec2 fragment_texture1_coordinates;
varying vec2 fragment_texture2_coordinates;

void main()
{
    gl_FragColor = fragment_color;

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

    if (fog_enabled) {
        float fragment_depth;
        if (fog_depth == FOG_DEPTH_PLANAR) {
            fragment_depth = -(fragment_view_position.z / fragment_view_position.w);
        } else if (fog_depth == FOG_DEPTH_PLANAR_ABSOLUTE) {
            fragment_depth = abs(fragment_view_position.z / fragment_view_position.w);
        } else if (fog_depth == FOG_DEPTH_RADIAL) {
            fragment_depth = length(fragment_view_position.xyz / fragment_view_position.w);
        }

        float fragment_fog_factor;
        if (fog_type == FOG_TYPE_LINEAR) {
            fragment_fog_factor = (fog_far_plane - fragment_depth) / fog_far_minus_near_plane;
        } else if (fog_type == FOG_TYPE_EXP) {
            fragment_fog_factor = exp(-1.0 * (fragment_depth * fog_density));
        } else if (fog_type == FOG_TYPE_EXP2) {
            fragment_fog_factor = fragment_depth * fog_density;
            fragment_fog_factor = exp(-(fragment_fog_factor * fragment_fog_factor));
        }
        fragment_fog_factor = clamp(fragment_fog_factor, 0.0, 1.0);

        gl_FragColor.rgb = mix(fog_color, gl_FragColor.rgb, fragment_fog_factor);
    }
}
