#include "recomp.h"
#include "disable_warnings.h"
#include "psx/libgte.h"

void KF_ApplyRotMatrix(uint8_t* rdram, recomp_context* ctx) {
    SVECTOR* v0 = (SVECTOR*)GET_PTR(ctx->r4); // a0
    VECTOR* v1 = (VECTOR*)GET_PTR(ctx->r5); // a1

    ApplyRotMatrix(v0, v1);
    ctx->r2 = ctx->r5; // Возвращаем указатель на v1
}