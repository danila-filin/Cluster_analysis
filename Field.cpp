#include "Field.h"

Field::Field() { number_clouds_in_field = number_find_clusters_in_field = number_points_in_field = 0; }

Field::Field(const Field& f)
{
    number_clouds_in_field = f.number_clouds_in_field;
    number_find_clusters_in_field = f.number_find_clusters_in_field;
    number_points_in_field = f.number_points_in_field;
    clouds_in_field = f.clouds_in_field;
    find_clusters = f.find_clusters;
    buffer = f.buffer;
}

const Field& Field::operator=(const Field& f)
{
    number_clouds_in_field = f.number_clouds_in_field;
    number_find_clusters_in_field = f.number_find_clusters_in_field;
    number_points_in_field = f.number_points_in_field;
    clouds_in_field = f.clouds_in_field;
    find_clusters = f.find_clusters;
    buffer = f.buffer;
    return *this;
}

void Field::add_cloud_in_field(Cloud c)
{
    int i, k = number_points_in_field;

    number_clouds_in_field++;
    number_points_in_field = number_points_in_field + c.get_number_points_in_cloud();
    clouds_in_field.push_back(c);
    clouds_in_field[number_clouds_in_field - 1].assign_cloud_id(number_clouds_in_field - 1);
    for (i = 0; i < clouds_in_field[number_clouds_in_field - 1].get_number_points_in_cloud(); i++)
    {
        clouds_in_field[number_clouds_in_field - 1].assign_point_id_in_cloud(i, k);
        k++;
    }
}

void Field::delete_cloud_from_field(int id)
{
    int i, j, k = 0;

    number_points_in_field = number_points_in_field - clouds_in_field[id].get_number_points_in_cloud();
    number_clouds_in_field--;
    clouds_in_field.erase(clouds_in_field.begin() + id);
    for (i = 0; i < number_clouds_in_field; i++) clouds_in_field[i].assign_cloud_id(i);
    for (i = 0; i < number_clouds_in_field; i++)
    {
        for (j = 0; j < clouds_in_field[i].get_number_points_in_cloud(); j++)
        {
            clouds_in_field[i].assign_point_id_in_cloud(j, k);
            k++;
        }
    }
}

void Field::print_field()
{
    ofstream f("Field with clouds.txt"), g("Field with clouds.plt");

    for (int i = 0; i < number_clouds_in_field; i++) clouds_in_field[i].print_cloud(f);
    g << "set size square\n" << "set palette\n" << "plot 'Field with clouds.txt' palette\n";
    f.close();
    g.close();
}

vector <Vector> Field::get_points_from_field()
{
    vector <Vector> points;

    for (int i = 0; i < number_clouds_in_field; i++)
    {
        for (int j = 0; j < clouds_in_field[i].get_number_points_in_cloud(); j++) points.push_back(clouds_in_field[i].get_point_in_cloud(j));
    }
    return points;
}

void Field::add_cloud_from_field_in_buffer(int id)
{
    buffer.add_cloud_in_buffer(clouds_in_field[id]);
    delete_cloud_from_field(id);
}

void Field::add_all_clouds_from_field_in_buffer()
{
    for (int i = 0; i < number_clouds_in_field; i++)
    {
        buffer.add_cloud_in_buffer(clouds_in_field[i]);
        delete_cloud_from_field(i);
    }
}

void Field::upload_cloud_from_buffer_in_field(int n) { add_cloud_in_field(buffer.upload_cloud_from_buffer(n)); }

void Field::upload_all_clouds_from_buffer_in_field()
{
    for (int i = 0; i < buffer.get_number_clouds_in_buffer(); i++) add_cloud_in_field(buffer.upload_cloud_from_buffer(i));
}

void Field::shift_cloud_in_buffer(int n, Vector v) { buffer.shift_cloud_in_buffer(n, v); }

void Field::shift_all_clouds_in_buffer(Vector v) { buffer.shift_all_clouds_in_buffer(v); }

void Field::turn_cloud_in_bufffer(int n, double phi) { buffer.turn_cloud_in_buffer(n, phi); }

void Field::turn_all_clouds_in_bufffer(double phi) { buffer.turn_all_clouds_in_buffer(phi); }

void Field::compression_cloud_in_buffer(int n, double lambda) { buffer.compression_cloud_in_buffer(n, lambda); }

void Field::compression_all_clouds_in_buffer(double lambda) { buffer.compression_all_clouds_in_buffer(lambda); }

