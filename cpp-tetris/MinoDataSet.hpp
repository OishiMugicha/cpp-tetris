#pragma once

#include "MinoData.hpp"

using Shape = MinoDataStruct::Shape;

static const std::array<Shape, MinoType::MAX> shapes
{{
    {{ // MinoType::I
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }},
    {{ // MinoType::O
        {0, 1, 1},
        {0, 1, 1},
        {0, 0, 0}
    }},
    {{ // MinoType::T
        {0, 1, 0},
        {1, 1, 1},
        {0, 0, 0}
    }},
    {{ // MinoType::S
        {0, 1, 1},
        {1, 1, 0},
        {0, 0, 0}
    }},
    {{ // MinoType::Z
        {1, 1, 0},
        {0, 1, 1},
        {0, 0, 0}
    }},
    {{ // MinoType::L
        {0, 0, 1},
        {1, 1, 1},
        {0, 0, 0}
    }},
    {{ // MinoType::J
        {1, 0, 0},
        {1, 1, 1},
        {0, 0, 0}
    }}
}};

static const std::array<MinoDataStruct, MinoType::MAX> minoDataSet
{{
    { /*Shape      shape  */shapes[MinoType::I]
    , /*double     centerY*/2.0
    , /*double     centerX*/2.0
    , /*index_type height */4
    , /*index_type width  */4
    , /*MinoType   type   */MinoType::I
    },
    { /*Shape      shape  */shapes[MinoType::O]
    , /*double     centerY*/1.0
    , /*double     centerX*/2.0
    , /*index_type height */3
    , /*index_type width  */3
    , /*MinoType   type   */MinoType::O
    },
    { /*Shape      shape  */shapes[MinoType::T]
    , /*double     centerY*/1.5
    , /*double     centerX*/1.5
    , /*index_type height */3
    , /*index_type width  */3
    , /*MinoType   type   */MinoType::T
    },
    { /*Shape      shape  */shapes[MinoType::S]
    , /*double     centerY*/1.5
    , /*double     centerX*/1.5
    , /*index_type height */3
    , /*index_type width  */3
    , /*MinoType   type   */MinoType::S
    },
    { /*Shape      shape  */shapes[MinoType::Z]
    , /*double     centerY*/1.5
    , /*double     centerX*/1.5
    , /*index_type height */3
    , /*index_type width  */3
    , /*MinoType   type   */MinoType::Z
    },
    { /*Shape      shape  */shapes[MinoType::L]
    , /*double     centerY*/1.5
    , /*double     centerX*/1.5
    , /*index_type height */3
    , /*index_type width  */3
    , /*MinoType   type   */MinoType::L
    },
    { /*Shape      shape  */shapes[MinoType::J]
    , /*double     centerY*/1.5
    , /*double     centerX*/1.5
    , /*index_type height */3
    , /*index_type width  */3
    , /*MinoType   type   */MinoType::J
    }
}};
