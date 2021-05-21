#include "Vector.h"

Vector::Vector()
{
    first_coordinate = second_coordinate = function_value = vector_id = 0;
}

Vector::Vector(double x, double y)
{
    first_coordinate = x;
    second_coordinate = y;
    function_value = (first_coordinate * first_coordinate - second_coordinate * second_coordinate) / 10 + 5;
    vector_id = 0;
}

Vector::Vector(const Vector& v)
{
    first_coordinate = v.first_coordinate;
    second_coordinate = v.second_coordinate;
    function_value = v.function_value;
    vector_id = v.vector_id;
}

Vector operator+(const Vector& v, const Vector& u)
{
    return Vector(v.first_coordinate + u.first_coordinate, v.second_coordinate + u.second_coordinate);
}

Vector operator-(const Vector& v, const Vector& u)
{
    return Vector(v.first_coordinate - u.first_coordinate, v.second_coordinate - u.second_coordinate);
}

Vector operator*(double lambda, const Vector& v)
{
    return Vector(lambda * v.first_coordinate, lambda * v.second_coordinate);
}

Vector operator*(const Vector& v, double lambda)
{
    return Vector(lambda * v.first_coordinate, lambda * v.second_coordinate);
}

const Vector& Vector::operator=(const Vector& v)
{
    first_coordinate = v.first_coordinate;
    second_coordinate = v.second_coordinate;
    function_value = v.function_value;
    vector_id = v.vector_id;
    return *this;
}

double Vector::length() { return sqrt(first_coordinate * first_coordinate + second_coordinate * second_coordinate); }

double Vector::get_first_coordinate() { return first_coordinate; }

double Vector::get_second_coordinate() { return second_coordinate; }

double Vector::get_function_value() { return function_value; }

int Vector::get_vector_id() { return vector_id; }

void Vector::assign_vector_id(int id) { vector_id = id; }

void Vector::print_vector(ofstream& file) { file << first_coordinate << " " << second_coordinate << endl; }