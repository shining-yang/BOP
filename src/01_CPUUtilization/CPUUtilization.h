//
// File: CPUUilization.h
// by Shining Yang, on 2014-11-12
//
#pragma once
#include <math.h>
#include <windows.h>

class CPUUtilization {
public:
    CPUUtilization(long nCPUAdditionsPerMS);
    ~CPUUtilization();

    void OccupyAs(int nPercent);
    void OccupyAsSineCurve(int nDuration);
    void Stop();

protected:
    void _OccupyIn100MS(int nPercent);

private:
    bool m_bStop;
    long m_nCPUAdditionsPerMS;
};


CPUUtilization::CPUUtilization(long nCPUAdditionsPerMS) : m_bStop(false)
{
    m_nCPUAdditionsPerMS = nCPUAdditionsPerMS;
}

CPUUtilization::~CPUUtilization()
{
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
            if (m_bStop) {
                break;
            }
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

#if 0
    long total = m_nCPUAdditionsPerMS * ms;
    for (long n = 0; n < total; n++) {
    }
#else
    /*
     * EASY & FAST way to occupy CPU, no need to MeasureCPU
     */
    DWORD dwBegin = ::GetTickCount();
    while (static_cast<int>(::GetTickCount() - dwBegin) <= ms) {
    }
#endif

    Sleep(100 - ms);
}

void CPUUtilization::Stop()
{
    m_bStop = true;
}