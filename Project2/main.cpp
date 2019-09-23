#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <istream>
#include <iomanip>

using namespace std;
// ASHFUDGBDHASDSHFIEWHRFOIHEWFUEIDGFDOSBCOHIDSBAOASDNOFDS
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
	long pixelCount;

};
struct Pixel 
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
	
	Pixel()
	{
		blue = 0;
		green = 0;
		red = 0;
	}

};

Header readHeader(std::ifstream &file)
{
	Header headerObject;
	if (file.is_open())
	{
		file.read(&headerObject.idLength, 1);
		file.read(&headerObject.colorMapType, 1);
		file.read(&headerObject.dataTypeCode, 1);
		file.read((char *)&headerObject.colorMapOrigin, 2);
		file.read((char *)&headerObject.colorMapLength, 2);
		file.read(&headerObject.colorMapDepth, 1);
		file.read((char *)&headerObject.xOrigin, 2);
		file.read((char *)&headerObject.yOrigin, 2);
		file.read((char *)&headerObject.width, 2);
		file.read((char *)&headerObject.height, 2);
		file.read(&headerObject.bitsPerPixel, 1);
		file.read(&headerObject.imageDescriptor, 1);
		headerObject.pixelCount = headerObject.height * headerObject.width;
	}
	return headerObject;
}
vector<Pixel> readPixelVector(std::ifstream &file , long numberOfPixels)
{
	int pixelss = (int) numberOfPixels;
	vector<Pixel> pixVector;
	pixVector.resize(pixelss);

	long pixelAmount = numberOfPixels;
	
	if (file.is_open())
	{
		file.seekg(18, ios::beg);
		for (int i = 0; (long)i < pixelAmount; ++i)
		{
			Pixel newPixel;
			file.read((char*)&newPixel.blue, 1);
			file.read((char*)&newPixel.green, 1);
			file.read((char*)&newPixel.red, 1);
			pixVector[i] = (newPixel);
		}
		file.close();
	}
	return pixVector;
}





