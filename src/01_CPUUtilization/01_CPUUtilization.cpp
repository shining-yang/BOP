//
// File: 01_UtilizeCPU.cpp
// by Shining Yang, on 2014-11-12
//
#include <windows.h>
#include <math.h>
#include <iostream>

//
// Try to get number of additions per millisecond that the CPU can perform
//
long MeasureCpuByAddtionPerMS()
{
    LARGE_INTEGER StartingTime, EndingTime, ElapsedMilliseconds;
    LARGE_INTEGER Frequency;

    QueryPerformanceFrequency(&Frequency);
    QueryPerformanceCounter(&StartingTime);

    for (unsigned i = 0; i < static_cast<unsigned>(-1); i++) {}

    QueryPerformanceCounter(&EndingTime);
    ElapsedMilliseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
    ElapsedMilliseconds.QuadPart *= 1000000;
    ElapsedMilliseconds.QuadPart /= Frequency.QuadPart;
    ElapsedMilliseconds.QuadPart /= 1000; // microsecond -> millisecond

    double nAdditionPerMillisecond = (double)(static_cast<unsigned>(-1)) / ElapsedMilliseconds.QuadPart;
    return static_cast<long>(nAdditionPerMillisecond);
}

// Utilize CPU within 100 ms
// ms: [0 - 100]
void OccupyCpuByPercentage(int nAdditionsPerMS, int ms)
{
    if ((ms < 0) || (ms > 100)) {
        throw new int;
    }

    nAdditionsPerMS *= ms;
    for (int i = 0; i < nAdditionsPerMS; i++) {}
    Sleep(100 - ms);
}

void OccupyCpuAtSinePercentage(int nAdditionsPerMS)
{
    const double PI = 3.14159265;
    int duration = 30 * 1000;
    int slice = duration / 100;
    double step = (2 * PI) / slice;

    for (double d = 0.0; ; d += step) {
        OccupyCpuByPercentage(nAdditionsPerMS, static_cast<int>((1 + sin(d)) * 50));
    }
}

int main(int argc, char* argv[])
{
    int nAdditionsPerMS = MeasureCpuByAddtionPerMS();

    while (true) {
        //OccupyCpuByPercentage(nAdditionsPerMS, 50);
        OccupyCpuAtSinePercentage(nAdditionsPerMS);
    }

    return 0;
}