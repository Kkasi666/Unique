#ifndef UNIQUE_UCM_PROLOADER_H_
#define UNIQUE_UCM_PROLOADER_H_

#include <fstream>
#include <string>
#include "def.h"

class ProLoader {
private:
	std::string workDir;
	std::string buffer;
	usint maxLen;
	usint len;
public:
	ProLoader(std::string workDir, usint maxLen);
	void initFile(std::string fileName);
	std::string getBuffer() const;
	~ProLoader();
};

#endif // UNIQUE_UCM_PROLOADER_H_