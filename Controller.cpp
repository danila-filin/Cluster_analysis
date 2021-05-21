#include "Controller.h"

Controller::Controller() { analysis_state = false; }

Controller::Controller(const Controller& c) { analysis_state = c.analysis_state; field = c.field; }

const Controller& Controller::operator=(const Controller& c)
{
    analysis_state = c.analysis_state;
    field = c.field;
    return *this;
}

void Controller::add_cloud_in_field(Cloud c) { field.add_cloud_in_field(c); }

void Controller::delete_cloud_from_field(int id) { field.delete_cloud_from_field(id); }

void Controller::print_field() { field.print_field(); }

bool Controller::get_analysis_state() { return analysis_state; }

void Controller::add_cloud_from_field_in_buffer(int id) { field.add_cloud_from_field_in_buffer(id); }

void Controller::add_all_clouds_from_field_in_buffer() { field.add_all_clouds_from_field_in_buffer(); }

void Controller::upload_cloud_from_buffer_in_field(int n) { field.upload_cloud_from_buffer_in_field(n); }

void Controller::upload_all_clouds_from_buffer_in_field() { field.upload_all_clouds_from_buffer_in_field(); }

void Controller::shift_cloud_in_buffer(int n, Vector v) { field.shift_cloud_in_buffer(n, v); }

void Controller::shift_all_clouds_in_buffer(Vector v) { field.shift_all_clouds_in_buffer(v); }

void Controller::turn_cloud_in_bufffer(int n, double phi) { field.turn_cloud_in_bufffer(n, phi); }

void Controller::turn_all_clouds_in_bufffer(double phi) { field.turn_all_clouds_in_bufffer(phi); }

void Controller::compression_cloud_in_buffer(int n, double lambda) { field.compression_cloud_in_buffer(n, lambda); }

void Controller::compression_all_clouds_in_buffer(double lambda) { field.compression_all_clouds_in_buffer(lambda); }

void Controller::creat_field_histogram(int number_of_columns) { field.creat_field_histogram(number_of_columns); }

void Controller::creat_cloud_histogram(int id, int number_of_colunms) { field.creat_cloud_histogram(id, number_of_colunms); }

void Controller::wave(double delta) { analysis_state = true; field.wave(delta); }

void Controller::dbscan(double delta, int k) { analysis_state = true; field.dbscan(delta, k); }

void Controller::k_m(int k) { analysis_state = true; field.k_m(k); }

void Controller::em(int k) { analysis_state = true; field.em(k); }

void Controller::tree() { analysis_state = true; field.tree(); }

void Controller::hierarchy() { analysis_state = true; field.hierarchy(); }

void Controller::function_interpolation(Vector p) { field.function_interpolation(p); }