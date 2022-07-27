#include "byteWriter.h"
#include <fstream>

ByteWriter::ByteWriter() {}

ByteWriter::ByteWriter(std::string workDir, std::string fileName)
	: workDir(workDir), fileName(fileName) {}

ByteWriter::~ByteWriter() {}

void ByteWriter::setWorkDir(std::string workDir) {
	this->workDir=workDir;
}

void ByteWriter::setCode(std::vector<byte> code) {
	this->code=code;
}

void ByteWriter::writing() {
	char *buffer = new char[code.size()];
	char head[] = {0x3C, 0x2B, 0x1C, 0x2E, 0x3C, 0x0E};
	for(int i=0; i<code.size(); i++) {
		buffer[i] = code.at(i);
	}

	std::ofstream outf(workDir+"/"+fileName,std::ios::out | std::ios::binary);
	outf.write(head,6);
	outf.write(buffer,code.size());
	outf.close();
	delete[] buffer;
}