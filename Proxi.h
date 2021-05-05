#pragma once
#pragma warning(suppress : 4996)
#pragma comment(lib, "Ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "Administrator.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define PORT    5555
#define BUFLEN  512

class Proxi
{
private:
	Administrator admin;
public:
	Proxi();
	Proxi(const Proxi& p);
	~Proxi() = default;
	const Proxi& operator=(const Proxi& p);
	int read_from_client(int fd, char* buf);
	void write_to_client(int fd, char* buf);
	void open_log();
};