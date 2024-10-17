#version 410
#extension GL_ARB_explicit_uniform_location : enable

uniform sampler2D previousPositions;
uniform sampler2D previousVelocities;
uniform sampler2D previousBounceData;
uniform float timestep;
uniform uint numParticles;
uniform float particleRadius;
uniform vec3 containerCenter;
uniform float containerRadius;
uniform bool interParticleCollision;

layout(location = 0) out vec3 finalPosition;
layout(location = 1) out vec3 finalVelocity;
layout(location = 2) out vec3 finalBounceData;

void main() {
    // ===== Task 1.1 Verlet Integration =====
    // Get the current particle index
    uint particleIndex = uint(gl_FragCoord.x);

    // Sample the previous position and velocity
    vec3 previousPosition = texelFetch(previousPositions, ivec2(particleIndex, 0), 0).rgb;
    vec3 previousVelocity = texelFetch(previousVelocities, ivec2(particleIndex, 0), 0).rgb;

    // Define the acceleration due to gravity
    vec3 acceleration = vec3(0.0, -9.81, 0.0);

    // Compute the new position using Velocity Verlet integration
    vec3 newPosition = previousPosition + previousVelocity * timestep + 0.5 * acceleration * timestep * timestep;

    // Compute the new velocity
    vec3 newVelocity = previousVelocity + 0.5 * (acceleration + acceleration) * timestep;

    // Output the new position and velocity
    finalPosition = newPosition;
    finalVelocity = newVelocity;

    // For now, pass through the previous bounce data
    finalBounceData = texelFetch(previousBounceData, ivec2(particleIndex, 0), 0).rgb;

    // ===== Task 1.3 Inter-particle Collision =====
    if (interParticleCollision) {
    }
    
    // ===== Task 1.2 Container Collision =====

}
