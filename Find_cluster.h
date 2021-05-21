#pragma once

#pragma once
#include "Cluster.h"

class Find_cluster
{
private:
    int number_clusters_in_find_cluster, number_points_in_find_cluster, alg_number;
    vector <Cluster> clusters;
    vector <vector <Cluster>> steps;
    string alg;
    double delta;
    int k;
public:
    //конструкторы и деструктор
    Find_cluster();
    Find_cluster(const Find_cluster& fc);
    ~Find_cluster() = default;

    const Find_cluster& operator=(const Find_cluster& fc);//операция присваивания

    //функции, связанные с атрибутами данного класса
    void add_cluster(Cluster c);
    int get_number_clusters_in_find_cluster();
    int get_number_points_in_find_cluster();
    int get_point_indicator(int i, int j);
    void assign_alg(string s);
    void assign_alg_number(int n);
    void assign_delta(double d);
    void assign_k(int k_k);
    string get_alg();
    int get_alg_number();
    double get_delta();
    int get_k();
    Cluster get_cluster(int id);

    //печать результатов алгоритмов
    void print_wave_algorithm(vector <Vector>& points);
    void print_dbscan_algorithm(vector <Vector>& points, vector <int>& cpd);
    void print_k_means_algorithm(vector <Vector>& points);
    void print_em_algorithm(vector <Vector>& points);
};