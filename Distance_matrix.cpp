#include "Distance_matrix.h"

Distance_matrix::Distance_matrix() { N = 0; }

Distance_matrix::Distance_matrix(const Distance_matrix& d) { N = d.N; D = d.D; }

const Distance_matrix& Distance_matrix::operator=(const Distance_matrix& d) { N = d.N; D = d.D; return *this; }

int Distance_matrix::get_N() { return N; }

double Distance_matrix::get_d(int i, int j) { return D[i * N + j]; }

void Distance_matrix::create_distance_matrix(vector <Vector> points)
{
    N = points.size();
    D.clear();
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            D.push_back((points[i] - points[j]).length());
}

void Distance_matrix::print_distance_matrix()
{
    ofstream file("Distance matrix.txt");

    for (int i = 0; i < N * N; i++)
    {
        file << D[i] << " ";
        if (i != 0 && (i + 1) & N == 0) file << "\n";
    }
    file.close();
}
