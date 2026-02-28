#include <array>
#include <vector>
#include "MinoFactory.hpp"
#include "MinoData.hpp"

class MinoDataContainer : public IMinoDataContainer
{
public:
    MinoDataContainer(const std::array<MinoDataStruct, MinoType::MAX>& dataStructs)
    {
        arr.reserve(MinoType::MAX);
        for(const auto& data : dataStructs){
            arr.emplace_back(data);
        }
    }

    const IMinoData& operator[](MinoType type) const override
    {
        return arr[type];
    }

private:
    std::vector<MinoData> arr;
};