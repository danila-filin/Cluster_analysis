#pragma once
#include "Find_cluster.h"

class FOREL
{
private:
	double R;
	int number_steps;
public:
	FOREL();
	FOREL(const FOREL& f);
	~FOREL() = default;
	const FOREL& operator=(const FOREL& f);
	void assign_R(double r);
	void assign_number_steps(int n);
	double get_R();
	int get_number_steps();
	Find_cluster find_clusters(vector <Vector>& points_in_field);
};

