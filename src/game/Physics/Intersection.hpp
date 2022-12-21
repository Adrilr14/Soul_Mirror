#pragma once

struct Intersection_t{

public:

    Intersection_t(const bool i,const float d)
    : intersection(i),distance(d) {}

    bool getIntersection() const { return intersection; };
    float getDistance() const { return distance; };

private:
    const bool intersection;
    const float distance; 
};
