#include "k_means.h"

k_means::k_means() { k = 0; }

k_means::k_means(const k_means& km) { k = km.k; }

const k_means& k_means::operator=(const k_means& km) { k = km.k; return *this; }

void k_means::assing_k(int k_k) { k = k_k; }

Find_cluster k_means::find_clusters(vector <Vector>& points)
{
    double dist;
    int i, j, m, c, N = points.size();
    vector <Vector> k_means;
    vector <int> n(k, 0);
    vector <double> sum_x(k, 0);
    vector <double> sum_y(k, 0);
    vector <Cluster> P(k);
    Find_cluster f;

    f.assign_alg("k means");
    for (i = 0; i < k; i++)
    {
        for (j = 0; j < N; j++) P[i].add_point_indicator(0);
    }
    for (i = 0; i < k; i++)
    {
        k_means.push_back(points[i]);
        P[i].assign_point_indicator(i, 1);
    }
    for (i = 0; i < N; i++)
    {
        dist = 1000;
        for (j = 0; j < k; j++)
        {
            if ((points[i] - k_means[j]).length() < dist)
            {
                dist = (points[i] - k_means[j]).length();
                m = j;
            }
        }
        P[m].assign_point_indicator(i, 1);
    }
    c = 1;
    while (c != 0)
    {
        c = 0;
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < k; j++)
            {
                sum_x[j] = sum_x[j] + points[i].get_first_coordinate() * P[j].get_point_indicator(i);
                sum_y[j] = sum_y[j] + points[i].get_second_coordinate() * P[j].get_point_indicator(i);
                n[j] = n[j] + P[j].get_point_indicator(i);
            }
        }
        k_means.clear();
        for (i = 0; i < k; i++)
        {
            sum_x[i] = sum_x[i] / n[i];
            sum_y[i] = sum_y[i] / n[i];
            k_means.push_back(Vector(sum_x[i], sum_y[i]));
            sum_x[i] = 0;
            sum_y[i] = 0;
            n[i] = 0;
        }
        for (i = 0; i < N; i++)
        {
            dist = 1000;
            for (j = 0; j < k; j++)
            {
                if ((points[i] - k_means[j]).length() < dist)
                {
                    dist = (points[i] - k_means[j]).length();
                    m = j;
                }
            }
            if (P[m].get_point_indicator(i) == 0)
            {
                for (j = 0; j < k; j++) P[j].assign_point_indicator(i, 0);
                P[m].assign_point_indicator(i, 1);
                c++;
            }
        }
    }
    for (i = 0; i < k; i++)
    {
        P[i].assign_cluster_center(k_means[i]);
        f.add_cluster(P[i]);
    }
    return f;
}