bool Test(string outputFile, string exampleFile, float testNumber)
{
	bool pixelsMatch = true;
	bool headerMatches = true;

	//file 1
	string path1 = "output//";
	path1.append(outputFile);
	std::ifstream file1(path1, std::ios_base::binary | std::ios_base::in);
	Header headerOutput = readHeader(file1);
	vector<Pixel> pixelsOutput = readPixelVector(file1, headerOutput.pixelCount);

	//file 2
	string path2 = "examples//";
	path2.append(exampleFile);
	std::ifstream file2(path2, std::ios_base::binary | std::ios_base::in);
	Header headerExample = readHeader(file2);
	vector<Pixel> pixelsExample = readPixelVector(file2, headerExample.pixelCount);

	if (headerOutput.idLength != headerExample.idLength){
		headerMatches = false;
		cout << "Failed: Incorrect ID Length" << endl;
	}else if (headerOutput.colorMapType != headerExample.colorMapType) {
		headerMatches = false;
		cout << "Failed: Incorrect Color Map Type" << endl;
	}else if (headerOutput.dataTypeCode != headerExample.dataTypeCode) {
		headerMatches = false;
		cout << "Failed: Incorrect Data Type Code" << endl;
	}else if (headerOutput.colorMapOrigin != headerExample.colorMapOrigin) {
		headerMatches = false;
		cout << "Failed: Incorrect Color Map Origin" << endl;
	}else if (headerOutput.colorMapLength != headerExample.colorMapLength) {
		headerMatches = false;
		cout << "Failed: Incorrect Color Map Length" << endl;
	}else if (headerOutput.colorMapDepth != headerExample.colorMapDepth) {
		headerMatches = false;
		cout << "Failed: Incorrect Color Map Depth" << endl;
	}else if (headerOutput.xOrigin != headerExample.xOrigin) {
		headerMatches = false;
		cout << "Failed: Incorrect X Origin" << endl;
	}else if (headerOutput.yOrigin != headerExample.yOrigin) {
		headerMatches = false;
		cout << "Failed: Incorrect Y Origin" << endl;
	}else if (headerOutput.width != headerExample.width) {
		headerMatches = false;
		cout << "Failed: Incorrect Width" << endl;
	}else if (headerOutput.height != headerExample.height) {
		headerMatches = false;
		cout << "Failed: Incorrect Height" << endl;
	}else if (headerOutput.bitsPerPixel != headerExample.bitsPerPixel) {
		headerMatches = false;
		cout << "Failed: Incorrect Bits Per Pixel" << endl;
	}else if (headerOutput.imageDescriptor != headerExample.imageDescriptor) {
		headerMatches = false;
		cout << "Failed: Incorrect Image Descriptor" << endl;
	}

	for (unsigned int i = 0; i < pixelsOutput.size(); ++i)
	{
		if (pixelsOutput[i].blue != pixelsExample[i].blue || pixelsOutput[i].green != pixelsExample[i].green || pixelsOutput[i].red != pixelsExample[i].red)
		{
			pixelsMatch = false;
			break;
		}
	}
	if (headerMatches && pixelsMatch)
	{
		cout << "Test #" << testNumber << " Passed!" << endl;
		return true;
	}
	else if (headerMatches)
	{
		cout << "Only headers match! Test #" << testNumber << " Failed!" << endl;
		return false;
	}
	else if (pixelsMatch)
	{
		cout << "Only pixels match! Test #" << testNumber << " Failed!" << endl;
		return false;
	}
	else if (pixelsMatch)
	{
		cout << "Only headers match! Test #" << testNumber << " Failed!" << endl;
		return false;
	}
	else
	{
		cout << "Are you even comparing the same image?!? Test #" << testNumber << " Failed!" << endl;
		return false;
	}
}
void NewOutputFile(Header header, vector<Pixel> &pixels, string fileName)
{
	string path = "output//";
	path.append(fileName);
	
	ofstream outFile(path, ios_base::binary | ios_base::out);
	
	char idLength = header.idLength;
	char colorMapType = header.colorMapType;
	char dataTypeCode = header.dataTypeCode;
	short colorMapOrigin = header.colorMapOrigin;
	short colorMapLength = header.colorMapLength;
	char colorMapDepth = header.colorMapDepth;
	short xOrigin = header.xOrigin;
	short yOrigin = header.yOrigin;
	short width = header.width;
	short height = header.height;
	char bitsPerPixel = header.bitsPerPixel;
	char imageDescriptor = header.imageDescriptor;
	long pixelCount = header.pixelCount;

	if (outFile.is_open())
	{
		outFile.write(&idLength, 1);
		outFile.write(&colorMapType, 1);
		outFile.write(&dataTypeCode, 1);
		outFile.write((char *)&colorMapOrigin, 2);
		outFile.write((char *)&colorMapLength, 2);
		outFile.write(&colorMapDepth, 1);
		outFile.write((char *)&xOrigin, 2);
		outFile.write((char *)&yOrigin, 2);
		outFile.write((char *)&width, 2);
		outFile.write((char *)&height, 2);
		outFile.write(&bitsPerPixel, 1);
		outFile.write(&imageDescriptor, 1);

		for (int i = 0; (long)i < pixelCount; ++i)
		{
			outFile.write((char*)&pixels[i].blue, 1);
			outFile.write((char*)&pixels[i].green, 1);
			outFile.write((char*)&pixels[i].red, 1);
		}
		outFile.close();
	}


}

