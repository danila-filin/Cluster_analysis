#include "Delaunay_triangulation.h"

Delaunay_triangulation::Delaunay_triangulation() { number_triangles = number_points = 0; }

Delaunay_triangulation::Delaunay_triangulation(const Delaunay_triangulation& Del_tr)
{
	triangles = Del_tr.triangles;
	number_triangles = Del_tr.number_triangles;
	number_points = Del_tr.number_points;
}

const Delaunay_triangulation& Delaunay_triangulation::operator=(const Delaunay_triangulation& Del_tr)
{
	triangles = Del_tr.triangles;
	number_triangles = Del_tr.number_triangles;
	number_points = Del_tr.number_points;
	return *this;
}

void Delaunay_triangulation::add_triangle(Triangle T)
{
	T.assign_id(number_triangles);
	triangles.push_back(T);
	number_triangles++;
	number_points = number_points + 3;
}