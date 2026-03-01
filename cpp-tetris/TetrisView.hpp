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

    char operator()(index_type y, index_type x) const
    {
        switch(tetris(y, x)){
            case Cell::EMPTY: return ' ';
            case Cell::I: return 'I';
            case Cell::O: return 'O';
            case Cell::T: return 'T';
            case Cell::S: return 'S';
            case Cell::Z: return 'Z';
            case Cell::L: return 'L';
            case Cell::J: return 'J';
            case Cell::B: return 'B';
        }
        std::unreachable();
    }

private:
    ITetris& tetris;
};