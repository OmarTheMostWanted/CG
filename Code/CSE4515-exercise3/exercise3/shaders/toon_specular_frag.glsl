#version 410

// Input from vertex shader
in vec3 fragPos;
in vec3 fragNormal;

// Light properties
uniform vec3 lightPos;
//uniform vec3 lightColor;

// Material properties
//uniform vec3 ks; // Specular reflectivity
uniform float shininess; // Shininess coefficient

// Camera position
uniform vec3 viewPos;

// Toon shading parameters
uniform float toonSpecularThreshold;

// Output color
out vec4 outColor;

void main() {
    // Normalize the normal vector
    vec3 normal = normalize(fragNormal);

    // Calculate the light direction
    vec3 lightDir = normalize(lightPos - fragPos);

    // Calculate the view direction
    vec3 viewDir = normalize(viewPos - fragPos);

    // Calculate the halfway vector
    vec3 halfwayDir = normalize(lightDir + viewDir);

    // Calculate the specular component using Blinn-Phong model
    float spec = pow(max(dot(normal, halfwayDir), 0.0), shininess);

    // Apply toon shading to the specular component
    if (spec >= toonSpecularThreshold) {
        outColor = vec4(1.0); // White color for specular highlight
    } else {
        outColor = vec4(0.0); // Black color otherwise
    }
}