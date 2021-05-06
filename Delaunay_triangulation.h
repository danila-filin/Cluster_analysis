#pragma once
#include "Triangle.h"

class Delaunay_triangulation
{
private:
    vector <Triangle> triangles;
    int number_triangles, number_points;
public:
    Delaunay_triangulation();
    Delaunay_triangulation(const Delaunay_triangulation& Del_tr);
    const Delaunay_triangulation& operator=(const Delaunay_triangulation& Del_tr);
    ~Delaunay_triangulation() = default;
    void add_triangle(Triangle T);
};

