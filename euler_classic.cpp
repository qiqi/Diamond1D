#include <cmath>
#include <cassert>
#include <ctime>
#include "euler.h"
#include "pde_classic.h"

int main(int argc, char*argv[])
{
    if (argc != 2) {
        exit(-1);
    }
    size_t numGridPerProc = atoi(argv[1]);
    ClassicDiscretization1D disc(numGridPerProc, 0.5, init);
    disc.colorMap.red.set(0, 0., 1.);
    disc.colorMap.green.set(1, -1., 1.);
    disc.colorMap.blue.set(2, 0., 3.);

    std::clock_t startTime = std::clock();

    for (int iPixel = 0; iPixel < nPixel; ++iPixel) {
        for (int iStep = 0; iStep < nStepsPerPixel; ++iStep) {
            disc.applyOp(pRatioStep0);
            disc.applyOp(updateStep0);
            disc.applyOp(pRatioStep1);
            disc.applyOp(updateStep1);
        }
        disc.variablesToColor(iPixel);
        disc.writePng("test_minmod");
    }

    if (iProc() == 0) {
        std::clock_t endTime = std::clock();
        double totalTime = (endTime - startTime) / (double)CLOCKS_PER_SEC;
        std::cout << totalTime * 1000000 / nStepsPerPixel / nPixel / 4
                  << " microseconds per SubStep" << std::endl;
    }
}
