#include "Triangle.h"

Triangle::Triangle() { A = B = C = Vector(0, 0); id = 0; }

Triangle::Triangle(Vector a, Vector b, Vector c) { A = a; B = b; C = c; id = 0; }

Triangle::Triangle(const Triangle& T) { A = T.A; B = T.B; C = T.C; id = T.id; neighbouring_triangle_id = T.neighbouring_triangle_id; }

const Triangle& Triangle::operator=(const Triangle& T) 
{ 
	A = T.A; B = T.B; C = T.C; id = T.id; neighbouring_triangle_id = T.neighbouring_triangle_id; 
	return *this; 
}

Vector Triangle::get_A() { return A; }

Vector Triangle::get_B() { return B; }

Vector Triangle::get_C() { return C; }

int Triangle::get_id() { return id; }

int Triangle::get_neighbouring_triangle_id() { return neighbouring_triangle_id; }

void Triangle::assign_A(Vector a) { A = a; }

void Triangle::assign_B(Vector b) { B = b; }

void Triangle::assign_C(Vector c) { C = c; }

void Triangle::assign_id(int k) { id = k; }

void Triangle::assing_neighbouring_triangle_id(int k) { neighbouring_triangle_id = k; }

void Triangle::print_triangle(ofstream& file)
{
	A.print_vector(file);
	B.print_vector(file);
	C.print_vector(file);
}