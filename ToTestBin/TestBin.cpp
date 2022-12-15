#include "TestBin.hpp"

TestBinData::TestBinData()
{
}

TestBinData::~TestBinData()
{
}

int TestBinData::OpenFile()
{
	fs = fopen(file.c_str(), "w");
	return 0;
}

int TestBinData::CloseFile()
{
	fclose(fs);
	return 0;
}

/*
*从Novatel文件获取IMU数据
*/
int TestBinData::GetNovatelImu(NovatelImuData &imuN)
{
	if (imuN.imus.update || imuN.imusx.update)
	{
		if (imuN.sec[0] >= 117110.34)
			sec1 *= 1.0;

#if 1
		int tmpN1 = floor((imuN.sec[0]) * imuFreq);
		int tmpN2 = floor((imuN.sec[1]) * imuFreq);
		imuUpdateCnt = tmpN1 - tmpN2;

		if (imuUpdateCnt >= 2)
			imuUpdateCnt *= 1.0;

		//if (imuUpdateCnt >= TESTBIN_LIST_N_MAX)
		//	return 0;

		for (int i = 0; i < imuUpdateCnt; i++)
		{
			double dtt = 1.0 / imuFreq;
			sec[i] = (tmpN1-i) * dtt;
			double c0, c1;
			double dt = imuN.sec[0] - imuN.sec[1];
			c0 = (sec[i] - imuN.sec[1]) / dt;
			c1 = (imuN.sec[0] - sec[i]) / dt;
			week[i] = imuN.week[0];
			gyrox[i] = c0 * imuN.gyrox[0] + c1 * imuN.gyrox[1];
			gyroy[i] = c0 * imuN.gyroy[0] + c1 * imuN.gyroy[1];
			gyroz[i] = c0 * imuN.gyroz[0] + c1 * imuN.gyroz[1];
			accx[i] = c0 * imuN.accx[0] + c1 * imuN.accx[1];
			accy[i] = c0 * imuN.accy[0] + c1 * imuN.accy[1];
			accz[i] = c0 * imuN.accz[0] + c1 * imuN.accz[1];
		}
#else
		sec0 = imuN.sec[0];
		sec1 = imuN.sec[1];
		data.nWeek = imuN.week[0];
		data.dSec_gnss = imuN.sec[0];
		data.dGyrox = imuN.gyrox[0];
		data.dGyroy = imuN.gyroy[0];
		data.dGyroz = imuN.gyroz[0];
		data.dAccx = imuN.accx[0];
		data.dAccy = imuN.accy[0];
		data.dAccz = imuN.accz[0];
#endif
	}
	return 0;
}

/*
*从Novatel文件获取GNSS数据
*/
int TestBinData::GetNovatelGnss(NovatelGnssData &gnssN)
{
	//BestPOS
	if (gnssN.bestPosHaved)
	{
		data.dLat_gnss = gnssN.bestPos.lat;
		data.dLon_gnss = gnssN.bestPos.lon;
		data.dH_gnss = gnssN.bestPos.hgt;

		data.dLatStd = gnssN.bestPos.latStd;
		data.dLonStd = gnssN.bestPos.lonStd;
		data.dHStd = gnssN.bestPos.hgtStd;

		if (gnssN.bestPos.posType != 0)
		{
			data.ucGnssPos_FixFlag = gnssN.bestPos.posType;
			data.ucGnssPos_Q = 1;

			if(  (gnssN.bestPos.posType == 50) || (gnssN.bestPos.posType == 58))
			{
				data.ucGnssPos_FixFlag = 1;
				data.ucGnssPos_Q = 1;
			}
		}
	}

	//BestVel
	if (gnssN.bestVelHaved)
	{
		double psi = gnssN.bestVel.trkGnd * 3.141592653589793 / 180;
		data.dVe_gnss = gnssN.bestVel.horSpd * sin(psi);
		data.dVn_gnss = gnssN.bestVel.horSpd * cos(psi);
		data.dVu_gnss = gnssN.bestVel.vertSpd;

		data.dVeStd = 0.01;
		data.dVnStd = 0.01;
		data.dVuStd = 0.01;

		data.dGnssVel_valid = 1;
	}

	data.ucState_gnss = data.ucState_gnss | 0x03;
	data.ucFlag_synchro = 160;

	return 0;
}

/*
*从TXT文件获取GNSS数据
*/
int TestBinData::GetTxtGnss(TxtGnssData &gnssT)
{
	data.dLat_gnss = gnssT.lat;
	data.dLon_gnss = gnssT.lon;
	data.dH_gnss = gnssT.hgt;

	data.dLatStd = gnssT.latStd;
	data.dLonStd = gnssT.lonStd;
	data.dHStd = gnssT.hgtStd;

	data.ucGnssPos_FixFlag = gnssT.fixFlag;
	data.ucGnssPos_Q = gnssT.Q;

	data.dVe_gnss = gnssT.ve;
	data.dVn_gnss = gnssT.vn;
	data.dVu_gnss = gnssT.vu;

	data.dVeStd = gnssT.veStd;
	data.dVnStd = gnssT.vnStd;
	data.dVuStd = gnssT.vuStd;

	data.dGnssVel_valid = 1;

	data.ucState_gnss = data.ucState_gnss | 0x03;
	data.ucFlag_synchro = 160;

	return 0;
}