vector<Pixel> Flip180(vector<Pixel> &first)
{
	unsigned char r1, g1, b1;
	vector<Pixel> newPixels(first.size());

	for (unsigned int i = 0; i < first.size(); ++i)
	{
		Pixel newPixel;
		r1 = first[i].red;
		g1 = first[i].green;
		b1 = first[i].blue;

		newPixel.red = r1;
		newPixel.green = g1;
		newPixel.blue = b1;
		newPixels[first.size() - i - 1] = newPixel;
	}
	return newPixels;
}
vector<Pixel> CombineChannels(vector<Pixel> &red, vector<Pixel> &green, vector<Pixel> &blue)
{
	unsigned char r1, g1, b1;
	vector<Pixel> newPixels;

	for (unsigned int i = 0; i < red.size(); ++i)
	{
		Pixel newPixel;
		r1 = red[i].red;
		g1 = green[i].green;
		b1 = blue[i].blue;

		newPixel.red = r1;
		newPixel.green = g1;
		newPixel.blue = b1;
		newPixels.push_back(newPixel);
	}
	return newPixels;
}
vector<Pixel> ColorExtraction(vector<Pixel> &first, bool blue, bool green, bool red)
{
	unsigned char r1, g1, b1;
	vector<Pixel> newPixels;

	if (blue)
	{
		for (unsigned int i = 0; i < first.size(); ++i)
		{
			Pixel newPixel;
			b1 = first[i].blue;
			newPixel.red = b1;
			newPixel.green = b1;
			newPixel.blue = b1;
			newPixels.push_back(newPixel);
		}
	}
	if (green)
	{
		for (unsigned int i = 0; i < first.size(); ++i)
		{
			Pixel newPixel;
			g1 = first[i].green;
			newPixel.red = g1;
			newPixel.green = g1;
			newPixel.blue = g1;
			newPixels.push_back(newPixel);
		}
	}
	if (red)
	{
		for (unsigned int i = 0; i < first.size(); ++i)
		{
			Pixel newPixel;
			r1 = first[i].red;
			newPixel.red = r1;
			newPixel.green = r1;
			newPixel.blue = r1;
			newPixels.push_back(newPixel);
		}
	}
	return newPixels;
}
vector<Pixel> Red4Blue0(vector<Pixel> &first)
{
	unsigned char r1, g1, b1;
	unsigned char r2;
	vector<Pixel> newPixels;

	for (unsigned int i = 0; i < first.size(); ++i)
	{
		Pixel newPixel;
		r1 = first[i].red;
		g1 = first[i].green;
		b1 = 0;


		if ((r1 * 4) <= 255) {
			r2 = r1 * 4;
		}
		else {
			r2 = 255;
		}

		newPixel.red = r2;
		newPixel.green = g1;
		newPixel.blue = b1;
		newPixels.push_back(newPixel);
	}
	return newPixels;
}
vector<Pixel> Add200Green(vector<Pixel> &first)
{
	unsigned char r1, g1, b1;
	unsigned char g2;
	vector<Pixel> newPixels;

	for (unsigned int i = 0; i < first.size(); ++i)
	{
		Pixel newPixel;
		r1 = first[i].red;
		g1 = first[i].green;
		b1 = first[i].blue;


		if ((g1 + 200) <= 255) {
			g2 = g1 + 200;
		}
		else {
			g2 = 255;
		}

		newPixel.red = r1;
		newPixel.green = g2;
		newPixel.blue = b1;
		newPixels.push_back(newPixel);
	}
	return newPixels;
}
vector<Pixel> Overlay(vector<Pixel> &first, vector<Pixel> &second)
{
	float r1f, g1f, b1f, r2f, g2f, b2f;
	unsigned char r1, r2, g1, g2, b1, b2, r3, g3, b3;
	vector<Pixel> newPixels;

	for (unsigned int i = 0; i < first.size(); ++i)
	{
		Pixel newPixel;
		r1 = first[i].red;
		g1 = first[i].green;
		b1 = first[i].blue;
		r2 = second[i].red;
		g2 = second[i].green;
		b2 = second[i].blue;

		r1f = (float)r1 / 255.0f;
		g1f = (float)g1 / 255.0f;
		b1f = (float)b1 / 255.0f;
		r2f = (float)r2 / 255.0f;
		g2f = (float)g2 / 255.0f;
		b2f = (float)b2 / 255.0f;

		if (b2f <= 0.5f) {
			b3 = (unsigned char)(round((2*(b1f * b2f) * 255)));
		}else {
			b3 = (unsigned char)(round(255 * (1 - 2 * (1-b1f) * (1-b2f))));
		}if (g2f <= 0.5f) {
			g3 = (unsigned char)(round((2 * (g1f * g2f) * 255)));
		}
		else {
			g3 = (unsigned char)(round(255 * (1 - 2 * (1 - g1f) * (1 - g2f))));
		}if (r2f <= 0.5f) {
			r3 = (unsigned char)(round((2 * (r1f * r2f) * 255)));
		}
		else {
			r3 = (unsigned char)(round(255 * (1 - 2 * (1 - r1f) * (1 - r2f))));
		}
		newPixel.red = r3;
		newPixel.green = g3;
		newPixel.blue = b3;
		newPixels.push_back(newPixel);
	}
	return newPixels;
}
vector<Pixel> Screen(vector<Pixel> &first, vector<Pixel> &second)
{
	float r1f, g1f, b1f, r2f, g2f, b2f;
	unsigned char r1, r2, g1, g2, b1, b2;
	unsigned char r3, g3, b3;
	vector<Pixel> newPixels;

	for (unsigned int i = 0; i < first.size(); ++i)
	{
		Pixel newPixel;
		r1 = first[i].red;
		g1 = first[i].green;
		b1 = first[i].blue;
		r2 = second[i].red;
		g2 = second[i].green;
		b2 = second[i].blue;

		r1f = (float)r1 / 255.0f;
		g1f = (float)g1 / 255.0f;
		b1f = (float)b1 / 255.0f;
		r2f = (float)r2 / 255.0f;
		g2f = (float)g2 / 255.0f;
		b2f = (float)b2 / 255.0f;

		r3 = (unsigned char)(round(255 * (1 - (1 - r1f) * (1 - r2f))));
		g3 = (unsigned char)(round(255 * (1 - (1 - g1f) * (1 - g2f))));
		b3 = (unsigned char)(round(255 * (1 - (1 - b1f) * (1 - b2f))));

		newPixel.red = r3;
		newPixel.green = g3;
		newPixel.blue = b3;
		newPixels.push_back(newPixel);
	}
	return newPixels;
}
vector<Pixel> Subtract(vector<Pixel> &first, vector<Pixel> &second)
{
	unsigned char r1, r2, g1, g2, b1, b2;
	unsigned char r3, g3, b3;
	vector<Pixel> newPixels;

	for (unsigned int i = 0; i < first.size(); ++i)
	{
		Pixel newPixel;
		r1 = first[i].red;
		g1 = first[i].green;
		b1 = first[i].blue;
		r2 = second[i].red;
		g2 = second[i].green;
		b2 = second[i].blue;

		if ((int)r1 - (int)r2 >= 0) {
			r3 = r1 - r2;
		}
		else {
			r3 = 0;
		}if ((int)g1 - (int)g2 >= 0) {
			g3 = g1 - g2;
		}
		else {
			g3 = 0;
		}if ((int)b1 - (int)b2 >= 0) {
			b3 = b1 - b2;
		}
		else {
			b3 = 0;
		}
		newPixel.red = r3;
		newPixel.green = g3;
		newPixel.blue = b3;
		newPixels.push_back(newPixel);
	}
	return newPixels;
}
vector<Pixel> Multiply(vector<Pixel> &first, vector<Pixel> &second)
{
	float r1f, g1f, b1f, r2f, g2f, b2f;
	unsigned char r1, r2, g1, g2, b1, b2;
	unsigned char r3, g3, b3;
	vector<Pixel> newPixels;

	for (unsigned int i = 0; i < first.size(); ++i)
	{
		Pixel newPixel;
		r1 = first[i].red;
		g1 = first[i].green;
		b1 = first[i].blue;
		r2 = second[i].red;
		g2 = second[i].green;
		b2 = second[i].blue;

		r1f = (float)r1 / 255.0f;
		g1f = (float)g1 / 255.0f;
		b1f = (float)b1 / 255.0f;
		r2f = (float)r2 / 255.0f;
		g2f = (float)g2 / 255.0f;
		b2f = (float)b2 / 255.0f;

		r3 = (unsigned char)(round(((r1f * r2f) * 255)));
		g3 = (unsigned char)(round(((g1f * g2f) * 255)));
		b3 = (unsigned char)(round(((b1f * b2f) * 255)));

		newPixel.red = r3;
		newPixel.green = g3;
		newPixel.blue = b3;
		newPixels.push_back(newPixel);
	}
	return newPixels;
}


