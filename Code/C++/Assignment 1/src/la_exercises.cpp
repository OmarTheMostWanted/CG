#include "la_exercises.h"
#include <cmath>

// Vector/scalar multiply
Vector3 mul(float s, const Vector3 &rhs) {
    // Your solution goes here


    return Vector3{rhs.x * s, rhs.y * s, rhs.z * s};
}

Vector3 add(const Vector3 &lhs, const Vector3 &rhs) {
    // Your solution goes here
    return Vector3{lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

Vector3 sub(const Vector3 &lhs, const Vector3 &rhs) {
    // Your solution goes here
    return Vector3{lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

Vector3 mul(const Vector3 &lhs, const Vector3 &rhs) {
    // Your solution goes here
    return Vector3{lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z};
}

Vector3 div(const Vector3 &lhs, const Vector3 &rhs) {
    // Your solution goes here
    return Vector3{lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z};
}

float dot(const Vector3 &lhs, const Vector3 &rhs) {
    // Your solution goes here
    return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
}

Vector3 cross(const Vector3 &lhs, const Vector3 &rhs) {
    // Your solution goes here
    return Vector3{(lhs.y * rhs.z) - (lhs.z * rhs.y), (lhs.z * rhs.x) - (lhs.x * rhs.z),
                   (lhs.x * rhs.y) - (lhs.y * rhs.x)};
}

float length(const Vector3 &lhs) {
    return std::sqrt(std::pow(lhs.x, 2) + std::pow(lhs.y, 2) + std::pow(lhs.z, 2));
}

Matrix3 add(const Matrix3 &lhs, const Matrix3 &rhs) {
    // Your solution goes here
    return Matrix3{Vector3{lhs.col1.x + rhs.col1.x, lhs.col1.y + rhs.col1.y, lhs.col1.z + rhs.col1.z},
                   Vector3{lhs.col2.x + rhs.col2.x, lhs.col2.y + rhs.col2.y, lhs.col2.z + rhs.col2.z},
                   Vector3{lhs.col3.x + rhs.col3.x, lhs.col3.y + rhs.col3.y, lhs.col3.z + rhs.col3.z}};
}

Matrix3 sub(const Matrix3 &lhs, const Matrix3 &rhs) {
    return Matrix3{Vector3{lhs.col1.x - rhs.col1.x, lhs.col1.y - rhs.col1.y, lhs.col1.z - rhs.col1.z},
                   Vector3{lhs.col2.x - rhs.col2.x, lhs.col2.y - rhs.col2.y, lhs.col2.z - rhs.col2.z},
                   Vector3{lhs.col3.x - rhs.col3.x, lhs.col3.y - rhs.col3.y, lhs.col3.z - rhs.col3.z}};
}

Matrix3 mul(const Matrix3 &lhs, const Matrix3 &rhs) {
    // Your solution goes here
    return Matrix3{Vector3{dot(Vector3{lhs.col1.x, lhs.col2.x, lhs.col3.x}, rhs.col1),
                           dot(Vector3{lhs.col1.y, lhs.col2.y, lhs.col3.y}, rhs.col1),
                           dot(Vector3{lhs.col1.z, lhs.col2.z, lhs.col3.z}, rhs.col1)},
                   Vector3{dot(Vector3{lhs.col1.x, lhs.col2.x, lhs.col3.x}, rhs.col2),
                           dot(Vector3{lhs.col1.y, lhs.col2.y, lhs.col3.y}, rhs.col2),
                           dot(Vector3{lhs.col1.z, lhs.col2.z, lhs.col3.z}, rhs.col2)},
                   Vector3{dot(Vector3{lhs.col1.x, lhs.col2.x, lhs.col3.x}, rhs.col3),
                           dot(Vector3{lhs.col1.y, lhs.col2.y, lhs.col3.y}, rhs.col3),
                           dot(Vector3{lhs.col1.z, lhs.col2.z, lhs.col3.z}, rhs.col3)}
    };

//    return Matrix3{Vector3{dot(Vector3{lhs.col1.x, lhs.col2.x, lhs.col3.x}, rhs.col1),
//                           dot(Vector3{lhs.col1.x, lhs.col2.x, lhs.col3.x}, rhs.col2),
//                           dot(Vector3{lhs.col1.x, lhs.col2.x, lhs.col3.x}, rhs.col3)},
//                   Vector3{dot(Vector3{lhs.col1.y, lhs.col2.y, lhs.col3.y}, rhs.col1),
//                           dot(Vector3{lhs.col1.y, lhs.col2.y, lhs.col3.y}, rhs.col2),
//                           dot(Vector3{lhs.col1.y, lhs.col2.y, lhs.col3.y}, rhs.col3)},
//                   Vector3{dot(Vector3{lhs.col1.z, lhs.col2.z, lhs.col3.z}, rhs.col1),
//                           dot(Vector3{lhs.col1.z, lhs.col2.z, lhs.col3.z}, rhs.col2),
//                           dot(Vector3{lhs.col1.z, lhs.col2.z, lhs.col3.z}, rhs.col3)}
}

Vector3 mul(const Matrix3 &lhs, const Vector3 &rhs) {
    // Your solution goes here
    return Vector3{dot(Vector3{lhs.col1.x, lhs.col2.x, lhs.col3.x}, rhs),
                   dot(Vector3{lhs.col1.y, lhs.col2.y, lhs.col3.y}, rhs),
                   dot(Vector3{lhs.col1.z, lhs.col2.z, lhs.col3.z}, rhs)};
}

Matrix3 mul(const Matrix3 &lhs, float rhs) {
    // Your solution goes here
    return Matrix3{mul(rhs, lhs.col1), mul(rhs, lhs.col2), mul(rhs, lhs.col3)};
}

Matrix3 transpose(const Matrix3 &m) {
    // Your solution goes here
    return Matrix3{Vector3{m.col1.x , m.col2.x , m.col3.x},
                   Vector3{m.col1.y , m.col2.y , m.col3.y},
                   Vector3{m.col1.z , m.col2.z , m.col3.z}};
}

float determinant(const Matrix3 &m) {
    // Your solution goes here
    return (m.col1.x * m.col2.y * m.col3.z) + (m.col2.x * m.col3.y * m.col1.z) + (m.col3.x * m.col1.y * m.col2.z) - (m.col3.x * m.col2.y * m.col1.z) - (m.col2.x * m.col1.y * m.col3.z) - (m.col1.x * m.col3.y * m.col2.z) ;
}

Matrix3 inverse(const Matrix3 &matrix) {
    // Your solution goes here
    return mul(transpose(matrix) , 1/determinant(matrix));
}
