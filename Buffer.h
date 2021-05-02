#pragma once
#include "Cloud.h"

class Buffer
{
private:
    int number_clouds_in_buffer;
    vector <Cloud> clouds_in_buffer;
public:
    //конструкторы копирования и деструкторы
    Buffer();
    Buffer(const Buffer& b);
    ~Buffer() = default;

    const Buffer& operator=(const Buffer& b);//операция присванивания

    //функции, связанные с атрибутами данного класса
    void add_cloud_in_buffer(Cloud c);
    Cloud upload_cloud_from_buffer(int n);
    int get_number_clouds_in_buffer();

    //преобразования облаков
    void shift_cloud_in_buffer(int n, Vector v);
    void shift_all_clouds_in_buffer(Vector v);
    void turn_cloud_in_buffer(int n, double phi);
    void turn_all_clouds_in_buffer(double phi);
    void compression_cloud_in_buffer(int n, double lambda);
    void compression_all_clouds_in_buffer(double lambda);
};

