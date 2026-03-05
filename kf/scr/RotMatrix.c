#include "recomp.h"
#include "disable_warnings.h"
#include "psx/libgte.h"

// MATRIX* RotMatrix(SVECTOR* r, MATRIX* m);
void KF_RotMatrix(uint8_t* rdram, recomp_context* ctx) {
    SVECTOR* r = (SVECTOR*)GET_PTR(ctx->r4); // a0 - входные углы
    MATRIX* m = (MATRIX*)GET_PTR(ctx->r5);  // a1 - матрица (результат)

    if (r && m) {
        RotMatrix(r, m);
    }

    // Возвращаем в v0 адрес результирующей матрицы (из r5)
    ctx->r2 = ctx->r5;
}