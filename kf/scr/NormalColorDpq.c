#include "recomp.h"
#include "disable_warnings.h"
#include "psx/libgte.h"

void KF_NormalColorDpq(uint8_t* rdram, recomp_context* ctx) {
    SVECTOR* v0 = (SVECTOR*)GET_PTR(ctx->r4);
    CVECTOR* v1 = (CVECTOR*)GET_PTR(ctx->r5);
    int p = (int)ctx->r6;                // Коэффициент тумана (значение)
    CVECTOR* v2 = (CVECTOR*)GET_PTR(ctx->r7); // Результат

    NormalColorDpq(v0, v1, p, v2);
}