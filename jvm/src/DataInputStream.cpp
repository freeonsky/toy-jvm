#include "../include/DataInputStream.h"



DataInputStream::DataInputStream(std::istream &is):is(is)
{
	
}

uint8_t DataInputStream::readU1() {
	return is.get();
};
uint16_t DataInputStream::readU2() {
	uint8_t byte1 = is.get();
	uint8_t byte2 = is.get();
	uint16_t ff = 0xFF;
	return ((byte1 & ff) << 8) + (byte2 & ff);
};


uint32_t DataInputStream::readU4() {
	uint8_t byte1 = is.get();
	uint8_t byte2 = is.get();
	uint8_t byte3 = is.get();
	uint8_t byte4 = is.get();
	uint32_t ff = 0xFF;
	return ((byte1 & ff) << 24) + ((byte2 & ff) << 16) + ((byte3 & ff) << 8) + (byte4 & ff);
};

bool DataInputStream::eof() {
	return is.eof();
};

DataInputStream::~DataInputStream()
{
}