/*
*从TxtDmiData获取DMI数据
*/
int TestBinData::GetTxtDmi(TxtDmiData &dmiT)
{
#if  1
	double t = floor(dmiT.time[0] + 0.01);
	double t0 = dmiT.time[0];
	double t1 = dmiT.time[1];

	double dt = t0 - t1;
	double c0 = (t - t1) / dt;
	double c1 = (t0 - t) / dt;

	data.dmiStatus = dmiT.status[0];
	data.dmi1 = c0 * dmiT.dmi1[0] + c1 * dmiT.dmi1[1];
	data.dmi2 = c0 * dmiT.dmi2[0] + c1 * dmiT.dmi2[1];
	data.dmi3 = c0 * dmiT.dmi3[0] + c1 * dmiT.dmi3[1];
	data.dmi4 = c0 * dmiT.dmi4[0] + c1 * dmiT.dmi4[1];
#else
	data.dmiStatus = dmiT.status[0];
	data.dmi1 = dmiT.dmi1[0];
	data.dmi2 = dmiT.dmi2[0];
	data.dmi3 = dmiT.dmi3[0];
	data.dmi4 = dmiT.dmi4[0];
#endif

	data.ucState_gnss = data.ucState_gnss | 0x08;
	data.ucFlag_synchro = 160;
	
	return 0;
}

/*
*从NovatelDmiData获取DMI数据
*/
int TestBinData::GetNovatelDmi(NovatelDmiData &dmiN)
{
	data.dmiStatus = dmiN.dmia.status;
	data.dmi1 = dmiN.dmia.dmi1;
	data.dmi2 = dmiN.dmia.dmi2;
	data.dmi3 = dmiN.dmia.dmi3;
	data.dmi4 = dmiN.dmia.dmi4;

	data.ucState_gnss = data.ucState_gnss | 0x08;
	return 0;
}


/*
*从CSV获取LIO数据
*/
int TestBinData::GetCsvLio(CsvLioData &lio)
{
#if 1
	double	tmp1 = lio.time[0] + 0.01;
	int		tmp2 = floor(tmp1 * lioFreq);
	double  tmp3 = 1.0 / lioFreq;

	double  t = tmp2 * tmp3;
	double t0 = lio.time[0];
	double t1 = lio.time[1];

	double dt = t0 - t1;
	double c0 = (t - t1) / dt;
	double c1 = (t0 - t) / dt;

	data.lio_time = t;
	data.lio_quality = lio.quality[0];
	data.lio_q0 = c0 * lio.q0[0] + c1 * lio.q0[1];
	data.lio_q1 = c0 * lio.q1[0] + c1 * lio.q1[1];
	data.lio_q2 = c0 * lio.q2[0] + c1 * lio.q2[1];
	data.lio_q3 = c0 * lio.q3[0] + c1 * lio.q3[1];
	data.lio_x = c0 * lio.x[0] + c1 * lio.x[1];
	data.lio_y = c0 * lio.y[0] + c1 * lio.y[1];
	data.lio_z = c0 * lio.z[0] + c1 * lio.z[1];

	double norm = sqrt(data.lio_q0 * data.lio_q0 + data.lio_q1 * data.lio_q1 + data.lio_q2 * data.lio_q2 + data.lio_q3 * data.lio_q3);
	double _1_norm = 1.0 / norm;
	data.lio_q0 = data.lio_q0 * _1_norm;
	data.lio_q1 = data.lio_q1 * _1_norm;
	data.lio_q2 = data.lio_q2 * _1_norm;
	data.lio_q3 = data.lio_q3 * _1_norm;
#else
	data.lio_time = lio.time[0];
	data.lio_quality = lio.quality[0];
	data.lio_q0 = lio.q0[0];
	data.lio_q1 = lio.q1[0];
	data.lio_q2 = lio.q2[0];
	data.lio_q3 = lio.q3[0];
	data.lio_x = lio.x[0];
	data.lio_y = lio.y[0];
	data.lio_z = lio.z[0];
#endif // 0

	data.ucState_gnss = data.ucState_gnss | 0x10;
	data.ucFlag_synchro = 160;
	return 0;
}

