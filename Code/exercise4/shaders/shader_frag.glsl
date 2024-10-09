#version 410 core

// Global variables for lighting calculations.
uniform sampler2D texShadow;

// scene uniforms
uniform mat4 lightMVP;
uniform vec3 lightPos;
uniform vec3 viewPos;
// config uniforms, use these to control the shader from UI
uniform int samplingMode = 0;
uniform int peelingMode = 0;
uniform int lightMode = 0;
uniform int lightColorMode = 0;
uniform float shadowMapResolution; // Add this uniform

// Output for on-screen color.
out vec4 outColor;

// Interpolated output data from vertex shader.
in vec3 fragPos; // World-space position
in vec3 fragNormal; // World-space normal

void main()
{
    float bias = 0.005;
    vec4 fragLightCoord = lightMVP * vec4(fragPos, 1.0);

    // perspective division
    fragLightCoord.xyz /= fragLightCoord.w;

    // The resulting value is in NDC space (-1 to +1),
    //  we transform them to texture space (0 to 1).
    fragLightCoord.xyz = fragLightCoord.xyz * 0.5 + 0.5;

    // Perform shadow test
    float shadow = 0.0;
    if (samplingMode == 1) {
        // PCF kernel size
        float kernelSize = 1.0 / shadowMapResolution; // Use the uniform
        int samples = 4; // Number of samples per axis
        float totalSamples = float((samples * 2 + 1) * (samples * 2 + 1));

        for (int x = -samples; x <= samples; ++x) {
            for (int y = -samples; y <= samples; ++y) {
                vec2 offset = vec2(float(x), float(y)) * kernelSize;
                float depth = texture(texShadow, fragLightCoord.xy + offset).r;
                shadow += (fragLightCoord.z - bias) > depth ? 1.0 : 0.0;
            }
        }
        shadow /= totalSamples;
    } else {
        float depth = texture(texShadow, fragLightCoord.xy).r;
        shadow = (fragLightCoord.z - bias) > depth ? 1.0 : 0.0;
    }

    // Output the normal as color.
    vec3 lightDir = normalize(lightPos - fragPos);
    vec3 normal = fragNormal;

    if (lightMode == 0) {
        float diff = max(dot(normal, lightDir), 0.0);
        vec3 diffuse = diff * vec3(1.0, 1.0, 1.0);
        outColor = vec4(diffuse * (1.0 - shadow), 1.0);
    } else {
        // Other lighting modes
    }
}