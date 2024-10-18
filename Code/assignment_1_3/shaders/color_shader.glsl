#version 410

// Output for on-screen color
layout(location = 0) out vec4 outColor;

//Textures
uniform sampler2D accumulator_texture;
uniform ivec2 screen_dimensions;

//Set gl_FragCoord to pixel center
layout(pixel_center_integer) in vec4 gl_FragCoord;

void main()
{

    // Ensure the fragment coordinates are within the screen dimensions
    if (gl_FragCoord.x < 0 || gl_FragCoord.x >= screen_dimensions.x || gl_FragCoord.y < 0 || gl_FragCoord.y >= screen_dimensions.y) {
        discard;
    }

    // Fetch the accumulated color and sample count from the accumulator texture
    vec4 accumulated_data = texelFetch(accumulator_texture, ivec2(gl_FragCoord.xy), 0);

    // The first three channels store the accumulated color
    vec3 accumulated_color = accumulated_data.rgb;

    // The fourth channel stores the count of samples
    float sample_count = accumulated_data.a;

    // Compute the weighted average color
    vec3 average_color = accumulated_color / sample_count;

    // Output the final color
    outColor = vec4(average_color, 1.0);
}
