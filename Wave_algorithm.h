#pragma once
#include "Find_cluster.h"
#include "Graph_matrix.h"

class Wave_algorithm
{
private:
    double delta;
public:
    Wave_algorithm();
    Wave_algorithm(const Wave_algorithm& alg);
    const Wave_algorithm& operator=(const Wave_algorithm& alg);
    ~Wave_algorithm() = default;
    void assign_delta(double d);
    double get_delta();
    Find_cluster find_clusters(vector <Vector>& points);
};

