// ==============================================
// ========   DO NOT MODIFY THIS FILE!   ========
// ==============================================
// ==> Implementation should go in la_exercises.cpp!
#pragma once
#include <array>

// ================================================
// ========    Linear Algebra Exercises    ========
// ================================================
struct Vector3 {
    float x, y, z;
};

// Basic operations of a 3D vector (addition, subtraction, multiplication and division)
Vector3 add(const Vector3& lhs, const Vector3& rhs);
Vector3 sub(const Vector3& lhs, const Vector3& rhs);
Vector3 mul(const Vector3& lhs, const Vector3& rhs);
Vector3 div(const Vector3& lhs, const Vector3& rhs);
// Dot product, cross product and vector length.
// If you need a Linear Algebra refresher, please check out:
// https://www.tudelft.nl/en/eemcs/study/online-education/math-explained/vectors/
float dot(const Vector3& lhs, const Vector3& rhs);
Vector3 cross(const Vector3& lhs, const Vector3& rhs);
float length(const Vector3& lhs);

// The matrix is defined as:
// | m00  m01  m02 |
// | m10  m11  m12 |
// | m20  m21  m22 |
//
// The columns are stored as Vector3's, where:
// col1 = (m00, m10, m20)
// col2 = (m01, m11, m21)
// col3 = (m02, m12, m22)
//
struct Matrix3 {
    Vector3 col1, col2, col3;
};

// Element-wise operations of a 3x3 matrix (addition and subtraction)
Matrix3 add(const Matrix3& lhs, const Matrix3& rhs);
Matrix3 sub(const Matrix3& lhs, const Matrix3& rhs);
// Matrix multiplication with another matrix, a vector and a scalar.
Matrix3 mul(const Matrix3& lhs, const Matrix3& rhs);
Vector3 mul(const Matrix3& lhs, const Vector3& rhs);
Matrix3 mul(const Matrix3& lhs, float rhs);

// Taking the transpose of a matrix means changing it's columns into rows and vice versa.
// Following our previous definition, the transpose of our matrix should look like:
// | m00  m10  m20 |
// | m01  m11  m21 |
// | m02  m12  m22 |
Matrix3 transpose(const Matrix3& matrix);
// The determimant is needed to compute the inverse of a matrix.
// If you need a Linear Algebra refresher, please check out:
// https://www.tudelft.nl/en/eemcs/study/online-education/math-explained/linear-algebra/#c144161
float determinant(const Matrix3& matrix);
// Computing the inverse of the given matrix. If you implemented it correctly then matrix M multiplied
// by its inverse should give the identity matrix). More information on how to compute the inverse of a
// 3x3 matrix can be found here:
// https://www.mathsisfun.com/algebra/matrix-inverse-minors-cofactors-adjugate.html
Matrix3 inverse(const Matrix3& matrix);
