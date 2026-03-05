#include "recomp.h"
#include "disable_warnings.h"
#include "psx/libgte.h"


// Оригинал: void SetFarColor(long rfc, long gfc, long bfc);
void KF_SetFarColor(uint8_t* rdram, recomp_context* ctx) {
    // Аргументы R, G, B в r4, r5, r6
    int r = (int)ctx->r4;
    int g = (int)ctx->r5;
    int b = (int)ctx->r6;

    SetFarColor(r, g, b);
}
