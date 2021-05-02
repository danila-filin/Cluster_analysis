#pragma once
#include "Vector.h"

class Distance_matrix
{
private:
    int N;
    vector <double> D;
public:
    //конструкторы и деструкторы
    Distance_matrix();
    Distance_matrix(const Distance_matrix& d);
    ~Distance_matrix() = default;

    const Distance_matrix& operator=(const Distance_matrix& d);//операция присванивания

    //функции, связанные с атрибутами данного класса
    int get_N();
    double get_d(int i, int j);

    void create_distance_matrix(vector <Vector> points);//создание матрицы расстояний

    void print_distance_matrix();//печать матрицы расстояний
};