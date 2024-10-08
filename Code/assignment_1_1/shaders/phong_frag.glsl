#version 410

in vec3 fragPos;
in vec3 fragNormal;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 ks;
uniform float shininess;
uniform vec3 viewPos;

out vec4 FragColor;

void main() {
    vec3 normal = normalize(fragNormal);
    vec3 lightDir = normalize(lightPos - fragPos);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);

    // Calculate the specular component
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = spec * lightColor * ks;

    FragColor = vec4(specular, 1.0);
}