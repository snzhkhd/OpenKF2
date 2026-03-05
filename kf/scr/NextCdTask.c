#include "recomp.h"
#include "disable_warnings.h"

void NextCdTask(uint8_t* rdram, recomp_context* ctx) 
{
    printf("--->NextCdTask<---\n");
    uint64_t hi = 0, lo = 0, result = 0;
    unsigned int rounding_mode = DEFAULT_ROUNDING_MODE;
    int c1cs = 0; 
    // addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // sw          $s0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r16;
    // addu        $s0, $a0, $zero
    ctx->r16 = ADD32(ctx->r4, 0);
    // sw          $ra, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r31;
    // sb          $zero, 0x0($s0)
    MEM_B(0X0, ctx->r16) = 0;
    // sb          $zero, 0x1($s0)
    MEM_B(0X1, ctx->r16) = 0;
    // addiu       $s0, $s0, 0x28
    ctx->r16 = ADD32(ctx->r16, 0X28);
    // lui         $v0, 0x801C
    ctx->r2 = S32(0X801C << 16);
    // addiu       $v0, $v0, -0x57BC
    ctx->r2 = ADD32(ctx->r2, -0X57BC);
    // bne         $s0, $v0, L_80017D5C
    if (ctx->r16 != ctx->r2) {
        // nop
    
        goto L_80017D5C;
    }
    // nop

    // addiu       $s0, $s0, -0x280
    ctx->r16 = ADD32(ctx->r16, -0X280);
L_80017D5C:
    // lui         $at, 0x801C
    ctx->r1 = S32(0X801C << 16);
    // sw          $s0, -0x57B8($at)
    MEM_W(-0X57B8, ctx->r1) = ctx->r16;
    // lbu         $v0, 0x0($s0)
    ctx->r2 = MEM_BU(0X0, ctx->r16);
    // nop

    // beq         $v0, $zero, L_80017D94
    if (ctx->r2 == 0) {
        // ori         $a0, $zero, 0x9
        ctx->r4 = 0 | 0X9;
        goto L_80017D94;
    }
    // ori         $a0, $zero, 0x9
    ctx->r4 = 0 | 0X9;
    // ori         $a0, $zero, 0x16
    ctx->r4 = 0 | 0X16;
L_80017D78:
    // addiu       $a1, $s0, 0x2
    ctx->r5 = ADD32(ctx->r16, 0X2);
    // jal         0x8004CAC0
    // addu        $a2, $zero, $zero
    ctx->r6 = ADD32(0, 0);
    KF_CdControl(rdram, ctx);
    goto after_0;
    // addu        $a2, $zero, $zero
    ctx->r6 = ADD32(0, 0);
    after_0:
    // beq         $v0, $zero, L_80017D78
    if (ctx->r2 == 0) {
        // ori         $a0, $zero, 0x16
        ctx->r4 = 0 | 0X16;
        goto L_80017D78;
    }
    // ori         $a0, $zero, 0x16
    ctx->r4 = 0 | 0X16;
    // j           L_80017DA0
    // nop

    goto L_80017DA0;
    // nop

L_80017D94:
    // addu        $a1, $zero, $zero
    ctx->r5 = ADD32(0, 0);
    // jal         0x8004CAC0
    // addu        $a2, $zero, $zero
    ctx->r6 = ADD32(0, 0);
    KF_CdControl(rdram, ctx);
    goto after_1;
    // addu        $a2, $zero, $zero
    ctx->r6 = ADD32(0, 0);
    after_1:
L_80017DA0:
    // lw          $ra, 0x14($sp)
    ctx->r31 = MEM_W(0X14, ctx->r29);
    // lw          $s0, 0x10($sp)
    ctx->r16 = MEM_W(0X10, ctx->r29);
    // addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);
    // jr          $ra
    // nop

    return;
    // nop

;}
