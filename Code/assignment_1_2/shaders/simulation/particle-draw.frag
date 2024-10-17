#version 410

uniform vec3 containerCenter;

uniform bool useSpeedBasedColor;
uniform vec3 colorAtZeroSpeed;
uniform vec3 colorAtMaxSpeed;
uniform float maxSpeed;

uniform bool useShading;
uniform float ambientCoefficient;
uniform float diffuseCoefficient;

layout(location = 0) in vec3 fragPosition;
layout(location = 1) in vec3 fragNormal;
layout(location = 2) in vec3 fragVelocity;
layout(location = 3) in vec3 fragBounceData;

layout(location = 0) out vec4 fragColor;

void main() {
    vec3 baseColor = vec3(1.0);

    // ===== Task 2.1 Speed-based Colors =====

    if (useSpeedBasedColor) {
        float speed = length(fragVelocity);
        float t = clamp(speed / maxSpeed, 0.0, 1.0);
        baseColor = mix(colorAtZeroSpeed, colorAtMaxSpeed, t);
    }


    vec3 finalColor = baseColor;

    // ===== Task 2.2 Shading =====
    if (useShading) {
        vec3 lightDir = normalize(containerCenter - fragPosition);
        float diffuse = max(dot(fragNormal, lightDir), 0.0);

        finalColor = ambientCoefficient * baseColor + diffuseCoefficient * diffuse * baseColor;
    }

    fragColor = vec4(finalColor, 1.0);
}
