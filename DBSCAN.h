#pragma once
#include "Find_cluster.h"
#include "Graph_matrix.h"

class DBSCAN
{
private:
    double delta;
    int k;
public:
    DBSCAN();
    DBSCAN(const DBSCAN& db_alg);
    const DBSCAN& operator=(const DBSCAN& db_alg);
    ~DBSCAN() = default;
    void assign_delta(double d_d);
    void assign_k(int k_k);
    double get_delta();
    int get_k();
    Find_cluster find_clusters(vector <Vector>& points, vector <int>& cpd);
};


