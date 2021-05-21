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
    ofstream f("C://Users//huawei//source//repos//Cluster Analysis//Cluster Analysis//Visualization//Field and histograms//Field with clouds.txt"),
        g("C://Users//huawei//source//repos//Cluster Analysis//Cluster Analysis//Visualization//Field and histograms//Field with clouds.plt");

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
    ofstream f_x("C://Users//huawei//source//repos//Cluster Analysis//Cluster Analysis//Visualization//Field and histograms//Field histogram for first coordinate.txt"), 
        f_y("C://Users//huawei//source//repos//Cluster Analysis//Cluster Analysis//Visualization//Field and histograms//Field histogram for second coordinate.txt");
    ofstream g_x("C://Users//huawei//source//repos//Cluster Analysis//Cluster Analysis//Visualization//Field and histograms//Field histogram for first coordinate.plt"), 
        g_y("C://Users//huawei//source//repos//Cluster Analysis//Cluster Analysis//Visualization//Field and histograms//Field histogram for second coordinate.plt");
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

void Field::print_fun(Vector p, double value)
{
    ofstream g("C://Users//huawei//source//repos//Cluster Analysis//Cluster Analysis//Visualization//Function interpolation//Function.plt");
    ofstream f("C://Users//huawei//source//repos//Cluster Analysis//Cluster Analysis//Visualization//Function interpolation//Point.txt");

    f << p.get_first_coordinate() << " " << p.get_second_coordinate() << " " << value;
    f.close();
    //g << "reset\n" << "set terminal png size 640, 800\n" << "set output 'function.png'\n" << "set view 60, 30, 1, 1\n" << "set xyplane at -4.5\n";
    //g << "set key top center font 'times, 14'\n" << "set pm3d\n" << "set xlabel 'x'\n";
    //g << "set ylabel 'y'\n" << "set zlabel 'z'\n" << "splot (x*x-y*y)/10+10\n"; 
//    g << "splot [x=" << p.get_first_coordinate()-2 << ":" << p.get_first_coordinate()+2 <<"] [y=" << p.get_second_coordinate() - 2 << ":" << p.get_second_coordinate() + 2 << "] (x*x-y*y)/10+10\n";
//    g << "set point " << p.get_first_coordinate() << "," << p.get_second_coordinate() << "," << value << " \n";
    //g << "set arrow 1 from 0, 3, 1 to 0, 0, 1\n";
    g << "splot (x*x-y*y)/10+5, 'Point.txt'\n";
    g << "set arrow from " << p.get_first_coordinate() << "," << p.get_second_coordinate() << "," << 0 << " to " << p.get_first_coordinate() << "," << p.get_second_coordinate() << "," << value << "\n";
//    g << "set point " << p.get_first_coordinate() << "," << p.get_second_coordinate() << "," << value << " \n";
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
}

void Field::find_min_y(vector <Vector>& points)
{
    int k = 0;
    for (int i = 0; i < points.size(); i++)
    {
        if ((i != k && points[i].get_second_coordinate() < points[k].get_second_coordinate()) || 
            (i != k && points[i].get_second_coordinate() == points[k].get_second_coordinate() && 
                points[i].get_first_coordinate() < points[k].get_first_coordinate()))
        {
            k = i;
        }
    }
    rotate(points.begin(), points.begin() + k, points.end());
}

void Field::polar_angle_sort(vector <Vector>& points)
{
    vector <double> angles;
    Vector v;
    double a;

    for (int i = 0; i < points.size(); i++)
    {
        if (i != 0)
        {
            if ((points[i] - points[0]).length() < 0.0001) angles.push_back(0);
            else angles.push_back(acos((points[i] - points[0]).get_first_coordinate() / (points[i] - points[0]).length()));
        }
        else angles.push_back(0);
    }
    for (int i = 0; i < points.size() - 1; i++)
    {
        for (int j = 0; j < points.size() - 1 - i; j++)
        {
            if (angles[j] > angles[j + 1])
            {
                a = angles[j];
                v = points[j];
                angles[j] = angles[j + 1];
                points[j] = points[j + 1];
                angles[j + 1] = a;
                points[j + 1] = v;
            }
        }
    }
}