int main() 
{
	int count = 0;

	//task 1
	bool passed = false;
	std::ifstream layer1("input//layer1.tga", std::ios_base::binary | std::ios_base::in);
	Header layer1Header = readHeader(layer1);
	vector<Pixel> layer1Pixels = readPixelVector(layer1, layer1Header.pixelCount);
	std::ifstream pattern1("input//pattern1.tga", std::ios_base::binary | std::ios_base::in);
	Header pattern1Header = readHeader(pattern1);
	vector<Pixel> pattern1Pixels = readPixelVector(pattern1, pattern1Header.pixelCount);
	vector<Pixel> task1 = Multiply(layer1Pixels, pattern1Pixels);
	NewOutputFile(layer1Header, task1, "part1.tga");
	passed = Test("part1.tga", "EXAMPLE_part1.tga", 1);
	if (passed) { ++count; }
	//std::cout << "Done with 1. Count:" << count << std::endl;

	//task 2
	std::ifstream layer2("input//layer2.tga", std::ios_base::binary | std::ios_base::in);
	Header layer2Header = readHeader(layer2);
	vector<Pixel> layer2Pixels = readPixelVector(layer2, layer2Header.pixelCount);
	std::ifstream car("input//car.tga", std::ios_base::binary | std::ios_base::in);
	Header carHeader = readHeader(car);
	vector<Pixel> carPixels = readPixelVector(car, carHeader.pixelCount);
	vector<Pixel> task2 = Subtract(carPixels, layer2Pixels);
	NewOutputFile(layer2Header, task2, "part2.tga");
	passed = Test("part2.tga", "EXAMPLE_part2.tga", 2);
	if (passed) { ++count; }

	//task 3
	std::ifstream pattern2("input//pattern2.tga", std::ios_base::binary | std::ios_base::in);
	Header pattern2Header = readHeader(pattern2);
	vector<Pixel> pattern2Pixels = readPixelVector(pattern2, pattern2Header.pixelCount);
	std::ifstream text("input//text.tga", std::ios_base::binary | std::ios_base::in);
	Header textHeader = readHeader(text);
	vector<Pixel> textPixels = readPixelVector(text, textHeader.pixelCount);
	vector<Pixel> task3Temp = Multiply(layer1Pixels, pattern2Pixels);
	vector<Pixel> task3 = Screen(textPixels, task3Temp);
	NewOutputFile(pattern2Header, task3, "part3.tga");
	passed = Test("part3.tga", "EXAMPLE_part3.tga", 3);
	if (passed) { ++count; }

	//task 4
	std::ifstream circles("input//circles.tga", std::ios_base::binary | std::ios_base::in);
	Header circlesHeader = readHeader(circles);
	vector<Pixel> circlesPixels = readPixelVector(circles, circlesHeader.pixelCount);
	vector<Pixel> task4Temp = Multiply(layer2Pixels, circlesPixels);
	vector<Pixel> task4 = Subtract(task4Temp, pattern2Pixels);
	NewOutputFile(pattern2Header, task4, "part4.tga");
	passed = Test("part4.tga", "EXAMPLE_part4.tga", 4);
	if (passed) { ++count; }

	//task 5
	vector<Pixel> task5 = Overlay(layer1Pixels, pattern1Pixels);
	NewOutputFile(pattern1Header, task5, "part5.tga");
	passed = Test("part5.tga", "EXAMPLE_part5.tga", 5);
	if (passed) { ++count; }

	//task 6
	vector<Pixel> task6 = Add200Green(carPixels);
	NewOutputFile(carHeader, task6, "part6.tga");
	passed = Test("part6.tga", "EXAMPLE_part6.tga", 6);
	if (passed) { ++count; }

	//task 7
	vector<Pixel> task7 = Red4Blue0(carPixels);
	NewOutputFile(carHeader, task7, "part7.tga");
	passed = Test("part7.tga", "EXAMPLE_part7.tga", 7);
	if (passed) { ++count; }

	//task 8
	vector<Pixel> task8b = ColorExtraction(carPixels, true,false,false);
	vector<Pixel> task8g = ColorExtraction(carPixels, false, true, false);
	vector<Pixel> task8r = ColorExtraction(carPixels, false, false, true);
	NewOutputFile(carHeader, task8r, "part8_r.tga");
	NewOutputFile(carHeader, task8g, "part8_g.tga");
	NewOutputFile(carHeader, task8b, "part8_b.tga");
	passed = Test("part8_r.tga", "EXAMPLE_part8_r.tga", 8.1);
	if (passed) { ++count; }
	passed = Test("part8_g.tga", "EXAMPLE_part8_g.tga", 8.2);
	if (passed) { ++count; }
	passed = Test("part8_b.tga", "EXAMPLE_part8_b.tga", 8.3);
	if (passed) { ++count; }
	
	//task 9
	std::ifstream layer_red("input//layer_red.tga", std::ios_base::binary | std::ios_base::in);
	Header layer_redHeader = readHeader(layer_red);
	vector<Pixel> layer_redPixels = readPixelVector(layer_red, layer_redHeader.pixelCount);
	std::ifstream layer_green("input//layer_green.tga", std::ios_base::binary | std::ios_base::in);
	Header layer_greenHeader = readHeader(layer_green);
	vector<Pixel> layer_greenPixels = readPixelVector(layer_green, layer_greenHeader.pixelCount);
	std::ifstream layer_blue("input//layer_blue.tga", std::ios_base::binary | std::ios_base::in);
	Header layer_blueHeader = readHeader(layer_blue);
	vector<Pixel> layer_bluePixels = readPixelVector(layer_blue, layer_blueHeader.pixelCount);
	
	
	vector<Pixel> task9 = CombineChannels(layer_redPixels , layer_greenPixels, layer_bluePixels);
	NewOutputFile(layer_redHeader, task9, "part9.tga");
	passed = Test("part9.tga", "EXAMPLE_part9.tga", 9);
	if (passed) { ++count; }

	//task 10
	std::ifstream text2("input//text2.tga", std::ios_base::binary | std::ios_base::in);
	Header text2Header = readHeader(text2);
	vector<Pixel> text2Pixels = readPixelVector(text2, text2Header.pixelCount);

	vector<Pixel> task10 = Flip180(text2Pixels);
	NewOutputFile(text2Header, task10, "part10.tga");
	passed = Test("part10.tga", "EXAMPLE_part10.tga", 10);
	if (passed) { ++count; }
	cout << endl << count << "/12 tests passed!" << endl;

	//system("pause");
	return 0;
}

