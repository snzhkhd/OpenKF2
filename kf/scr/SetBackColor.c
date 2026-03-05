#include "recomp.h"
#include "disable_warnings.h"
#include "psx/libgte.h"

// Оригинал: void SetBackColor(long rbk, long gbk, long bbk);
void KF_SetBackColor(uint8_t* rdram, recomp_context* ctx) {
    // Аргументы передаются по значению (R, G, B) в r4, r5, r6
    int r = (int)ctx->r4;
    int g = (int)ctx->r5;
    int b = (int)ctx->r6;

    SetBackColor(r, g, b);
}