double Field::left_rotate(Vector p, Vector q, Vector r)
{
    Vector v = q - p, u = r - q;
    return v.get_first_coordinate() * u.get_second_coordinate() - v.get_second_coordinate() * u.get_first_coordinate();
}

vector <Vector> Field::convex_hull(vector <Vector> points)
{
    vector <Vector> q;

    if (points.size() < 3) return points;
    find_min_y(points);
    q.push_back(points[0]);
    polar_angle_sort(points);
    q.push_back(points[1]);
    for (int i = 2; i < points.size(); i++)
    {
        while (left_rotate(q[q.size() - 2], q[q.size() - 1], points[i]) < 0 && q.size() > 1) q.pop_back();
        q.push_back(points[i]);
    }
    q.push_back(points[0]);
    return q;
}

Delaunay_triangulation Field::generate_delaunay_trinagulation(vector <Vector>& points)
{
    Delaunay_triangulation triangulation;
    vector <Vector> vertices;
    int i, j, k;
    Vector a, b, c;
    vector <int> ind(points.size(), 0);

    for (i = 0; i < points.size() - 1; i++)
    {
        for (j = 0; j < points.size() - 1 - i; j++)
        {
            if (points[j].get_first_coordinate() > points[j + 1].get_first_coordinate())
            {
                a = points[j];
                points[j] = points[j + 1];
                points[j + 1] = a;
            }
        }
    }
    a = points[0];
    b = points[1];
    c = points[2];
    triangulation.add_triangle(Triangle(a, b, c));
    ind[0] = ind[1] = ind[2] = 1;
    c = points[2];
    for (i = 3; i < points.size(); i++)
    {
        vertices.clear();
        for (j = 0; j < points.size(); j++)
        {
            if (ind[j] == 1) vertices.push_back(points[j]);
        }
        vertices = convex_hull(vertices);
        for (j = 0; j < vertices.size(); j++)
        {
            if (vertices[j].get_first_coordinate() == c.get_first_coordinate() &&
                vertices[j].get_second_coordinate() == c.get_second_coordinate()) k = j;
        }
        rotate(vertices.begin(), vertices.begin() + k, vertices.end());
        vertices.push_back(vertices[0]);
        a = c - points[i];
        a.assign_vector_id(c.get_vector_id());
        b = vertices[1] - points[i];
        b.assign_vector_id(vertices[1].get_vector_id());
        for (j = 2; j < vertices.size(); j++)
        {
            if (a.get_first_coordinate() * b.get_second_coordinate() - a.get_second_coordinate() * b.get_first_coordinate() < 0)
            {
                Vector p = a + points[i];
                Vector q = b + points[i];
                p.assign_vector_id(a.get_vector_id());
                q.assign_vector_id(b.get_vector_id());
                Triangle T = Triangle(points[i], p, q);
                T.assing_neighbouring_triangle_id(triangulation.find_triangle(p, q));
                triangulation.add_triangle(T);
                ind[i] = 1;
            }
            if (a.get_first_coordinate() * b.get_second_coordinate() - a.get_second_coordinate() * b.get_first_coordinate() > 0) break;
            a = b;
            b = vertices[j] - points[i];
            b.assign_vector_id(vertices[j].get_vector_id());
        }
        reverse(vertices.begin(), vertices.end());
        a = c - points[i];
        a.assign_vector_id(c.get_vector_id());
        b = vertices[1] - points[i];
        b.assign_vector_id(vertices[1].get_vector_id());
        for (j = 2; j < vertices.size(); j++)
        {
            if (a.get_first_coordinate() * b.get_second_coordinate() - a.get_second_coordinate() * b.get_first_coordinate() > 0)
            {
                Vector p = a + points[i];
                Vector q = b + points[i];
                p.assign_vector_id(a.get_vector_id());
                q.assign_vector_id(b.get_vector_id());
                Triangle T = Triangle(points[i], p, q);
                T.assing_neighbouring_triangle_id(triangulation.find_triangle(p, q));
                triangulation.add_triangle(T);
                ind[i] = 1;
            }
            if (a.get_first_coordinate() * b.get_second_coordinate() - a.get_second_coordinate() * b.get_first_coordinate() < 0) break;
            a = b;
            b = vertices[j] - points[i];
            b.assign_vector_id(vertices[j].get_vector_id());
        }
        c = points[i];
    }
    return triangulation;
}

