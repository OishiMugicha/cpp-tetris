#pragma once

#include "Mino.hpp"

struct MinoDataStruct
{
    static const index_type MINOSIZE_MAX = 4;
    using Shape = std::array<std::array<bool, MINOSIZE_MAX>, MINOSIZE_MAX>;

    Shape shape;
    double centerY;
    double centerX;
    index_type height;
    index_type width;
    MinoType type;
};

class MinoData : public IMinoData
{
public:
    MinoData(const MinoDataStruct& data) : data(data) {}

    bool operator()(Direction dir, index_type y, index_type x) const override
    {
        const auto [y_, x_] = inverse(dir, y, x);
        return data.shape[y_][x_];
    }

    index_type height() const noexcept override
    {
        return data.height;
    }

    index_type width() const noexcept override
    {
        return data.width;
    }

    MinoType type() const noexcept override
    {
        return data.type;
    }

private:
    std::pair<index_type, index_type> inverse(Direction dir, index_type y, index_type x) const
    {
        const double ry = (double)y + 0.5 - data.centerY;
        const double rx = (double)x + 0.5 - data.centerX;

        double ry_, rx_;
        switch(dir){
            case Direction::NORTH: ry_ =  ry; rx_ =  rx; break;
            case Direction::EAST : ry_ = -rx; rx_ =  ry; break;
            case Direction::SOUTH: ry_ = -ry; rx_ = -rx; break;
            case Direction::WEST : ry_ =  rx; rx_ = -ry; break;
        }

        const index_type y_ = static_cast<index_type>(data.centerY + ry_);
        const index_type x_ = static_cast<index_type>(data.centerX + rx_);

        return {y_, x_};
    }

private:
    const MinoDataStruct& data;
};