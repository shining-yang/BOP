//
// CPU utilization
//
#include "CPUUtilization.h"

int main(int argc, char* argv[])
{
    CPUUtilization cu;
    //cu.OccupyAs(100);
    cu.OccupyAsSineCurve(40);

    return 0;
}