double Field::Gauss_function(double x) { return exp(-(x * x) / 2); }

void Field::function_interpolation(Vector p)
{
    Find_cluster F;
    k_means alg;
    vector <Vector> points, cluster, neighbouring_points, points_1;
    int i, j, k;
    double dist = 100, h = 0.1, sum_w = 0, sum_w_y = 0, r = 0, sum_y = 0, sum_eps = 0, mean_y = 0;
    Delaunay_triangulation T;
    vector <double> w, eps;

    for (i = 0; i < number_clouds_in_field; i++)
    {
        for (j = 0; j < clouds_in_field[i].get_number_points_in_cloud(); j++)
            points.push_back(clouds_in_field[i].get_point_in_cloud(j));
    }
    alg.assing_k(5);
    F = alg.find_clusters(points);
    F.print_k_means_algorithm(points);
    for (i = 0; i < F.get_number_clusters_in_find_cluster(); i++)
    {
        if ((p - F.get_cluster(i).get_cluster_center()).length() < dist)
        {
            dist = (p - F.get_cluster(i).get_cluster_center()).length();
            k = i;
        }
    }
    if (dist == 10)
    {
        cout << "Error. Points is too far away from the clusters.\n\n";
    }
    else
    {
        for (i = 0; i < number_points_in_field; i++)
            if (F.get_cluster(k).get_point_indicator(i) == 1) cluster.push_back(points[i]);
        cluster.push_back(p);
        T = generate_delaunay_trinagulation(cluster);
        T.create_triangle_indicators();
        T.print_Delaunay_triangulation();
        neighbouring_points = T.find_neighbouring_points(p);
        for (i = 0; i < neighbouring_points.size(); i++) w.push_back(Gauss_function((p - neighbouring_points[i]).length() / h));
        for (i = 0; i < neighbouring_points.size(); i++)
        {
            sum_w_y = sum_w_y + points[i].get_function_value() * w[i];
            sum_w = sum_w + w[i];
        }
    }
    cluster.pop_back();
    for (i = 0; i < cluster.size(); i++) mean_y = mean_y + points[i].get_function_value();
    mean_y = mean_y * (1 / cluster.size());
    for (i = 0; i < cluster.size(); i++)
    {
        neighbouring_points.clear();
        w.clear();
        points_1.clear();
        for (j = 0; j < i; j++) points_1.push_back(cluster[i]);
        for (j = i + 1; j < points.size(); j++) points_1.push_back(cluster[i]);
        T = generate_delaunay_trinagulation(points_1);
        T.create_triangle_indicators();
        neighbouring_points = T.find_neighbouring_points(points[i]);
        for (j = 0; j < neighbouring_points.size(); j++) w.push_back(Gauss_function((cluster[i] - neighbouring_points[i]).length() / h));
        for (j = 0; j < neighbouring_points.size(); j++)
        {
            sum_w_y = sum_w_y + points_1[i].get_function_value() * w[i];
            sum_w = sum_w + w[i];
        }
        eps.push_back(cluster[i].get_function_value() - sum_w_y / sum_w);
    }
    for (i = 0; i < cluster.size(); i++) 
        sum_y = sum_y + ((cluster[i].get_function_value() - mean_y) * (cluster[i].get_function_value() - mean_y));
    for (i = 0; i < cluster.size(); i++) sum_eps = sum_eps + eps[i] * eps[i];
    r = 1 - sum_eps / sum_y;
    cout << "Real: " << p.get_function_value() << ". Forecast: " << sum_w_y / sum_w << ". r^2=" << r << "." << endl;
    print_fun(p, sum_w_y / sum_w);
}