#include "FOREL.h"

FOREL::FOREL() { R = number_steps = 0; }

FOREL::FOREL(const FOREL& f) { R = f.R; number_steps = f.number_steps; }

const FOREL& FOREL::operator=(const FOREL& f) { R = f.R; number_steps = f.number_steps; return *this; }

void FOREL::assign_R(double r) { R = r; }

void FOREL::assign_number_steps(int n) { number_steps = n; }

double FOREL::get_R() { return R; }

int FOREL::get_number_steps() { return number_steps; }

//Find_cluster FOREL::find_clusters(vector <Vector>& points_in_field)
//{
//    Vector cent;
//    int i, j, n = points_in_field.size(), c, t, N, m;
//    vector <Vector> clust;
//    vector <Vector> points;
//    Vector centers[number_steps][n];
//    vector <int> k(number_steps, 0);
//    double sum_x, sum_y;
//    vector <int> ind, ind_1(n, 0);
//    Find_cluster fc;
//
//    for (i = 0; i < n; i++) { ind.push_back(0); }
//    for (m = 0; m < number_steps; m++)
//    {
//        n = points.size();
//        c = n;
//        while (c != 0)
//        {
//            c = 0;
//            for (i = 0; i < n; i++)
//            {
//                if (ind[i] == 0)
//                {
//                    cent = points[i];
//                    i = n;
//                }
//            }
//            for (i = 0; i < n; i++)
//            {
//                if (((points[i] - cent).length()) <= R && (ind[i] != 2)) ind[i] = 1;
//            }
//            t = 1;
//            while (t != 0)
//            {
//                t = 0;
//                sum_x = 0;
//                sum_y = 0;
//                N = 0;
//                for (i = 0; i < n; i++)
//                {
//                    if (ind[i] == 1)
//                    {
//                        sum_x = sum_x + points[i].get_first_coordinate();
//                        sum_y = sum_y + points[i].get_second_coordinate();
//                        N++;
//                    }
//                }
//                sum_x = sum_x / N;
//                sum_y = sum_y / N;
//                if (((cent.get_first_coordinate()) != sum_x) || ((cent.get_second_coordinate()) != sum_y))
//                {
//                    cent = Vector(sum_x, sum_y);
//                    t++;
//                    for (i = 0; i < n; i++)
//                    {
//                        if (ind[i] != 2) ind[i]=0;
//                    }
//                    for (i = 0; i < n; i++)
//                    {
//                        if ((points[i] - cent).length() <= R && ind[i] != 2) ind[i] = 1;
//                    }
//                }
//            }
//            for (i = 0; i < n; i++)
//            {
//                if (ind[i] != 2) ind[i] = 0;
//                if ((points[i] - cent).length() <= R && ind[i] != 2) 
//                {
//                    ind[i] = 2;
//                }
//            }
//            for (i = 0; i < n; i++)
//            {
//                if (ind[i] == 0) c++;
//            }
//            centers[m][k[m]] = cent;
//            k[m]++;
//        }
//        points.clear();
//        ind.clear();
//        for (i = 0; i < k[m]; i++)
//        {
//            points.push_back(centers[m][i]);
//            ind.push_back(0);
//        }
//        for (i = 0; i < k[m]; i++)
//        {
//            Cluster cl;
//            for (j = 0; j < points_in_field.size(); j++)
//            {
//                cl.add_point_indicator(0);
//                if ((points_in_field[j] - centers[m][i]).length() <= R && ind_1[j] != 2)
//                {
//                    cl.assign_point_indicator(j, 1);
//                    ind_1[j] = 2;
//                }
//            }
//            fc.add_cluster(cl);
//        }
//        for (i = 0; i < points_in_field.size(); i++) ind_1[i] = 0;
//        if (m != number_steps - 1) R = R * 3.1415;
//    }
//}
