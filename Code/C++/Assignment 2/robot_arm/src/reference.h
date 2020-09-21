#pragma once
#include "disable_all_warnings.h"
#include "robot_arm.h"
DISABLE_WARNINGS_PUSH()
#include <gsl-lite/gsl-lite.hpp>
DISABLE_WARNINGS_POP()
#include <filesystem>
#include <vector>

class ReferenceSolutionLoader {
public:
    ReferenceSolutionLoader(const std::filesystem::path& file);

    int getNumReferenceSolutions() const;
    std::vector<glm::mat4> getReferenceSolution(int id, gsl::span<ArmSegment> armSegments) const;

private:
    struct Solution {
        std::vector<ArmSegment> armSegments;
        std::vector<glm::mat4> transforms;
    };

    std::vector<Solution> m_solutions;
};