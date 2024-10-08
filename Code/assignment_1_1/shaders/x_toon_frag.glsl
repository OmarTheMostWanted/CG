#version 410

in vec3 fragPos;
in vec3 fragNormal;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 kd;
uniform sampler2D texToon;

out vec4 outColor;

void main() {
    vec3 normal = normalize(fragNormal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);

    // Use the brightness value to look up a color in the texture
    vec3 toonColor = texture(texToon, vec2(diff, 0.0)).rgb;
    vec3 diffuse = toonColor * lightColor * kd;

    outColor = vec4(diffuse, 1.0);
}