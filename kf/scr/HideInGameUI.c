#include "recomp.h"
#include "disable_warnings.h"
#include "psx/libpad.h"
#include "PsyX/PsyX_render.h"


extern bool g_forceSaveNextFrame;


void HideInGameUI(uint8_t* rdram, recomp_context* ctx) 
{

    //rdram[0x19B58D] = 0;
    //rdram[0x19B58E] = 0;
    //
    //uint8_t isbg = rdram[0x190178];

    //uint8_t hpmp = rdram[0x19B58D];
    //uint8_t compas = rdram[0x19B58E];


    //printf("after GpuUpdate isbg = %d,  hpmp= %d,  compas=%d\n", isbg, hpmp, compas);

    uint64_t hi = 0, lo = 0, result = 0;
    unsigned int rounding_mode = DEFAULT_ROUNDING_MODE;
    int c1cs = 0; 
    // addiu       $sp, $sp, -0x20
    ctx->r29 = ADD32(ctx->r29, -0X20);
    // sw          $s0, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r16;
    // lui         $s0, 0x801A
    ctx->r16 = S32(0X801A << 16);
    // addiu       $s0, $s0, -0x4A73
    ctx->r16 = ADD32(ctx->r16, -0X4A73);
    // addu        $a0, $zero, $zero
    ctx->r4 = ADD32(0, 0);
    // sw          $ra, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r31;
    // sw          $s2, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r18;
    // sw          $s1, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r17;
    // lbu         $s1, 0x0($s0)
    ctx->r17 = MEM_BU(0X0, ctx->r16);
    // lui         $s2, 0x801A
    ctx->r18 = S32(0X801A << 16);
    // lbu         $s2, -0x4A72($s2)
    ctx->r18 = MEM_BU(-0X4A72, ctx->r18);
    // sb          $zero, 0x0($s0)
    MEM_B(0X0, ctx->r16) = 0;
    // lui         $at, 0x801A
    ctx->r1 = S32(0X801A << 16);
    // sb          $zero, -0x4A72($at)
    MEM_B(-0X4A72, ctx->r1) = 0;
    // jal         0x800360A0
    // addu        $a1, $zero, $zero
    ctx->r5 = ADD32(0, 0);

   

    g_forceSaveNextFrame = true;
    KF_GpuUpdate(rdram, ctx);

    g_forceSaveNextFrame = false;

    
    
    goto after_0;
    // addu        $a1, $zero, $zero
    ctx->r5 = ADD32(0, 0);
after_0:

   
    // sb          $s1, 0x0($s0)
    MEM_B(0X0, ctx->r16) = ctx->r17;
    // lui         $at, 0x801A
    ctx->r1 = S32(0X801A << 16);
    // sb          $s2, -0x4A72($at)
    MEM_B(-0X4A72, ctx->r1) = ctx->r18;
    // jal         0x80037184
    // nop


    

    CleaningUpTempResources(rdram, ctx);
    goto after_1;
    // nop

    after_1:
    // lw          $ra, 0x1C($sp)
    ctx->r31 = MEM_W(0X1C, ctx->r29);
    // lw          $s2, 0x18($sp)
    ctx->r18 = MEM_W(0X18, ctx->r29);
    // lw          $s1, 0x14($sp)
    ctx->r17 = MEM_W(0X14, ctx->r29);
    // lw          $s0, 0x10($sp)
    ctx->r16 = MEM_W(0X10, ctx->r29);
    // addiu       $sp, $sp, 0x20
    ctx->r29 = ADD32(ctx->r29, 0X20);
    // jr          $ra
    // nop

    return;
    // nop

;}
