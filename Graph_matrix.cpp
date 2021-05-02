#include "Graph_matrix.h"

Graph_matrix::Graph_matrix() { N = 0; }

Graph_matrix::Graph_matrix(const Graph_matrix& b) { N = b.N; B = b.B; }

const Graph_matrix& Graph_matrix::operator=(const Graph_matrix& b) { N = b.N; B = b.B; return *this; }

int Graph_matrix::get_N() { return N; }

int Graph_matrix::get_b(int i, int j) { return B[i * N + j]; }

void Graph_matrix::create_graph_matrix(Distance_matrix& d, double delta)
{
    N = d.get_N();
    B.clear();
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (d.get_d(i, j) < delta) B.push_back(1);
            else B.push_back(0);
        }
    }
}

void Graph_matrix::print_graph_matrix()
{
    ofstream file("Graph matrix.txt");
    for (int i = 0; i < N * N; i++)
    {
        file << B[i] << " ";
        if (i != 0 && (i + 1) % N == 0) file << "\n";
    }
    file.close();
}
