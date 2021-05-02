#pragma once
#include "Graph_matrix.h"
#include "Find_cluster.h"

class Spanning_tree
{
public:
    vector <pair <double, pair <int, int>>> creat_spanning_tree(vector <Vector>& points);
    void print_spanning_tree(vector <Vector>& points, vector <pair <double, pair <int, int>>>& edges);
};

