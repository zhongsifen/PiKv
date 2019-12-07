// PiMien.cpp

#include "PiMien.hpp"
#include <cmath>

bool mien_subim(uint8_t im[], int size[2], int rect[4], uint8_t subim[], int subsiz[2])
{
    int m0 = size[0];
    int m1 = size[1];
    int n0 = subsiz[0];
    int n1 = subsiz[1];
    float pos0 = (float)rect[0];
    float pos1 = (float)rect[1];
    float siz0 = (float)rect[2] - pos0 + 1;
    float siz1 = (float)rect[3] - pos1 + 1;
    float scl0 = siz0 / (float)n0;
    float scl1 = siz1 / (float)n1;

    float x1 = pos1;
    for (int j=0,j1=0; j1<n1; j1++) {
        float t1 = floor(x1);
        float p1 = x1 - t1;
        float q1 = 1 - p1;
        int i1 = (int)t1;
        float x0 = pos0;
        for (int j0 = 0; j0 < n0; j0++)
        {
            float t0 = floor(x0);
            float p0 = x0 - t0;
            float q0 = 1 - p0;
            int i0 = (int)t0;
            int i = i0 + i1 * m0;

            subim[j] = im[i];
            x0 += scl0;
        }
        x1 += scl1;
    }
    return true;
}