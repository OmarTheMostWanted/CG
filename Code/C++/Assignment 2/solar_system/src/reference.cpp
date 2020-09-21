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
        file.read(reinterpret_cast<char*>(&solution.time), sizeof(solution.time));
        size_t numBodies { 0 };
        file.read(reinterpret_cast<char*>(&numBodies), sizeof(numBodies));

        solution.bodies.resize(numBodies);
        //file.read(reinterpret_cast<char*>(solution.bodies.data()), solution.bodies.size() * sizeof(solution.bodies[0]));
        for (auto& body : solution.bodies) {
            file.read(reinterpret_cast<char*>(&body.radius), sizeof(float));
            file.read(reinterpret_cast<char*>(&body.spinPeriod), sizeof(float));
            file.read(reinterpret_cast<char*>(&body.orbitAltitude), sizeof(float));
            file.read(reinterpret_cast<char*>(&body.orbitPeriod), sizeof(float));
        }

        solution.transforms.resize(numBodies);
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

std::vector<glm::mat4> ReferenceSolutionLoader::getReferenceSolution(int id, float& time, gsl::span<CelestrialBody> bodies) const
{
    const auto& solution = m_solutions[id];
    time = solution.time;
    assert(solution.bodies.size() == bodies.size());

    for (size_t i = 0; i < bodies.size(); i++) {
        // Don't copy name / texture (std::string is not trivially copyable).
        bodies[i].radius = solution.bodies[i].radius;
        bodies[i].spinPeriod = solution.bodies[i].spinPeriod;
        bodies[i].orbitAltitude = solution.bodies[i].orbitAltitude;
        bodies[i].orbitPeriod = solution.bodies[i].orbitPeriod;
    }

    return solution.transforms;
}
