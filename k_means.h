#pragma once
#include "Find_cluster.h"

class k_means
{
private:
    int k;
public:
    k_means();
    k_means(const k_means& km);
    const k_means& operator=(const k_means& km);
    ~k_means() = default;
    void assing_k(int k_k);
    Find_cluster find_clusters(vector <Vector>& points);
};

