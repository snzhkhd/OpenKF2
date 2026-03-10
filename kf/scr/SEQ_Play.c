#include "recomp.h"
#include "disable_warnings.h"
#include "audio/PsyX_SPUAL.h"

void SEQ_Play(uint8_t* rdram, recomp_context* ctx) 
{
  /*  printf("[SEQ_Play] trackID=%d word_8019E6E6=%04X\n",
        (int16_t)ctx->r4, MEM_HU(0, 0x8019E6E6));*/
    //printf("[VAB dump] dword_8016DAA0=%08X dword_8016E5F8=%08X\n",
    //    MEM_W(0, 0x8016DAA0), MEM_W(0, 0x8016E5F8));

    //uint32_t vag_base = MEM_W(0, 0x8016DAA0);
    //if (vag_base) {
    //    printf("[VAG table] base=%08X:\n", vag_base);
    //    for (int i = 0; i < 20; i++) {
    //        uint32_t entry = vag_base + i * 16;
    //        printf("  vag[%d] +12=%04X (real=%08X) +14=%04X (real=%08X)\n",
    //            i,
    //            MEM_HU(12, entry), MEM_HU(12, entry) << 3,
    //            MEM_HU(14, entry), MEM_HU(14, entry) << 3);
    //    }
    //}


    uint64_t hi = 0, lo = 0, result = 0;
    unsigned int rounding_mode = DEFAULT_ROUNDING_MODE;
    int c1cs = 0; 
    // addiu       $sp, $sp, -0x18
    ctx->r29 = ADD32(ctx->r29, -0X18);
    // sw          $ra, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r31;
    // sll         $a0, $a0, 16
    ctx->r4 = S32(ctx->r4) << 16;
    // sra         $a0, $a0, 16
    ctx->r4 = S32(ctx->r4) >> 16;
    // andi        $v0, $a1, 0xFF
    ctx->r2 = ctx->r5 & 0XFF;
    // addu        $a1, $zero, $zero
    ctx->r5 = ADD32(0, 0);
    // sll         $a3, $a2, 16
    ctx->r7 = S32(ctx->r6) << 16;
    // addu        $a2, $v0, $zero
    ctx->r6 = ADD32(ctx->r2, 0);
    // jal         0x8005C32C
    // sra         $a3, $a3, 16
    ctx->r7 = S32(ctx->r7) >> 16;
    sub_8005C32C(rdram, ctx);
    goto after_0;
    // sra         $a3, $a3, 16
    ctx->r7 = S32(ctx->r7) >> 16;
    after_0:
    // lw          $ra, 0x10($sp)
    ctx->r31 = MEM_W(0X10, ctx->r29);
    // nop

    // jr          $ra
    // addiu       $sp, $sp, 0x18
    ctx->r29 = ADD32(ctx->r29, 0X18);


    //uint8_t* spu = PsyX_SPUAL_GetMemory();
    //printf("[SPU RAM 0x23030]:\n");
    //for (int row = 0; row < 8; row++) {
    //    printf("  +%03X: ", row * 16);
    //    for (int j = 0; j < 16; j++)
    //        printf("%02X ", spu[0x23030 + row * 16 + j]);
    //    printf("\n");
    //}
    //printf("[SPU RAM 0x3A400]:\n");
    //for (int row = 0; row < 4; row++) {
    //    printf("  +%03X: ", row * 16);
    //    for (int j = 0; j < 16; j++)
    //        printf("%02X ", spu[0x3A400 + row * 16 + j]);
    //    printf("\n");
    //}

    return;

;}
