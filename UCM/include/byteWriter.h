#ifndef UNIQUE_UCM_BYTEWRITER_H_
#define UNIQUE_UCM_BYTEWRITER_H_

#include "def.h"
#include <vector>
#include <string>

class ByteWriter
{
private:
	std::string workDir;
	std::string fileName;
	std::vector<byte> code;
public:
	ByteWriter();
	ByteWriter(std::string workDir, std::string fileName);
	~ByteWriter();

	void setWorkDir(std::string workDir);
	void setCode(std::vector<byte> code);
	void writing();
};

#endif // UNIQUE_UCM_BYTEWRITER_H_