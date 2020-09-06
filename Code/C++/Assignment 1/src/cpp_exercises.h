// ==============================================
// ========   DO NOT MODIFY THIS FILE!   ========
// ==============================================
// ==> Implementation should go in cpp_exercises.cpp!
#pragma once
#include <gsl/span>
#include <tuple>
#include <vector>

// Exercise 1.
std::pair<float, float> statistics(gsl::span<const float> values);

// Exercise 2.
struct Tree {
    float value;
    std::vector<Tree> children;
};
float countTree(const Tree& t, bool countOnlyEvenLevels);