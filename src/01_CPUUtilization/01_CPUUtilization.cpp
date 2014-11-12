//
// CPU utilization
//
#include "CPUUtilization.h"

int main(int argc, char* argv[])
{
    CPUUtilization cu;
#if 0
    cu.OccupyAs(50);
#else
    cu.OccupyAsSineCurve(40);
#endif
    return 0;
}
