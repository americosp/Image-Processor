#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Header
{
	char idLength;
	char colorMapType;
	char dataTypeCode;
	short colorMapOrigin;
	short colorMapLength;
	char colorMapDepth;
	short xOrigin;
	short yOrigin;
	short width;
	short height;
	char bitsPerPixel;
	char imageDescriptor;
};
Header headerObject;
ifstream inFile("car.TGA", ios_base::binary);
struct Pixel {};
struct ImageFile {};
Header readHeader(ifstream &file)
{
	file.read(&headerObject.idLength, sizeof(&headerObject.idLength));
	cout << headerObject.idLength;
}
Pixel readPixel(ifstream &file){}
ImageFile AddImage(string name){}

