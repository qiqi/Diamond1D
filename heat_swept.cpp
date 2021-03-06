#include <cmath>
#include <cassert>
#include <ctime>
#include "heat.h"
#include "pde_swept.h"

int main(int argc, char*argv[])
{
    if (argc != 2) {
        exit(-1);
    }
    size_t numGridPerProc = atoi(argv[1]);
    SweptDiscretization1D disc(numGridPerProc, 0.5, init);
    // disc.colorMap.red.set(0, -2., 2.);

    std::clock_t startTime = std::clock();

    for (int iPixel = 0; iPixel < nPixel; ++iPixel) {
        for (int iStep = 0; iStep < nStepsPerPixel; ++iStep) {
            disc.applyOp(updateStep);
        }
    }

    if (iProc() == 0) {
        std::clock_t endTime = std::clock();
        double totalTime = (endTime - startTime) / (double)CLOCKS_PER_SEC;
        std::cout << totalTime * 1000000 / nStepsPerPixel / nPixel
                  << " microseconds per SubStep" << std::endl;
    }
}
