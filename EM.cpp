#include "EM.h"

EM::EM() { k = 0; }

EM::EM(const EM& em) { k = em.k; }

const EM& EM::operator=(const EM& em) { k = em.k; return *this; }

void EM::assign_k(int k_k) { k = k_k; }

Find_cluster EM::find_clusters(vector <Vector>& points)
{
    int i, j, N = points.size(), c=0;
    vector <Cluster> C(k);
    vector <vector <double>> P(N);
    vector <double> W(k); //веса кластеров
    vector <Vector> M(k); //средние значения кластеров
    vector <pair<Vector, Vector>> S(k); //матрицы ковариаций, матрица представлена в виде двух векторов-столбцов
    double delta, det, x, y, l_1, l_2, dl, eps = 0.001, m, phi;
    vector <double> sum_p(N); //вектор с суммами строк матрицы вероятностей
    vector <double> sigma(4);
    Find_cluster fc;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < k; j++) P[i].push_back(0);
    }

    //инициализация
    for (i = 0; i < k; i++)
    {
        W[i] = k;
        W[i] = 1 / W[i];
        if (i % 2 == 0) M[i] = Vector(i, i);
        else M[i] = Vector(-i, -i);
        S[i].first = Vector(1, 0);
        S[i].second = Vector(0, 1);
    }
    for (i = 0; i < k; i++)
    {
        for (j = 0; j < N; j++) C[i].add_point_indicator(0);
    }
    //EM-алгоритм
    l_1 = 0;
    l_2 = 0;
    dl = 1;
    while (dl >= eps)
    {
        l_1 = l_2;
        l_2 = 0;
        //E-шаг
        for (i = 0; i < N; i++)
        {
            sum_p[i] = 0;
            for (j = 0; j < k; j++)
            {
                //вычисление определителя, обратной матрицы и расстояния Махаланобиса
                sigma[0] = S[j].first.get_first_coordinate();
                sigma[1] = S[j].second.get_first_coordinate();
                sigma[2] = S[j].first.get_second_coordinate();
                sigma[3] = S[j].second.get_second_coordinate();
                det = sigma[0] * sigma[3] - sigma[1] * sigma[2];
                sigma[0] = (S[j].second.get_second_coordinate()) / det;
                sigma[1] = -(S[j].first.get_second_coordinate()) / det;
                sigma[2] = -(S[j].second.get_first_coordinate()) / det;
                sigma[3] = (S[j].first.get_first_coordinate()) / det;
                x = (points[i] - M[j]).get_first_coordinate();
                y = (points[i] - M[j]).get_second_coordinate();
                delta = x * (x * sigma[0] + y * sigma[2]) + y * (x * sigma[1] + y * sigma[3]);

                //вычисление вероятности
                P[i][j] = (exp(-0.5 * delta)) / (2 * 3.1415 * sqrt(det));
                P[i][j] = W[j] * P[i][j];
                sum_p[i] = sum_p[i] + P[i][j];
            }
            if (sum_p[i] == 0) sum_p[i] = 0.0001;
            for (j = 0; j < k; j++) P[i][j] = P[i][j] / sum_p[i]; //окончательное вычисление вероятности
            l_2 = l_2 + log(sum_p[i]); //вычисление логарифмического правдоподобия
        }
        //M-шаг
        for (j = 0; j < k; j++)
        {
            //вычисление новых весов кластеров
            W[j] = 0;
            for (i = 0; i < N; i++) W[j] = W[j] + P[i][j];
            W[j] = W[j] / N;
            //вычисление новых средних значений кластеров
            x = 0;
            y = 0;
            for (i = 0; i < N; i++)
            {
                x = x + P[i][j] * (points[i].get_first_coordinate());
                y = y + P[i][j] * (points[i].get_second_coordinate());
            }
            x = x / (N * W[j]);
            y = y / (N * W[j]);
            M[j] = Vector(x, y);
            //вычисление новых матриц ковариаций
            sigma[0] = 0;
            sigma[1] = 0;
            sigma[2] = 0;
            sigma[3] = 0;
            for (i = 0; i < N; i++)
            {
                sigma[0] = sigma[0] + P[i][j] * ((points[i] - M[j]).get_first_coordinate()) * ((points[i] - M[j]).get_first_coordinate());
                sigma[1] = sigma[1] + P[i][j] * ((points[i] - M[j]).get_first_coordinate()) * ((points[i] - M[j]).get_second_coordinate());
                sigma[2] = sigma[2] + P[i][j] * ((points[i] - M[j]).get_first_coordinate()) * ((points[i] - M[j]).get_second_coordinate());
                sigma[3] = sigma[3] + P[i][j] * ((points[i] - M[j]).get_second_coordinate()) * ((points[i] - M[j]).get_second_coordinate());
            }
            sigma[0] = sigma[0] / (N * W[j]);
            sigma[1] = sigma[1] / (N * W[j]);
            sigma[2] = sigma[2] / (N * W[j]);
            sigma[3] = sigma[3] / (N * W[j]);
            S[j].first = Vector(sigma[0], sigma[2]);
            S[j].second = Vector(sigma[1], sigma[3]);
        }
        dl = fabs(l_1 - l_2);
    }
    for (i = 0; i < N; i++)
    {
        m = 0;
        for (j = 0; j < k; j++)
        {
            if (P[i][j] > m)
            {
                m = P[i][j];
                c = j;
            }
        }
        C[c].assign_point_indicator(i, 1);
    }
    for (i = 0; i < k; i++) fc.add_cluster(C[i]);
    return fc;
}
