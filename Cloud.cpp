#include "Cloud.h"

Cloud::Cloud()
{
    mean_value_for_first_coordinate = mean_value_for_second_coordinate = dispersion_for_first_coordinate = dispersion_for_second_coordinate = 0;
    radius = diameter = number_points_in_cloud = cloud_id = 0;
}

Cloud::Cloud(double mean_x, double mean_y, double sigma_x, double sigma_y, int n)
{
    int i, j;
    double sum_x = 0, sum_y = 0;
    vector <double> dist;
    vector <double> max_dist(n, 0);

    mean_value_for_first_coordinate = mean_x;
    mean_value_for_second_coordinate = mean_y;
    dispersion_for_first_coordinate = sigma_x;
    dispersion_for_second_coordinate = sigma_y;
    radius = 0;
    diameter = 0;
    number_points_in_cloud = n;
    cloud_id = 0;
    if (number_points_in_cloud != 0)
    {
        for (i = 0; i < number_points_in_cloud; i++)
        {
            for (j = 0; j < 1000; j++)
            {
                sum_x = sum_x + rand() % 201 - 100;
                sum_y = sum_y + rand() % 201 - 100;
            }
            sum_x = sum_x * 0.001 * dispersion_for_first_coordinate + mean_value_for_first_coordinate;
            sum_y = sum_y * 0.001 * dispersion_for_second_coordinate + mean_value_for_second_coordinate;
            points_in_cloud.push_back(Vector(sum_x, sum_y));
            sum_x = 0;
            sum_y = 0;
        }
    }
    for (i = 0; i < number_points_in_cloud; i++) points_in_cloud[i].assign_vector_id(i);
    for (i = 0; i < number_points_in_cloud; i++)
    {
        for (j = 0; j < number_points_in_cloud; j++)
            dist.push_back((points_in_cloud[i] - points_in_cloud[j]).length());
    }
    for (i = 0; i < number_points_in_cloud; i++)
    {
        for (j = 0; j < number_points_in_cloud; j++)
            if (dist[i * number_points_in_cloud + j] > max_dist[i]) max_dist[i] = dist[i * number_points_in_cloud + j];
    }
    for (i = 0; i < number_points_in_cloud; i++)
        if (max_dist[i] > diameter) diameter = max_dist[i];
    radius = diameter;
    for (i = 0; i < number_points_in_cloud; i++)
        if (max_dist[i] < radius) radius = max_dist[i];
}

Cloud::Cloud(const Cloud& c)
{
    mean_value_for_first_coordinate = c.mean_value_for_first_coordinate;
    mean_value_for_second_coordinate = c.mean_value_for_second_coordinate;
    dispersion_for_first_coordinate = c.dispersion_for_first_coordinate;
    dispersion_for_second_coordinate = c.dispersion_for_second_coordinate;
    radius = c.radius;
    diameter = c.diameter;
    number_points_in_cloud = c.number_points_in_cloud;
    cloud_id = c.cloud_id;
    points_in_cloud = c.points_in_cloud;
}

const Cloud& Cloud::operator=(const Cloud& c)
{
    mean_value_for_first_coordinate = c.mean_value_for_first_coordinate;
    mean_value_for_second_coordinate = c.mean_value_for_second_coordinate;
    dispersion_for_first_coordinate = c.dispersion_for_first_coordinate;
    dispersion_for_second_coordinate = c.dispersion_for_second_coordinate;
    radius = c.radius;
    diameter = c.diameter;
    number_points_in_cloud = c.number_points_in_cloud;
    cloud_id = c.cloud_id;
    points_in_cloud = c.points_in_cloud;
    return *this;
}

Vector Cloud::get_cloud_center() { return Vector(mean_value_for_first_coordinate, mean_value_for_second_coordinate); }

Vector Cloud::get_dispersions() { return Vector(dispersion_for_first_coordinate, dispersion_for_second_coordinate); }

double Cloud::get_radius() { return radius; }

double Cloud::get_diameter() { return diameter; }

int Cloud::get_number_points_in_cloud() { return number_points_in_cloud; }

int Cloud::get_cloud_id() { return cloud_id; }

Vector Cloud::get_point_in_cloud(int point_id) { return points_in_cloud[point_id]; }

void Cloud::assign_cloud_id(int id) { cloud_id = id; }

void Cloud::assign_point_id_in_cloud(int n, int id) { points_in_cloud[n].assign_vector_id(id); }

void Cloud::print_cloud(ofstream& file)
{
    for (int i = 0; i < number_points_in_cloud; i++)
        file << points_in_cloud[i].get_first_coordinate() << " " << points_in_cloud[i].get_second_coordinate() << " " << cloud_id << endl;
}

