#version 410

#define M_PI 3.14159265359f

// Output for accumulated color
layout(location = 0) out vec4 outColor;

//Set gl_FragCoord to pixel center
layout(pixel_center_integer) in vec4 gl_FragCoord;


//Circle and line struct equivalent to the one in shape.h
struct Circle {
    vec4 color;
    vec2 position;
    float radius;
};

struct Line {
    vec2 start_point;
    vec2 end_point;
    vec4 color_left[2];
    vec4 color_right[2];
};

//The uniform buffers for the shapes containing the count of shapes in the first slot and after that, the actual shapes
//We need to give the arrays a fixed size to work with opengl 4.1
layout(std140) uniform circleBuffer
{
    int circle_count;
    Circle circles[32];
};

layout(std140) uniform lineBuffer
{
    int line_count;
    Line lines[800];
};

//Textures for the rasterized shapes, and the accumulator
uniform isampler2D rasterized_texture;
uniform sampler2D accumulator_texture;

//The type of the shape we are rasterizing, the same as the enumerator in shapes.h
// 0 - circles
// 1 - lines
// 2 - BezierCurves (Unused)
uniform uint shape_type;

//The number of samples we have already taken
uniform uint frame_nr;
//Screen dimensions
uniform ivec2 screen_dimensions;

//Step size for ray-marching
uniform float step_size; 

//The maximum amount of raymarching steps we can take
uniform uint max_raymarch_iter;

//Random number generator outputs numbers between [0-1]
float get_random_numbers(inout uint seed) {
    seed = 1664525u * seed + 1013904223u;
    seed += 1664525u * seed;
    seed ^= (seed >> 16u);
    seed += 1664525u * seed;
    seed ^= (seed >> 16u);
    return seed * pow(0.5, 32.0);
}
vec2 march_ray(vec2 origin, vec2 direction, float step_size) {
    vec2 current_position = origin;
    for (uint i = 0; i < max_raymarch_iter; ++i) {
        ivec2 tex_coords = ivec2(current_position);
        if (tex_coords.x < 0 || tex_coords.x >= screen_dimensions.x || tex_coords.y < 0 || tex_coords.y >= screen_dimensions.y) {
            break;
        }
        int circle_index = texelFetch(rasterized_texture, tex_coords, 0).r;
        if (circle_index >= 0 && circle_index < circle_count) {
            Circle circle = circles[circle_index];
            float distance = length(current_position - circle.position);
            if (distance <= circle.radius) {
                return current_position;
            }
        }
        current_position += direction * step_size;
    }
    return current_position;
}

void main()
{

    // Ensure the fragment coordinates are within the screen dimensions
    if (gl_FragCoord.x < 0 || gl_FragCoord.x >= screen_dimensions.x || gl_FragCoord.y < 0 || gl_FragCoord.y >= screen_dimensions.y) {
        discard;
    }

    // Initialize the seed for the random number generator
    uint seed = uint(gl_FragCoord.x) * 1973u + uint(gl_FragCoord.y) * 9277u + frame_nr * 26699u;

    // Generate a random direction for the ray
    float angle = 2.0 * M_PI * get_random_numbers(seed);
    vec2 direction = vec2(cos(angle), sin(angle));
    vec2 origin = gl_FragCoord.xy;

    // March the ray and check for intersections
    vec2 intersection = march_ray(origin, direction, step_size);
    ivec2 tex_coords = ivec2(intersection);

    // Fetch the circle index from the rasterized texture
    int circle_index = texelFetch(rasterized_texture, tex_coords, 0).r;

    // Initialize the output color
    vec4 accumulated_color = texelFetch(accumulator_texture, ivec2(gl_FragCoord.xy), 0);

    //If a shape is hit we can sample it
    bool hit = circle_index >= 0 && circle_index < circle_count;
    if(hit){

        Circle circle = circles[circle_index];
        float distance = length(intersection - circle.position);
        // ---- Circle
        if (shape_type == 0 && distance <= circle.radius) {
            accumulated_color += circle.color;
        }
        // ---- Line
        else if (shape_type == 1) {
        }
    }
    outColor = accumulated_color;
}
