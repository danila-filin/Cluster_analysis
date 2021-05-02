#pragma once
#include "Vector.h"

class Cloud
{
private:
    double mean_value_for_first_coordinate, mean_value_for_second_coordinate, dispersion_for_first_coordinate, dispersion_for_second_coordinate, radius, diameter;
    int number_points_in_cloud, cloud_id;
    vector <Vector> points_in_cloud;
public:
    //конструкторы и деструкторы
    Cloud();
    Cloud(double mean_x, double mean_y, double sigma_x, double sigma_y, int n);
    Cloud(const Cloud& c);
    ~Cloud() = default;

    const Cloud& operator=(const Cloud& c);//операция присваивания

    //функции, связанные с атрибутами данного класса
    Vector get_cloud_center();
    Vector get_dispersions();
    double get_radius();
    double get_diameter();
    int get_number_points_in_cloud();
    int get_cloud_id();
    Vector get_point_in_cloud(int point_id);
    void assign_cloud_id(int id);
    void assign_point_id_in_cloud(int n, int id);

    void print_cloud(ofstream& file);//печать облака

    void creat_cloud_histogram(int number_of_columns);//создание гистограммы облака

    //преобразования облака
    void shift_cloud(Vector v);
    void turn_cloud(double phi);
    void compression_cloud(double lambda);
};