#version 410

// Input from vertex shader
in vec3 fragPos;
in vec3 fragNormal;

// Light properties
uniform vec3 lightPos;
uniform vec3 lightColor;

// Material properties
uniform vec3 kd; // Diffuse reflectivity
uniform vec3 ks; // Specular reflectivity
uniform float shininess; // Shininess coefficient

// Camera position
uniform vec3 viewPos;

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

    // Calculate the diffuse component
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * kd;

    // Calculate the specular component
    float spec = pow(max(dot(normal, halfwayDir), 0.0), shininess);
    vec3 specular = spec * lightColor * ks;

    // Combine the components
    vec3 color = diffuse + specular;

    // Set the output color
    outColor = vec4(color, 1.0);
}