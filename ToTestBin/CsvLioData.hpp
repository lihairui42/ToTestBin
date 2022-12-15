#pragma once

#include "iostream"
#include "fstream"
#include "Tools.hpp"

#define		CSV_LIO_LIST_N							2

using	namespace  std;

class CsvLioData
{
public:
	friend	class		Tools;

	string				file;
	bool				update;
	string				line;

	Tools				tool;

	double				time[CSV_LIO_LIST_N];
	double				quality[CSV_LIO_LIST_N];
	double				x[CSV_LIO_LIST_N];
	double				y[CSV_LIO_LIST_N];
	double				z[CSV_LIO_LIST_N];
	double				q0[CSV_LIO_LIST_N];
	double				q1[CSV_LIO_LIST_N];
	double				q2[CSV_LIO_LIST_N];
	double				q3[CSV_LIO_LIST_N];

	int OpenFile();
	int CloseFile();
	int GetData();

	CsvLioData();
	~CsvLioData();

private:
	ifstream			fs;
	bool				opened;
};

