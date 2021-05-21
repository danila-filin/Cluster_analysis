#pragma once
#include "Cloud.h"
#include "Buffer.h"
#include "Find_cluster.h"
#include "Wave_algorithm.h"
#include "DBSCAN.h"
#include "k_means.h"
#include "EM.h"
#include "Spanning_tree.h"
#include "Hierarchical_algorithm.h"
#include "Delaunay_triangulation.h"
#pragma warning (disable:4244)
#pragma warning (disable:26451)
#pragma warning (disable:6001)
#pragma warning (disable:4018)

class Field
{
private:
    int number_clouds_in_field, number_points_in_field, number_find_clusters_in_field;
    vector <Cloud> clouds_in_field;
    Buffer buffer;
    vector <Find_cluster> find_clusters;
public:
    //конструкторы и деструктор
    Field();
    Field(const Field& f);
    ~Field() = default;

    const Field& operator=(const Field& f);//операция присваивания

    //функции, связанные с атрибутами данного класса
    void add_cloud_in_field(Cloud c);
    void delete_cloud_from_field(int id);
    vector <Vector> get_points_from_field();

    void print_field();//печать поля

    //буфер
    void add_cloud_from_field_in_buffer(int id);
    void add_all_clouds_from_field_in_buffer();
    void upload_cloud_from_buffer_in_field(int n);
    void upload_all_clouds_from_buffer_in_field();
    void shift_cloud_in_buffer(int n, Vector v);
    void shift_all_clouds_in_buffer(Vector v);
    void turn_cloud_in_bufffer(int n, double phi);
    void turn_all_clouds_in_bufffer(double phi);
    void compression_cloud_in_buffer(int n, double lambda);
    void compression_all_clouds_in_buffer(double lambda);

    //гистограммы
    void creat_field_histogram(int number_of_columns);
    void creat_cloud_histogram(int id, int number_of_colunms);
    void creat_distance_matrix();
    void creat_graph_matrix(double delta);

    //функция
    double fun(double x, double y);
    void print_fun(Vector p, double value);

    void add_find_cluster();

    //алгоритмы
    void wave(double delta);
    void dbscan(double delta, int k);
    void tree();
    void k_m(int k);
    void em(int k);
    void hierarchy();

    void find_min_y(vector <Vector>& points);
    void polar_angle_sort(vector <Vector>& points);
    double left_rotate(Vector p, Vector q, Vector r);
    vector <Vector> convex_hull(vector <Vector> points);
    Delaunay_triangulation generate_delaunay_trinagulation(vector <Vector>& points);
    double Gauss_function(double x);
    void function_interpolation(Vector p);
};