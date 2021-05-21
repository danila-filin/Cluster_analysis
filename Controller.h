#pragma once
#include "Field.h"

class Controller
{
private:
    Field field;
    bool analysis_state;
public:
    Controller();
    Controller(const Controller& c);
    ~Controller() = default;
    const Controller& operator=(const Controller& c);
    void add_cloud_in_field(Cloud c);
    void delete_cloud_from_field(int id);
    void print_field();
    bool get_analysis_state();
    void add_cloud_from_field_in_buffer(int id);
    void add_all_clouds_from_field_in_buffer();
    void upload_cloud_from_buffer_in_field(int n);
    void upload_all_clouds_from_buffer_in_field();
    void shift_cloud_in_buffer(int n, Vector v);
    void shift_all_clouds_in_buffer(Vector v);
    void turn_cloud_in_bufffer(int n, double phi);
    void turn_all_clouds_in_bufffer(double phi);
    void compression_cloud_in_buffer(int n, double lambda);
    void compression_all_clouds_in_buffer(double lambda);
    void creat_field_histogram(int number_of_columns);
    void creat_cloud_histogram(int id, int number_of_colunms);
    void wave(double delta);
    void dbscan(double delta, int k);
    void k_m(int k);
    void em(int k);
    void tree();
    void hierarchy();
    void function_interpolation(Vector p);
};

