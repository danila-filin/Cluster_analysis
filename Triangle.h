#pragma once
#include "Vector.h"

class Triangle
{
private:
	Vector A, B, C;
	int id;
public:
	Triangle();
	Triangle(Vector a, Vector b, Vector c);
	Triangle(const Triangle& T);
	~Triangle() = default;
	const Triangle& operator=(const Triangle& T);
	Vector get_A();
	Vector get_B();
	Vector get_C();
	Vector get_id();
	void assign_A(Vector a);
	void assign_B(Vector b);
	void assign_C(Vector c);
	void assign_id(int k);
};

