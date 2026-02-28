#pragma once

#include "Mino.hpp"

struct IMinoDataContainer
{
    virtual ~IMinoDataContainer() = default;
    virtual const IMinoData& operator[](MinoType type) const = 0;
};

class MinoFactory : public IMinoFactory
{
public:
    MinoFactory(const IMinoDataContainer& dataContainer) : dataContainer(dataContainer) {}

    std::unique_ptr<IMino> create(MinoType type, index_type positionY, index_type positionX) const override
    {
        return std::make_unique<Mino>
        ( /*const IMinoData& data     */dataContainer[type]
        , /*index_type       positionY*/positionY
        , /*index_type       positionX*/positionX
        );
    }

private:
    const IMinoDataContainer& dataContainer;
};