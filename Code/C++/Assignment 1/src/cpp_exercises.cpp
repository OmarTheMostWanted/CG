#include "cpp_exercises.h"
#include <cmath>
#include <iostream>

// ==================================
// ========    Exercise 1    ========
// ==================================
std::pair<float, float> statistics(gsl::span<const float> values) {
    // Your solution goes here
    if (values.empty())
        return {0.0f, 0.0f};

    int avg = 0;

    for (int i : values) {
        avg += i;
    }

    avg /= values.size();

    int st = 0;

    for (int i : values) {
        st += std::pow(i - avg, 2);
    }

    st /= (values.size() - 1);

    st = std::sqrt(st);

    return {avg, st};


}

// ==================================
// ========    Exercise 2    ========
// ==================================
float visitTree(const Tree &tree, bool isEvenLevel, bool countOnlyEvenLevels) {

    float count = 0;
    for (auto &c : tree.children) {
        count += visitTree(c, !isEvenLevel, countOnlyEvenLevels);
    }
    if (isEvenLevel && countOnlyEvenLevels || !countOnlyEvenLevels) return tree.value + count;
    else return count;

}

// Your implementation goes here. Feel free to define helper functions/structs/classes in this
// file if you need to. Make sure to put them above this function to prevent linker warnings.
float countTree(const Tree &tree, bool countOnlyEvenLevels) {

    float res = visitTree(tree, true, countOnlyEvenLevels);

    std::cout << res << "\n";

    return res;

}
