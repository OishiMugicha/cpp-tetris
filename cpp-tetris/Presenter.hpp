#pragma once

#include "TetrisView.hpp"
#include "TetrisInterface.hpp"
#include "Tetris.hpp"
#include "Geometry.hpp"
#include "MinoFactory.hpp"
#include "MinoDataContainer.hpp"
#include "MinoDataSet.hpp"

class Presenter
{
public:
    Presenter() : tetris
        ( std::make_unique<Geometry>()
        , std::make_unique<MinoFactory>(dataContainer))
    {}

    TetrisView make_view()
    {
        return TetrisView(tetris);
    }

private:
    Tetris tetris;
    static const MinoDataContainer dataContainer;
};

const MinoDataContainer Presenter::dataContainer(minoDataSet);