#pragma once
#include "Vector.h"

class Cluster
{
private:
    int number_points_in_cluster, cluster_id;
    vector <int> point_indicators;
    Vector cluster_center;
    double radius, diameter;
public:
    //������������ � ����������
    Cluster();
    Cluster(const Cluster& c);
    ~Cluster() = default;

    const Cluster& operator=(const Cluster& c);//�������� ������������

    //�������, ��������� � ���������� ������� ������
    int get_number_points_in_cluster();
    int get_cluster_id();
    int get_point_indicator(int id);
    Vector get_cluster_center();
    double get_radius();
    double get_diameter();
    void assign_cluster_id(int id);
    void add_point_indicator(int n);
    void assign_point_indicator(int id, int n);

    void print_cluster(ofstream& file, vector <Vector>& points);//������ ��������

    //����� ������, ������� � �������� ��������
    void find_cluster_center(vector <Vector>& points);
    void find_radius_and_diameter(vector <Vector>& points);
};

