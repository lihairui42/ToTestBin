#pragma once

#include "iostream"
#include "fstream"

using	namespace  std;

class CsvVioData
{
public:
	string				file;
	bool				update;
	string				line;

	double				time;
	double				quality;
	double				pos[3];
	double				q0;
	double				q1;
	double				q2;
	double				q3;

	int OpenFile();
	int CloseFile();
	int GetData();

	CsvVioData();
	~CsvVioData();

private:
	ifstream			fs;
	bool				opened;
};

