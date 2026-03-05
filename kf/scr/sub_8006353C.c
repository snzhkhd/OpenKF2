#include "recomp.h"
#include "disable_warnings.h"
#include "PsyX/PsyX_public.h"
#include "PsyX/PsyX_render.h"
#include "psx/libetc.h"

void KF_ClearOTagR(uint8_t* rdram, recomp_context* ctx) 
{
    uint32_t ot_addr = ctx->r4;
    int n = (int)ctx->r5;
    uint32_t* ot = (uint32_t*)GET_PTR(ot_addr);
    if (ot && n > 0) {
        ot[0] = 0x00FFFFFF;
        for (int i = 1; i < n; i++)
            ot[i] = (ot_addr + (i - 1) * 4) & 0x00FFFFFF;
    }
	//printf("[ClearOTagR] PsyX_BeginScene\n");

    //u_long ot_addr = ctx->r4;
    //int n = (int)ctx->r5;
    //u_long* ot = (u_long*)GET_PTR(ot_addr);
    //ClearOTagR(ot, n);
    //PsyX_BeginScene();
    ctx->r2 = 0;

;}
