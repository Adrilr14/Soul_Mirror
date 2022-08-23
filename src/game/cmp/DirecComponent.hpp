#pragma once
#include <map>
#include <cstdint>
#include "../util/Vector3D.hpp"
#include "../../ecs/cmp/component.hpp"

struct DirecComponent_t : ComponentBase_t<DirecComponent_t>{
    explicit DirecComponent_t(std::size_t eid)
    :   ComponentBase_t(eid)
    {};
    int dir {-1};
    int dirPrevia {-1};
    int dirCollision {-1};
    std::map<int,Vector3D> valuesDirection {
        {1, Vector3D{ 1  , 0 ,  0 ,  90  }    },
        {2, Vector3D{-1  , 0 ,  0 , -90  }    },
        {3, Vector3D{ 0  , 0 ,  1 ,   0  }    },
        {4, Vector3D{ 0  , 0 , -1 , 180  }    },
        {5, Vector3D{ 1  , 0 ,  1 ,  30  }    },
        {6, Vector3D{-1  , 0 ,  1 , -30  }    },
        {7, Vector3D{ 1  , 0 , -1 , 150  }    },
        {8, Vector3D{-1  , 0 , -1 , -150 }    }, 
    };

    Vector3D getValuesDirection(int direccion){
        return valuesDirection[direccion];
    }
};