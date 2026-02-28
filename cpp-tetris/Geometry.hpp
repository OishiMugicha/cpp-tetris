#pragma once

#include <array>
#include "Tetris.hpp"

class Geometry : public IGeometry
{
public:
    Geometry() : matrix() {}

    Cell operator()(index_type y, index_type x) const override
    {
        return matrix[y][x];
    }

    Cell& operator()(index_type y, index_type x) override
    {
        return matrix[y][x];
    }

    void reset() override
    {
        matrix = std::array<std::array<Cell, MATRIX_WIDTH>, MATRIX_HEIGHT>{};
    }

private:
    std::array<std::array<Cell, MATRIX_WIDTH>, MATRIX_HEIGHT> matrix;
};