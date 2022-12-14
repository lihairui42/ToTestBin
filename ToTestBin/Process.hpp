#pragma once

#include "iostream"
#include "fstream"

#include "NovatelImuData.hpp"
#include "NovatelGnssData.hpp"
#include "NovatelDmiData.hpp"
#include "TxtGnssData.hpp"
#include "TxtDmiData.hpp"
#include "CsvLioData.hpp"
#include "CsvVioData.hpp"
#include "TestBin.hpp"

using	namespace  std;

enum  DataFileType
{
	Novatel = 1,
	TXT = 2,
	CSV = 3,
};


/*
* IMU都从LOG读取数据
* GNSS DMR从txt读取数据
*/
class Process
{
public:
	friend class NovatelImuData;
	friend class NovatelGnssData;
	friend class NovatelDmiData;
	friend class TxtGnssData;
	friend class TxtDmiData;
	friend class CsvLioData;
	friend class CsvVioData;
	friend class TestBin;

	NovatelImuData				imuN;			//Novatel协议IMU数据
	NovatelGnssData				gnssN;			//Novatel协议GNSS数据
	NovatelDmiData				dmiN;			//Novatel协议DMI数据

	TxtGnssData					gnssT;			//txt文件GNSS数据
	TxtDmiData					dmiT;			//txt文件DMI数据

	CsvLioData					lioC;			//LIO文件CSV数据
	CsvVioData					vioC;			//VIO文件CSV数据

	TestBinData					testBin;

	int							imuEnable;
	int							gnssEnable;
	int							dmiEnable;
	int							lioEnable;
	int							vioEnable;
	int							outEnable;

	DataFileType				imuFileType;
	DataFileType				gnssFileType;
	DataFileType				dmiFileType;
	DataFileType				lioFileType;
	DataFileType				vioFileType;

	int							imuFreq;
	int							gnssFreq;
	int							dmiFreq;
	int							lioFreq;
	int							vioFreq;

	Process();
	Process( string _imuFile, DataFileType _imuFileType,int _imuEn, int _imuFreq,
			 string _gnssFile, DataFileType _gnssFileType, int _gnssEn, int _gnssFreq,
			 string _dmiFile, DataFileType _dmiFileType,  int _dmiEn, int _dmiFreq,
		     string _lioFile, DataFileType _lioFileType, int _lioEn, int _lioFreq,
			 string _vioFile, DataFileType _vioFileType, int _vioEn, int _vioFreq,
			 string _testBinFile, int _outEn);
	~Process();

	int Init();
	int OpenFile();
	int CloseFile();

	int GetIMU();
	int GetGNSS();
	int GetDMI();
	int GetLIO();
	int GetVIO();

	int TestBinIMU();
	int TestBinGNSS();
	int TestBinDMI();
	int TestBinLIO();
	int TestBinVIO();
	int TestBinOut();

	int Deal();

private:
	int imuFileEof;
	int gnssFileEof;
	int dmiFileEof;
	int lioFileEof;
	int vioFileEof;

	int imuNeedRead;
	int gnssNeedRead;
	int dmiNeedRead;
	int lioNeedRead;
	int vioNeedRead;

	double gnssSec;
	double dmiSec;
	double lioSec;
	double vioSec;
};

