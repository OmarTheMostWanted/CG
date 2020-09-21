#include "solar_system.h"
// Suppress warnings in third-party code.
#include "disable_all_warnings.h"

DISABLE_WARNINGS_PUSH()

#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <gsl-lite/gsl-lite.hpp>

DISABLE_WARNINGS_POP()

// ===============================
// =====   HELPER FUNCTIONS  =====
// ===============================
// glm::scale / glm::translate / glm::translate apply the matrices in reverse order.
// E.g. calling glm::rotate(glm::translate(inMatrix, ...), ...) will first rotate and then
// translate (reversed order in which the C++ functions are called). We provide these simple
// helpers methods that return a scale/translation/rotation matrix matrix so that you can
// decide on the multiplication order yourself.
glm::mat4 rotationMatrix(float angle, const glm::vec3 &axis) {
    return glm::rotate(glm::identity<glm::mat4>(), angle, axis);
}

glm::mat4 translationMatrix(const glm::vec3 &translation) {
    return glm::translate(glm::identity<glm::mat4>(), translation);
}

glm::mat4 scaleMatrix(const glm::vec3 &scale) {
    return glm::scale(glm::identity<glm::mat4>(), scale);
}

// =========================
// =====   EXERCISE 2  =====
// =========================
// Compute the positions/orientations of the solar system (list of celestrial bodies) at the given time.
// Orbiting should not impact the spin of the body in any way. E.g. if the body had zero spin and was
// orbiting around another body then it should not rotate at all (only translate). If you implement
// orbit/spin correctly then the earth should always see the same side of the moon.
//
// Both spin and orbiting should be performed around the positive Y axis (glm::vec3(0, 1, 0)).
std::vector<glm::mat4>
computeCelestrialBodyTransformations(gsl::span<const CelestrialBody> celestrialBodies, float time) {
    // For each celestrial body, compute the matrix which scales the object (relative to a sphere at the origin with radius=1),
    //  translates and rotates it such that it respects the orbit / spin / scale stored in the input.
    std::vector<glm::mat4> transforms;
    for (const CelestrialBody &body : celestrialBodies) {
        // Your implementation goes here

        glm::mat4 matrix = glm::identity<glm::mat4>();

        //if its not the sun
        if (body.pOrbitAround != NULL) {
//            float speed = body.orbitPeriod / (body.orbitAltitude * glm::pi<float>());
//            float rotate = speed * time;
            float angle = (time/ body.orbitPeriod)*2*glm::pi<float>(); //find the angle of orbit at a given time


            glm::mat4 rotationmatrix = rotationMatrix(angle, glm::vec3{0, 1, 0});

//            glm::mat4 transformationmatrix = translationMatrix(glm::vec3 {body.orbitAltitude , 0 , 0});
//            matrix =  rotationmatrix * transformationmatrix;

            //use a vector to set planet position, to not cause the planet to spin
            glm::vec4 orbitPos = rotationmatrix * glm::vec4 {body.orbitAltitude , 0 , 0 ,1};

            if(body.pOrbitAround->pOrbitAround){ // if its a moon


                // move the origin towards the parent planet
                float angleEarth = (time/ body.pOrbitAround->orbitPeriod)*2*glm::pi<float>();
                glm::mat4 rotationmatrixEarth = rotationMatrix(angleEarth , glm::vec3{0 , 1 ,0});
                glm::vec4 orbitPosEarth = rotationmatrixEarth * glm::vec4 {(body.pOrbitAround)->orbitAltitude , 0 , 0 ,1};
                //

                //move the vector to the moons postion.
                orbitPos = orbitPos + orbitPosEarth;
            }

            //multiply position vector with the unity matrix
            matrix = translationMatrix(orbitPos);
        }

        //make the planets spin
        float spin = (time / body.spinPeriod) *2 * glm::pi<float>();
        matrix = matrix* rotationMatrix(spin , glm::vec3(0,1,0));
        //

        matrix  = matrix * scaleMatrix(glm::vec3 { body.radius , body.radius , body.radius });

        transforms.push_back(matrix);
    }
    return transforms;
}