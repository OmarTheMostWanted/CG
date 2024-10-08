#version 410

// Input from vertex shader
in vec3 fragPos;
in vec3 fragNormal;

// Light properties
uniform vec3 lightPos;
uniform vec3 lightColor;

// Material properties
uniform vec3 kd; // Diffuse reflectivity

// Toon shading parameters
uniform int toonDiscretize;

// Output color
out vec4 outColor;

void main() {
    // Normalize the normal vector
    vec3 normal = normalize(fragNormal);

    // Calculate the light direction
    vec3 lightDir = normalize(lightPos - fragPos);

    // Calculate the diffuse component
    float diff = max(dot(normal, lightDir), 0.0);

    // Quantize the diffuse component
    float quantizedDiff = floor(diff * toonDiscretize) / toonDiscretize;

    // Calculate the final color
    vec3 color = quantizedDiff * lightColor * kd;

    // Set the output color
    outColor = vec4(color, 1.0);
}