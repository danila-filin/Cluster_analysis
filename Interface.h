#pragma once
#include "Controller.h"
#include <ctime>
#include <cstdio>
#include <io.h>

class Interface
{
private:
    Controller controller;
public:
    Interface();
    Interface(const Interface& i);
    ~Interface() = default;
    const Interface& operator=(const Interface& i);
    void reading_commands();
};

