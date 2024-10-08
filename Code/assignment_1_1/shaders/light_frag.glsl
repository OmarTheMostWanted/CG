#version 410

uniform vec3 color;
uniform sampler2D lightTexture;
uniform bool useTexture;

// Output for on-screen color
out vec4 outColor;

void main()
{
    if (useTexture) {
        vec2 texCoords = gl_PointCoord; // Use point coordinates for texture sampling
        vec4 texColor = texture(lightTexture, texCoords);
        outColor = texColor * vec4(color, 1.0);
    } else {
        outColor = vec4(color, 1.0);
    }
}