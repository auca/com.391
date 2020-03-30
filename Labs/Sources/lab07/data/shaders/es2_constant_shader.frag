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

uniform sampler2D texture1_sampler;
uniform bool texture1_enabled;
uniform int texturing_mode1;

uniform sampler2D texture2_sampler;
uniform bool texture2_enabled;
uniform int texturing_mode2;

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
}
