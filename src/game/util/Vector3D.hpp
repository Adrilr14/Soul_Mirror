#pragma once

#include <cmath>

enum Graph_data {
    invalid_index = -1
};

struct Vector3D{
    float m_x;
    float m_y;
    float m_z;
    float angle;
};

inline double vec3DDistance(const Vector3D& pos1, const Vector3D& pos2){
    double valueX = pow(2,(pos2.m_x - pos1.m_x));
    double valueY = pow(2,(pos2.m_y - pos1.m_y));
    double valueZ = pow(2,(pos2.m_z - pos1.m_z));

    return sqrt((valueX+valueY+valueZ));
}