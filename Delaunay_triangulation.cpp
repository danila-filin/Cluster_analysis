#include "Delaunay_triangulation.h"

Delaunay_triangulation::Delaunay_triangulation() { number_triangles = number_points = 0; }

Delaunay_triangulation::Delaunay_triangulation(const Delaunay_triangulation& Del_tr)
{
	triangles = Del_tr.triangles;
	number_triangles = Del_tr.number_triangles;
	number_points = Del_tr.number_points;
	triangle_indicators = Del_tr.triangle_indicators;
}

const Delaunay_triangulation& Delaunay_triangulation::operator=(const Delaunay_triangulation& Del_tr)
{
	triangles = Del_tr.triangles;
	number_triangles = Del_tr.number_triangles;
	number_points = Del_tr.number_points;
	triangle_indicators = Del_tr.triangle_indicators;
	return *this;
}

void Delaunay_triangulation::add_triangle(Triangle T)
{
	T.assign_id(number_triangles);
	triangles.push_back(T);
	number_triangles++;
	number_points = number_points + 3;
}

Triangle Delaunay_triangulation::get_triangle(int id) { return triangles[id]; }

int Delaunay_triangulation::get_number_triangles() { return number_triangles; }

int Delaunay_triangulation::find_triangle(Vector p, Vector q)
{
	for (int i = 0; i < number_triangles; i++)
	{
		Vector a = triangles[i].get_A(), b = triangles[i].get_B(), c = triangles[i].get_C();
		//cout << "+ " << a.get_vector_id() << " " << b.get_vector_id() << " " << c.get_vector_id() << endl;
		if (a.get_vector_id() == p.get_vector_id() && b.get_vector_id() == q.get_vector_id()) return i;
		if (a.get_vector_id() == p.get_vector_id() && c.get_vector_id() == q.get_vector_id()) return i;
		if (b.get_vector_id() == p.get_vector_id() && a.get_vector_id() == q.get_vector_id()) return i;
		if (c.get_vector_id() == p.get_vector_id() && a.get_vector_id() == q.get_vector_id()) return i;
		if (b.get_vector_id() == p.get_vector_id() && c.get_vector_id() == q.get_vector_id()) return i;
		if (c.get_vector_id() == p.get_vector_id() && b.get_vector_id() == q.get_vector_id()) return i;
	}
	return -1;
}

void Delaunay_triangulation::create_triangle_indicators()
{
	triangle_indicators.resize(number_triangles);
	for (int i = 0; i < number_triangles; i++) triangle_indicators[i].resize(number_triangles);
	for (int i = 0; i < number_triangles; i++)
	{
		for (int j = 0; j < number_triangles; j++) triangle_indicators[i][j] = 0;
	}
	for (int i = 0; i < number_triangles; i++)
	{
		for (int j = 0; j < number_triangles; j++)
			if (triangles[i].get_neighbouring_triangle_id() == j) triangle_indicators[i][j] = triangle_indicators[j][i] = 1;
	}
}

