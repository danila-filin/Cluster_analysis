#pragma once
#include "Controller.h"

class Administrator
{
private: 
	Controller controller;
public:
	Administrator();
	Administrator(const Administrator& admin);
	~Administrator() = default;
	const Administrator& operator=(const Administrator& admin);
	void open_log();
	void read_command(char *command);
};