/*
*从CSV获取VIO数据
*/
int TestBinData::GetCsvVio(CsvVioData &vio)
{
#if 1
	double	tmp1 = vio.time[0] + 0.01;
	int		tmp2 = floor(tmp1 * vioFreq);
	double  tmp3 = 1.0 / vioFreq;

	double  t = tmp2 * tmp3;
	double t0 = vio.time[0];
	double t1 = vio.time[1];

	double dt = t0 - t1;
	double c0 = (t - t1) / dt;
	double c1 = (t0 - t) / dt;

	data.vio_time = t;
	data.vio_quality = vio.quality[0];
	data.vio_q0 = c0 * vio.q0[0] + c1 * vio.q0[1];
	data.vio_q1 = c0 * vio.q1[0] + c1 * vio.q1[1];
	data.vio_q2 = c0 * vio.q2[0] + c1 * vio.q2[1];
	data.vio_q3 = c0 * vio.q3[0] + c1 * vio.q3[1];
	data.vio_x = c0 * vio.x[0] + c1 * vio.x[1];
	data.vio_y = c0 * vio.y[0] + c1 * vio.y[1];
	data.vio_z = c0 * vio.z[0] + c1 * vio.z[1];

	double norm = sqrt(data.vio_q0 * data.vio_q0 + data.vio_q1 * data.vio_q1 + data.vio_q2 * data.vio_q2 + data.vio_q3 * data.vio_q3);
	double _1_norm = 1.0 / norm;
	data.vio_q0 = data.vio_q0 * _1_norm;
	data.vio_q1 = data.vio_q1 * _1_norm;
	data.vio_q2 = data.vio_q2 * _1_norm;
	data.vio_q3 = data.vio_q3 * _1_norm;
#else
	data.vio_time = vio.time[0];
	data.vio_quality = vio.quality[0];
	data.vio_q0 = vio.q0[0];
	data.vio_q1 = vio.q1[0];
	data.vio_q2 = vio.q2[0];
	data.vio_q3 = vio.q3[0];
	data.vio_x = vio.x[0];
	data.vio_y = vio.y[0];
	data.vio_z = vio.z[0];
#endif // 0

	data.ucState_gnss = data.ucState_gnss | 0x20;
	data.ucFlag_synchro = 160;

	return 0;
}

/*
*TestBin数据输出到TXT
*/
int TestBinData::WriteData()
{
	if (gnssOutEnable)
	{
		fprintf(fs, "%4d,    ", data.nWeek);					//1
		fprintf(fs, "%.10f,    ", data.dSec_gnss);				//2

		fprintf(fs, "%.8f,    ", data.dLat_gnss);				//3
		fprintf(fs, "%.8f,    ", data.dLon_gnss);				//4
		fprintf(fs, "%.4f,    ", data.dH_gnss);					//5
		fprintf(fs, "%.4f,    ", data.dLatStd);					//6
		fprintf(fs, "%.4f,    ", data.dLonStd);					//7
		fprintf(fs, "%.4f,    ", data.dHStd);					//8

		fprintf(fs, "%4d,    ", data.ucGnssPos_FixFlag);		//9
		fprintf(fs, "%4d,    ", data.ucGnssPos_Q);				//10

		fprintf(fs, "%.5f,    ", data.dVe_gnss);				//11
		fprintf(fs, "%.5f,    ", data.dVn_gnss);				//12
		fprintf(fs, "%.5f,    ", data.dVu_gnss);				//13
		fprintf(fs, "%.5f,    ", data.dVeStd);					//14
		fprintf(fs, "%.5f,    ", data.dVnStd);					//15
		fprintf(fs, "%.5f,    ", data.dVuStd);					//16

		fprintf(fs, "%4d,    ", data.dGnssVel_valid);			//17

		fprintf(fs, "%.8f,    ", data.dAzi_gnss);				//18
		fprintf(fs, "%.8f,    ", data.dAzi_Std_gnss);			//19

		fprintf(fs, "%.3f,    ", data.dBaseline_gnss);			//20
		fprintf(fs, "%d,    ", data.ucState_gnss);				//21
	}

	if (imuOutEnable)
	{
		fprintf(fs, "%.10f,    ", data.dGyrox);					//22
		fprintf(fs, "%.10f,    ", data.dGyroy);					//23
		fprintf(fs, "%.10f,    ", data.dGyroz);					//24
		fprintf(fs, "%.10f,    ", data.dAccx);					//25
		fprintf(fs, "%.10f,    ", data.dAccy);					//26
		fprintf(fs, "%.10f,    ", data.dAccz);					//27

		fprintf(fs, "%d,    ", data.dwDltCnt_dmi);				//28
	}

	if (dmiOutEnable)
	{
		fprintf(fs, "%d,    ", data.dmiStatus);					//29
		fprintf(fs, "%.5f,    ", data.dmi1);					//30
		fprintf(fs, "%.5f,    ", data.dmi2);					//31
		fprintf(fs, "%.5f,    ", data.dmi3);					//32
		fprintf(fs, "%.5f,    ", data.dmi4);					//33
	}

	if (lioOutEnable)
	{
		fprintf(fs, "%.8f,    ", data.lio_q0);					//34
		fprintf(fs, "%.8f,    ", data.lio_q1);					//35
		fprintf(fs, "%.8f,    ", data.lio_q2);					//36
		fprintf(fs, "%.8f,    ", data.lio_q3);					//37
		fprintf(fs, "%.8f,    ", data.lio_x);					//38
		fprintf(fs, "%.8f,    ", data.lio_y);					//39
		fprintf(fs, "%.8f,    ", data.lio_z);					//40
		fprintf(fs, "%.8f,    ", data.lio_quality);				//41
	}

	fprintf(fs, "%d,    ", data.ucFlag_synchro);				//42
	fprintf(fs, "\n");

	return 0;
}