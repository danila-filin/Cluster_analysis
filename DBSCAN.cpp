#include "DBSCAN.h"

DBSCAN::DBSCAN() { delta = k = 0; }

DBSCAN::DBSCAN(const DBSCAN& alg) { delta = alg.delta; k = alg.k; }

const DBSCAN& DBSCAN::operator=(const DBSCAN& alg) { delta = alg.delta; k = alg.k; return *this; }

void DBSCAN::assign_delta(double d_d) { delta = d_d; }

void DBSCAN::assign_k(int k_k) { k = k_k; }

double DBSCAN::get_delta() { return delta; }

int DBSCAN::get_k() { return k; }

Find_cluster DBSCAN::find_clusters(vector <Vector>& points, vector <int>& cpd)
{
    int i, j, l, t, c, N = 0, n = points.size(), s = 1;
    Distance_matrix D, D_core;
    Graph_matrix B, B_core;
    vector <Vector> core_points;
    vector <int> core_points_indicators;
    vector <vector <int>> point_indicators;
    vector <Cluster> C;
    Find_cluster fc;

    cpd.resize(n);
    D.create_distance_matrix(points);
    B.create_graph_matrix(D, delta);
    for (i = 0; i < n; i++) cpd[i] = 2;
    for (i = 0; i < n; i++)
    {
        l = 0;
        for (j = 0; j < n; j++)
        {
            if (B.get_b(i, j) == 1) l++;
        }
        l--;
        if (l > k - 1) cpd[i] = 0;
    }
    for (i = 0; i < n; i++)
    {
        if (cpd[i] == 2)
        {
            for (j = 0; j < n; j++)
            {
                if (B.get_b(i, j) == 1 && cpd[j] == 0)
                {
                    cpd[i] = 1;
                    j = n - 1;
                }
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        Cluster cl;
        for (j = 0; j < n; j++) cl.add_point_indicator(0);
        if (cpd[i] == 2)
        {
            cl.assign_point_indicator(i, 1);
            C.push_back(cl);
        }
        else
        {
            core_points.push_back(points[i]);
            core_points_indicators.push_back(i);
            N++;
        }
    }
    D_core.create_distance_matrix(core_points);
    B_core.create_graph_matrix(D_core, delta);
    point_indicators.resize(N);
    for (i = 0; i < N; i++)
    {
        point_indicators[i].push_back(0);
        point_indicators[i].push_back(0);
        point_indicators[i].push_back(0);
    }
    for (i = 0; i < N; i++)
    {
        if (point_indicators[i][2] == 0)
        {
            Cluster cl;
            t = 1;
            point_indicators[i][0] = t;
            point_indicators[i][2] = 1;
            for (j = 0; j < n; j++) cl.add_point_indicator(0);
            cl.assign_point_indicator(core_points_indicators[i], 1);
            C.push_back(cl);
            c = 1;
            while (c != 0)
            {
                c = 0;
                for (j = 0; j < N; j++)
                {
                    if (point_indicators[j][0] == t)
                    {
                        for (l = 0; l < N; l++)
                        {
                            if (l == j) point_indicators[l][1] = t;
                            if (B_core.get_b(j, l) == 1 && point_indicators[l][2] == 0 && point_indicators[l][0] == 0)
                            {
                                point_indicators[l][1] = t + 1;
                                point_indicators[l][2] = 1;
                                C[s].assign_point_indicator(core_points_indicators[l], 1);
                                c++;
                            }
                        }
                    }
                }
                for (j = 0; j < N; j++) point_indicators[j][0] = point_indicators[j][1];
                t++;
            }
            s++;
        }
    }
    for (i = 0; i < C.size(); i++) fc.add_cluster(C[i]);
    return fc;
}
