#include "iostream"
#include "sstream"
#include "vector"

#include "CsvLioData.hpp"

using namespace std;

CsvLioData::CsvLioData()
{
}

CsvLioData::~CsvLioData()
{
}

int CsvLioData::OpenFile()
{
	fs.open(file.data());
	opened = fs.is_open();
	if (!opened)
	{
		cout << "DMI txt数据文件打开失败" << endl;
		return 1;
	}
	getline(fs, line);
	return 0;
}

int CsvLioData::CloseFile()
{
	fs.close();
	return 0;
}

int CsvLioData::GetData()
{
	update = false;

	if (!opened)
		return 1;

	getline(fs, line);
	if (fs.eof())
		return 1;

	vector<double>  dd;
	char *s_input = (char *)line.c_str();
	const char *split = ",";
	char *p = strtok(s_input, split);
	istringstream devide(line);
	while (p != NULL)
	{
		dd.push_back(std::atof(p));
		p = strtok(NULL,  split);
	}

	if (dd.size() == 9)
	{
		int week = 604800;
		int N = dd[0] / week;
		time = dd[0] - week * N;
		quality = dd[1];
		pos[0] = dd[2];
		pos[1] = dd[3];
		pos[2] = dd[4];
		q0 = dd[5];
		q1 = dd[6];
		q2 = dd[7];
		q3 = dd[8];

		update = true;
	}

	return 0;
}