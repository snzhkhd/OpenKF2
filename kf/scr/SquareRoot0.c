#include "recomp.h"
#include "disable_warnings.h"

#include "psx/libgte.h"

void KF_SquareRoot0(uint8_t* rdram, recomp_context* ctx)
{

    int a = (int)ctx->r4;
    int result = SquareRoot0(a);
    ctx->r2 = (uint32_t)result;

    ;
}
