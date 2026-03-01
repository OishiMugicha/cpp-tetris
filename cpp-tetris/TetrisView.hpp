#pragma once

#include <iostream>
#include <utility>
#include "TetrisInterface.hpp"

class TetrisView
{
public:
    TetrisView(ITetris& tetris_) : tetris(tetris_) {}

    void start()
    {
        tetris.start();
    }

    void proc(Command cmd)
    {
        tetris.proc(cmd);
    }

    Cell operator()(index_type y, index_type x) const
    {
        return tetris(y, x);
    }

private:
    ITetris& tetris;
};