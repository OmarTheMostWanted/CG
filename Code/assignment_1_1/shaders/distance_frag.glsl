#version 410

in vec3 fragPos;
in vec3 fragNormal;


uniform vec3 viewPos;
out vec4 outColor;

void main() {
    float distance = length(viewPos - fragPos);
    float gray = clamp(distance / 3.0, 0.0, 1.0); // Adjust the divisor to control the range
    outColor = vec4(vec3(gray), 1.0);
}