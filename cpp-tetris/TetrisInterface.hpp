#pragma once

enum class Command
{
    MOVE_RIGHT, MOVE_LEFT, MOVE_DOWN, ROTATE_RIGHT, ROTATE_LEFT, HARD_DROP,
};

struct Cell
{
    enum CellEnum
    {
        EMPTY, I, O, T, S, Z, L, J, B
    };

    Cell() noexcept : value() {}
    Cell(CellEnum value_) noexcept : value{value_} {}

    operator CellEnum() const noexcept
    {
        return value;
    }

    CellEnum value;
};

using index_type = int;

const index_type MATRIX_HEIGHT = 10;
const index_type MATRIX_WIDTH  = 10;

struct ITetris
{
    virtual ~ITetris() = default;
    virtual void start() = 0;
    virtual Cell operator()(index_type y, index_type x) const = 0;
    virtual bool proc(Command cmd) = 0;
};
