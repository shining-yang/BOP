//
// This program attempts to make CPU utilization as a SINE Curve.
//
// by Shining Yang, on 2014-11-12
//
#include "CPUUtilization.h"
#include <conio.h>
#include <process.h>
#include <iostream>

long MeasureCpuByAdditionsPerMS()
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

    double nAdditionPerMillisecond = 
        (double)(static_cast<unsigned>(-1)) / ElapsedMilliseconds.QuadPart;

    return static_cast<long>(nAdditionPerMillisecond);
}

unsigned int __stdcall OccupyCpuFunc(LPVOID lpData)
{
    CPUUtilization* pObj = reinterpret_cast<CPUUtilization*>(lpData);
    if (pObj) {
        pObj->OccupyAsSineCurve(20);
    }

    return 0;
}

int main(int argc, char* argv[])
{
    long nAddPerMS = MeasureCpuByAdditionsPerMS();

    const int NUM_CPU_CORES = 2;
    HANDLE hArrayThreads[NUM_CPU_CORES] = { 0 };
    CPUUtilization* lpObjs[NUM_CPU_CORES] = { 0 };

    for (int i = 0; i < NUM_CPU_CORES; i++) {
        lpObjs[i] = new CPUUtilization(nAddPerMS);
        if (lpObjs[i]) {
            hArrayThreads[i] = (HANDLE)_beginthreadex(NULL, 0, OccupyCpuFunc,
                lpObjs[i], CREATE_SUSPENDED, NULL);
        }
    }

    for (int i = 0; i < NUM_CPU_CORES; i++) {
        if (hArrayThreads[i]) {
            ResumeThread(hArrayThreads[i]);
        }
    }

    std::cout << "Press any key to exit..." << std::endl;
    _getch();

    for (int i = 0; i < NUM_CPU_CORES; i++) {
        if (lpObjs[i]) {
            lpObjs[i]->Stop();
        }
    }

    for (int i = 0; i < NUM_CPU_CORES; i++) {
        if (hArrayThreads[i]) {
            WaitForSingleObject(hArrayThreads[i], INFINITE);
            CloseHandle(hArrayThreads[i]);
        }
    }

    for (int i = 0; i < NUM_CPU_CORES; i++) {
        if (lpObjs[i]) {
            delete lpObjs[i];
        }
    }

    return 0;
}
