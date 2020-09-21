#pragma once
#include "disable_all_warnings.h"
#include "solar_system.h"
DISABLE_WARNINGS_PUSH()
#include <gsl-lite/gsl-lite.hpp>
DISABLE_WARNINGS_POP()
#include <filesystem>
#include <vector>

class ReferenceSolutionLoader {
public:
    ReferenceSolutionLoader(const std::filesystem::path& file);

    int getNumReferenceSolutions() const;
    std::vector<glm::mat4> getReferenceSolution(int id, float& time, gsl::span<CelestrialBody> bodies) const;

private:
    struct Solution {
        float time;
        std::vector<CelestrialBody> bodies;
        std::vector<glm::mat4> transforms;
    };

    std::vector<Solution> m_solutions;
};