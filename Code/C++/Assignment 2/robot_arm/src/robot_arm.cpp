#include "robot_arm.h"
// Suppress warnings in third-party code.
#include "disable_all_warnings.h"

DISABLE_WARNINGS_PUSH()

#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <gsl-lite/gsl-lite.hpp>

DISABLE_WARNINGS_POP()

#include <vector>

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
// =====   EXERCISE 1  =====
// =========================
// We want to draw a robot arm constisting of multiple segment. Each segment is a 3D box with a varying
// width/height/length. Each segment N is connected to it's parent N-1 (the first segment is connected
// to the origin). Segments are connected at the center of the front/back faces of the box. The back
// face (z=0) of a segment N is connected to segment N-1 (or the origin if N==0) and the front
// face (z=1) is connected to segment N+1 (if any).
//
// We will draw this arm by transforming unit cubes into boxes of the correct shape and translating /
// rotating them into their corresponding positions.This function should compute the matrices that perform
// these transformations. Given a list of arm segments compute the associated matrices and return them as
// a vector (where the nth matrix corresponds to the nth arm segment). Rotations should be performed around
// the positive x axis (glm::vec3(1, 0, 0)).
std::vector<glm::mat4> computeRobotArmTransforms(gsl::span<const ArmSegment> armSegments) {
    // For each celestrial body, compute the matrix which scales the object (a box from (0, 0, 0) to (1, 1, 1)),
    //  translates and rotates it such that it forms a robot arm.
    std::vector<glm::mat4> transforms;

    int count = 0;
    for (const ArmSegment &armSegment : armSegments) {
        count++;

        glm::mat4 matrix = glm::identity<glm::mat4>();

        //for each new segment redo all transformations.
        for (auto &prevArm : armSegments) {

            if (&prevArm != &armSegment) {

                //the scalings dont add up, but the Z value needs to be changed
                glm::mat4 translatetomiddlepriv = translationMatrix( glm::vec3(0 , 0 , prevArm.boxSize.z));
                glm::mat4 rotationmatrixpriv = rotationMatrix(prevArm.rotationX, {1, 0, 0});
                matrix *= rotationmatrixpriv * translatetomiddlepriv;
            }
            else break;
        }


        glm::mat4 translatetomiddle = translationMatrix( glm::vec3(-0.5f , -0.5 , 0));
        glm::mat4 rotationmatrix = rotationMatrix(armSegment.rotationX, {1, 0, 0});
        glm::mat4 scalematrix = scaleMatrix(armSegment.boxSize);



        matrix *=rotationmatrix * scalematrix * translatetomiddle;


        transforms.push_back(matrix);
        count++;
    }
    return transforms;
}
