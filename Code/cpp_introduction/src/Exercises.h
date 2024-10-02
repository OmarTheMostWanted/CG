#pragma once
#include <algorithm>
#include <map>
#include <numeric>
#include <set>
#include <span>
#include <tuple>
#include <vector>

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
    float visitTreeHelper(const Tree& tree, bool countOnlyEvenLevels, int level) {
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
        return Complex(real + c.real, im + c.im);
    }

    Complex operator-(const Complex& c) const
    {
        return Complex(real - c.real, im - c.im);
    }

    Complex operator*(const Complex& c) const
    {
        return Complex(real * c.real - im * c.im, real * c.im + im * c.real);
    }

    Complex operator/(const Complex& c) const
    {
        return Complex((real * c.real + im * c.im) / (c.real * c.real + c.im * c.im), (im * c.real - real * c.im) / (c.real * c.real + c.im * c.im));
    }


    float real, im;
};
//////////////////////////////////////////////////////////////////

////////////////// Exercise 4 ////////////////////////////////////
float WaterLevels(std::span<const float> heights)
{

    auto size = heights.size();
    float water = 0.0f;

    if (heights.size() < 3)
    {
        return water;
    }

    float leftMax = heights[0];;
    float rightMax = -INFINITY;

    for (int i = 1; i < size; i++)
    {
        for (int j = i++ ; j < size; ++j)
        {
            rightMax = std::max(rightMax, heights[j]);
            if (heights[j] >= heights[i]) // if we find a height greater than the leftmost height, we can calculate the water trapped
            {
                for (int k = i; k < j; ++k)
                {
                    water += std::min(leftMax, rightMax) - heights[k];
                }
                break;
            }
            leftMax = rightMax;
            i = j;
        }
    }
}
//////////////////////////////////////////////////////////////////

////////////////// Exercise 5 ////////////////////////////////////
using location = std::pair<int, int>;

int Labyrinth(const std::set<std::pair<location, location>>& labyrinth, int size)
{
    return 0;
}
//////////////////////////////////////////////////////////////////
