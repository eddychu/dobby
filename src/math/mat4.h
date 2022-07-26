#pragma once
#include "math/vector4.h"
struct Matrix4
{
public:
    union
    {
        float v[16];
        struct
        {
            Vector4F right;
            Vector4F up;
            Vector4F forward;
            Vector4F position;
        };
        struct
        {
            // colum 1
            float xx;
            float xy;
            float xz;
            float xw;
            // column 2
            float yx;
            float yy;
            float yz;
            float yw;
            /* column 3 */
            float zx;
            float zy;
            float zz;
            float zw;
            /* column 4 */
            float tx;
            float ty;
            float tz;
            float tw;
        };
        struct
        {
            float c0r0;
            float c0r1;
            float c0r2;
            float c0r3;
            float c1r0;
            float c1r1;
            float c1r2;
            float c1r3;
            float c2r0;
            float c2r1;
            float c2r2;
            float c2r3;
            float c3r0;
            float c3r1;
            float c3r2;
            float c3r3;
        };
        struct
        {
            float r0c0;
            float r1c0;
            float r2c0;
            float r3c0;
            float r0c1;
            float r1c1;
            float r2c1;
            float r3c1;
            float r0c2;
            float r1c2;
            float r2c2;
            float r3c2;
            float r0c3;
            float r1c3;
            float r2c3;
            float r3c3;
        };
    };

    inline Matrix4()
        : xx(1), xy(0), xz(0), xw(0),
          yx(0), yy(1), yz(0), yw(0),
          zx(0), zy(0), zz(1), zw(0),
          tx(0), ty(0), tz(0), tw(1)
    {
    }
};