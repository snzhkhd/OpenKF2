#include "recomp.h"
#include "disable_warnings.h"

void sub_8005F2C8(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    unsigned int rounding_mode = DEFAULT_ROUNDING_MODE;
    int c1cs = 0; 
    // lwc2        $0, 0x0($a0)
    gte_lwc2(rdram, ctx, 0, 4, 0);
    // lwc2        $1, 0x4($a0)
    gte_lwc2(rdram, ctx, 1, 4, 4);
    // nop

    // .word       0x4A180001                   # INVALID     $s0, $t8, 0x1 # 00000000 <InstrIdType: CPU_COP2>
    gte_command(ctx, 0x4A180001);
    // swc2        $14, 0x0($a1)
    gte_swc2(rdram, ctx, 14, 5, 0);
    // swc2        $8, 0x0($a2)
    gte_swc2(rdram, ctx, 8, 6, 0);
    // cfc2        $v1, $31
    ctx->r3 = gte_cfc2(ctx, 31);
    // mfc2        $v0, $19
    ctx->r2 = gte_mfc2(ctx, 19);
    // sw          $v1, 0x0($a3)
    MEM_W(0X0, ctx->r7) = ctx->r3;
    // jr          $ra
    // sra         $v0, $v0, 2
    ctx->r2 = S32(ctx->r2) >> 2;
    return;
    // sra         $v0, $v0, 2
    ctx->r2 = S32(ctx->r2) >> 2;
;}
