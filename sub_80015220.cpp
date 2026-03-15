#include "recomp.h"
#include "disable_warnings.h"


void sub_80015220(uint8_t* rdram, recomp_context* ctx)
{
    uint32_t src = ctx->r4;  // a0 = source SVECTOR
    uint32_t dst = ctx->r5;  // a1 = dest SVECTOR
    int mode = (int)ctx->r6; // a2 = rotation mode (0-3)

    int16_t x = (int16_t)MEM_HU(0, src);
    int16_t y = (int16_t)MEM_HU(2, src);
    int16_t z = (int16_t)MEM_HU(4, src);

    switch (mode) {
    case 0: // identity
        MEM_H(0, dst) = x;
        MEM_H(2, dst) = y;
        MEM_H(4, dst) = z;
        break;
    case 1: // rotate 90
        MEM_H(0, dst) = -z;
        MEM_H(2, dst) = y;
        MEM_H(4, dst) = x;
        break;
    case 2: // rotate 180
        MEM_H(0, dst) = -x;
        MEM_H(2, dst) = y;
        MEM_H(4, dst) = -z;
        break;
    case 3: // rotate 270
        MEM_H(0, dst) = z;
        MEM_H(2, dst) = y;
        MEM_H(4, dst) = -x;
        break;
    }
}