vector <Vector> Delaunay_triangulation::find_neighbouring_points(Vector p)
{
	int i, j, k;
	vector <Vector> neighbouring_points;

	for (i = 0; i < number_triangles; i++)
	{
		if (triangles[i].get_A().get_vector_id() == p.get_vector_id())
		{
			k = i;
			if (triangles[k].get_A().get_vector_id() != p.get_vector_id()) neighbouring_points.push_back(triangles[k].get_A());
			if (triangles[k].get_B().get_vector_id() != p.get_vector_id()) neighbouring_points.push_back(triangles[k].get_B());
			if (triangles[k].get_C().get_vector_id() != p.get_vector_id()) neighbouring_points.push_back(triangles[k].get_C());
			/*for (j = 0; j < number_triangles; j++)
			{
				if (triangle_indicators[k][j] == 1 && j != k)
				{
					if (triangles[j].get_A().get_vector_id() == p.get_vector_id() || triangles[j].get_B().get_vector_id() == p.get_vector_id() ||
						triangles[j].get_C().get_vector_id() == p.get_vector_id())
					{
						if (triangles[k].get_A().get_vector_id() != p.get_vector_id()) neighbouring_points.push_back(triangles[k].get_A());
						if (triangles[k].get_B().get_vector_id() != p.get_vector_id()) neighbouring_points.push_back(triangles[k].get_B());
						if (triangles[k].get_C().get_vector_id() != p.get_vector_id()) neighbouring_points.push_back(triangles[k].get_C());
					}
				}
			}*/
			//break;
		}
		if (triangles[i].get_B().get_vector_id() == p.get_vector_id())
		{
			k = i;
			if (triangles[k].get_A().get_vector_id() != p.get_vector_id()) neighbouring_points.push_back(triangles[k].get_A());
			if (triangles[k].get_B().get_vector_id() != p.get_vector_id()) neighbouring_points.push_back(triangles[k].get_B());
			if (triangles[k].get_C().get_vector_id() != p.get_vector_id()) neighbouring_points.push_back(triangles[k].get_C());
			/*for (j = 0; j < number_triangles; j++)
			{
				if (triangle_indicators[k][j] == 1 && j != k)
				{
					if (triangles[j].get_A().get_vector_id() == p.get_vector_id() || triangles[j].get_B().get_vector_id() == p.get_vector_id() ||
						triangles[j].get_C().get_vector_id() == p.get_vector_id())
					{
						if (triangles[k].get_A().get_vector_id() != p.get_vector_id()) neighbouring_points.push_back(triangles[k].get_A());
						if (triangles[k].get_B().get_vector_id() != p.get_vector_id()) neighbouring_points.push_back(triangles[k].get_B());
						if (triangles[k].get_C().get_vector_id() != p.get_vector_id()) neighbouring_points.push_back(triangles[k].get_C());
					}
				}
			}*/
			//break;
		}
		if (triangles[i].get_C().get_vector_id() == p.get_vector_id())
		{
			k = i;
			if (triangles[k].get_A().get_vector_id() != p.get_vector_id()) neighbouring_points.push_back(triangles[k].get_A());
			if (triangles[k].get_B().get_vector_id() != p.get_vector_id()) neighbouring_points.push_back(triangles[k].get_B());
			if (triangles[k].get_C().get_vector_id() != p.get_vector_id()) neighbouring_points.push_back(triangles[k].get_C());
			/*for (j = 0; j < number_triangles; j++)
			{
				if (triangle_indicators[k][j] == 1 && j != k)
				{
					if (triangles[j].get_A().get_vector_id() == p.get_vector_id() || triangles[j].get_B().get_vector_id() == p.get_vector_id() ||
						triangles[j].get_C().get_vector_id() == p.get_vector_id())
					{
						if (triangles[k].get_A().get_vector_id() != p.get_vector_id()) neighbouring_points.push_back(triangles[k].get_A());
						if (triangles[k].get_B().get_vector_id() != p.get_vector_id()) neighbouring_points.push_back(triangles[k].get_B());
						if (triangles[k].get_C().get_vector_id() != p.get_vector_id()) neighbouring_points.push_back(triangles[k].get_C());
					}
				}
			}*/
			//break;
		}
	}
	for (i = 0; i < neighbouring_points.size(); i++)
	{
		for (j = i + 1; j < neighbouring_points.size(); j++)
		{
			if (neighbouring_points[i].get_vector_id() == neighbouring_points[j].get_vector_id())
			{
				neighbouring_points.erase(neighbouring_points.begin() + j);
//				for (k = j; k < neighbouring_points.size()-1; k++) neighbouring_points[k] = neighbouring_points[k + 1];
			}
		}
	}
	if (neighbouring_points.size() != 0)
	{
		Vector a;
		for (i = 0; i < neighbouring_points.size() - 1; i++)
		{
			for (j = 0; j < neighbouring_points.size() - 1 - i; j++)
			{
				if ((neighbouring_points[j] - p).length() > (neighbouring_points[j + 1] - p).length())
				{
					a = neighbouring_points[j];
					neighbouring_points[j] = neighbouring_points[j + 1];
					neighbouring_points[j + 1] = a;
				}
			}
		}
		while (neighbouring_points.size() > 3) neighbouring_points.pop_back();
	}
	return neighbouring_points;
}

void Delaunay_triangulation::print_Delaunay_triangulation()
{
	ofstream f("C://Users//huawei//source//repos//Cluster Analysis//Cluster Analysis//Visualization//Function interpolation//Delaunay triangulation.txt"), 
		g("C://Users//huawei//source//repos//Cluster Analysis//Cluster Analysis//Visualization//Function interpolation//Delaunay triangulation.plt");
	g << "set size square\n" << "plot 'Delaunay triangulation.txt' with linespoints\n";
	for (int i = 0; i < number_triangles; i++)
	{
		triangles[i].print_triangle(f);
		f << "\n\n";
	}
	f.close();
	g.close();
}

void Delaunay_triangulation::print(int n)
{

}

void Delaunay_triangulation::print_gif(int n)
{

}