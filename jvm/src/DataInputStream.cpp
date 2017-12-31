#include "../include/DataInputStream.h"



DataInputStream::DataInputStream(std::istream &is):is(is)
{
	
}

uint8_t DataInputStream::readU1() {
	return (uint8_t)is.get();
};
uint16_t DataInputStream::readU2() {
	uint8_t byte1 = (uint8_t)is.get();
	uint8_t byte2 = (uint8_t)is.get();
	uint16_t ff = 0xFF;
	uint16_t ret = (uint16_t)(((byte1 & ff) << 8) + (byte2 & ff));
	return ret;
};


uint32_t DataInputStream::readU4() {
	uint8_t byte1 = (uint8_t)is.get();
	uint8_t byte2 = (uint8_t)is.get();
	uint8_t byte3 = (uint8_t)is.get();
	uint8_t byte4 = (uint8_t)is.get();
	uint32_t ff = 0xFF;
	return ((byte1 & ff) << 24) + ((byte2 & ff) << 16) + ((byte3 & ff) << 8) + (byte4 & ff);
};

bool DataInputStream::eof() {
	return is.eof();
};

DataInputStream::~DataInputStream()
{
}
