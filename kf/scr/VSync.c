#include "recomp.h"
#include "disable_warnings.h"
#include "PsyX/PsyX_public.h"
#include "PsyX/PsyX_render.h"
#include "psx/libetc.h"



void KF_VSync(uint8_t* rdram, recomp_context* ctx) {
    // Не делаем swap здесь — только запоминаем что он нужен
    //printf("[DEBUG] Game called KF_VSync!\n");
    int mode = (int32_t)ctx->r4;
    ctx->r2 = VSync(mode == 0 ? 1 : mode);

    // Тик SEQ секвенсора
    uint32_t saved_r4 = ctx->r4;
    uint32_t saved_ra = ctx->r31;

    KF_SsSeqCalledTbyT(rdram, ctx);   //KF_SpuUpdateTick
    ctx->r4 = saved_r4;
    ctx->r31 = saved_ra;

    g_vsync_pending = true;
//    PsyX_UpdateInput();
    ctx->r2 = 0;
    WRITE_W(0x1F801814, 0x1C000000);
}
