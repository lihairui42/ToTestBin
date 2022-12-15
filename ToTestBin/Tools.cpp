#include "iostream"
#include "sstream"
#include "vector"

#include "Tools.hpp"

using namespace std;

const static double gpst0[] = { 1980,1, 6,0,0,0 };

Tools::Tools()
{
}

Tools::~Tools()
{
}

gtime_t Tools::epoch2time(const double *ep)
{
	const int doy[] = { 1,32,60,91,121,152,182,213,244,274,305,335 };
	gtime_t time = { 0 };
	int days, sec, year = (int)ep[0], mon = (int)ep[1], day = (int)ep[2];

	if (year<1970 || 2099<year || mon<1 || 12<mon) return time;

	days = (year - 1970) * 365 + (year - 1969) / 4 + doy[mon - 1] + day - 2 + (year % 4 == 0 && mon >= 3 ? 1 : 0);
	sec = (int)floor(ep[5]);
	time.time = (time_t)days * 86400 + (int)ep[3] * 3600 + (int)ep[4] * 60 + sec;
	time.sec = ep[5] - sec;
	return time;
}

/*
*gpst2time
*/
gtime_t  Tools::gpst2time(int week, double sec)
{
	gtime_t t = epoch2time(gpst0);

	if (sec<-1E9 || 1E9<sec) sec = 0.0;
	t.time += 86400 * 7 * week + (int)sec;
	t.sec = sec - (int)sec;

	t.time = t.time - 18;
	//double pose_time = double(t.time + t.sec - 18.0);
	return t;
}

/*
*time2gpst
*/
double Tools::time2gpst(gtime_t t, int *week)
{
	gtime_t t0 = epoch2time(gpst0);
	time_t sec = t.time + 18 - t0.time;
	int w = (int)(sec / (86400 * 7));

	if (week) *week = w;
	return (double)(sec - (double)w * 86400 * 7) + t.sec;
}


gtime_t Tools::timeadd(gtime_t t, double sec)
{
	double tt;
	t.sec += sec; tt = floor(t.sec); t.time += (int)tt; t.sec -= tt;
	return t;
}

gtime_t Tools::GPSTime2UTCTime(int week, double sec, double leapsec)
{
	gtime_t gpst = gpst2time(week, sec);
	return timeadd(gpst, -leapsec);
}
