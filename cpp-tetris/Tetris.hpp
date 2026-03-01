#pragma once

#include <memory>
#include <utility>
#include <random>
#include "TetrisInterface.hpp"

struct MinoType
{
    enum MinoTypeEnum
    {
        I, O, T, S, Z, L, J
    };
    static const int MAX = 7;

    MinoType() noexcept : value() {}
    MinoType(MinoTypeEnum value_) noexcept : value(value_) {}

    operator MinoTypeEnum() const noexcept
    {
        return value;
    }
    
    operator Cell() const noexcept
    {
        switch (value){
            case I: return Cell::I;
            case O: return Cell::O;
            case T: return Cell::T;
            case S: return Cell::S;
            case Z: return Cell::Z;
            case L: return Cell::L;
            case J: return Cell::J;
        }
        std::unreachable();
    }

    MinoTypeEnum value;
};

struct Direction
{
    enum DirectionEnum
    {
        NORTH, EAST, SOUTH, WEST
    };

    Direction(DirectionEnum value_) : value(value_) {}

    operator DirectionEnum() const noexcept
    {
        return value;
    }

    Direction& operator++() noexcept
    {
        value = static_cast<DirectionEnum>((value + 1) % 4);
        return *this;
    }

    Direction& operator--() noexcept
    {
        value = static_cast<DirectionEnum>((value - 1 + 4) % 4);
        return *this;
    }

    DirectionEnum value;
};

struct IMino;

struct IGeometry
{
    virtual ~IGeometry() = default;
    virtual Cell operator()(index_type y, index_type x) const = 0;
    virtual Cell& operator()(index_type y, index_type x) = 0;
    virtual void reset() = 0;
};

struct IMino
{
    virtual ~IMino() = default;
    virtual bool operator()(index_type y, index_type x) const = 0;
    virtual MinoType type() const noexcept = 0;
    virtual bool proc(Command cmd, const IGeometry& geo) = 0;
    virtual bool colliding(const IGeometry& geo) const = 0;
    virtual void overwrite(IGeometry& geo) const = 0;
};

struct IMinoFactory
{
    virtual ~IMinoFactory() = default;
    virtual std::unique_ptr<IMino> create(MinoType type, index_type y, index_type x) const = 0;
};

class Tetris : public ITetris
{
public:
    Tetris(std::unique_ptr<IGeometry>&& geo_, std::unique_ptr<IMinoFactory>&& factory_)
        : geo(std::move(geo_)), factory(std::move(factory_)), mino(), in_game_flag(), seed_gen(), engine(seed_gen())
    {
        if(!(this->geo && this->factory)) throw std::exception();
    }

    void start() override
    {
        in_game_flag = true;
        geo->reset();
        randamly_spone();
    }

    Cell operator()(index_type y, index_type x) const override
    {
        if(mino && (*mino)(y, x)){
            const Cell c = mino->type();
            return c ? c : (*geo)(y, x);
        }
        return (*geo)(y, x);
    }

    bool proc(Command cmd) override
    {
        if(mino){
            const bool moved = mino->proc(cmd, *geo);
            if(!moved && (cmd == Command::MOVE_DOWN || cmd == Command::HARD_DROP)){
                mino->overwrite(*geo);
                randamly_spone();
                if(mino->colliding(*geo)){
                    mino.release();
                    in_game_flag = false;
                }
            }
        }
        return in_game_flag;
    }

private:
    void randamly_spone()
    {
        MinoType type = static_cast<MinoType::MinoTypeEnum>(engine() % MinoType::MAX);
        mino = factory->create(type, 0, MATRIX_WIDTH / 2);
    }

private:
    std::unique_ptr<IGeometry> geo;
    std::unique_ptr<IMinoFactory> factory;
    std::unique_ptr<IMino> mino;

    bool in_game_flag;
    std::random_device seed_gen;
    std::mt19937 engine;
};