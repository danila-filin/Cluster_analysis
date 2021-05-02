#pragma once
#include "Find_cluster.h"

class EM
{
private:
    int k;
public:
    EM();
    EM(const EM& em);
    const EM& operator=(const EM& em);
    ~EM() = default;
    void assign_k(int k_k);
    Find_cluster find_clusters(vector <Vector>& points);
};