void Cloud::creat_cloud_histogram(int number_of_columns)
{
    ofstream f_x, f_y, g_x, g_y;
    int i, j;
    double max_x, min_x, d_x, max_y, min_y, d_y;
    vector <int> hist_x(number_of_columns, 0);
    vector <int> hist_y(number_of_columns, 0);
    Vector v = get_point_in_cloud(0);
    string s_1 = to_string(cloud_id), 
        s_2("C://Users//huawei//source//repos//Cluster Analysis//Cluster Analysis//Visualization//Field and histograms//"), 
        s_3("C://Users//huawei//source//repos//Cluster Analysis//Cluster Analysis//Visualization//Field and histograms//"),
        s_4("C://Users//huawei//source//repos//Cluster Analysis//Cluster Analysis//Visualization//Field and histograms//"),
        s_5("C://Users//huawei//source//repos//Cluster Analysis//Cluster Analysis//Visualization//Field and histograms//");
    s_2.append(s_1);
    s_2.append("-th cloud histogram for first coordinate.txt");
    s_3.append(s_1);
    s_3.append("-th cloud histogram for first coordinate.plt");
    s_4.append(s_1);
    s_4.append("-th cloud histogram for second coordinate.txt");
    s_5.append(s_1);
    s_5.append("-th cloud histogram for second coordinate.plt");
    
    f_x.open(s_2);
    g_x.open(s_3);
    g_x << "set style data histogram\n" << "set style fill solid\n" << "set yrange [0:]\n" << "set autoscale x\n" << "set autoscale y\n" << "set boxwidth 2\n" 
        << "plot '"<< s_1 << "-th cloud histogram for first coordinate.txt'\n";
    f_y.open(s_4);
    g_y.open(s_5);
    g_y << "set style data histogram\n" << "set style fill solid\n" << "set yrange [0:]\n" << "set autoscale x\n" << "set autoscale y\n" << "set boxwidth 2\n" 
        << "plot '" << s_1 << "-th cloud histogram for second coordinate.txt'\n";

    min_x = v.get_first_coordinate();
    max_x = v.get_first_coordinate();
    min_y = v.get_second_coordinate();
    max_y = v.get_second_coordinate();

    for (i = 0; i < number_points_in_cloud; i++)
    {
        v = get_point_in_cloud(i);
        if (v.get_first_coordinate() < min_x) min_x = v.get_first_coordinate();
        if (v.get_first_coordinate() > max_x) max_x = v.get_first_coordinate();
        if (v.get_second_coordinate() < min_y) min_y = v.get_second_coordinate();
        if (v.get_second_coordinate() > max_y) max_y = v.get_second_coordinate();
    }
    d_x = (max_x - min_x) / number_of_columns;
    d_y = (max_y - min_y) / number_of_columns;
    for (i = 0; i < number_points_in_cloud; i++)
    {
        v = get_point_in_cloud(i);
        for (j = 1; j < number_of_columns + 1; j++)
        {
            if (v.get_first_coordinate() < (min_x + j * d_x) && v.get_first_coordinate() >= (min_x + (j - 1) * d_x)) hist_x[j - 1]++;
            if (v.get_second_coordinate() < (min_y + j * d_y) && v.get_second_coordinate() >= (min_y + (j - 1) * d_y)) hist_y[j - 1]++;
        }
    }
    for (i = 0; i < number_of_columns; i++)
    {
        f_x << hist_x[i] << endl;
        f_y << hist_y[i] << endl;
    }
    f_x.close();
    g_x.close();
    f_y.close();
    g_y.close();
}

void Cloud::shift_cloud(Vector v)
{
    mean_value_for_first_coordinate = get_cloud_center().get_first_coordinate() + v.get_first_coordinate();
    mean_value_for_second_coordinate = get_cloud_center().get_second_coordinate() + v.get_second_coordinate();
    for (int i = 0; i < number_points_in_cloud; i++) points_in_cloud[i] = points_in_cloud[i] + v;
}

void Cloud::turn_cloud(double phi)
{
    double x, y;

    for (int i = 0; i < number_points_in_cloud; i++)
    {
        x = cos(phi) * (points_in_cloud[i].get_first_coordinate() - mean_value_for_first_coordinate) - sin(phi) * (points_in_cloud[i].get_second_coordinate() - mean_value_for_second_coordinate);
        y = sin(phi) * (points_in_cloud[i].get_first_coordinate() - mean_value_for_first_coordinate) - cos(phi) * (points_in_cloud[i].get_second_coordinate() - mean_value_for_second_coordinate);
        points_in_cloud[i] = Vector(x, y) + get_cloud_center();
    }
}

void Cloud::compression_cloud(double lambda)
{
    for (int i = 0; i < number_points_in_cloud; i++)
    {
        points_in_cloud[i] = lambda * (points_in_cloud[i] - get_cloud_center());
        points_in_cloud[i] = points_in_cloud[i] + get_cloud_center();
    }
}