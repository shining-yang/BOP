//
// File: CPUUilization.h
// by Shining Yang, on 2014-11-12
//
#pragma once
#include <math.h>
#include <windows.h>

class CPUUtilization {
public:
    CPUUtilization();
    ~CPUUtilization();

    void OccupyAs(int nPercent);
    void OccupyAsSineCurve(int nDuration);
    void Stop() { m_bStop = true; }

protected:
    long _MeasureCpuByAdditionsPerMS() const;
    void _OccupyIn100MS(int nPercent);

private:
    volatile bool m_bStop;
    long m_nCPUAdditionsPerMS;
};


CPUUtilization::CPUUtilization() : m_bStop(false)
{
    m_nCPUAdditionsPerMS = _MeasureCpuByAdditionsPerMS();
}

CPUUtilization::~CPUUtilization()
{
}

long CPUUtilization::_MeasureCpuByAdditionsPerMS() const
{
    LARGE_INTEGER StartingTime, EndingTime, ElapsedMilliseconds;
    LARGE_INTEGER Frequency;

    QueryPerformanceFrequency(&Frequency);
    QueryPerformanceCounter(&StartingTime);

    for (unsigned i = 0; i < static_cast<unsigned>(-1); i++) {
        // do not allow compilation optimization
    }

    QueryPerformanceCounter(&EndingTime);
    ElapsedMilliseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
    ElapsedMilliseconds.QuadPart *= 1000000;
    ElapsedMilliseconds.QuadPart /= Frequency.QuadPart;
    ElapsedMilliseconds.QuadPart /= 1000; // microsecond -> millisecond

    double nAdditionPerMillisecond = (double)(static_cast<unsigned>(-1)) / ElapsedMilliseconds.QuadPart;
    return static_cast<long>(nAdditionPerMillisecond);
}

void CPUUtilization::OccupyAs(int nPercent)
{
    m_bStop = false;

    while (!m_bStop) {
        _OccupyIn100MS(nPercent);
    }
}

// nDuration: duration of a cycle in seconds
void CPUUtilization::OccupyAsSineCurve(int nDuration)
{
    int slices = nDuration * 1000 / 100; // 100 ms per slice for sampling
    double PI = 3.14159265;
    double step = 2 * PI / slices;
    double sample = 0.0;

    int* nSineArray = new int[slices];
    for (int i = 0; i < slices; i++) {
        nSineArray[i] = static_cast<int>((sin(sample) + 1) * 50);
        sample += step;
    }

    m_bStop = false;

    while (!m_bStop) {
        for (int i = 0; i < slices; i++) {
            _OccupyIn100MS(nSineArray[i]);
        }
    }

    delete[] nSineArray;
}

// Occupy CPU within 100 ms
void CPUUtilization::_OccupyIn100MS(int ms)
{
    //     if ((ms < 0) || (ms > 100)) {
    //         throw new int;
    //     }

    long total = m_nCPUAdditionsPerMS * ms;
    for (long n = 0; n < total; n++) {
    }

    Sleep(100 - ms);
}

