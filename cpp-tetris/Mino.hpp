#pragma once

#include "Tetris.hpp"

struct IMinoData
{
    virtual ~IMinoData() = default;
    virtual bool operator()(Direction dir, index_type y, index_type x) const = 0;
    virtual index_type height() const noexcept = 0;
    virtual index_type width() const noexcept = 0;
    virtual MinoType type() const noexcept = 0;
};

class Mino : public IMino
{
public:
    Mino(const IMinoData& data, index_type positionY, index_type positionX, Direction dir = Direction::NORTH)
        : data(data), positionY(positionY), positionX(positionX), dir(dir) {}

    bool operator()(index_type y, index_type x) const override
    {
        const auto [localY, localX] = world2local(y, x);
        if(0 <= localY && localY < data.height() && 0 <= localX && localX < data.width())
            return data(dir, localY, localX);
        else
            return false;
    }

    MinoType type() const noexcept override
    {
        return data.type();
    }

    bool proc(Command cmd, const IGeometry& geo) override
    {
        switch(cmd){
            case Command::MOVE_RIGHT:   return move_right(geo);
            case Command::MOVE_LEFT:    return move_left(geo);
            case Command::MOVE_DOWN:    return move_down(geo);
            case Command::ROTATE_RIGHT: return rotate_right(geo);
            case Command::ROTATE_LEFT:  return rotate_left(geo);
            case Command::HARD_DROP:    return hard_drop(geo);
        }
    }

    bool colliding(const IGeometry& geo) const override
    {
        for(index_type localY = 0; localY < data.height(); ++localY){
            for(index_type localX = 0; localX < data.width(); ++localX){
                if(data(dir, localY, localX)){
                    const auto [y, x] = local2world(localY, localX);
                    if(!(0 <= y && y < MATRIX_HEIGHT && 0 <= x && x < MATRIX_WIDTH)) return true;
                    if(geo(y, x)) return true;
                }
            }
        }
        return false;
    }

    void overwrite(IGeometry& geo) const override
    {
        for(index_type localY = 0; localY < data.height(); ++localY){
            for(index_type localX = 0; localX < data.width(); ++localX){
                const auto [y, x] = local2world(localY, localX);
                if(this->operator()(y, x))
                    geo(y, x) = data.type();
            }
        }
    }

private:
    bool move_right(const IGeometry& geo)
    {
        ++positionX;
        if(colliding(geo)){
            --positionX;
            return false;
        }
        else
            return true;
    }

    bool move_left(const IGeometry& geo)
    {
        --positionX;
        if(colliding(geo)){
            ++positionX;
            return false;
        }
        else
            return true;
    }

    bool move_down(const IGeometry& geo)
    {
        ++positionY;
        if(colliding(geo)){
            --positionY;
            return false;
        }
        else
            return true;
    }

    bool rotate_right(const IGeometry& geo)
    {
        ++dir;
        if(colliding(geo)){
            --dir;
            return false;
        }
        else
            return true;
    }

    bool rotate_left(const IGeometry& geo)
    {
        --dir;
        if(colliding(geo)){
            ++dir;
            return false;
        }
        else
            return true;
    }

    bool hard_drop(const IGeometry& geo)
    {
        if(!move_down(geo)) return false;
        while(move_down(geo));
        return true;
    }

    std::pair<index_type, index_type> world2local(index_type y, index_type x) const
    {
        return {y - positionY, x - positionX};
    }

    std::pair<index_type, index_type> local2world(index_type localY, index_type localX) const
    {
        return {positionY + localY, positionX + localX};
    }

private:
    const IMinoData& data;
    index_type positionY;
    index_type positionX;
    Direction dir;
};
