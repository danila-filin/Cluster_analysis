#include "Hierarchical_algorithm.h"

double Hierarchical_algorithm::distance_for_hierarchy(vector <Vector>& a, vector <Vector>& b)
{
    int n = a.size(), m = b.size(), i, j;
    double dist = 0;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++) dist = dist + (a[i] - b[j]).length();
    }
    dist = dist / (n * m);
    return dist;
}

vector <Vector> Hierarchical_algorithm::tree_walk(vector <Vector>& T, vector <Vector>& points, int n, vector <vector <int>>& point_indicators)
{
    int i_1, i_2;

    i_1 = point_indicators[n][0];
    i_2 = point_indicators[n][1];
    if (T.size() == 0) T.push_back(points[n]);
    if (i_1 != 0 && i_2 != 0)
    {
        tree_walk(T, points, i_1, point_indicators);
        T.push_back(points[i_1]);
        T.push_back(points[i_2]);
        tree_walk(T, points, i_2, point_indicators);
    }
    return T;
}

void Hierarchical_algorithm::hierarchy(vector <Vector>& points_from_field)
{
    char s[500];
    ofstream f("Hierarchial algorithm (graph).txt"), g("Hierarchial algorithm (graph).plt");
    int n = points_from_field.size(), k = n, i, j, N = n, i_1, i_2, m;
    vector <double> Dist((2 * n - 1) * (2 * n - 1), 0);
    double min_D;
    Vector v;
    vector <Vector> points;
    vector <Vector> a;
    vector <Vector> b;
    vector <vector <int>> point_indicators(2 * n);

    for (i = 0; i < n; i++)
    {
        points.push_back(points_from_field[i]);
        point_indicators[i].push_back(0);
        point_indicators[i].push_back(0);
        point_indicators[i].push_back(0);
        point_indicators[i].push_back(0);
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++) Dist[i * (2 * n - 1) + j] = (points[i] - points[j]).length();
    }
    while (k > 1)
    {
        cout << k << endl;
        min_D = 10000;
        for (i = 0; i < N; i++)
        {
            if (point_indicators[i][3] == 0)
            {
                for (j = 0; j < N; j++)
                {
                    if (Dist[i * (2 * n - 1) + j] < min_D && i != j && point_indicators[j][3] == 0)
                    {
                        i_1 = i;
                        i_2 = j;
                        min_D = Dist[i * (2 * n - 1) + j];
                    }
                }
            }
        }
        point_indicators[i_1][3] = 1;
        point_indicators[i_2][3] = 1;
        N++;
        v = 0.5 * (points[i_1] + points[i_2]);
        points.push_back(v);
        point_indicators[N - 1].push_back(i_1);
        point_indicators[N - 1].push_back(i_2);
        point_indicators[N - 1].push_back(N - n);
        point_indicators[N - 1].push_back(0);
        for (i = 0; i < N - 1; i++)
        {
            if (point_indicators[i][3] == 0) point_indicators[i][2] == N - n;
        }
        a = tree_walk(a, points, N - 1, point_indicators);
        for (i = 0; i < N - 1; i++)
        {
            if (point_indicators[i][3] == 0)
            {
                b = tree_walk(b, points, i, point_indicators);
                Dist[(N - 1) * (2 * n - 1) + i] = distance_for_hierarchy(a, b);
                Dist[i * (2 * n - 1) + N - 1] = Dist[(N - 1) * (2 * n - 1) + i];
                b.clear();
            }
        }
        a.clear();
        k--;
        //        sprintf(s, "%d", N-n);
        //        strcat(s, " HA.txt");
        //        f=fopen(s, "w");
        //        for (i=0; i<N; i++)
        //        {
        //            if (points[i].get_c()==N-n) print_tree(f, points, i);
        //        }
        //        fclose(f);
        //        sprintf(s, "%d", N-n);
        //        strcat(s, " HAA.txt");
        //        f=fopen(s, "w");
        //        for (i=0; i<N; i++)
        //        {
        //            fprintf(f, "%f %f\n", points[i].get_x(), points[i].get_y());
        //        }
        //        fclose(f);
        //        fprintf(file, "%d hierarchy\n", N-n);
    }
    for (i = 0; i < N; i++)
    {
        if (point_indicators[i][2] == N - n) m = i;
    }
    //    g=fopen("Hierarchy (gif).plt", "w");
    //    fprintf(g, "set term gif animate delay 20\n");
    //    fprintf(g, "set output 'Hierarchy (gif).gif'\n");
    //    fprintf(g, "set size square\n");
    //    fprintf(g, "set nokey\n");
    //    fprintf(g, "do for\[i=1:%d\] {\n", N-n);
    //    fprintf(g, "plot ");
    //    fprintf(g, "''.i.' HAA.txt' with points,\ ");
    //    fprintf(g, "''.i.' HA.txt' with linespoints\ ");
    //    fprintf(g, "\n}");
    //    fclose(g);
    g << "set size square\n" << "plot 'Hierarchial algorithm (graph).txt' with linespoints title 'Hierarchial algorithm'\n";
    print_tree(f, points, m, point_indicators);
    f.close();
    g.close();
}

void Hierarchical_algorithm::print_tree(ofstream& file, vector <Vector>& points, int n, vector <vector <int>>& point_indicators)
{
    int i_1, i_2;

    i_1 = point_indicators[n][0];
    i_2 = point_indicators[n][1];
    if (i_1 != 0 && i_2 != 0)
    {
        print_tree(file, points, i_1, point_indicators);
        points[n].print_vector(file);
        points[i_1].print_vector(file);
        file << "\n\n";
        points[n].print_vector(file);
        points[i_2].print_vector(file);
        file << "\n\n";
        print_tree(file, points, i_2, point_indicators);
    }
}
