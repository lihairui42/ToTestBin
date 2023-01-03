#include "iostream"
#include "iomanip"
#include "Process.hpp"


/*
*构造函数
*/
Process::Process()
{
	//初始化
	Init();
}

/*
*构造函数
*/
Process::Process(string _imuFile, DataFileType _imuFileType, int _imuEn, int _imuFreq,
				string _gnssFile, DataFileType _gnssFileType, int _gnssEn, int _gnssFreq,
				string _dmiFile, DataFileType _dmiFileType, int _dmiEn, int _dmiFreq,
				string _lioFile, DataFileType _lioFileType, int _lioEn, int _lioFreq,
				string _vioFile, DataFileType _vioFileType, int _vioEn, int _vioFreq,
				string _testBinFile, int _outEn)
{
	//IMU
	imuFileType = _imuFileType;
	imuEnable = _imuEn;
	imuFreq = _imuFreq;
	if (imuFileType == Novatel)
		imuN.file = _imuFile;

	//GNSS
	gnssFileType = _gnssFileType;
	gnssEnable = _gnssEn;
	gnssFreq = _gnssFreq;
	if (gnssFileType == Novatel)
		gnssN.file = _gnssFile;
	else if(gnssFileType == TXT)
		gnssT.file = _gnssFile;

	//DMI
	dmiFileType = _dmiFileType;
	dmiEnable = _dmiEn;
	dmiFreq = _dmiFreq;
	if (dmiFileType == Novatel)
		dmiN.file = _dmiFile;
	else if (dmiFileType == TXT)
		dmiT.file = _dmiFile;

	//LIO
	lioFileType = _lioFileType;
	lioEnable = _lioEn;
	lioFreq = _lioFreq;
	if (lioFileType == CSV)
		lioC.file = _lioFile;

	//VIO
	vioFileType = _vioFileType;
	vioEnable = _vioEn;
	vioFreq = _vioFreq;
	if (vioFileType == CSV)
		vioC.file = _vioFile;

	outEnable = _outEn;
	testBin.file = _testBinFile;

	//初始化
	Init();
}

/*
*析构函数
*/
Process::~Process()
{
}

/*
*打开需要的文件
*/
int Process::Init()
{
	imuFileEof = 0;
	gnssFileEof = 0;
	dmiFileEof = 0;
	lioFileEof = 0;
	vioFileEof = 0;

	imuNeedRead = 1;
	gnssNeedRead = 1;
	dmiNeedRead = 1;
	lioNeedRead = 1;
	vioNeedRead = 1;

	testBin.imuFreq = imuFreq;
	testBin.gnssFreq = gnssFreq;
	testBin.dmiFreq = dmiFreq;
	testBin.lioFreq = lioFreq;
	testBin.vioFreq = vioFreq;

	return 0;
}

/*
*打开需要的文件
*/
int Process::OpenFile()
{
	//IMU
	if (imuFileType == Novatel)
	{
		imuN.OpenFile();
		imuN.Check();
	}
		
	//GNSS
	if (gnssFileType == Novatel)
	{
		gnssN.OpenFile();
		gnssN.Check();
	}	
	else if (gnssFileType == TXT)
	{
		gnssT.OpenFile();
	}
		

	//DMI
	if (dmiFileType == Novatel)
	{
		dmiN.OpenFile();
		dmiN.Check();
	}
	else if (dmiFileType == TXT)
		dmiT.OpenFile();

	//LIO
	if (lioFileType == CSV)
		lioC.OpenFile();

	//VIO
	if (vioFileType == CSV)
		vioC.OpenFile();

	//TESTBIN
	testBin.OpenFile();
	return 0;
}

/*
*关闭文件
*/
int Process::CloseFile()
{
	//IMU
	if (imuFileType == Novatel)
		imuN.CloseFile();

	//GNSS
	if (gnssFileType == Novatel)
		gnssN.CloseFile();
	else if (gnssFileType == TXT)
		gnssT.CloseFile();

	//DMI
	if (dmiFileType == Novatel)
		dmiN.CloseFile();
	else if (dmiFileType == TXT)
		dmiT.CloseFile();

	//LIO
	if (lioFileType == CSV)
		lioC.CloseFile();

	//VIO
	if (vioFileType == CSV)
		vioC.CloseFile();

	//TESTBIN
	testBin.CloseFile();
	return 0;
}


