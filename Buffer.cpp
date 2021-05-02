#include "Buffer.h"

Buffer::Buffer() { number_clouds_in_buffer = 0; }

Buffer::Buffer(const Buffer& b)
{
    number_clouds_in_buffer = b.number_clouds_in_buffer;
    clouds_in_buffer = b.clouds_in_buffer;
}

const Buffer& Buffer::operator=(const Buffer& b)
{
    number_clouds_in_buffer = b.number_clouds_in_buffer;
    clouds_in_buffer = b.clouds_in_buffer;
    return *this;
}

void Buffer::add_cloud_in_buffer(Cloud c)
{
    number_clouds_in_buffer++;
    clouds_in_buffer.push_back(c);
}

Cloud Buffer::upload_cloud_from_buffer(int n)
{
    Cloud c = clouds_in_buffer[n];
    clouds_in_buffer.erase(clouds_in_buffer.begin() + n);
    return c;
}

int Buffer::get_number_clouds_in_buffer() { return number_clouds_in_buffer; }

void Buffer::shift_cloud_in_buffer(int n, Vector v) { clouds_in_buffer[n].shift_cloud(v); }

void Buffer::shift_all_clouds_in_buffer(Vector v)
{
    for (int i = 0; i < number_clouds_in_buffer; i++) clouds_in_buffer[i].shift_cloud(v);
}

void Buffer::turn_cloud_in_buffer(int n, double phi) { clouds_in_buffer[n].turn_cloud(phi); }

void Buffer::turn_all_clouds_in_buffer(double phi)
{
    for (int i = 0; i < number_clouds_in_buffer; i++) clouds_in_buffer[i].turn_cloud(phi);
}

void Buffer::compression_cloud_in_buffer(int n, double lambda) { clouds_in_buffer[n].compression_cloud(lambda); }

void Buffer::compression_all_clouds_in_buffer(double lambda)
{
    for (int i = 0; i < number_clouds_in_buffer; i++) clouds_in_buffer[i].compression_cloud(lambda);
}