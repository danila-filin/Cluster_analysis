#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <string.h>
#include <string>

using namespace std;

class Vector
{
private:
    double first_coordinate, second_coordinate, function_value; 
    int vector_id;
public:
    Vector();
    Vector(double x, double y);
    Vector(const Vector& v);
    ~Vector() = default;
    const Vector& operator=(const Vector& v);
    friend Vector operator+(const Vector& v, const Vector& u);
    friend Vector operator-(const Vector& v, const Vector& u);
    friend Vector operator*(double lambda, const Vector& v);
    friend Vector operator*(const Vector& v, double lambda);
    double length();
    double get_first_coordinate();
    double get_second_coordinate();
    double get_function_value();
    int get_vector_id();
    void assign_vector_id(int id);
    void print_vector(ofstream& file);
};