/*获取IMU数据*/
int Process::GetIMU()
{
	imuN.imus.update = false;
	imuN.imusx.update = false;

	if (!imuEnable || !imuNeedRead)
		return 0;

	if (imuFileType == Novatel)
	{
		if (!imuFileEof && imuNeedRead)
		{
			imuFileEof = imuN.GetData();
			imuNeedRead = 0;
		}
	}
	return 0;
}

/*获取GNSS数据*/
int Process::GetGNSS()
{
	gnssN.update = false;
	gnssT.update = false;

	if (!gnssEnable || !gnssNeedRead || gnssFileEof)
		return 0;

	if (gnssFileType == Novatel)
	{
		gnssFileEof = gnssN.GetData();
		gnssNeedRead = 0;
	}
		
	else if (gnssFileType == TXT)
	{
		gnssFileEof = gnssT.GetData();
		gnssNeedRead = 0;
	}		
	return 0;
}

/*获取DMI数据*/
int Process::GetDMI()
{
	dmiN.update = false;
	dmiT.update = false;

	if (!dmiEnable || !dmiNeedRead || dmiFileEof)
		return 0;

	if (dmiFileType == Novatel)
	{
		dmiFileEof = dmiN.GetData();
		dmiNeedRead = 0;
	}

	else if (dmiFileType == TXT)
	{
		dmiFileEof = dmiT.GetData();
		dmiNeedRead = 0;
	}
	return 0;
}

/*获取LIO数据*/
int Process::GetLIO()
{
	lioC.update = false;

	if (!lioEnable || !lioNeedRead || lioFileEof)
		return 0;

	if (lioFileType == CSV)
	{
		lioFileEof = lioC.GetData();
		lioNeedRead = 0;
	}
	return 0;
}


/*获取VIO数据*/
int Process::GetVIO()
{
	vioC.update = false;

	if (!vioEnable || !vioNeedRead || vioFileEof)
		return 0;

	if(vioFileType == CSV)
	{
		vioFileEof = vioC.GetData();
		vioNeedRead = 0;
	}
	return 0;
}

/*TestBin融入IMU数据*/
int Process::TestBinIMU()
{
	testBin.imuUpdateCnt = 0;

	if (!imuEnable || imuFileEof)
		return 0;

	if (imuFileType == Novatel)
		testBin.GetNovatelImu(imuN);

	imuNeedRead = 1;

	return 0;
}

/*TestBin融入GNSS数据*/
int Process::TestBinGNSS()
{
	if (!gnssEnable || gnssFileEof)
		return 0;

	if (gnssFileType == Novatel)
		gnssSec = gnssN.bestPos.ms * 0.001;
	else if (gnssFileType == TXT)
		gnssSec = gnssT.sec;

	if (gnssSec <= testBin.sec1)
	{
		gnssNeedRead = 1;
		return 0;
	}

	if ((gnssSec <= testBin.sec0) && (gnssSec > testBin.sec1))
	{
		if (gnssFileType == Novatel)
			testBin.GetNovatelGnss(gnssN);
		else if (gnssFileType == TXT)
			testBin.GetTxtGnss(gnssT);

		//cout << fixed << setprecision(3) << testBin.sec0 << "   "
		//		<< setprecision(3) << gnssSec << "   "
		//		<< setprecision(3) << dmiSec << "   "
		//		<< setprecision(3) << lioSec << "   "
		//		<< setprecision(3) << vioSec <<endl;

		gnssNeedRead = 1;
	}

	return 0;
}

/*TestBin融入DMI数据*/
int Process::TestBinDMI()
{
	if (!dmiEnable || dmiFileEof)
		return 0;

	if (dmiFileType == Novatel)
		dmiSec = floor(dmiN.dmia.ms * 0.001 + 0.01);
	else if(dmiFileType == TXT)
		dmiSec = floor(dmiT.time[0] + 0.01);

	if (testBin.sec0 >= 116101.995)
		testBin.sec0 *= 1.0;

	if (dmiSec <= testBin.sec1)
	{
		dmiNeedRead = 1;
		return 0;
	}

	if (testBin.sec0 == dmiSec)
	{
		if (dmiFileType == Novatel)
			testBin.GetNovatelDmi(dmiN);
		else if(dmiFileType == TXT)
			testBin.GetTxtDmi(dmiT);
		/*cout << fixed << setprecision(3) << testBin.sec0 << "   " 
					<< setprecision(3) << gnssSec << "   "
					<< setprecision(3) << floor(dmiSec) << endl;*/

		dmiNeedRead = 1;
	}

	return 0;
}

