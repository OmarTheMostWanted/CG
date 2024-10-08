
#version 410

in vec3 fragPos;
in vec3 fragNormal;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 ks;
uniform float shininess;
uniform vec3 viewPos;
uniform float toonSpecularThreshold;

out vec4 outColor;

void main() {
    vec3 normal = normalize(fragNormal);
    vec3 lightDir = normalize(lightPos - fragPos);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);

    // Calculate the specular component
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    // Apply toon threshold
    spec = spec > toonSpecularThreshold ? 1.0 : 0.0;
    vec3 specular = spec * lightColor * ks;

    outColor = vec4(specular, 1.0);
}

//#version 410
//
//// Input from vertex shader
//in vec3 fragPos;
//in vec3 fragNormal;
//
//// Light properties
//uniform vec3 lightPos;
//uniform vec3 lightColor;
//
//// Material properties
//uniform vec3 ks; // Specular reflectivity
//uniform float shininess; // Shininess coefficient
//
//// Camera position
//uniform vec3 viewPos;
//
//// Toon shading parameters
//uniform float toonSpecularThreshold;
//
//// Output color
//out vec4 outColor;
//
//void main() {
//    // Normalize the normal vector
//    vec3 normal = normalize(fragNormal);
//
//    // Calculate the light direction
//    vec3 lightDir = normalize(lightPos - fragPos);
//
//    // Calculate the view direction
//    vec3 viewDir = normalize(viewPos - fragPos);
//
//    // Calculate the halfway vector
//    vec3 halfwayDir = normalize(lightDir + viewDir);
//
//    // Calculate the specular component using Blinn-Phong model
//    float spec = pow(max(dot(normal, halfwayDir), 0.0), shininess);
//
//    // Apply toon shading to the specular component
//    if (spec >= toonSpecularThreshold) {
//        outColor = vec4(1.0); // White color for specular highlight
//    } else {
//        outColor = vec4(0.0); // Black color otherwise
//    }
//}