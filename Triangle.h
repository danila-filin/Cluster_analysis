#pragma once
#include "Vector.h"

class Triangle
{
private:
	Vector A, B, C;
	int id;
	int neighbouring_triangle_id;
public:
	Triangle();
	Triangle(Vector a, Vector b, Vector c);
	Triangle(const Triangle& T);
	~Triangle() = default;
	const Triangle& operator=(const Triangle& T);
	Vector get_A();
	Vector get_B();
	Vector get_C();
	int get_id();
	int get_neighbouring_triangle_id();
	void assign_A(Vector a);
	void assign_B(Vector b);
	void assign_C(Vector c);
	void assign_id(int k);
	void assing_neighbouring_triangle_id(int k);
	void print_triangle(ofstream& file);
};

