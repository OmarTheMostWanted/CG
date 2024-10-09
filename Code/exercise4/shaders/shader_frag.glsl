#version 410 core

// Global variables for lighting calculations.
//uniform vec3 viewPos;
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

// Output for on-screen color.
out vec4 outColor;

// Interpolated output data from vertex shader.
in vec3 fragPos; // World-space position
in vec3 fragNormal; // World-space normal

void main()
{
    vec4 fragLightCoord = lightMVP * vec4(fragPos, 1.0);

    // perspective division
    fragLightCoord.xyz /= fragLightCoord.w;

    // The resulting value is in NDC space (-1 to +1),
    //  we transform them to texture space (0 to 1).
    fragLightCoord.xyz = fragLightCoord.xyz * 0.5 + 0.5;

    // Depth of the fragment with respect to the light
    float fragLightDepth = fragLightCoord.z;

    // Shadow map coordinate corresponding to this fragment
    vec2 shadowMapCoord = fragLightCoord.xy;

    // Shadow map value from the corresponding shadow map position
    float shadowMapDepth = texture(texShadow, shadowMapCoord).x;

    // Output the normal as color.
    vec3 lightDir = normalize(lightPos - fragPos);

    vec3 normal = fragNormal;

    if (lightMode == 0)
    {
        float bias = 0.005f;
        //compare the depth of the fragment with the depth stored in the shadow map
        if (fragLightDepth - bias > shadowMapDepth)
        {
            outColor = vec4(0.0, 0.0, 0.0, 1.0);

        } else {
            outColor = vec4(vec3(max(dot(fragNormal, lightDir), 0.0)), 1.0);
        }

    }
//    outColor = vec4(vec3(max(dot(fragNormal, lightDir), 0.0)), 1.0);
}