void Field::creat_field_histogram(int number_of_columns)
{
    ofstream f_x("Field histogram for first coordinate.txt"), f_y("Field histogram for second coordinate.txt");
    ofstream g_x("Field histogram for first coordinate.plt"), g_y("Field histogram for second coordinate.plt");
    double min_x, max_x, min_y, max_y, d_x, d_y;
    int i, j, k;
    vector <int> hist_x(number_of_columns, 0);
    vector <int> hist_y(number_of_columns, 0);
    Vector v = clouds_in_field[0].get_point_in_cloud(0);

    g_x << "set style data histogram\n" << "set style fill solid\n" << "set yrange [0:]\n" << "set autoscale x\n" << "set autoscale y\n" << "set boxwidth 2\n" << "plot 'Field histogram for first coordinate.txt'\n";
    g_y << "set style data histogram\n" << "set style fill solid\n" << "set yrange [0:]\n" << "set autoscale x\n" << "set autoscale y\n" << "set boxwidth 2\n" << "plot 'Field histogram for second coordinate.txt'\n";

    min_x = v.get_first_coordinate();
    max_x = v.get_first_coordinate();
    min_y = v.get_second_coordinate();
    max_y = v.get_second_coordinate();

    for (i = 0; i < number_clouds_in_field; i++)
    {
        for (j = 0; j < clouds_in_field[i].get_number_points_in_cloud(); j++)
        {
            v = clouds_in_field[i].get_point_in_cloud(j);
            if (v.get_first_coordinate() < min_x) min_x = v.get_first_coordinate();
            if (v.get_first_coordinate() > max_x) max_x = v.get_first_coordinate();
            if (v.get_second_coordinate() < min_y) min_y = v.get_second_coordinate();
            if (v.get_second_coordinate() > max_y) max_y = v.get_second_coordinate();
        }
    }
    d_x = (max_x - min_x) / number_of_columns;
    d_y = (max_y - min_y) / number_of_columns;
    for (i = 0; i < number_clouds_in_field; i++)
    {
        for (j = 0; j < clouds_in_field[i].get_number_points_in_cloud(); j++)
        {
            v = clouds_in_field[i].get_point_in_cloud(j);
            for (k = 1; k < number_of_columns + 1; k++)
            {
                if (v.get_first_coordinate() < (min_x + k * d_x) && v.get_first_coordinate() >= (min_x + (k - 1) * d_x)) hist_x[k - 1]++;
                if (v.get_second_coordinate() < (min_y + k * d_y) && v.get_second_coordinate() >= (min_y + (k - 1) * d_y)) hist_y[k - 1]++;
            }
        }
    }
    for (i = 0; i < number_of_columns; i++)
    {
        f_x << hist_x[i] << endl;
        f_y << hist_y[i] << endl;
    }
    f_x.close();
    f_y.close();
    g_x.close();
    g_y.close();
}

void Field::creat_cloud_histogram(int id, int number_of_colunms) { clouds_in_field[id].creat_cloud_histogram(number_of_colunms); }

double Field::fun(double x, double y) { return (x * x - y * y) / 10 + 5; }

void Field::print_fun()
{
    ofstream g("Function.plt");

    g << "reset\n" << "set terminal png size 640, 800\n" << "set output 'function.png'\n" << "set view 60, 30, 1, 1\n" << "set xyplane at -4.5\n";
    g << "set key top center font 'times, 14'\n" << "set pm3d\n" << "set xlabel 'x'\n";
    g << "set ylabel 'y'\n" << "set zlabel 'z'\n" << "splot (x*x-y*y)/10+10\n";
    g.close();
}

void Field::wave(double delta)
{
    int c = 0;
    Wave_algorithm w;
    vector <Vector> points;

    for (int i = 0; i < number_clouds_in_field; i++)
    {
        for (int j = 0; j < clouds_in_field[i].get_number_points_in_cloud(); j++) points.push_back(clouds_in_field[i].get_point_in_cloud(j));
    }
    number_find_clusters_in_field++;
    w.assign_delta(delta);
    find_clusters.push_back(w.find_clusters(points));
    find_clusters[number_find_clusters_in_field - 1].assign_alg("Wave");
    for (int i = 0; i < number_find_clusters_in_field - 1; i++)
    {
        if (find_clusters[i].get_alg() == "Wave") c++;
    }
    find_clusters[number_find_clusters_in_field - 1].assign_delta(delta);
    find_clusters[number_find_clusters_in_field - 1].assign_alg_number(c);
    find_clusters[number_find_clusters_in_field - 1].print_wave_algorithm(points);
    cout << "Wave" << endl;
}

