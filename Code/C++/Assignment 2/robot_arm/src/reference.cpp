#include "reference.h"
#include <cassert>
#include <fstream>

ReferenceSolutionLoader::ReferenceSolutionLoader(const std::filesystem::path& filePath)
{
    assert(std::filesystem::exists(filePath));

    std::fstream file { filePath, std::ios::binary | std::ios::in };
    //return;
    while (!file.eof()) {
        Solution solution {};
        size_t numSegments { 0 };
        file.read(reinterpret_cast<char*>(&numSegments), sizeof(numSegments));

        solution.armSegments.resize(numSegments);
        file.read(reinterpret_cast<char*>(solution.armSegments.data()), solution.armSegments.size() * sizeof(solution.armSegments[0]));

        solution.transforms.resize(numSegments);
        file.read(reinterpret_cast<char*>(solution.transforms.data()), solution.transforms.size() * sizeof(solution.transforms[0]));

        m_solutions.push_back(solution);
    }
    // Closes 1 too late?
    m_solutions.resize(m_solutions.size() - 1);
}

int ReferenceSolutionLoader::getNumReferenceSolutions() const
{
    return static_cast<int>(m_solutions.size());
}

std::vector<glm::mat4> ReferenceSolutionLoader::getReferenceSolution(int id, gsl::span<ArmSegment> armSegments) const
{
    const auto& solution = m_solutions[id];
    assert(solution.armSegments.size() == armSegments.size());
    std::copy(std::begin(solution.armSegments), std::end(solution.armSegments), std::begin(armSegments));
    return solution.transforms;
}
