#include "fileAPI.h"
#include <direct.h>

std::string getWorkPath() {
	char *buffer = new char[512];
	std::string workPath;
	buffer = getcwd(nullptr, sizeof(512));
	workPath = buffer;
	delete[] buffer;
	return workPath;
}