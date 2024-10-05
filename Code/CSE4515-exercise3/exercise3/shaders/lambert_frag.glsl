#version 410

// Global variables for lighting calculations
//uniform vec3 viewPos;

uniform vec3 lightPos; // Position of the light
uniform vec3 lightColor; // Color of the light
uniform vec3 kd; // Diffuse reflectivity of the material

// Output for on-screen color
out vec4 outColor;

// Interpolated output data from vertex shader
in vec3 fragPos; // World-space position
in vec3 fragNormal; // World-space normal

void main()
{

    // Normalize the normal and calculate the light direction
    vec3 normal = normalize(fragNormal);
    vec3 lightDir = normalize(lightPos - fragPos);

    // Calculate the diffuse component using Lambertian model
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = kd * diff * lightColor;

    // Output the normal as color
    outColor = vec4(diffuse, 1.0); // make sure to use the value lol otherwise the comipler will optimize it away
}