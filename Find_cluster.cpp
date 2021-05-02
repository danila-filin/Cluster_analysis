#include "Find_cluster.h"

Find_cluster::Find_cluster() { number_clusters_in_find_cluster = number_points_in_find_cluster = delta = k = 0; }

Find_cluster::Find_cluster(const Find_cluster& fc)
{
    number_clusters_in_find_cluster = fc.number_clusters_in_find_cluster;
    number_points_in_find_cluster = fc.number_points_in_find_cluster;
    alg_number = fc.alg_number;
    alg = fc.alg;
    delta = fc.delta;
    k = fc.k;
    clusters = fc.clusters;
    steps = fc.steps;
}

const Find_cluster& Find_cluster::operator=(const Find_cluster& fc)
{
    number_clusters_in_find_cluster = fc.number_clusters_in_find_cluster;
    number_points_in_find_cluster = fc.number_points_in_find_cluster;
    alg_number = fc.alg_number;
    alg = fc.alg;
    delta = fc.delta;
    k = fc.k;
    clusters = fc.clusters;
    steps = fc.steps;
    return *this;
}

void Find_cluster::add_cluster(Cluster c)
{
    number_clusters_in_find_cluster++;
    number_points_in_find_cluster = number_points_in_find_cluster + c.get_number_points_in_cluster();
    clusters.push_back(c);
    clusters[number_clusters_in_find_cluster - 1].assign_cluster_id(number_clusters_in_find_cluster - 1);
    //cout << "+" << endl;
//clusters[number_clusters_in_find_cluster-1].find_mean_point(points);
  //  cout << "+" << endl;
//    clusters[number_clusters_in_find_cluster-1].find_R_and_D(points);
//        cout << "+" << endl;
}

int Find_cluster::get_number_clusters_in_find_cluster() { return number_clusters_in_find_cluster; }

int Find_cluster::get_number_points_in_find_cluster() { return number_points_in_find_cluster; }

int Find_cluster::get_point_indicator(int i, int j) { return clusters[i].get_point_indicator(j); }

void Find_cluster::assign_alg(string s) { alg = s; }

void Find_cluster::assign_alg_number(int n) { alg_number = n; }

void Find_cluster::assign_delta(double d) { delta = d; }

void Find_cluster::assign_k(int k_k) { k = k_k; }

int Find_cluster::get_alg_number() { return alg_number; }

string Find_cluster::get_alg() { return alg; }

double Find_cluster::get_delta() { return delta; }

int Find_cluster::get_k() { return k; }

void Find_cluster::print_wave_algorithm(vector <Vector>& points)
{
    ofstream f("Wave.txt"), g("Wave.plt");
    g << "set size square\n" << "set palette\n" << "plot 'Wave.txt' palette title 'Wave, delta=" << delta << "\n";
    for (int i = 0; i < number_clusters_in_find_cluster; i++) clusters[i].print_cluster(f, points);
    f.close();
    g.close();
}

void Find_cluster::print_dbscan_algorithm(vector <Vector>& points, vector <int>& cpd)
{
    ofstream f("DBSCAN.txt"), g("DBSCAN.plt"), f_1("Core.txt"), f_2("Peripheral.txt"), f_3("Dust.txt");

    g << "set size square\n" << "set palette\n" << "plot 'DBSCAN.txt' palette title 'DBSCAN, delta=" << delta << ", k=" << k << "\n";
    for (int i = 0; i < number_clusters_in_find_cluster; i++) clusters[i].print_cluster(f, points);
    f.close();
    g.close();

    g.open("DBSCAN (core, peripheral, dust).plt");
    for (int i = 0; i < points.size(); i++)
    {
        if (cpd[i] == 0) points[i].print_vector(f_1);
        if (cpd[i] == 1) points[i].print_vector(f_2);
        if (cpd[i] == 2) points[i].print_vector(f_3);
    }
    g << "set size square\n" << "plot 'Core.txt', 'Peripheral.txt', 'Dust.txt'\n";
    g.close();
    f_1.close();
    f_2.close();
    f_3.close();
}

void Find_cluster::print_k_means_algorithm(vector <Vector>& points)
{
    ofstream f("k means.txt"), g("k means.plt");
    g << "set size square\n" << "set palette\n" << "plot 'k means.txt' palette title 'k means, k=" << k << "\n";
    for (int i = 0; i < number_clusters_in_find_cluster; i++) clusters[i].print_cluster(f, points);
    f.close();
    g.close();
}

void Find_cluster::print_em_algorithm(vector <Vector>& points)
{
    ofstream f("EM.txt"), g("EM.plt");

    g << "set size square\n" << "set palette\n" << "plot 'em.txt' palette title 'em, k=" << k << "\n";
    for (int i = 0; i < number_clusters_in_find_cluster; i++) clusters[i].print_cluster(f, points);
    f.close();
    g.close();
}