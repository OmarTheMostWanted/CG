#pragma once
#include <algorithm>
#include <map>
#include <numeric>
#include <set>
#include <span>
#include <tuple>
#include <vector>
#include <queue>

struct Tree;

////////////////// Exercise 1 ////////////////////////////////////
std::pair<float, float> Statistics(std::span<const float> values)
{
    if (values.empty())
    {
        return {0.0f, 0.0f};
    }

    auto mean = 0.0f;
    auto variance = 0.0f;
    for (const auto& value : values)
    {
        mean += value;
    }
    mean /= static_cast<float>(values.size());
    for (const auto& value : values)
    {
        variance += (value - mean) * (value - mean);
    }
    variance /= static_cast<float>(values.size());
    return {mean, std::sqrt(variance)};
}
//////////////////////////////////////////////////////////////////

////////////////// Exercise 2 ////////////////////////////////////
class TreeVisitor {
public:
    float visitTree(const Tree& tree, bool countOnlyEvenLevels)
    {
        return visitTreeHelper(tree, countOnlyEvenLevels, 0);
    }
private:
    float visitTreeHelper(const Tree& tree, bool countOnlyEvenLevels, int level) {  // NOLINT
        float sum = 0.0f;
        if (!countOnlyEvenLevels || (level % 2 == 0)) {
            sum += tree.value;
        }
        for (const auto& child : tree.children) {
            sum += visitTreeHelper(child, countOnlyEvenLevels, level + 1);
        }
        return sum;
    }
};
//////////////////////////////////////////////////////////////////

////////////////// Exercise 3 ////////////////////////////////////
class Complex {
public:
    Complex(float real_, float imaginary_)
    {
        this -> real = real_;
        this -> im = imaginary_;
    }

    //overload operators
    Complex operator+(const Complex& c) const
    {
        return {real + c.real, im + c.im};
    }

    Complex operator-(const Complex& c) const
    {
        return {real - c.real, im - c.im};
    }

    Complex operator*(const Complex& c) const
    {
        return {real * c.real - im * c.im, real * c.im + im * c.real};
    }

    Complex operator/(const Complex& c) const
    {
        return {(real * c.real + im * c.im) / (c.real * c.real + c.im * c.im), (im * c.real - real * c.im) / (c.real * c.real + c.im * c.im)};
    }


    float real, im;
};
//////////////////////////////////////////////////////////////////

////////////////// Exercise 4 ////////////////////////////////////
float WaterLevels(std::span<const float> heights)
{
    auto size = heights.size();
    float water = 0.0f;

    if (size < 3)
    {
        return water;
    }

    unsigned long left = 0;
    unsigned long right = size - 1;
    float leftMax = heights[left];
    float rightMax = heights[right];

    while (left < right)
    {
        if (heights[left] < heights[right])
        {
            left++;
            leftMax = std::max(leftMax, heights[left]);
            water += std::max(0.0f, leftMax - heights[left]);
        }
        else
        {
            right--;
            rightMax = std::max(rightMax, heights[right]);
            water += std::max(0.0f, rightMax - heights[right]);
        }
    }

    return water;
}
//////////////////////////////////////////////////////////////////

////////////////// Exercise 5 ////////////////////////////////////
using location = std::pair<int, int>;

int Labyrinth(const std::set<std::pair<location, location>>& labyrinth, int size)
{
    if (size <= 0) return 0;

    std::queue<std::pair<location, int>> q;
    std::set<location> visited;
    std::vector<location> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    q.push({{0, 0}, 1});
    visited.insert({0, 0});

    while (!q.empty())
    {
        auto [current, distance] = q.front();
        q.pop();

        if (current == location(size - 1, size - 1))
        {
            return distance;
        }

        for (const auto& dir : directions)
        {
            location next = {current.first + dir.first, current.second + dir.second};

            if (next.first >= 0 && next.first < size && next.second >= 0 && next.second < size &&
                visited.find(next) == visited.end() &&
                labyrinth.find({current, next}) == labyrinth.end() &&
                labyrinth.find({next, current}) == labyrinth.end())
            {
                q.emplace(next, distance + 1);
                visited.insert(next);
            }
        }
    }

    return 0;
}
//////////////////////////////////////////////////////////////////