/*TestBin融入LIO数据*/
int Process::TestBinLIO()
{
	if (!lioEnable || lioFileEof)
		return 0;

	if (lioFileType == CSV)
	{
		double	tmp1 = lioC.time[0] + 0.01;
		int		tmp2 = floor(tmp1 * lioFreq);
		double  tmp3 = 1.0 / lioFreq;
		lioSec = tmp2 * tmp3;
	}
		
	if (lioSec <= testBin.sec1)
	{
		lioNeedRead = 1;
		return 0;
	}

	if (testBin.sec0 == lioSec)
	{
		if (lioFileType == CSV)
			testBin.GetCsvLio(lioC);

		cout << fixed << setprecision(3) << testBin.sec0 << "   "
			<< setprecision(3) << gnssSec << "   "
			<< setprecision(3) << dmiSec << "   "
			<< setprecision(3) << lioSec << "   "
			<< setprecision(3) << vioSec << endl;

		lioNeedRead = 1;
	}

	return 0;
}

/*TestBin融入VIO数据*/
int Process::TestBinVIO()
{
	if (!vioEnable || vioFileEof)
		return 0;

	if (vioFileType == CSV)
	{
		double	tmp1 = vioC.time[0] + 0.01;
		int		tmp2 = floor(tmp1 * vioFreq);
		double  tmp3 = 1.0 / vioFreq;
		vioSec = tmp2 * tmp3;
	}

	if (vioSec <= testBin.sec1)
	{
		vioNeedRead = 1;
		return 0;
	}

	if (testBin.sec0 == vioSec)
	{
		if (vioFileType == CSV)
			testBin.GetCsvVio(vioC);

		vioNeedRead = 1;
	}
	return 0;
}

/*TestBin数据输出*/
int Process::TestBinOut()
{
	double ts = 372800;
	double te = 116552 + 60000000;
	if (testBin.sec0 < ts)
		outEnable = 0;
	else if (testBin.sec0 > te)
		outEnable = 0;
	else
		outEnable = 1;

	//输出数据到TestBin
	testBin.imuOutEnable = imuEnable;
	testBin.gnssOutEnable = gnssEnable;
	testBin.dmiOutEnable = dmiEnable;
	testBin.lioOutEnable = lioEnable;
	testBin.vioOutEnable = vioEnable;
	if (outEnable)
		testBin.WriteData();

	return 0;
}



/*处理过程*/
int Process::Deal()
{
	//打开文件
	OpenFile();

	while (true)
	{
		//IMU
		GetIMU();
		if (imuFileEof)
			break;

		//GNSS
		GetGNSS();

		//DMI
		GetDMI();

		//LIO
		GetLIO();

		//VIO
		GetVIO();

		memset(&testBin.data, 0, sizeof(TestBinUnit));
		TestBinIMU();

		//if (testBin.imuUpdateCnt >= TESTBIN_LIST_N_MAX)
		//	continue;

		for (int i = testBin.imuUpdateCnt - 1; i >= 0; i--)
		{
			static int testBinSecFirst = 1;
			if (testBinSecFirst)
			{
				testBin.sec1 = testBin.sec[i];
				testBin.sec0 = testBin.sec[i];
				testBinSecFirst = 0;
			}
			else
			{
				testBin.sec1 = testBin.sec0;
				testBin.sec0 = testBin.sec[i];
			}

			//IMU
			testBin.data.nWeek = testBin.week[i];
			testBin.data.dSec_gnss = testBin.sec[i];
			testBin.data.dGyrox = testBin.gyrox[i];
			testBin.data.dGyroy = testBin.gyroy[i];
			testBin.data.dGyroz = testBin.gyroz[i];
			testBin.data.dAccx = testBin.accx[i];
			testBin.data.dAccy = testBin.accy[i];
			testBin.data.dAccz = testBin.accz[i];

			//GNSS
			TestBinGNSS();

			//DMI
			TestBinDMI();

			//LIO
			TestBinLIO();

			//VIO
			TestBinVIO();

			//输出到文件
			TestBinOut();		
		}
	}
	//关闭文件
	CloseFile();
	return 0;
}