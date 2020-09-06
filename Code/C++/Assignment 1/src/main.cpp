#include "cpp_exercises.h"
#include "la_exercises.h"
#include <cassert>
#include <cmath>
#include <iostream>

void fillTree(Tree& tree, int level)
{
    tree.value = 2.0f * static_cast<float>(level);
    if (level >= 4)
        return;

    Tree child;
    fillTree(child, level + 1);

    for (int i = 0; i < level + 2; ++i) {
        tree.children.push_back(child);
    }
}

static constexpr float EPSILON = 10e-3f;
bool equalFloats(float f1, float f2)
{
    return std::abs(f1 - f2) < EPSILON;
}
int main()
{
    // Basic test for exericse 1.
    std::vector<float> stats;
    stats.push_back(-3.0f);
    stats.push_back(-1.0f);
    stats.push_back(1.0f);
    stats.push_back(1.0f);
    stats.push_back(1.0f);
    stats.push_back(3.0f);
    stats.push_back(3.0f);
    stats.push_back(3.0f);

    const std::pair<float, float> statsAnswer = statistics(stats);

    if (equalFloats(statsAnswer.first, 1.0f) && equalFloats(statsAnswer.second, 2.0f)) {
        std::cout << "Exercise 1: Correct for this specific test case" << std::endl;
    } else {
        std::cout << "Exercise 1: Incorrect for this specific test case" << std::endl;
    }

    // Basic test for exericse 2.
    Tree root;
    fillTree(root, 0);
    float visitAnswer1 = countTree(root, false);
    float visitAnswer2 = countTree(root, true);

    if (equalFloats(visitAnswer1, 1132.0f) && equalFloats(visitAnswer2, 984.0f)) {
        std::cout << "Exercise 2: Correct for this specific test case" << std::endl;
    } else {
        std::cout << "Exercise 2: Incorrect for this specific test case" << std::endl;
    }

    // If you want to test your implementation of the linear algebra exercises then you can put them here.
    // Use the equalsFloats function to compare two floating point numbers with an epsilon to prevent tests
    // from failing because of small rounding errors.
    std::cout << "Exercise 3: please add your own tests" << std::endl;
    {
        // Example test for addition...
        const Vector3 a { 1, 2, 3 };
        const Vector3 b { 4, 5, 6 };
        const Vector3 c = add(a, b);
        if (c.x == 5 && c.y == 7 && c.z == 9)
            std::cout << "Vector addition correct" << std::endl;
        else
            std::cout << "Vector addition incorrect" << std::endl;
    }

    std::cout << "All done!" << std::endl;
    return 0;
}
