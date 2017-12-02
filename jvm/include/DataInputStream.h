#ifndef DATAINPUTSTREAM_H
#define DATAINPUTSTREAM_H

#include <iostream>
#include <cstdint>

class DataInputStream
{
private:
	std::istream &is;
public:
	DataInputStream(std::istream &);
	uint8_t readU1();
	uint16_t readU2();
	uint32_t readU4();
	bool eof();
	~DataInputStream();
};

#endif // !DATAINPUTSTREAM_H