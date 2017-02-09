//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Bicubic B-Spline Assessment
// Bitmap.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <fstream>
#pragma hdrstop
#include "Bitmap.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// constructor
Bitmap::Bitmap(int sizeX /*= 0*/, int sizeY /*= 0*/) {
	_filename = "";
	strcpy(_type, "BM");
	_fileSize = BF_SIZE_HEADER + BI_SIZE_HEADER + sizeX * sizeY * COMPONENTS;
	_reserved1 = 0;
	_reserved2 = 0;
	_offBits = BF_SIZE_HEADER + BI_SIZE_HEADER;
	_headerSize = BI_SIZE_HEADER;
	_width = sizeX;
	_height = sizeY;
	_planes = 1;
	_bitCount = 24;
	_compression = 0;
	_imageSize = sizeX * sizeY * COMPONENTS;
	_xPelsPerMeter = 0;
	_yPelsPerMeter = 0;
	_clrUsed = 0;
	_clrImportant = 0;
	_header = new char[_offBits];
	_image = new char[_imageSize];
}

//------------------------------------------------------------------------------
// destructor
Bitmap::~Bitmap() {
	delete [] _header;
	delete [] _image;
}

//------------------------------------------------------------------------------
// read the bitmap
void Bitmap::read(char* filename) {
	_filename = filename;
    ifstream file(_filename, ios::in | ios::binary);
	// open input file
	if (!file.good())	{
		cout << "Error opening file - " << _filename << "\n";
		return;
	}
	// read input file
	int i;
	for (i = 0; i < _offBits; i++)	{
		file.get(_header[i]);
	}
	decodeHeader();
	size(_width, _height);
	// each line should be padded to an even number of bytes
	for (i = 0; i < _imageSize; i += COMPONENTS) {
    	for (int j = COMPONENTS - 1; j >= 0; j--) {
		    file.get(_image[i + j]);
        }
	}
}

//------------------------------------------------------------------------------
// set the image size
void Bitmap::size(int sizeX, int sizeY) {
	delete [] _image;
	_fileSize = BF_SIZE_HEADER + BI_SIZE_HEADER + sizeX * sizeY * COMPONENTS;
	_width = sizeX;
	_height = sizeY;
	_imageSize = sizeX * sizeY * COMPONENTS;
	_image = new char[_imageSize];
}

//------------------------------------------------------------------------------
// decode the header
void Bitmap::decodeHeader() {
	_index = 0;
	decodeHeader(_type);
	decodeHeader(_fileSize);
	decodeHeader(_reserved1);
	decodeHeader(_reserved2);
	decodeHeader(_offBits);
	decodeHeader(_headerSize);
	decodeHeader(_width);
	decodeHeader(_height);
	decodeHeader(_planes);
	decodeHeader(_bitCount);
	decodeHeader(_compression);
	decodeHeader(_imageSize);
	decodeHeader(_xPelsPerMeter);
	decodeHeader(_yPelsPerMeter);
	decodeHeader(_clrUsed);
	decodeHeader(_clrImportant);
}

//------------------------------------------------------------------------------
// decode char array to the header
void Bitmap::decodeHeader(char *c) {
	while (*c) {
		*c++ = _header[_index++];
	}
}

//------------------------------------------------------------------------------
// decode unsigned short int from the header
void Bitmap::decodeHeader(unsigned short int &c) {
	c = (unsigned short int)_header[_index++];
	c |= (unsigned short int)_header[_index++] << 8;
}

//------------------------------------------------------------------------------
// decode unsigned long int from the header
void Bitmap::decodeHeader(unsigned long int &c) {
	c = (unsigned long int)_header[_index++];
	c |= (unsigned long int)_header[_index++] << 8;
	c |= (unsigned long int)_header[_index++] << 16;
	c |= (unsigned long int)_header[_index++] << 24;
}

//------------------------------------------------------------------------------
