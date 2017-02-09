//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Bicubic B-Spline Assessment
// Bitmap.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Bitmap_h
#define Bitmap_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // constants

    const int COMPONENTS = 3;
    const int BF_SIZE_HEADER = 14;
    const int BI_SIZE_HEADER = 40;

    //------------------------------------------------------------------------------
    // class definition

    class Bitmap {

    public:

	    Bitmap(int sizeX = 0, int sizeY = 0);
	    ~Bitmap();
	    void read(char *filename);
	    void size(int sizeX, int sizeY);
        int width() {
            return _width;
        }
        int height() {
            return _height;
        }
        char *image() {
            return _image;
        }

    private:

        Bitmap(const Bitmap &bitmap) {}
        Bitmap &operator=(const Bitmap &bitmap) {}
	    void decodeHeader();
	    void decodeHeader(char *c);
	    void decodeHeader(unsigned short int &c);
	    void decodeHeader(unsigned long int &c);

	    char *_filename;
	    char _type[3];
	    unsigned long int _fileSize;
	    unsigned short int _reserved1;
	    unsigned short int _reserved2;
	    unsigned long int _offBits;
	    unsigned long int _headerSize;
	    unsigned long int _width;
	    unsigned long int _height;
	    unsigned short int _planes;
	    unsigned short int _bitCount;
	    unsigned long int _compression;
	    unsigned long int _imageSize;
	    unsigned long int _xPelsPerMeter;
	    unsigned long int _yPelsPerMeter;
	    unsigned long int _clrUsed;
	    unsigned long int _clrImportant;
	    unsigned int _index;
	    char *_header;
	    char *_image;
    };

} // ComputerGraphics

#endif // Bitmap_h

//------------------------------------------------------------------------------
