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
* IMU����LOG��ȡ����
* GNSS DMR��txt��ȡ����
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

	NovatelImuData				imuN;			//NovatelЭ��IMU����
	NovatelGnssData				gnssN;			//NovatelЭ��GNSS����
	NovatelDmiData				dmiN;			//NovatelЭ��DMI����

	TxtGnssData					gnssT;			//txt�ļ�GNSS����
	TxtDmiData					dmiT;			//txt�ļ�DMI����

	CsvLioData					lioC;			//LIO�ļ�CSV����
	CsvVioData					vioC;			//VIO�ļ�CSV����

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

