#pragma once
#include "Find_cluster.h"

class Hierarchical_algorithm
{
public:
    double distance_for_hierarchy(vector <Vector>& a, vector <Vector>& b);
    vector <Vector> tree_walk(vector <Vector>& T, vector <Vector>& points, int n, vector <vector <int>>& point_indicators);
    void hierarchy(vector <Vector>& points_from_field);
    void print_tree(ofstream& file, vector <Vector>& points, int n, vector <vector <int>>& point_indicators);
};

