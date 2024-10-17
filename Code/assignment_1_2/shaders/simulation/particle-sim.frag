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

uniform int collisionThreshold;
uniform int blinkDuration;


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
    vec3 previousBounceData = texelFetch(previousBounceData, ivec2(particleIndex, 0), 0).rgb;

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
    finalBounceData = previousBounceData;

    // ===== Task 1.3 Inter-particle Collision =====
    if (interParticleCollision) {
        for (uint i = 0; i < numParticles; ++i) {
            if (i == particleIndex) continue; // Skip self-collision check

            // Sample the position of the other particle
            vec3 otherPosition = texelFetch(previousPositions, ivec2(i, 0), 0).rgb;

            // Calculate the distance to the other particle
            vec3 toOther = newPosition - otherPosition;
            float distanceToOther = length(toOther);

            // Check if a collision has occurred
            if (distanceToOther < 2.0 * particleRadius) {
                // Calculate the normal at the point of collision
                vec3 normal = normalize(toOther);

                // Adjust the position to push the particle away from the other particle
                newPosition = otherPosition + normal * (2.0 * particleRadius * 1.01);

                // Reflect the velocity about the normal
                newVelocity = reflect(newVelocity, normal);

                // Increment collision counter
                previousBounceData.x += 1.0;
            }
        }
    }
    
    // ===== Task 1.2 Container Collision =====
    // Calculate the distance from the particle to the center of the container
    vec3 toCenter = newPosition - containerCenter;
    float distanceToCenter = length(toCenter);

    // Check if the particle is outside the container
    if (distanceToCenter + particleRadius > containerRadius) {
        // Calculate the normal at the point of collision
        vec3 normal = normalize(toCenter);

        // Adjust the position to push the particle back inside the container
        newPosition = containerCenter + normal * (containerRadius - particleRadius * 1.01);

        // Reflect the velocity about the normal
        newVelocity = reflect(newVelocity, normal);

        // Increment collision counter
        previousBounceData.x += 1.0;
    }

    // Handle blinking
    if (previousBounceData.x >= float(collisionThreshold)) {
        previousBounceData.x = 0.0;
        previousBounceData.y = float(blinkDuration);
    }

    if (previousBounceData.y > 0.0) {
        previousBounceData.y -= 1.0;
    }

    // Output the new position and velocity
    finalPosition = newPosition;
    finalVelocity = newVelocity;

    // For now, pass through the previous bounce data
//    finalBounceData = texelFetch(previousBounceData, ivec2(particleIndex, 0), 0).rgb;
    finalBounceData = previousBounceData;

}
