#include "iostream"
#include "iomanip"
#include "ProcessNNN.hpp"
#include "ProcessNNT.hpp"
#include "ProcessNTN.hpp"
#include "ProcessNTT.hpp"
#include "Process.hpp"
#include "Tools.hpp"

using namespace std;

enum NT_Slect
{
	NNN = 1,
	NNT = 2,
	NTN = 3,
	NTT = 4,
	COM = 5,
	OTHER = 6,
};

/*
*funNNN
*/
int funNNN()
{
	string imuNovatelFile = "D:\\IE\\Group1\\data\\NMND22180012G_2022-08-15_09-51-21.LOG";
	string gnssNovatelFile = "D:\\IE\\Group1\\data\\NMND22180012G_2022-08-15_09-51-21.LOG";
	string dmiNovatelFile = "D:\\IE\\Group1\\data\\NMND22180012G_2022-08-15_09-51-21.LOG";
	string testBinFile = "D:\\IE\\Group1\\data\\NMND22180012G_2022-08-15_09-51-21.testbin.txt";

	//NNN
	//第1个N代表IMU使用Novatel的数据格式,若为T，代表txt文件
	//第2个N代表GNSS使用Novatel的数据格式,若为T，代表txt文件
	//第3个n代表DMI使用Novatel的数据格式,若为T，代表txt文件
	ProcessNNN NNN(imuNovatelFile, 1, gnssNovatelFile, 1, dmiNovatelFile, 1, testBinFile, 1);
	NNN.Process();

	return 0;
}

/*
*funNNT
*/
int funNNT()
{
	string imuNovatelFile = "D:\\IE\\Group1\\data\\NMND22180012G_2022-08-15_09-51-21.LOG";
	string gnssNovatelFile = "D:\\IE\\Group1\\data\\NMND22180012G_2022-08-15_09-51-21.LOG";
	string dmiNovatelFile = "D:\\IE\\Group1\\data\\NMND22180012G_2022-08-15_09-51-21.dmr.txt";
	string testBinFile = "D:\\IE\\Group1\\data\\NMND22180012G_2022-08-15_09-51-21.testbin.txt";

	ProcessNNT NNT(imuNovatelFile, 1, gnssNovatelFile, 1, dmiNovatelFile, 1, testBinFile, 1);
	NNT.Process();
	return 0;
}


/*
*funNTN
*/
int funNTN()
{
	string imuNovatelFile = "D:\\IE\\Group1\\data\\NMND22180012G_2022-08-15_09-51-21.LOG";
	string gnssTxtFile = "D:\\IE\\Group1\\data\\Group1-gnss.txt";
	string dmiTxtFile = "D:\\IE\\Group1\\data\\NMND22180012G_2022-08-15_09-51-21.LOG";
	string testBinFile = "D:\\IE\\Group1\\data\\NMND22180012G_2022-08-15_09-51-21.testbin.txt";

	ProcessNTN NTN(imuNovatelFile, 1,  gnssTxtFile, 1,  dmiTxtFile, 1,  testBinFile, 1);
	NTN.Process();
	return 0;
}

/*
*funNTT
*/
int funNTT()
{
	string imuNovatelFile = "D:\\IE\\Group1\\data\\NMND22180012G_2022-08-15_09-51-21.LOG";
	string gnssTxtFile = "D:\\IE\\Group1\\data\\Group1-gnss.txt";
	string dmiTxtFile = "D:\\IE\\Group1\\data\\NMND22180012G_2022-08-15_09-51-21.dmr.txt";
	string testBinFile = "D:\\IE\\Group1\\data\\NMND22180012G_2022-08-15_09-51-21.testbin.txt";

	ProcessNTT NTT(imuNovatelFile, 1, gnssTxtFile, 1, dmiTxtFile, 1, testBinFile, 1);
	NTT.Process();
	return 0;
}

int funCOM()
{
	//string imuNovatelFile = "D:\\IE\\Group1\\data\\NMND22180012G_2022-08-15_09-51-21.LOG";
	//string gnssTxtFile = "D:\\IE\\Group1\\data\\Group1-gnss.txt";
	//string dmiTxtFile = "D:\\IE\\Group1\\data\\NMND22180012G_2022-08-15_09-51-21.dmr.txt";
	//string testBinFile = "D:\\IE\\Group1\\data\\NMND22180012G_2022-08-15_09-51-21.testbin.txt";

	string imuNovatelFile = "D:\\IE\\Nav1020\\data\\2022_10_20_23_6_13_imu_data.dat.BIN";
	string gnssTxtFile = "D:\\IE\\Nav1020\\data\\2022_10_20_23_6_13_gps_data.dat";
	string dmiTxtFile = "D:\\IE\\Nav1020\\data\\2022_10_20_23_6_13_gps_data.dat";
	string testBinFile = "D:\\IE\\Nav1020\\data\\2022_10_20_23_6_13_gps_data.testbin.txt";
	string lioFile = "D:\\IE\\Nav1020\\lio_odom\\odom.csv";
	string vioFile = "D:\\IE\\Nav1020\\lio_odom\\odom.csv";

	Process COM(imuNovatelFile, Novatel, 1, 200,
				gnssTxtFile, Novatel, 1, 5,
				dmiTxtFile, Novatel, 1, 100,
				lioFile, CSV, 1, 10,
				vioFile, CSV, 1, 10,
				testBinFile, 1);
	COM.Deal();
	return 0;
}


int funOther()
{
	Tools tool;
	gtime_t t;
	int week = 0;
	double sec = 0;
	//double ep[6] = { 2021,12,21,8,27,56 };
	//t = tool.epoch2time(ep);
	//t = tool.gpst2time(2232, 371196);
	//sec = tool.time2gpst(t, &week);

	t.time = 1666250542;
	t.sec = 0.29894;
	sec = tool.time2gpst(t, &week);

	return 0;
}

int main()
{
	NT_Slect nt = COM;
	switch (nt)
	{
	case NNN:
		funNNN();
		break;

	case NNT:
		funNNT();
		break;

	case NTN:
		funNTN();
		break;

	case NTT:
		funNTT();
		break;

	case COM:
		funCOM();
		break;

	case OTHER:
		funOther();
		break;

	default:
		break;
	}

	cout << "Hello TestBin!!!" << endl;
	//std::cin.ignore();
	return 0;
}