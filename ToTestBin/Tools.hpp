#pragma once

using	namespace  std;

#define   LEAPS   18

typedef struct
{
	int time;
	double sec;
} gtime_t;

class Tools
{
public:
	Tools();
	~Tools();

	gtime_t epoch2time(const double *ep);
	gtime_t  gpst2time(int week, double sec);
	double time2gpst(gtime_t t, int *week);
	gtime_t timeadd(gtime_t t, double sec);
	gtime_t GPSTime2UTCTime(int week, double sec, double leapsec);


private:

};
