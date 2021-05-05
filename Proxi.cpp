#include "Proxi.h"

Proxi::Proxi() {}

Proxi::Proxi(const Proxi& p) { admin = p.admin; }

const Proxi& Proxi::operator=(const Proxi& p) { admin = p.admin; return *this; }

int Proxi::read_from_client(int fd, char* buf)
{
	int  nbytes;

	nbytes = recv(fd, buf, BUFLEN, 0);
	if (nbytes < 0) 
	{
		perror("Server: read failure");
		return -1;
	}
	else if (nbytes == 0) 
	{
		return -1;
	}
	else 
	{
		cout << "Server got message: " << buf << endl;
		admin.read_command(buf);
		return 0;
	}
}

void Proxi::write_to_client(int fd, char* buf)
{
	int  nbytes;
	unsigned char* s;

	for (s = (unsigned char*)buf; *s; s++) *s = toupper(*s);
	nbytes = send(fd, buf, strlen(buf) + 1, 0);
	cout << "Write back: " << buf << endl;
	if (nbytes < 0) {
		perror("Server: write failure");
	}
}

void Proxi::open_log() { admin.open_log(); }