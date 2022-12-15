#pragma once

#include "iostream"
#include "fstream"
#include "Tools.hpp"

#define		CSV_VIO_LIST_N							2

using	namespace  std;

class CsvVioData
{
public:
	friend	class		Tools;

	string				file;
	bool				update;
	string				line;

	Tools				tool;

	double				time[CSV_VIO_LIST_N];
	double				quality[CSV_VIO_LIST_N];
	double				x[CSV_VIO_LIST_N];
	double				y[CSV_VIO_LIST_N];
	double				z[CSV_VIO_LIST_N];
	double				q0[CSV_VIO_LIST_N];
	double				q1[CSV_VIO_LIST_N];
	double				q2[CSV_VIO_LIST_N];
	double				q3[CSV_VIO_LIST_N];

	int OpenFile();
	int CloseFile();
	int GetData();

	CsvVioData();
	~CsvVioData();

private:
	ifstream			fs;
	bool				opened;
};

