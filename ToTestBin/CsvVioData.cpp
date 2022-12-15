#include "iostream"
#include "sstream"
#include "vector"

#include "CsvVioData.hpp"

using namespace std;

CsvVioData::CsvVioData()
{
}

CsvVioData::~CsvVioData()
{
}

int CsvVioData::OpenFile()
{
	fs.open(file.data());
	opened = fs.is_open();
	if (!opened)
	{
		cout << "VIO CSV数据文件打开失败" << endl;
		return 1;
	}
	getline(fs, line);
	return 0;
}

int CsvVioData::CloseFile()
{
	fs.close();
	return 0;
}

int CsvVioData::GetData()
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
		p = strtok(NULL, split);
	}

	static int firstFlag = 1;
	if (!firstFlag)
	{
		for (int i = CSV_VIO_LIST_N - 1; i >= 1; i--)
		{
			time[i] = time[i - 1];
			quality[i] = quality[i - 1];
			x[i] = x[i - 1];;
			y[i] = y[i - 1];
			z[i] = z[i - 1];
			q0[i] = q0[i - 1];
			q1[i] = q1[i - 1];
			q2[i] = q2[i - 1];
			q3[i] = q3[i - 1];
		}
	}

	if (dd.size() == 9)
	{
		int week;
		double sec;
		gtime_t t;
		t.time = floor(dd[0]);
		t.sec = dd[0] - t.time;
		sec = tool.time2gpst(t, &week);
		time[0] = sec;
		quality[0] = dd[1];
		x[0] = dd[2];
		y[0] = dd[3];
		z[0] = dd[4];
		q0[0] = dd[5];
		q1[0] = dd[6];
		q2[0] = dd[7];
		q3[0] = dd[8];

		update = true;
	}

	if (update && firstFlag)
	{
		for (int i = 1; i < CSV_VIO_LIST_N; i++)
		{
			time[i] = time[0] - 0.1;
			quality[i] = quality[0];
			x[i] = x[0];;
			y[i] = y[0];
			z[i] = z[0];
			q0[i] = q0[0];
			q1[i] = q1[0];
			q2[i] = q2[0];
			q3[i] = q3[0];
		}
		firstFlag = 0;
	}

	return 0;
}