void Field::dbscan(double delta, int k)
{
    int c = 0;
    DBSCAN db;
    vector <Vector> points;
    vector <int> cpd;

    for (int i = 0; i < number_clouds_in_field; i++)
    {
        for (int j = 0; j < clouds_in_field[i].get_number_points_in_cloud(); j++) points.push_back(clouds_in_field[i].get_point_in_cloud(j));
    }
    number_find_clusters_in_field++;
    db.assign_delta(delta);
    db.assign_k(k);
    find_clusters.push_back(db.find_clusters(points, cpd));
    find_clusters[number_find_clusters_in_field - 1].assign_alg("DBSCAN");
    for (int i = 0; i < number_find_clusters_in_field - 1; i++)
    {
        if (find_clusters[i].get_alg() == "DBSCAN") c++;
    }
    find_clusters[number_find_clusters_in_field - 1].assign_delta(delta);
    find_clusters[number_find_clusters_in_field - 1].assign_k(k);
    find_clusters[number_find_clusters_in_field - 1].assign_alg_number(c);
    find_clusters[number_find_clusters_in_field - 1].print_dbscan_algorithm(points, cpd);
    cout << "DBSCAN" << endl;
}

void Field::k_m(int k)
{
    int c = 0;
    k_means km;
    vector <Vector> points;

    for (int i = 0; i < number_clouds_in_field; i++)
    {
        for (int j = 0; j < clouds_in_field[i].get_number_points_in_cloud(); j++) points.push_back(clouds_in_field[i].get_point_in_cloud(j));
    }
    number_find_clusters_in_field++;
    km.assing_k(k);
    find_clusters.push_back(km.find_clusters(points));
    find_clusters[number_find_clusters_in_field - 1].assign_alg("k means");
    for (int i = 0; i < number_find_clusters_in_field - 1; i++)
    {
        if (find_clusters[i].get_alg() == "k means") c++;
    }
    find_clusters[number_find_clusters_in_field - 1].assign_k(k);
    find_clusters[number_find_clusters_in_field - 1].assign_alg_number(c);
    find_clusters[number_find_clusters_in_field - 1].print_k_means_algorithm(points);
    cout << "k means" << endl;
}

void Field::em(int k)
{
    int c = 0;
    EM em;
    vector <Vector> points;

    for (int i = 0; i < number_clouds_in_field; i++)
    {
        for (int j = 0; j < clouds_in_field[i].get_number_points_in_cloud(); j++) points.push_back(clouds_in_field[i].get_point_in_cloud(j));
    }
    number_find_clusters_in_field++;
    em.assign_k(k);
    find_clusters.push_back(em.find_clusters(points));
    find_clusters[number_find_clusters_in_field - 1].assign_alg("EM");
    for (int i = 0; i < number_find_clusters_in_field - 1; i++)
    {
        if (find_clusters[i].get_alg() == "EM") c++;
    }
    find_clusters[number_find_clusters_in_field - 1].assign_k(k);
    find_clusters[number_find_clusters_in_field - 1].assign_alg_number(c);
    find_clusters[number_find_clusters_in_field - 1].print_em_algorithm(points);
    cout << "EM" << endl;
}

void Field::tree()
{
    Spanning_tree T;
    vector <Vector> points;
    vector <pair <double, pair <int, int>>> edges;

    for (int i = 0; i < number_clouds_in_field; i++)
    {
        for (int j = 0; j < clouds_in_field[i].get_number_points_in_cloud(); j++) points.push_back(clouds_in_field[i].get_point_in_cloud(j));
    }
    edges = T.creat_spanning_tree(points);
    T.print_spanning_tree(points, edges);
    cout << "Spanning tree" << endl;
}

void Field::hierarchy()
{
    Hierarchical_algorithm h;
    vector <Vector> points;

    for (int i = 0; i < number_clouds_in_field; i++)
    {
        for (int j = 0; j < clouds_in_field[i].get_number_points_in_cloud(); j++) points.push_back(clouds_in_field[i].get_point_in_cloud(j));
    }
    h.hierarchy(points);
    cout << "Hierarchy" << endl;
}
